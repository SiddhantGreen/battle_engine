#include <pokeagb/pokeagb.h>
#include "../../../battle_data/pkmn_bank.h"
#include "../../../battle_data/pkmn_bank_stats.h"
#include "../../../battle_data/battle_state.h"
#include "../../../moves/moves.h"
#include "../../move_chain_states.h"
#include "../../../abilities/battle_abilities.h"
#include "../../../status_effects/status.h"

extern u16 rand_range(u16, u16);
extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

void stat_boost(u8 bank, u8 stat_id, s8 amount)
{
    if (!amount)
        return;
    if (ABILITIES_MAX > BANK_ABILITY(bank)) {
        if (abilities_table[BANK_ABILITY(bank)]->on_boost) {
            if (abilities_table[BANK_ABILITY(bank)]->on_boost(bank, amount, stat_id))
                return;
        }
    }

    s8* stat_stored;
    switch (stat_id + 1) {
        case STAT_ATTACK:
            {
            stat_stored = &(p_bank[bank]->b_data.attack);
            break;
            }
        case STAT_DEFENSE:
            {
            stat_stored = &(p_bank[bank]->b_data.defense);
            break;
            }
        case STAT_SPEED:
            {
            stat_stored = &(p_bank[bank]->b_data.speed);
            break;
            }
        case STAT_SPECIAL_ATTACK:
            {
            stat_stored = &(p_bank[bank]->b_data.sp_atk);
            break;
            }
        case STAT_SPECIAL_DEFENSE:
            {
            stat_stored = &(p_bank[bank]->b_data.sp_def);
            break;
            }
        case STAT_EVASION: // evasion
            {
            stat_stored = &(p_bank[bank]->b_data.evasion);
            break;
            }
        case STAT_ACCURACY: // accuracy
            {
            stat_stored = &(p_bank[bank]->b_data.accuracy);
            break;
            }
        case STAT_CRIT: // crit
            {
            stat_stored = &(p_bank[bank]->b_data.crit_mod);
            break;
            }
        default:
            return;
    };

    s8 stat_total = *stat_stored + amount;
    stat_total = MIN(6, stat_total);
    stat_total = MAX(-6, stat_total);
    switch ((ABS(stat_total - (*stat_stored)))) {
        case 0:
           // stat didn't change - string can't go up/down anymore
            if (amount > 0) {
                enqueue_message(0, bank, STRING_STAT_MOD_CANT_GO_HIGHER, stat_id + REQUEST_ATK);
            } else {
                enqueue_message(0, bank, STRING_STAT_MOD_CANT_GO_LOWER, stat_id + REQUEST_ATK);
            }
            break;
        case 1:
            // stat changed by 1 stage
            *stat_stored += (amount > 0) ? 1 : -1;
            if (amount > 0) {
                enqueue_message(0, bank, STRING_STAT_MOD_RISE, stat_id + REQUEST_ATK);
            } else {
                enqueue_message(0, bank, STRING_STAT_MOD_DROP, stat_id + REQUEST_ATK);
            }
            break;
        case 2:
            // stat changed by 2 stages
            *stat_stored += (amount > 0) ? 2 : -2;
            if (amount > 0) {
                enqueue_message(0, bank, STRING_STAT_MOD_HARSH_RISE, stat_id + REQUEST_ATK);
            } else {
                enqueue_message(0, bank, STRING_STAT_MOD_HARSH_DROP, stat_id + REQUEST_ATK);
            }
            break;
        case 3:
            // stat changed by 3 stages
            *stat_stored += (amount > 0) ? 3 : -3;
            if (amount > 0) {
                enqueue_message(0, bank, STRING_STAT_MOD_ROSE_DRASTICALLY, stat_id + REQUEST_ATK);
            } else {
                enqueue_message(0, bank, STRING_STAT_MOD_SEVERELY_FELL, stat_id + REQUEST_ATK);
            }
            break;
    };
}

void move_procs_perform(u8 bank_index, u16 move)
{
	if (moves[move].procs) {

		/* first step is to apply user boosts */
		for (u8 i = 0; i < 8; i++) {
			if (B_USER_STAT_MOD_CHANCE(bank_index, i) >= rand_range(0, 100)) {
				stat_boost(bank_index, i, B_USER_STAT_MOD_AMOUNT(bank_index, i));
				B_USER_STAT_MOD_CHANCE(bank_index, i) = 0;
                return;
			}
		}

		/* second step is to apply target boosts */
		for (u8 i = 0; i < 8; i++) {
			if (B_TARGET_STAT_MOD_CHANCE(bank_index, i) >= rand_range(0, 100)) {
				stat_boost(TARGET_OF(bank_index), i, B_TARGET_STAT_MOD_AMOUNT(bank_index, i));
				B_TARGET_STAT_MOD_CHANCE(bank_index, i) = 0;
                return;
			}
		}
        super.multi_purpose_state_tracker = S_SECONDARY_ROLL_AILMENTS;
	}
	super.multi_purpose_state_tracker = S_SECONDARY_ROLL_AILMENTS;
}


extern void status_graphical_update(u8 bank, enum Effect status);
extern bool b_pkmn_has_type(u8 bank, enum PokemonType type);
void set_status(u8 bank, enum Effect status)
{
    bool status_applied = false;
    // lowest priority for override are types and current status
    switch (status) {
        case EFFECT_NONE:
            // no status to set
            return;
            break;
        case EFFECT_PARALYZE:
            // electric types are immune. Already status'd is immune
            if ((b_pkmn_has_type(bank, TYPE_ELECTRIC)) || (p_bank[bank]->b_data.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
            break;
        case EFFECT_BURN:
            // fire types are immune.  Already status'd is immune
            if ((b_pkmn_has_type(bank, TYPE_FIRE)) || (p_bank[bank]->b_data.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
            break;
        case EFFECT_POISON:
        case EFFECT_BAD_POISON:
            // poison and steel types are immune. Already status'd is immune
            if ((b_pkmn_has_type(bank, TYPE_POISON)) || (b_pkmn_has_type(bank, TYPE_STEEL)) ||
                (p_bank[bank]->b_data.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
			break;
        case EFFECT_SLEEP:
            // sleep isn't affected by type
            if ((p_bank[bank]->b_data.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
            break;
        case EFFECT_FREEZE:
            // fire types cannot be frozen
            if ((b_pkmn_has_type(bank, TYPE_FIRE)) || (p_bank[bank]->b_data.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
			break;
        case EFFECT_CONFUSION:
            // Confusion isn't affected by type
            if (p_bank[bank]->b_data.pseudo_ailment != AILMENT_CONFUSION)
                status_applied = true;
			break;
        case EFFECT_CURE:
            // cure status
			status_applied = true;
            break;
        default:
            break;
    };

    if (status_applied) {
        if (statuses[status].on_inflict) {
            statuses[status].on_inflict(bank);
            status_graphical_update(bank, status);
        }
    } else {
        enqueue_message(0, bank, STRING_AILMENT_IMMUNE, status);
    }
}

u8 ailment_encode(u8 bank)
{
    switch(p_bank[bank]->b_data.status)
    {
        case AILMENT_SLEEP:
            return p_bank[bank]->b_data.status_turns;
        case AILMENT_POISON:
            return 1<<3;
        case AILMENT_BURN:
            return 1<<4;
        case AILMENT_FREEZE:
            return 1<<5;
        case AILMENT_PARALYZE:
            return 1<<6;
        case AILMENT_BAD_POISON:
            return 1<<7;
        default:
            return 0;
    }
}

void ailment_decode(u8 bank, u8 ailment)
{
    if ((ailment & 7) > 0) {
        p_bank[bank]->b_data.status = AILMENT_SLEEP;
        p_bank[bank]->b_data.status_turns = ailment & 7;
    } else if (ailment & (1<<3))
        p_bank[bank]->b_data.status = AILMENT_POISON;
    else if (ailment & (1<<4))
        p_bank[bank]->b_data.status = AILMENT_BURN;
    else if (ailment & (1<<5))
        p_bank[bank]->b_data.status = AILMENT_FREEZE;
    else if (ailment & (1<<6))
        p_bank[bank]->b_data.status = AILMENT_PARALYZE;
    else if (ailment & (1<<7))
        p_bank[bank]->b_data.status = AILMENT_BAD_POISON;
}


void status_procs_perform(u8 bank_index)
{
	if (B_AILMENT_PROCS_CHANCE_USER(bank_index) >= rand_range(1, 100)) {
		// apply status user
		B_AILMENT_PROCS_CHANCE_USER(bank_index) = 0;
		set_status(bank_index, B_AILMENT_PROCS_USER(bank_index));
		return;
	}

	if (B_AILMENT_PROCS_CHANCE_TARGET(bank_index) >= rand_range(1, 100)) {
		// apply status target
		B_AILMENT_PROCS_CHANCE_TARGET(bank_index) = 0;
		set_status(TARGET_OF(bank_index), B_AILMENT_PROCS_TARGET(bank_index));
		return;
	}
	super.multi_purpose_state_tracker = S_AFTER_MOVE_SECONDARY;
}
