#include <pokeagb/pokeagb.h>
#include "../../battle_data/pkmn_bank.h"
#include "../../battle_data/pkmn_bank_stats.h"
#include "../../battle_data/battle_state.h"
#include "../../moves/moves.h"
#include "../../battle_text/battle_pick_message.h"
#include "../move_chain_states.h"

extern void run_decision(void);
extern bool peek_message(void);


void run_after_switch()
{
    while (peek_message())
        return;
    u8 attacker = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    u16 move = CURRENT_MOVE(attacker);
    if (moves[move].on_start) {
        add_callback(CB_ON_START, 0, 0, attacker, (u32)moves[move].on_start);
    }
    // run on start callbacks
    build_execution_order(CB_ON_START);
    battle_master->executing = true;
    while (battle_master->executing) {
        pop_callback(attacker, move);
    }
    super.multi_purpose_state_tracker = S_RUN_SWITCH_ALTERNATE_BANK;
    set_callback1(run_decision);
}
