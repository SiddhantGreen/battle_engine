#include <pokeagb/pokeagb.h>
#include "../../battle_data/pkmn_bank.h"
#include "../../battle_data/pkmn_bank_stats.h"
#include "../../battle_data/battle_state.h"
#include "../../moves/moves.h"
#include "../../battle_text/battle_pick_message.h"
#include "../move_chain_states.h"

extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool peek_message(void);
extern void run_decision(void);
extern void dprintf(const char * str, ...);
extern void run_flee(void);
extern bool b_pkmn_has_type(u8 bank, u8 type);

bool bank_trapped(u8 bank)
{
    if (b_pkmn_has_type(bank, TYPE_GHOST))
        return true;
    if (HAS_VOLATILE(bank, VOLATILE_TRAPPED)) {
        return false;
    }
    return true;
}

void switch_battler(u8 switching_bank)
{
    /* TODO actual switching */
    return;
}

void move_on_switch_cb()
{
    u16 move = CURRENT_MOVE(battle_master->first_bank);
    if (moves[move].before_switch)
        moves[move].before_switch(battle_master->first_bank);
        
    move = CURRENT_MOVE(battle_master->second_bank);
    if (moves[move].before_switch)
        moves[move].before_switch(battle_master->second_bank);
}

void run_switch()
{
    while (peek_message())
        return;
        
    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;   
    switch(super.multi_purpose_state_tracker) {
        case S_RUN_FLEE:
            set_callback1(run_flee);
            super.multi_purpose_state_tracker = S_CHECK_FLEEING;
            break;
        case S_RUN_SWITCH_CHECKS:
            // if first bank is switching exec before switch cbs. Else jump to second bank is switching check
            if (p_bank[bank_index]->b_data.is_switching) {
                ability_on_before_switch(bank_index);
                super.multi_purpose_state_tracker++;
            } else {
                set_callback1(run_decision);
                super.multi_purpose_state_tracker = S_RUN_SWITCH_ALTERNATE_BANK;
            }
            break;
        case S_SWITCH_LOGIC:
            move_on_switch_cb();
            // do actual switch
            switch_battler(bank_index);
            dprintf("trying to alternate bank inside run switch\n");
            set_callback1(run_decision);
            super.multi_purpose_state_tracker = S_RUN_SWITCH_ALTERNATE_BANK;
            break;
    };
}
