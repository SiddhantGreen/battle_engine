#include <pokeagb/pokeagb.h>
#include "../../../battle_data/pkmn_bank.h"
#include "../../../battle_data/pkmn_bank_stats.h"
#include "../../../battle_data/battle_state.h"
#include "../../../moves/moves.h"
#include "../../../battle_text/battle_pick_message.h"
#include "../../move_chain_states.h"

extern u16 rand_range(u16 min, u16 max);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

bool try_hit(u8 attacker)
{
    // if moves never misses, exit early
    u8 move_accuracy = B_MOVE_ACCURACY(attacker);
    if (move_accuracy > 100)
        return true;
    
    // if target is in semi invulnerability do checks
    u8 defender = TARGET_OF(attacker);
    if (HAS_VOLATILE(defender, VOLATILE_SEMI_INVULNERABLE)) {
        if (moves[CURRENT_MOVE(attacker)].on_inv_tryhit_move) {
            if (!(moves[CURRENT_MOVE(attacker)].on_inv_tryhit_move(attacker, defender, CURRENT_MOVE(attacker)))) {
                // if user's move doesn't hit invulnerable target
                enqueue_message(0, attacker, STRING_INVULNERABLE, 0);
                return false;
            }
        } else {
            // if user's move doesn't hit invulnerable target
            enqueue_message(0, attacker, STRING_INVULNERABLE, 0);
            return false;
        }
    }

    // standard accuracy formula check
    u16 target_evasion = B_EVASION_STAT(defender);
    u16 user_accuracy = B_ACCURACY_STAT(attacker);
    
    u16 result = (user_accuracy / target_evasion) * move_accuracy;
    if (rand_range(0, 100) <= result)
        return true;
    if (target_evasion > 100) {
        enqueue_message(0, TARGET_OF(attacker), STRING_ATTACK_AVOIDED, 0);
    } else {
        enqueue_message(0, attacker, STRING_ATTACK_MISSED, 0);
    }
    return false;
}

bool is_immune(u8 attacker, u8 defender, u16 move)
{
    return false;
}

