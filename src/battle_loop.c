#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_state.h"
#include "moves/moves.h"
#include "battle_text/battle_pick_message.h"

extern void priority_triage_mod(u8 ability, u16 moveid, u8 bank);
extern void priority_gale_wings_mod(u8 ability, u16 moveid, u8 bank);
extern void priority_prankster_mod(u8 ability, u16 moveid, u8 bank);
extern void pick_battle_message(u16 move_id, u8 user_bank, enum BattleFlag battle_type, enum battle_string_ids id);

void run_switch(u8 bank_id) 
{
    if (p_bank[bank_id]->user_action.is_switching) {
        //battle_pkmm_switch(bank_id, p_bank[bank_id]->user_action.switching_slot);
        /* TODO : RUN BEFORE SWITCH MOVES */
    }
}

u16 get_player_attack()
{
    u16 player_moveid = battle_master->battle_cursor.cursor_pos + REQUEST_MOVE1;
    if (player_moveid == (REQUEST_MOVE1 + 1)) {
        player_moveid += 1;
    } else if (player_moveid == (REQUEST_MOVE1 + 2)) {
        player_moveid -= 1;
    }
    
    return pokemon_getattr(p_bank[PLAYER_SINGLES_BANK]->this_pkmn, player_moveid, NULL);    
}

u16 get_opponent_attack()
{
    u8 moves_total = 0;
    u8 i;
    for (i = 0; i < 4; i++) {
        if (pokemon_getattr(p_bank[OPPONENT_SINGLES_BANK]->this_pkmn, REQUEST_MOVE1 + i, NULL)) {
            moves_total++;
        } else {
            break;
        }
        
    }
    return pokemon_getattr(p_bank[OPPONENT_SINGLES_BANK]->this_pkmn, (rand() / (0xFFFF / moves_total)) + REQUEST_MOVE1, NULL);
}

u8 get_bank_ability(u8 bank)
{
    u8 ability = pokemon_getattr(p_bank[bank]->this_pkmn, REQUEST_ABILITY_BIT, NULL);
    return pokemon_base_stats[pokemon_getattr(p_bank[bank]->this_pkmn, REQUEST_SPECIES, NULL)].ability[ability];
}


u16 field_speed_mod(u16 speed, u8 ability, u8 side, u8 bank, struct battle_field_state field_state) {
    // Ability speed bonus
    switch (ability) {
        case ABILITY_SWIFT_SWIM:
        {
            speed *= (field_state.is_raining) ? 2 : 1;
            break;
        }
        case ABILITY_SLUSH_RUSH:
        {
            speed *= (field_state.is_hail) ? 2 : 1;
            break;
        }
        case ABILITY_CHLOROPHYLL:
        {
            speed *= (field_state.is_sunny) ? 2 : 1;
            break;
        }
        case ABILITY_SAND_RUSH:
        {
            speed *= (field_state.is_sandstorm) ? 2 : 1;
            break;
        }
    };
    
    // tailwind
    speed *= (field_state.is_tailwind & side) ? 2 : 1;
    
    // speed modifier apply
    if (p_bank[bank]->user_action.speed < 0) {
        speed = speed / p_bank[bank]->user_action.speed;
    } else if (p_bank[bank]->user_action.speed) {
        speed = speed * p_bank[bank]->user_action.speed;
    }
    return speed;
}

u8 get_side(u8 bank)
{
    return (bank > 1) ? 1 : 0;
}

void run_move_text(u16 attack, u8 bank, u16 speed)
{
    // display move was used
    pick_battle_message(attack, bank, battle_type_flags, STRING_ATTACK_USED);
    battle_show_message((u8*)string_buffer, 0x18);
    

}

u8 get_target_bank(u8 user_bank, u16 move_id)
{
    // check who the move targets
    if (*(move_t[move_id].m_flags) & FLAG_ONSELF) {
        p_bank[user_bank]->user_action.target_bank = user_bank;
        return user_bank;
    } else { //if (*(move_t[move_id].m_flags) & FLAG_TARGET) {
        u8 t_bank = (user_bank == PLAYER_SINGLES_BANK) ? OPPONENT_SINGLES_BANK : PLAYER_SINGLES_BANK;
        p_bank[user_bank]->user_action.target_bank = t_bank;
        return t_bank;
    }

}


void battle_loop()
{
    u8 p_ability = p_bank[PLAYER_SINGLES_BANK]->user_action.ability;
    u8 opp_ability = p_bank[OPPONENT_SINGLES_BANK]->user_action.ability;
    switch(super.multi_purpose_state_tracker) {
        case 0:
        {
            // set p_bank temp vars and fix priority tiers
            u16 p_move = get_player_attack();
            u16 opp_move = get_opponent_attack();
            
            p_bank[PLAYER_SINGLES_BANK]->user_action.move_id = p_move;
            p_bank[OPPONENT_SINGLES_BANK]->user_action.move_id = opp_move;
            
            /* check if ability boosts priority of move */
            // Triage
            priority_triage_mod(p_ability, p_move, PLAYER_SINGLES_BANK);
            priority_triage_mod(opp_ability, opp_move, OPPONENT_SINGLES_BANK);
            
            // Gale wings
            priority_gale_wings_mod(p_ability, p_move, PLAYER_SINGLES_BANK);
            priority_gale_wings_mod(opp_ability, opp_move, OPPONENT_SINGLES_BANK);
            
            // Prankster
            priority_prankster_mod(p_ability, p_move, PLAYER_SINGLES_BANK);
            priority_prankster_mod(opp_ability, opp_move, OPPONENT_SINGLES_BANK);
            
            /* add to p_bank priority based on natural move priority */
            p_bank[PLAYER_SINGLES_BANK]->user_action.priority += move_t[p_move].priority;
            p_bank[OPPONENT_SINGLES_BANK]->user_action.priority += move_t[opp_move].priority;
            super.multi_purpose_state_tracker++;
            return;
        }
        break;
        case 1:
        {
            // figure out who goes first
            if (p_bank[PLAYER_SINGLES_BANK]->user_action.priority > p_bank[OPPONENT_SINGLES_BANK]->user_action.priority) {
                battle_master->first_bank = PLAYER_SINGLES_BANK;
                battle_master->second_bank = OPPONENT_SINGLES_BANK;
            } else if (p_bank[PLAYER_SINGLES_BANK]->user_action.priority < p_bank[OPPONENT_SINGLES_BANK]->user_action.priority) {
                battle_master->first_bank = OPPONENT_SINGLES_BANK;
                battle_master->second_bank = PLAYER_SINGLES_BANK;
            } else {
                u16 player_speed = pokemon_getattr(p_bank[PLAYER_SINGLES_BANK]->this_pkmn, REQUEST_SPD, NULL);
                u16 opponent_speed = pokemon_getattr(p_bank[OPPONENT_SINGLES_BANK]->this_pkmn, REQUEST_SPD, NULL);
                
                player_speed = field_speed_mod(player_speed, p_ability, 1, PLAYER_SINGLES_BANK, battle_master->field_state);
                opponent_speed = field_speed_mod(opponent_speed, opp_ability, 2, OPPONENT_SINGLES_BANK, battle_master->field_state);
                
                p_bank[PLAYER_SINGLES_BANK]->user_action.speed_current = player_speed;
                p_bank[OPPONENT_SINGLES_BANK]->user_action.speed_current = opponent_speed;
                
                if (player_speed > opponent_speed) {
                    battle_master->first_bank = PLAYER_SINGLES_BANK;
                    battle_master->second_bank = OPPONENT_SINGLES_BANK;
                } else {
                    battle_master->first_bank = OPPONENT_SINGLES_BANK;
                    battle_master->second_bank = PLAYER_SINGLES_BANK;
                }
                
            }
            battle_master->b_moves[0].move_id = p_bank[battle_master->first_bank]->user_action.move_id;
            battle_master->b_moves[0].user_bank = battle_master->first_bank;
            battle_master->b_moves[1].move_id = p_bank[battle_master->second_bank]->user_action.move_id;
            battle_master->b_moves[1].user_bank = battle_master->second_bank;
            super.multi_purpose_state_tracker = 3;
            return;
        }
        break;
    };
    extern void run_decision(void);
    
    /* Run each move's before turn */
    if (move_t[p_bank[battle_master->first_bank]->user_action.move_id].move_cb->bm_cb)
        move_t[p_bank[battle_master->first_bank]->user_action.move_id].move_cb->bm_cb(battle_master->first_bank);
    if (move_t[p_bank[battle_master->second_bank]->user_action.move_id].move_cb->bm_cb)
        move_t[p_bank[battle_master->second_bank]->user_action.move_id].move_cb->bm_cb(battle_master->second_bank);
    
    super.multi_purpose_state_tracker = 0;
    battle_master->execution_index = 0;
    set_callback1(run_decision);
}

void run_decision(void)
{
    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    switch (super.multi_purpose_state_tracker) {
        case 0:
        {
            /* TODO: Run switch */
            super.multi_purpose_state_tracker++;
        }
        break;
        case 1:
        {
            /* TODO: Run after switch */
            super.multi_purpose_state_tracker++;
        }
        break;
        case 2:
        {
            /* Run move used text */
            run_move_text(p_bank[bank_index]->user_action.move_id, bank_index, p_bank[bank_index]->user_action.speed_current);
            super.multi_purpose_state_tracker++;
        }
        break;
        case 3:
        {
            if (!dialogid_was_acknowledged(0x18 & 0x3F)) {
                super.multi_purpose_state_tracker++;
            }
        }
        break;
        case 4:
        {
            /* Run before move callbacks */
            break;
        }
    
    /* Run After switch */
    
    /* Run move */
        
        
        //set_callback1(wait_text);
        //battle_show_message((u8*)string_buffer, 0x18);
       
    
    /* Run faint */
    
    /* Run residual */
    
    /* Run switch */
    
    /* Run After switch */
    };
}























