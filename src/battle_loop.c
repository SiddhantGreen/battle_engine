#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/pkmn_bank_stats.h"
#include "battle_state.h"
#include "moves/moves.h"
#include "battle_text/battle_pick_message.h"

extern void pick_battle_message(u16 move_id, u8 user_bank, enum BattleFlag battle_type, enum battle_string_ids id, u16 effect_id);
extern u8 get_side(u8 bank);
extern u8 move_target(u8 bank, u16 move_id);
extern void run_decision(void);
extern u16 rand_range(u16 min, u16 max);
extern void build_message(u8 state, u16 move_id, u8 user_bank, enum battle_string_ids id, u16 move_effect_id);

u16 pick_player_attack()
{
    u16 player_moveid = battle_master->battle_cursor.cursor_pos + REQUEST_MOVE1;
    if (player_moveid == (REQUEST_MOVE1 + 1)) {
        player_moveid += 1;
    } else if (player_moveid == (REQUEST_MOVE1 + 2)) {
        player_moveid -= 1;
    }  
    return pokemon_getattr(p_bank[PLAYER_SINGLES_BANK]->this_pkmn, player_moveid, NULL);    
}

u16 pick_opponent_attack()
{
    u8 move_total = 0;
    u8 i;
    for (i = 0; i < 4; i++) {
        if (pokemon_getattr(p_bank[OPPONENT_SINGLES_BANK]->this_pkmn, REQUEST_MOVE1 + i, NULL)) {
            move_total++;
        } else {
            break;
        }     
    }  
    return pokemon_getattr(p_bank[OPPONENT_SINGLES_BANK]->this_pkmn, rand_range(0, move_total)+ REQUEST_MOVE1, NULL);
}

void set_attack(u8 bank, u16 move_id)
{
    battle_master->b_moves[bank].move_id = move_id;
    battle_master->b_moves[bank].user_bank = bank;
    battle_master->b_moves[bank].power = move_t[move_id].base_power;
    battle_master->b_moves[bank].type[0] = move_t[move_id].type;
    battle_master->b_moves[bank].accuracy = move_t[move_id].accuracy;
    battle_master->b_moves[bank].chance_self = move_t[move_id].procs->chance_self;
    battle_master->b_moves[bank].chance_target = move_t[move_id].procs->chance_target;
    
    battle_master->b_moves[bank].stat_self[0] = move_t[move_id].procs->stat_self[0];
    battle_master->b_moves[bank].stat_self[1] = move_t[move_id].procs->stat_self[1];
    battle_master->b_moves[bank].stat_self[2] = move_t[move_id].procs->stat_self[2];
    battle_master->b_moves[bank].stat_self[3] = move_t[move_id].procs->stat_self[3];
    battle_master->b_moves[bank].stat_self[4] = move_t[move_id].procs->stat_self[4];
    battle_master->b_moves[bank].stat_self[5] = move_t[move_id].procs->stat_self[5];
    
    battle_master->b_moves[bank].stat_target[0] = move_t[move_id].procs->stat_target[0];
    battle_master->b_moves[bank].stat_target[1] = move_t[move_id].procs->stat_target[1];
    battle_master->b_moves[bank].stat_target[2] = move_t[move_id].procs->stat_target[2];
    battle_master->b_moves[bank].stat_target[3] = move_t[move_id].procs->stat_target[3];
    battle_master->b_moves[bank].stat_target[4] = move_t[move_id].procs->stat_target[4];
    battle_master->b_moves[bank].stat_target[5] = move_t[move_id].procs->stat_target[5];
    
    battle_master->b_moves[bank].amount_self[0] = move_t[move_id].procs->amount_self[0];
    battle_master->b_moves[bank].amount_self[1] = move_t[move_id].procs->amount_self[1];
    battle_master->b_moves[bank].amount_self[2] = move_t[move_id].procs->amount_self[2];
    battle_master->b_moves[bank].amount_self[3] = move_t[move_id].procs->amount_self[3];
    battle_master->b_moves[bank].amount_self[4] = move_t[move_id].procs->amount_self[4];
    battle_master->b_moves[bank].amount_self[5] = move_t[move_id].procs->amount_self[5];
    
    battle_master->b_moves[bank].amount_target[0] = move_t[move_id].procs->amount_target[0];
    battle_master->b_moves[bank].amount_target[1] = move_t[move_id].procs->amount_target[1];
    battle_master->b_moves[bank].amount_target[2] = move_t[move_id].procs->amount_target[2];
    battle_master->b_moves[bank].amount_target[3] = move_t[move_id].procs->amount_target[3];
    battle_master->b_moves[bank].amount_target[4] = move_t[move_id].procs->amount_target[4];
    battle_master->b_moves[bank].amount_target[5] = move_t[move_id].procs->amount_target[5];

}



void run_move_text(u16 attack, u8 bank)
{
    // display move was used
    pick_battle_message(attack, bank, battle_type_flags, STRING_ATTACK_USED, 0);
    battle_show_message((u8*)string_buffer, 0x18);
    

}

u8 get_target_bank(u8 user_bank, u16 move_id)
{
    // check who the move targets
    if (*(move_t[move_id].m_flags) & FLAG_ONSELF) {
        p_bank[user_bank]->b_data.my_target = user_bank;
        return user_bank;
    } else { //if (*(move_t[move_id].m_flags) & FLAG_TARGET) {
        u8 t_bank = (user_bank == PLAYER_SINGLES_BANK) ? OPPONENT_SINGLES_BANK : PLAYER_SINGLES_BANK;
        p_bank[user_bank]->b_data.my_target = t_bank;
        return t_bank;
    }

}


void battle_loop()
{
    // set p_bank temp vars and fix priority tiers
    u16 p_move = pick_player_attack();
    u16 opp_move = pick_opponent_attack();
    battle_master->fight_menu_content_spawned = 0;
    
    update_moves(PLAYER_SINGLES_BANK, p_move);
    update_moves(OPPONENT_SINGLES_BANK, opp_move);
    
    /* check if ability boosts priority of move */
    s8 player_priority = ability_priority_mod(PLAYER_SINGLES_BANK, p_move);
    s8 opp_priority = ability_priority_mod(PLAYER_SINGLES_BANK, p_move);
    /* check selected move's innate priority */
    player_priority += MOVE_PRIORITY(p_move);
    opp_priority += MOVE_PRIORITY(opp_move);
    
    // Higher priority will go first
    if (player_priority > opp_priority) {
        battle_master->first_bank = PLAYER_SINGLES_BANK;
        battle_master->second_bank = OPPONENT_SINGLES_BANK;
    } else if (player_priority < opp_priority) {
        battle_master->first_bank = OPPONENT_SINGLES_BANK;
        battle_master->second_bank = PLAYER_SINGLES_BANK;
    } else {
        // matching priorities, get speed
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
    battle_master->b_moves[0].move_id = CURRENT_MOVE(battle_master->first_bank);
    battle_master->b_moves[0].user_bank = battle_master->first_bank;
    battle_master->b_moves[1].move_id = CURRENT_MOVE(battle_master->second_bank);
    battle_master->b_moves[1].user_bank = battle_master->second_bank;
    
    // figure out who the target of the move used is
    set_attack(battle_master->first_bank, battle_master->b_moves[0].move_id);
    set_attack(battle_master->second_bank, battle_master->b_moves[1].move_id);
    
    /* Run each move's before turn */
    if (move_t[CURRENT_MOVE(battle_master->first_bank)].move_cb->bt_cb)
        move_t[CURRENT_MOVE(battle_master->first_bank)].move_cb->bt_cb(battle_master->first_bank);
    if (move_t[CURRENT_MOVE(battle_master->second_bank)].move_cb->bt_cb)
        move_t[CURRENT_MOVE(battle_master->second_bank)].move_cb->bt_cb(battle_master->second_bank);
    
    super.multi_purpose_state_tracker = 0;
    battle_master->execution_index = 0;
    set_callback1(run_decision);
}

void unclean_move_select(void)
{
    return;
}

void run_decision(void)
{
    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    switch (super.multi_purpose_state_tracker) {
        case 0:
        {
            /* TODO: Run switch and Player running away from battle checks */
            super.multi_purpose_state_tracker++;
            break;
        }
        case 1:
        {
            /* TODO: Run after switch */
            super.multi_purpose_state_tracker++;
            break;
        }
        case 2:
        {
            /* Run before move callbacks */
            super.multi_purpose_state_tracker++;

            break;
        }
        case 3:
        {
            /* Run move used text */

            
            build_message(super.multi_purpose_state_tracker + 1, CURRENT_MOVE(bank_index), bank_index,
                        STRING_ATTACK_USED, 0);
            //super.multi_purpose_state_tracker++;
            break;
        }
        case 4:
        {
           // if (!dialogid_was_acknowledged(0x18)) {
                super.multi_purpose_state_tracker++;
           // }
            break;
        }
        case 5:
        {
            super.multi_purpose_state_tracker++;
            break;
        }
        case 6:
        {
            /* check target exists */
            if (p_bank[p_bank[bank_index]->b_data.my_target]->this_pkmn->current_hp) {
                super.multi_purpose_state_tracker += 2;
            } else {
                u16 move_id = battle_master->b_moves[battle_master->execution_index].move_id;
                pick_battle_message(move_id, bank_index, battle_type_flags, STRING_NO_TARGET, move_id);
                battle_show_message((u8*)string_buffer, 0x18);
                var_8000 = 0x92 + battle_master->execution_index;
                super.multi_purpose_state_tracker++;
            }
            break;
        }
        case 7:
        {
            if (!dialogid_was_acknowledged(0x18)) {
                super.multi_purpose_state_tracker++;
            }
            break;
        }
        case 8:
        {
            /* Move hit */
            
            super.multi_purpose_state_tracker = 98;
            break;
        }
        case 98:
        {
            
            battle_master->execution_index++;
            if (battle_master->execution_index > 1) {
                extern void option_selection(void);
                set_callback1(option_selection);
                super.multi_purpose_state_tracker = 0;
                battle_master->execution_index = 0;
                return;
            }
            super.multi_purpose_state_tracker = 0;
            break;
        }
        default:
            break;
    };
}























