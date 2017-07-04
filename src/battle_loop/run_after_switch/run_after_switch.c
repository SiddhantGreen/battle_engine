#include <pokeagb/pokeagb.h>
#include "../../battle_data/pkmn_bank.h"
#include "../../battle_data/pkmn_bank_stats.h"
#include "../../battle_data/battle_state.h"
#include "../../moves/moves.h"
#include "../../battle_text/battle_pick_message.h"
#include "../move_chain_states.h"

extern void run_decision(void);
extern bool peek_message(void);

void move_on_start(u8 bank)
{
    u16 move = CURRENT_MOVE(bank);
    if (moves[move].on_start)
        moves[move].on_start(bank);
}

void run_after_switch()
{
    while (peek_message())
        return;
    
    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    ability_on_switch(bank_index);
    move_on_start(bank_index);
    super.multi_purpose_state_tracker = S_RUN_SWITCH_ALTERNATE_BANK;
    set_callback1(run_decision);
}

