#include <pokeagb/pokeagb.h>
#include "../../../battle_data/pkmn_bank.h"
#include "../../../battle_data/pkmn_bank_stats.h"
#include "../../../battle_data/battle_state.h"
#include "../../../moves/moves.h"
#include "../../move_chain_states.h"
#include "../../../abilities/battle_abilities.h"

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
	
    switch (stat_id + 1) {
        case STAT_ATTACK:
            {
            p_bank[bank]->b_data.attack += amount;
            break;
            }
        case STAT_DEFENSE:
            {
            p_bank[bank]->b_data.defense += amount;
            break;
            }
        case STAT_SPEED:
            {
            p_bank[bank]->b_data.speed += amount;
            break;
            }
        case STAT_SPECIAL_ATTACK:
            {
            p_bank[bank]->b_data.sp_atk += amount;
            break;
            }
        case STAT_SPECIAL_DEFENSE:
            {
            p_bank[bank]->b_data.sp_def += amount;
            break;
            }
        case STAT_EVASION: // evasion
            {
            p_bank[bank]->b_data.evasion += amount;
            break;
            }
        case STAT_ACCURACY: // accuracy
            {
            p_bank[bank]->b_data.accuracy += amount;
            break;
            }
        case STAT_CRIT: // crit
            {
            p_bank[bank]->b_data.crit_mod += amount;
            break;
            }
        default:
            return;
    };

    amount += 6;
    switch (amount) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            enqueue_message(0, bank, STRING_STAT_MOD_HARSH_DROP, stat_id + REQUEST_ATK);
            break;
        case 5:
            enqueue_message(0, bank, STRING_STAT_MOD_DROP, stat_id + REQUEST_ATK);
            break;
        case 6:
            break;
        case 7:
            enqueue_message(0, bank, STRING_STAT_MOD_RISE, stat_id + REQUEST_ATK);
            break;
        default:
            enqueue_message(0, bank, STRING_STAT_MOD_HARSH_RISE, stat_id + REQUEST_ATK);
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
				dprintf("mod user stat %d by %d stages\n", i, B_USER_STAT_MOD_AMOUNT(bank_index, i));
			}	
		}
		
		/* second step is to apply target boosts */
		for (u8 i = 0; i < 8; i++) {
			if (B_TARGET_STAT_MOD_CHANCE(bank_index, i) >= rand_range(0, 100)) {
				stat_boost(TARGET_OF(bank_index), i, B_TARGET_STAT_MOD_AMOUNT(bank_index, i));
				B_TARGET_STAT_MOD_CHANCE(bank_index, i) = 0;
				dprintf("mod target stat %d by %d stages\n", i, B_TARGET_STAT_MOD_AMOUNT(bank_index, i));
			}	
		}
	}
	super.multi_purpose_state_tracker = S_AFTER_MOVE_SECONDARY;
}


