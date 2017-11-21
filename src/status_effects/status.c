#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "status.h"

extern u16 rand_range(u16, u16);
extern void status_graphical_update(u8 bank, enum Effect status);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void do_damage(u8 bank_index, u16 dmg);
extern u16 get_damage(u8 attacker, u8 defender, u16 move);
extern void dprintf(const char * str, ...);

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
			REMOVE_VOLATILE(bank, VOLATILE_CONFUSE_TURN); // don't skip turn
		}
	} else {
		p_bank[bank]->b_data.status = AILMENT_NONE;
		enqueue_message(0, bank, STRING_SNAPPED_OUT, 0);
		status_graphical_update(bank, AILMENT_NONE);
		REMOVE_VOLATILE(bank, VOLATILE_CONFUSE_TURN);
	}
}


void sleep_on_before_move(u8 bank)
{
	if (p_bank[bank]->b_data.status == AILMENT_SLEEP) {
		if (p_bank[bank]->b_data.status_turns) {
			ADD_VOLATILE(bank, VOLATILE_SLEEP_TURN);
		} else {
			p_bank[bank]->b_data.status = AILMENT_NONE;
			enqueue_message(0, bank, STRING_WOKE_UP, 0);
			status_graphical_update(bank, AILMENT_NONE);
			REMOVE_VOLATILE(bank, VOLATILE_SLEEP_TURN);
		}
	}
}

void sleep_on_inflict(u8 bank)
{
	u8 ailment = rand_range(1, 3);
	p_bank[bank]->b_data.status_turns = ailment;
	p_bank[bank]->b_data.status = AILMENT_SLEEP;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_SLEEP);
}

void poison_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_POISON;
    p_bank[bank]->b_data.status = AILMENT_POISON;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_POISON);
}

void toxic_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_TOXIC;
    p_bank[bank]->b_data.status = AILMENT_BAD_POISON;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_BAD_POISON);
}

void burn_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_BURN;
    p_bank[bank]->b_data.status = AILMENT_BURN;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_BURN);

}

void freeze_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_FREEZE;
    p_bank[bank]->b_data.status = AILMENT_FREEZE;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_FREEZE);
}

void paralyze_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_PARALYZE;
    p_bank[bank]->b_data.status = AILMENT_PARALYZE;
    p_bank[bank]->b_data.status_turns = 0;
	pokemon_setattr(p_bank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_PARALYZE);

}

void confusion_on_inflict(u8 bank)
{
    p_bank[bank]->b_data.status = AILMENT_CONFUSION;
	p_bank[bank]->b_data.confusion_turns = rand_range(1, 5);
    enqueue_message(0, bank, STRING_AILMENT_APPLIED, AILMENT_CONFUSION);
}

void effect_cure_on_inflict(u8 bank)
{
	p_bank[bank]->b_data.status = AILMENT_NONE;
	p_bank[bank]->b_data.status_turns = 0;
	p_bank[bank]->b_data.confusion_turns = 0;
	enqueue_message(0, bank, STRING_AILMENT_CURED, 0);
}


void confusion_on_residual(u8 bank)
{
	if (p_bank[bank]->b_data.confusion_turns) {
		p_bank[bank]->b_data.confusion_turns--;
	} else {
		p_bank[bank]->b_data.status_turns = 0;
	}
	REMOVE_VOLATILE(bank, VOLATILE_CONFUSE_TURN);
}

void sleep_on_residual(u8 bank)
{
	if (p_bank[bank]->b_data.status_turns) {
		p_bank[bank]->b_data.status_turns--;
	} else {
		p_bank[bank]->b_data.status_turns = 0;
	}
}

void poison_on_residual(u8 bank)
{
	// do dmg
    u16 dmg = TOTAL_HP(bank) / 16;
    do_damage(bank, MAX(1, dmg));
    enqueue_message(0, bank, STRING_RESIDUAL_STATUS_DMG, AILMENT_POISON);
    p_bank[bank]->b_data.status_turns++;
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

void burn_on_residual(u8 bank)
{
	// do dmg
    u16 dmg = TOTAL_HP(bank) / 16;
    do_damage(bank, MAX(1, dmg));
    enqueue_message(0, bank, STRING_RESIDUAL_STATUS_DMG, AILMENT_BURN);
    p_bank[bank]->b_data.status_turns++;
}

void do_residual_status_effects(u8 order)
{
    bool do_player = (statuses[B_STATUS(PLAYER_SINGLES_BANK)].on_residual) ? true : false;
    bool do_opponent = (statuses[B_STATUS(OPPONENT_SINGLES_BANK)].on_residual) ? true : false;
    if (order) {
        if (do_player) {
            statuses[B_STATUS(PLAYER_SINGLES_BANK)].on_residual(PLAYER_SINGLES_BANK);
        }
        if (do_opponent) {
            statuses[B_STATUS(OPPONENT_SINGLES_BANK)].on_residual(OPPONENT_SINGLES_BANK);
        }
    } else {
        if (do_opponent) {
            statuses[B_STATUS(OPPONENT_SINGLES_BANK)].on_residual(OPPONENT_SINGLES_BANK);
        }
        if (do_player) {
            statuses[B_STATUS(PLAYER_SINGLES_BANK)].on_residual(PLAYER_SINGLES_BANK);
        }
    }
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
        .on_inflict = freeze_on_inflict,
    },
    
    // Ailment paralyze
    {
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

