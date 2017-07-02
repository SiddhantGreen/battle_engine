#include <pokeagb/pokeagb.h>
#include "../../battle_data/pkmn_bank.h"
#include "../../battle_data/pkmn_bank_stats.h"
#include "../../battle_data/battle_state.h"
#include "../../moves/moves.h"
#include "../../battle_text/battle_pick_message.h"
#include "../move_chain_states.h"

extern u16 pick_player_attack(void);
extern u16 pick_opponent_attack(void);
extern u16 rand_range(u16 min, u16 max);
extern void set_attack_battle_master(u8 bank, u8 index, s8 priority);
extern u8 set_target_bank(u8 user_bank, u16 move_id);

void configure_selected_moves()
{
    // fetch moves used from input
    u16 p_move = pick_player_attack();
    u16 opp_move = pick_opponent_attack();
    battle_master->fight_menu_content_spawned = 0;
    
    // update internal move history
    update_move_history(PLAYER_SINGLES_BANK, p_move);
    update_move_history(OPPONENT_SINGLES_BANK, opp_move);
}

s8 get_move_priority(u8 bank)
{
    u16 move = CURRENT_MOVE(bank);
    
    /* check if ability boosts priority of move, and update */
    s8 priority = ability_priority_mod(bank, move);

    /* update selected move's innate priority */
    priority += MOVE_PRIORITY(move);  

    /* on flee the actor has a priority high enough to outspeed everything except pursuit */
    if (p_bank[bank]->b_data.is_running)
        priority = 6;
    return priority;
}

void battle_set_order()
{
    configure_selected_moves();
    s8 player_priority = get_move_priority(PLAYER_SINGLES_BANK);
    s8 opp_priority = get_move_priority(OPPONENT_SINGLES_BANK);
    
    /* Turn order, higher priority will go first */
    if (player_priority > opp_priority) {
        battle_master->first_bank = PLAYER_SINGLES_BANK;
        battle_master->second_bank = OPPONENT_SINGLES_BANK;
    } else if (player_priority < opp_priority) {
        battle_master->first_bank = OPPONENT_SINGLES_BANK;
        battle_master->second_bank = PLAYER_SINGLES_BANK;
    } else {
        // matching priorities, retrieve speed stat
        u16 player_speed = B_SPEED_STAT(PLAYER_SINGLES_BANK);
        u16 opponent_speed = B_SPEED_STAT(OPPONENT_SINGLES_BANK);
        
        // roll speed tie
        if (player_speed == opponent_speed) {
            if (rand_range(0, 1))
                player_speed++;
            else
                opponent_speed++;
        }
        
        // higher speed goes first
        if (player_speed > opponent_speed) {
            battle_master->first_bank = PLAYER_SINGLES_BANK;
            battle_master->second_bank = OPPONENT_SINGLES_BANK;
        } else {
            battle_master->first_bank = OPPONENT_SINGLES_BANK;
            battle_master->second_bank = PLAYER_SINGLES_BANK;
        }   
    }
    set_attack_battle_master(battle_master->first_bank, 0, battle_master->first_bank == PLAYER_SINGLES_BANK ? player_priority : opp_priority);
    set_attack_battle_master(battle_master->second_bank, 1, battle_master->second_bank == OPPONENT_SINGLES_BANK ? opp_priority : player_priority);
    set_target_bank(battle_master->first_bank, p_bank[battle_master->first_bank]->b_data.current_move);
    set_target_bank(battle_master->second_bank, p_bank[battle_master->second_bank]->b_data.current_move);
   
    /* Run each move's before turn TODO */
    /*if (moves[CURRENT_MOVE(battle_master->first_bank)].move_cb->bt_cb)
        moves[CURRENT_MOVE(battle_master->first_bank)].move_cb->bt_cb(battle_master->first_bank);
    if (moves[CURRENT_MOVE(battle_master->second_bank)].move_cb->bt_cb)
        moves[CURRENT_MOVE(battle_master->second_bank)].move_cb->bt_cb(battle_master->second_bank);*/
    
    super.multi_purpose_state_tracker = 0;
    battle_master->execution_index = 0;
}