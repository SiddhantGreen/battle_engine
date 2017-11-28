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
extern u16 rand_range(u16 min, u16 max);
extern void dprintf(const char * str, ...);

void run_move_failed_cbs(u8 attacker, u8 defender, u16 move)
{
    // add callbacks specific to field
    if (moves[move].on_move_fail) {
        add_callback(CB_ON_MOVE_FAIL, 0, 0, attacker, (u32)moves[move].on_move_fail);
    }
    // run callbacks
    build_execution_order(CB_ON_MOVE_FAIL);
    battle_master->executing = true;
    while (battle_master->executing) {
        pop_callback(attacker, move);
    }
}
