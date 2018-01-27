#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "status.h"

extern u16 rand_range(u16, u16);
extern void status_graphical_update(u8 bank, enum Effect status);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void do_damage(u8 bank_index, u16 dmg);
extern u16 get_damage(u8 attacker, u8 defender, u16 move);
extern void dprintf(const char * str, ...);
extern void hpbar_apply_dmg(u8 task_id);
extern void ailment_decode(u8 bank, u8 ailment);

/* Sleep Related */
u8 sleep_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	if (p_bank[user]->b_data.status == AILMENT_SLEEP) {
		if (p_bank[user]->b_data.status_turns) {
			ADD_VOLATILE(user, VOLATILE_SLEEP_TURN);
		} else {
			p_bank[user]->b_data.status = AILMENT_NONE;
			enqueue_message(0, user, STRING_WOKE_UP, 0);
			status_graphical_update(user, AILMENT_NONE);
			CLEAR_VOLATILE(user, VOLATILE_SLEEP_TURN);
		}
	}
	return true;
}

u8 sleep_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	if (p_bank[user]->b_data.status_turns) {
		p_bank[user]->b_data.status_turns--;
	} else {
		p_bank[user]->b_data.status_turns = 0;
		acb->in_use = false;
	}
	return true;
}

void sleep_on_inflict(u8 bank)
{
	if ((BANK_ABILITY(bank) != ABILITY_COMATOSE) || (BANK_ABILITY(bank) != ABILITY_INSOMNIA) ||
	(BANK_ABILITY(bank) != ABILITY_VITALSPIRIT) || (BANK_ABILITY(bank) != ABILITY_SWEETVEIL)) {
		u8 ailment = rand_range(1, 4);
		p_bank[bank]->b_data.status_turns = ailment;
		p_bank[bank]->b_data.status = AILMENT_SLEEP;
		pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
		enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_SLEEP);
		add_callback(CB_ON_RESIDUAL, 3, ailment, bank, (u32)sleep_on_residual);
		add_callback(CB_ON_BEFORE_MOVE, 3, ailment, bank, (u32)sleep_on_before_move);
	}
}


/* Poison Related */
u8 poison_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	// do dmg
    u16 dmg = TOTAL_HP(user) / 8;
    do_damage(user, MAX(1, dmg));
    enqueue_message(0, user, STRING_RESIDUAL_STATUS_DMG, AILMENT_POISON);
    p_bank[user]->b_data.status_turns++;
	return true;
}

void poison_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_POISON;
	B_STATUS(bank) = AILMENT_POISON;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_POISON);
	add_callback(CB_ON_RESIDUAL, 0, 0xFF, bank, (u32)poison_on_residual);
}


/* Burn Related */
u8 burn_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	// do dmg
	// heatproof:
	u16 dmg;
	if (BANK_ABILITY(user) == ABILITY_HEATPROOF)
		dmg = MAX(1, TOTAL_HP(user) / 16);
	else
		dmg = MAX(1, TOTAL_HP(user) >> 3);
    do_damage(user, dmg);
    enqueue_message(0, user, STRING_RESIDUAL_STATUS_DMG, AILMENT_BURN);
    p_bank[user]->b_data.status_turns++;
	return true;
}

void burn_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_BURN;
    p_bank[bank]->b_data.status = AILMENT_BURN;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_BURN);
	add_callback(CB_ON_RESIDUAL, 0, 0xFF, bank, (u32)burn_on_residual);

}



/* Freeze Related */
u8 freeze_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
    // 20% change to break out
    if ((rand_range(0, 100) < 20) || (IS_DEFROST(CURRENT_MOVE(user))))  {
        p_bank[user]->b_data.status = AILMENT_NONE;
		enqueue_message(0, user, STRING_FREEZE_THAWED, 0);
		status_graphical_update(user, AILMENT_NONE);
    } else {
        ADD_VOLATILE(user, VOLATILE_ATK_SKIP_TURN);
        enqueue_message(0, user, STRING_FROZEN_SOLID, 0);
    }
	return true;
}

void freeze_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_FREEZE;
    p_bank[bank]->b_data.status = AILMENT_FREEZE;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_FREEZE);
	add_callback(CB_ON_BEFORE_MOVE, 3, CB_PERMA, bank, (u32)freeze_on_before_move);
}


/* Paralyze Related */
u8 paralyze_on_before_move(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
	if (user != src) return true;
    if (rand_range(0, 100) < 25) {
        ADD_VOLATILE(user, VOLATILE_ATK_SKIP_TURN);
        enqueue_message(0, user, STRING_FULL_PARA, 0);
    }
	return true;
}

u16 paralyze_on_mod_stat(u8 bank, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
	if (B_STATUS(bank) != AILMENT_NONE) {
		dprintf("old speed = %d\tnew speed = %d\n",(u32)acb->data_ptr,  PERCENT((u32)acb->data_ptr, 50));
		if (stat_id != SPEED_MOD) return (u32)acb->data_ptr;
	    if (!(BANK_ABILITY(bank) == ABILITY_QUICK_FEET))
	        return PERCENT((u32)acb->data_ptr, 50);
	} else {
		acb->in_use = false;
	}
	return (u32)acb->data_ptr;
}

void paralyze_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_PARALYZE;
    p_bank[bank]->b_data.status = AILMENT_PARALYZE;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_PARALYZE);
	add_callback(CB_ON_STAT_MOD, 0, CB_PERMA, NULL, (u32)paralyze_on_mod_stat);
	add_callback(CB_ON_BEFORE_MOVE, 3, CB_PERMA, bank, (u32)paralyze_on_before_move);
}


/* Toxic Related */
u8 toxic_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	// do dmg
    if (p_bank[user]->b_data.status_turns < 15) {
        p_bank[user]->b_data.status_turns++;
    }
    u16 dmg = ((MAX(1, (TOTAL_HP(user) / 16))) * p_bank[user]->b_data.status_turns);
    do_damage(user, dmg);
    enqueue_message(0, user, STRING_RESIDUAL_STATUS_DMG, AILMENT_POISON);
	return true;
}

void toxic_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_TOXIC;
	B_STATUS(bank) = AILMENT_BAD_POISON;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_BAD_POISON);
	add_callback(CB_ON_RESIDUAL, 0, CB_PERMA, bank, (u32)toxic_on_residual);
}

/* Infactuation related */
// 50% chance to fail to hit the target infactuated with
u8 infactuated_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	if (rand_range(0, 100) < 50) {
		return true;
	} else {
		enqueue_message(0, user, STRING_INFATUATED, 0);
		return 3;
	}
}

void infactuate_on_inflict(u8 bank)
{
	if (HAS_VOLATILE(bank, VOLATILE_INFACTUATION))
		return;
	ADD_VOLATILE(bank, VOLATILE_INFACTUATION);
	enqueue_message(0, bank, STRING_ATTRACT, AILMENT_INFACTUATE);
	add_callback(CB_ON_BEFORE_MOVE, 3, CB_PERMA, bank, (u32)infactuated_before_move);
}


/* Confusion Related */
u8 confusion_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	ADD_VOLATILE(user, VOLATILE_CONFUSE_TURN);
	if (p_bank[user]->b_data.confusion_turns) {
		enqueue_message(0, user, STRING_IS_CONFUSED, 0);
		if (rand_range(0, 100) <= 33) {
			// hurt itself in confusion
			enqueue_message(0, user, STRING_CONFUSION_HURT, 0);
			B_MOVE_TYPE(user, 0) = MTYPE_NONE;
			B_MOVE_POWER(user) = 40;
			B_MOVE_ACCURACY(user) = 101;
			B_MOVE_IGNORING_ABILITIES(user) = true;
			B_MOVE_CATEGORY(user) = MOVE_PHYSICAL;
			B_MOVE_CAN_CRIT(user) = false;
			B_MOVE_WILL_CRIT(user) = false;
			battle_master->b_moves[(user)].hit_times = 0;
			u16 dmg = get_damage(user, user, CURRENT_MOVE(user));
			do_damage(user, MAX(1, dmg));
		} else {
			CLEAR_VOLATILE(user, VOLATILE_CONFUSE_TURN); // don't skip turn
		}
	} else {
		p_bank[user]->b_data.pseudo_ailment = AILMENT_NONE;
		enqueue_message(0, user, STRING_SNAPPED_OUT, 0);
		CLEAR_VOLATILE(user, VOLATILE_CONFUSE_TURN);
	}
	return true;
}

u8 confusion_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	if (p_bank[user]->b_data.confusion_turns) {
		p_bank[user]->b_data.confusion_turns--;
	}
	CLEAR_VOLATILE(user, VOLATILE_CONFUSE_TURN);
	return true;
}

void confusion_on_inflict(u8 bank)
{
	p_bank[bank]->b_data.pseudo_ailment = AILMENT_CONFUSION;
	p_bank[bank]->b_data.confusion_turns = rand_range(1, 5);
	enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_CONFUSION);
	add_callback(CB_ON_RESIDUAL, 0, p_bank[bank]->b_data.confusion_turns, bank, (u32)confusion_on_residual);
	add_callback(CB_ON_BEFORE_MOVE, 3, p_bank[bank]->b_data.confusion_turns, bank, (u32)confusion_on_before_move);
}


/* Misc Ailment related effects */
void silent_cure_major(u8 bank) {
	p_bank[bank]->b_data.status = AILMENT_NONE;
	p_bank[bank]->b_data.status_turns = 0;
	delete_callback_src((u32)toxic_on_residual, bank);
	delete_callback_src((u32)paralyze_on_before_move, bank);
	delete_callback_src((u32)paralyze_on_mod_stat, bank);
	delete_callback_src((u32)freeze_on_before_move, bank);
	delete_callback_src((u32)burn_on_residual, bank);
	delete_callback_src((u32)poison_on_residual, bank);
	delete_callback_src((u32)sleep_on_before_move, bank);
	delete_callback_src((u32)sleep_on_residual, bank);
	status_graphical_update(bank, AILMENT_NONE);
}

void clear_ailments_silent(u8 bank) {
	p_bank[bank]->b_data.status = AILMENT_NONE;
	p_bank[bank]->b_data.pseudo_ailment = AILMENT_NONE;
	p_bank[bank]->b_data.status_turns = 0;
	p_bank[bank]->b_data.confusion_turns = 0;
	delete_callback_src((u32)confusion_on_residual, bank);
	delete_callback_src((u32)confusion_on_before_move, bank);
	delete_callback_src((u32)toxic_on_residual, bank);
	delete_callback_src((u32)paralyze_on_before_move, bank);
	delete_callback_src((u32)paralyze_on_mod_stat, bank);
	delete_callback_src((u32)freeze_on_before_move, bank);
	delete_callback_src((u32)burn_on_residual, bank);
	delete_callback_src((u32)poison_on_residual, bank);
	delete_callback_src((u32)sleep_on_before_move, bank);
	delete_callback_src((u32)sleep_on_residual, bank);
    status_graphical_update(bank, AILMENT_NONE);
}

void effect_cure_on_inflict(u8 bank)
{
	clear_ailments_silent(bank);
	enqueue_message(0, bank, STRING_AILMENT_CURED, 0);
}


void battle_start_ailment_callback_init(u8 bank)
{
	ailment_decode(bank, pokemon_getattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, NULL));
	switch (p_bank[bank]->b_data.status) {
		case AILMENT_BURN:
			add_callback(CB_ON_RESIDUAL, 0, CB_PERMA, bank, (u32)burn_on_residual);
			break;
		case AILMENT_SLEEP:
			add_callback(CB_ON_RESIDUAL, 3, 3, bank, (u32)sleep_on_residual);
			add_callback(CB_ON_BEFORE_MOVE, 3, 3, bank, (u32)sleep_on_before_move);
			break;
		case AILMENT_POISON:
			add_callback(CB_ON_RESIDUAL, 0, CB_PERMA, bank, (u32)poison_on_residual);
			break;
		case AILMENT_BAD_POISON:
			add_callback(CB_ON_RESIDUAL, 0, CB_PERMA, bank, (u32)toxic_on_residual);
			break;
		case AILMENT_FREEZE:
			add_callback(CB_ON_BEFORE_MOVE, 3, CB_PERMA, bank, (u32)freeze_on_before_move);
			break;
		case AILMENT_PARALYZE:
			add_callback(CB_ON_STAT_MOD, 0, CB_PERMA, NULL, (u32)paralyze_on_mod_stat);
			add_callback(CB_ON_BEFORE_MOVE, 3, CB_PERMA, bank, (u32)paralyze_on_before_move);
			break;
		default:
			return;
	};
}



struct status_ailments statuses[] =
{
    // Ailment none
    {
    },
    // Ailment sleep
    {
        .on_inflict = sleep_on_inflict,
    },

    // Ailment poison
    {
        .on_inflict = poison_on_inflict,
    },

    // Ailment burn
    {
        .on_inflict = burn_on_inflict,
    },

    // Ailment freeze
    {
        .on_inflict = freeze_on_inflict,
    },

    // Ailment paralyze
    {
        .on_inflict = paralyze_on_inflict,
    },

    // Ailment toxic
    {
        .on_inflict = toxic_on_inflict,
    },

    // Ailment confusion
    {
        .on_inflict = confusion_on_inflict,
    },

    // Ailment cure
    {
        .on_inflict = effect_cure_on_inflict,
    },

	// Ailment infactuation
	{
		.on_inflict = infactuate_on_inflict,
	}
};
