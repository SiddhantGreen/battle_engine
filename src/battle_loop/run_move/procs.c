#include <pokeagb/pokeagb.h>
#include "../../battle_data/pkmn_bank.h"
#include "../../battle_data/pkmn_bank_stats.h"
#include "../../battle_data/battle_state.h"
#include "../../moves/moves.h"
#include "../../battle_text/battle_pick_message.h"
#include "../move_chain_states.h"

extern void run_decision(void);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool peek_message(void);
extern void move_hit(void);
extern bool target_exists(u8 bank);
extern void stat_boost(u8 bank, u8 stat_id, s8 amount);
extern u16 rand_range(u16 min, u16 max);

/* TODO Unsloppify this */
void boost_procs(u8 attacker, u8 defender, u16 move) {

    u8 i;
    struct move_used move_data = battle_master->b_moves[B_MOVE_BANK(attacker)];
     for (i = 0; i < 6; i ++) {
        if (rand_range(0, 100) < move_data.chance_self) {
            stat_boost(attacker, i, move_data.stat_self[i]);
        }
    }

    for (i = 0; i < 6; i ++) {
        if (rand_range(0, 100) < move_data.chance_target) {
            stat_boost(defender, i, move_data.stat_target[i]);
        }
    }
    
    for (i = 0; i < 2; i ++) {
        if (rand_range(0, 100) < move_data.secondary_status_chance[i]) {
            // TODO: Apply status move_data.secondary_status[i] to target i
        }
    }
    
}

