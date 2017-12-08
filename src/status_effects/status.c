#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "status.h"
#include "../battle_loop/move_chain_states.h"

extern u16 rand_range(u16, u16);
extern void status_graphical_update(u8 bank, enum Effect status);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void do_damage(u8 bank_index, u16 dmg);
extern u16 get_damage(u8 attacker, u8 defender, u16 move);
extern void dprintf(const char * str, ...);
extern void hpbar_apply_dmg(u8 task_id);
extern bool peek_message(void);
extern void run_move(void);

/* Sleep Related */
void sleep_on_before_move(u8 bank)
{
	if (p_bank[bank]->b_data.status == AILMENT_SLEEP) {
		if (p_bank[bank]->b_data.status_turns) {
			ADD_VOLATILE(bank, VOLATILE_SLEEP_TURN);
		} else {
			p_bank[bank]->b_data.status = AILMENT_NONE;
			enqueue_message(0, bank, STRING_WOKE_UP, 0);
			status_graphical_update(bank, AILMENT_NONE);
			CLEAR_VOLATILE(bank, VOLATILE_SLEEP_TURN);
		}
	}
}

void sleep_on_inflict(u8 bank)
{
	if ((BANK_ABILITY(bank) != ABILITY_COMATOSE) || (BANK_ABILITY(bank) != ABILITY_INSOMNIA) ||
	(BANK_ABILITY(bank) != ABILITY_VITAL_SPIRIT) || (BANK_ABILITY(bank) != ABILITY_SWEET_VEIL)) {
		u8 ailment = rand_range(1, 4);
		p_bank[bank]->b_data.status_turns = ailment;
		p_bank[bank]->b_data.status = AILMENT_SLEEP;
		pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
		enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_SLEEP);
	}
}

void sleep_on_residual(u8 bank)
{
	if (p_bank[bank]->b_data.status_turns) {
		p_bank[bank]->b_data.status_turns--;
	} else {
		p_bank[bank]->b_data.status_turns = 0;
	}
}


/* Poison Related */
void poison_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_POISON;
    p_bank[bank]->b_data.status = AILMENT_POISON;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_POISON);
}

void poison_on_residual(u8 bank)
{
	// do dmg
    u16 dmg = TOTAL_HP(bank) / 8;
    do_damage(bank, MAX(1, dmg));
    enqueue_message(0, bank, STRING_RESIDUAL_STATUS_DMG, AILMENT_POISON);
    p_bank[bank]->b_data.status_turns++;
}


/* Burn Related */
void burn_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_BURN;
    p_bank[bank]->b_data.status = AILMENT_BURN;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_BURN);

}

void burn_on_residual(u8 bank)
{
	// do dmg
    u16 dmg = TOTAL_HP(bank) / 8;
    do_damage(bank, MAX(1, dmg));
    enqueue_message(0, bank, STRING_RESIDUAL_STATUS_DMG, AILMENT_BURN);
    p_bank[bank]->b_data.status_turns++;
}


/* Freeze Related */
void freeze_on_before_move(u8 bank)
{
    // 20% change to break out
    if ((rand_range(0, 100) < 20) || (IS_DEFROST(CURRENT_MOVE(bank))))  {
        p_bank[bank]->b_data.status = AILMENT_NONE;
		enqueue_message(0, bank, STRING_FREEZE_THAWED, 0);
		status_graphical_update(bank, AILMENT_NONE);
    } else {
        ADD_VOLATILE(bank, VOLATILE_ATK_SKIP_TURN);
        enqueue_message(0, bank, STRING_FROZEN_SOLID, 0);
    }
}

void freeze_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_FREEZE;
    p_bank[bank]->b_data.status = AILMENT_FREEZE;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_FREEZE);
}


/* Paralyze Related */
void paralyze_on_before_move(u8 bank)
{
    if (rand_range(0, 100) < 25) {
        ADD_VOLATILE(bank, VOLATILE_ATK_SKIP_TURN);
        enqueue_message(0, bank, STRING_FULL_PARA, 0);
    }
}

u16 paralyze_on_mod_stat(u8 bank, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
	if (B_STATUS(bank) != AILMENT_NONE) {
		if (stat_id != SPEED_MOD) return (u32)acb->data_ptr;
	    if (!(BANK_ABILITY(bank) == ABILITY_QUICK_FEET))
	        return NUM_MOD((u32)acb->data_ptr, 50);
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
	add_callback(CB_ON_STAT_MOD, 0, 0xFF, NULL, (u32)paralyze_on_mod_stat);
}


/* Toxic Related */
void toxic_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_TOXIC;
    p_bank[bank]->b_data.status = AILMENT_BAD_POISON;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_BAD_POISON);
}

void toxic_on_residual(u8 bank)
{
	// do dmg
    if (p_bank[bank]->b_data.status_turns < 15) {
        p_bank[bank]->b_data.status_turns++;
    }
    u16 dmg = ((MAX(1, (TOTAL_HP(bank) / 16))) * p_bank[bank]->b_data.status_turns);
    do_damage(bank, dmg);
    enqueue_message(0, bank, STRING_RESIDUAL_STATUS_DMG, AILMENT_POISON);
}


/* Confusion Related */
void confusion_on_before_move(u8 bank)
{
	ADD_VOLATILE(bank, VOLATILE_CONFUSE_TURN);
	if (p_bank[bank]->b_data.confusion_turns) {
		enqueue_message(0, bank, STRING_IS_CONFUSED, 0);
		if (rand_range(0, 100) <= 33) {
			// hurt itself in confusion
			enqueue_message(0, bank, STRING_CONFUSION_HURT, 0);
			B_MOVE_TYPE(bank, 0) = MTYPE_NONE;
			B_MOVE_POWER(bank) = 40;
			B_MOVE_ACCURACY(bank) = 101;
			B_MOVE_IGNORING_ABILITIES(bank) = true;
			B_MOVE_CATEGORY(bank) = MOVE_PHYSICAL;
			B_MOVE_CAN_CRIT(bank) = false;
			B_MOVE_WILL_CRIT_SET(bank, 0);
			battle_master->b_moves[B_MOVE_BANK(bank)].hit_times = 0;
			u16 dmg = get_damage(bank, bank, CURRENT_MOVE(bank));
			do_damage(bank, MAX(1, dmg));
		} else {
			CLEAR_VOLATILE(bank, VOLATILE_CONFUSE_TURN); // don't skip turn
		}
	} else {
		p_bank[bank]->b_data.pseudo_ailment = AILMENT_NONE;
		enqueue_message(0, bank, STRING_SNAPPED_OUT, 0);
		CLEAR_VOLATILE(bank, VOLATILE_CONFUSE_TURN);
	}
}

void confusion_on_inflict(u8 bank)
{
	p_bank[bank]->b_data.pseudo_ailment = AILMENT_CONFUSION;
	p_bank[bank]->b_data.confusion_turns = rand_range(1, 5);
	enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_CONFUSION);
}

void confusion_on_residual(u8 bank)
{
	if (p_bank[bank]->b_data.confusion_turns) {
		p_bank[bank]->b_data.confusion_turns--;
	}
	CLEAR_VOLATILE(bank, VOLATILE_CONFUSE_TURN);
}


/* Misc Ailment related effects */
void effect_cure_on_inflict(u8 bank)
{
	p_bank[bank]->b_data.status = AILMENT_NONE;
	p_bank[bank]->b_data.pseudo_ailment = AILMENT_NONE;
	p_bank[bank]->b_data.status_turns = 0;
	p_bank[bank]->b_data.confusion_turns = 0;
	enqueue_message(0, bank, STRING_AILMENT_CURED, 0);
}


void c1_residual_status_effects()
{
	while (peek_message())
		return;
	if (task_is_running(hpbar_apply_dmg))
		return;
	u16 player_speed = B_SPEED_STAT(PLAYER_SINGLES_BANK);
	u16 opponent_speed = B_SPEED_STAT(OPPONENT_SINGLES_BANK);
	u16 bank_index = (player_speed > opponent_speed) ? PLAYER_SINGLES_BANK : OPPONENT_SINGLES_BANK;
	switch (super.multi_purpose_state_tracker) {
	case 0:
		if (statuses[B_STATUS(bank_index)].on_residual)
			statuses[B_STATUS(bank_index)].on_residual(bank_index);
		if (statuses[B_PSTATUS(bank_index)].on_residual)
			statuses[B_PSTATUS(bank_index)].on_residual(bank_index);
		super.multi_purpose_state_tracker++;
		break;
	case 1:
		bank_index = (player_speed < opponent_speed) ? PLAYER_SINGLES_BANK : OPPONENT_SINGLES_BANK;
		if (statuses[B_STATUS(bank_index)].on_residual)
			statuses[B_STATUS(bank_index)].on_residual(bank_index);
		if (statuses[B_PSTATUS(bank_index)].on_residual)
			statuses[B_PSTATUS(bank_index)].on_residual(bank_index);
		super.multi_purpose_state_tracker++;
		break;
	default:
		set_callback1(run_move);
		super.multi_purpose_state_tracker = S_WAIT_HPUPDATE_RUN_MOVE;
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
		.on_before_move = sleep_on_before_move,
        .on_inflict = sleep_on_inflict,
        .on_residual = sleep_on_residual,
    },

    // Ailment poison
    {
        .on_inflict = poison_on_inflict,
        .on_residual = poison_on_residual,
    },

    // Ailment burn
    {
        .on_inflict = burn_on_inflict,
        .on_residual = burn_on_residual,
    },

    // Ailment freeze
    {
        .on_before_move = freeze_on_before_move,
        .on_inflict = freeze_on_inflict,
    },

    // Ailment paralyze
    {
        .on_before_move = paralyze_on_before_move,
        .on_inflict = paralyze_on_inflict,
    },

    // Ailment toxic
    {
        .on_inflict = toxic_on_inflict,
        .on_residual = toxic_on_residual,
    },

    // Ailment confusion
    {
		.on_before_move = confusion_on_before_move,
        .on_inflict = confusion_on_inflict,
        .on_residual = confusion_on_residual,
    },

    // Ailment cure
    {
        .on_inflict = effect_cure_on_inflict,
    },
};
