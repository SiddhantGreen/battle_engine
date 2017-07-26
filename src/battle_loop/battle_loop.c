#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/pkmn_bank_stats.h"
#include "battle_data/battle_state.h"
#include "moves/moves.h"
#include "battle_text/battle_pick_message.h"
#include "move_chain_states.h"

extern bool peek_message(void);
extern void run_move(void);
extern void dprintf(const char * str, ...);
extern void reset_turn_bits(u8 bank);
extern void run_after_switch(void);
extern void option_selection(void);
extern void on_faint(void);
extern void run_switch(void);
extern void sync_battler_struct(u8 bank);

void run_decision(void)
{
    while (peek_message())
        return;

    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    switch (super.multi_purpose_state_tracker) {
       case S_RUN_SWITCH:
            set_callback1(run_switch);
            super.multi_purpose_state_tracker = 0;
            break;
        case S_RUN_AFTER_SWITCH:
            set_callback1(run_after_switch);
            super.multi_purpose_state_tracker = 0;
            break;
        case S_RUN_SWITCH_ALTERNATE_BANK:
        {
            // once first bank's run_switch and run_after_switch have exec'd, run second bank
            if (bank_index == battle_master->second_bank) {
                // if second bank run, switch back to first bank and go to next phase
                battle_master->execution_index = 0;
                super.multi_purpose_state_tracker++;
            } else {
                battle_master->execution_index = 1;
                super.multi_purpose_state_tracker = 0;
            }
            break;
        }
        case S_RUN_MOVE:
            set_callback1(run_move);
            super.multi_purpose_state_tracker = 0;
            break;
        case S_RUN_FAINT:
            // Run on faint stuff
            set_callback1(on_faint);
            super.multi_purpose_state_tracker = S_CHECK_BANK1_FAINT;
            break;
        case S_RUN_MOVE_ALTERNATE_BANK:
            // run move for second bank after first bank is run.
            if (bank_index == battle_master->second_bank) {
                battle_master->execution_index = 0;
                super.multi_purpose_state_tracker++;
            } else {
                battle_master->execution_index = 1;
                super.multi_purpose_state_tracker = 3;
            }
            break;
        case S_SOFT_RESET_BANK:
        {
            // reset turn based bits
            reset_turn_bits(battle_master->first_bank);
            reset_turn_bits(battle_master->second_bank);
            set_callback1(option_selection);
            super.multi_purpose_state_tracker = 0;
            battle_master->execution_index = 0;
            break;
        }
        case S_END_BATTLE:
            // TODO: free resources
            sync_battler_struct(PLAYER_SINGLES_BANK);
            exit_to_overworld_2_switch();
            set_callback1(c1_overworld);
            break;
        default:
            break;
    };
}


void battle_loop()
{
    extern void battle_set_order(void);
    battle_set_order();
    set_callback1(run_decision);
}


