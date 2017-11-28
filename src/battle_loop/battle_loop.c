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
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

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
            update_callbacks();
            reset_turn_bits(battle_master->first_bank);
            reset_turn_bits(battle_master->second_bank);
            set_callback1(option_selection);
            super.multi_purpose_state_tracker = 0;
            battle_master->execution_index = 0;
            battle_master->fight_menu_content_spawned  = 0;
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

extern u16 pick_player_attack(void);
extern u8 move_pp_count(u16 move_id, struct Pokemon* p);
extern u8 get_move_index(u16 move_id, struct Pokemon* p);

void battle_loop()
{
    extern void battle_set_order(void);
	// check if Player picked a move with PP
	if (p_bank[PLAYER_SINGLES_BANK]->b_data.is_running == false) {
		u16 move_player = pick_player_attack();
		if (move_pp_count(move_player, p_bank[PLAYER_SINGLES_BANK]->this_pkmn) < 1) {
			enqueue_message(0, 0, STRING_NO_PP, 0);
			super.multi_purpose_state_tracker = S_SOFT_RESET_BANK;
			set_callback1(run_decision);
			return;
		}

		// check if Player is trying to use a disabled move
		u8 index = get_move_index(move_player, p_bank[PLAYER_SINGLES_BANK]->this_pkmn);
		if (p_bank[PLAYER_SINGLES_BANK]->b_data.disabled_moves[index] > 0) {
			enqueue_message(0, 0, STRING_DISABLED_PICKED, 0);
			p_bank[PLAYER_SINGLES_BANK]->b_data.skip_move_select = false;
			p_bank[PLAYER_SINGLES_BANK]->b_data.move_lock_counter = 0;
			super.multi_purpose_state_tracker = S_SOFT_RESET_BANK;
			set_callback1(run_decision);
			return;
		}
	}
	// A usable move was picked
	battle_set_order();
	set_callback1(run_decision);
}
