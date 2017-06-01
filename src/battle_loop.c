#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_state.h"
#include "moves/moves.h"

extern void priority_triage_mod(u8 ability, u16 moveid, u8 bank);
extern void priority_gale_wings_mod(u8 ability, u16 moveid, u8 bank);
extern void priority_prankster_mod(u8 ability, u16 moveid, u8 bank);

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
    var_8002 = 0x99;
        speed = speed / p_bank[bank]->user_action.speed;
    } else if (p_bank[bank]->user_action.speed) {
        speed = speed * p_bank[bank]->user_action.speed;
    }
    return speed;
}

void battle_loop()
{
    // get player and opponent's moves used
    u16 p_move = get_player_attack();
    u16 opp_move = get_opponent_attack();
    u8 p_ability = p_bank[PLAYER_SINGLES_BANK]->user_action.ability;
    u8 opp_ability = p_bank[OPPONENT_SINGLES_BANK]->user_action.ability;
    
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
   
    
    /* Running each move now, determine which slot goes first */
    u8 first_bank;
    u8 second_bank;
    if (p_bank[PLAYER_SINGLES_BANK]->user_action.priority > p_bank[OPPONENT_SINGLES_BANK]->user_action.priority) {
        first_bank = PLAYER_SINGLES_BANK;
        second_bank = OPPONENT_SINGLES_BANK;
    } else if (p_bank[PLAYER_SINGLES_BANK]->user_action.priority < p_bank[OPPONENT_SINGLES_BANK]->user_action.priority) {
        first_bank = OPPONENT_SINGLES_BANK;
        second_bank = PLAYER_SINGLES_BANK;
    } else {
        u16 player_speed = pokemon_getattr(p_bank[PLAYER_SINGLES_BANK]->this_pkmn, REQUEST_SPD, NULL);
        u16 opponent_speed = pokemon_getattr(p_bank[OPPONENT_SINGLES_BANK]->this_pkmn, REQUEST_SPD, NULL);
        
        player_speed = field_speed_mod(player_speed, p_ability, 1, PLAYER_SINGLES_BANK, battle_master->field_state);
        opponent_speed = field_speed_mod(opponent_speed, opp_ability, 2, OPPONENT_SINGLES_BANK, battle_master->field_state);
        
        if (player_speed > opponent_speed) {
            first_bank = PLAYER_SINGLES_BANK;
            second_bank = OPPONENT_SINGLES_BANK;
        } else {
            first_bank = OPPONENT_SINGLES_BANK;
            second_bank = PLAYER_SINGLES_BANK;
        }
        
        var_8000 = player_speed;
        var_8001 = opponent_speed;
        
        while(1) {
            var_8002 ++;
        }
        
    }
    
    
    /* 
    for every move:
        ModifyPriority]
        move's [BeforeTurn]   
    */
    
    
    
}






















