#include <pokeagb/pokeagb.h>
#include "../../battle_data/pkmn_bank.h"
#include "../../battle_data/pkmn_bank_stats.h"
#include "../../battle_data/battle_state.h"
#include "../../moves/moves.h"
#include "../../battle_text/battle_pick_message.h"
#include "../move_chain_states.h"

extern u16 rand_range(u16 min, u16 max);
extern void dprintf(const char * str, ...);

u16 pick_player_attack()
{
    if (p_bank[PLAYER_SINGLES_BANK]->b_data.is_running)
        return 0;
    u16 player_moveid = battle_master->battle_cursor.cursor_pos + REQUEST_MOVE1;
    if (player_moveid == (REQUEST_MOVE1 + 1)) {
        player_moveid += 1;
    } else if (player_moveid == (REQUEST_MOVE1 + 2)) {
        player_moveid -= 1;
    }
    p_bank[PLAYER_SINGLES_BANK]->b_data.pp_index = player_moveid - REQUEST_MOVE1;
    return pokemon_getattr(p_bank[PLAYER_SINGLES_BANK]->this_pkmn, player_moveid, NULL);    
}

u16 pick_opponent_attack()
{
    if (p_bank[OPPONENT_SINGLES_BANK]->b_data.is_running)
        return 0;    
    u8 move_total = 0;
    u8 usable_moves = 0;
    u8 i;
    for (i = 0; i < 4; i++) {
        if (pokemon_getattr(p_bank[OPPONENT_SINGLES_BANK]->this_pkmn, REQUEST_MOVE1 + i, NULL)) {
            move_total++;
            if (pokemon_getattr(p_bank[OPPONENT_SINGLES_BANK]->this_pkmn, REQUEST_PP1 + 1, NULL))
                usable_moves++;
        } else {
            break;
        }     
    }
    if (usable_moves < 1) {
        return MOVE_STRUGGLE;
    }
    while (true) {
        u8 pp_index = rand_range(0, move_total);
        if (pokemon_getattr(p_bank[OPPONENT_SINGLES_BANK]->this_pkmn, rand_range(0, move_total) + 
            REQUEST_PP1, NULL) > 0) {
            p_bank[OPPONENT_SINGLES_BANK]->b_data.pp_index = pp_index;
            return pokemon_getattr(p_bank[OPPONENT_SINGLES_BANK]->this_pkmn, pp_index + REQUEST_MOVE1, NULL);
        }
    }
    return 0;
}

void set_attack_battle_master(u8 bank, u8 index, s8 priority)
{
    u16 move_id = p_bank[bank]->b_data.current_move;
    B_MOVE_FAILED(bank) = false;
    
    battle_master->b_moves[index].user_bank = bank;
    battle_master->b_moves[index].move_id = move_id;
    battle_master->b_moves[index].priority = priority;
    battle_master->b_moves[index].stab = 150; // move stab bonus
    battle_master->b_moves[index].power = MOVE_POWER(move_id);
    battle_master->b_moves[index].category = MOVE_CATEGORY(move_id);
    battle_master->b_moves[index].type[0] = MOVE_TYPE(move_id);
    battle_master->b_moves[index].type[1] = MTYPE_EGG;
    battle_master->b_moves[index].flinch = 0;
    battle_master->b_moves[index].accuracy = MOVE_ACCURACY(move_id);
    battle_master->b_moves[index].remove_contact = false;
    battle_master->b_moves[index].copied = false;
    battle_master->b_moves[index].ignore_abilities = false;
    battle_master->b_moves[index].prankstered = HAS_VOLATILE(bank, VOLATILE_PRANKSTERED);
    REMOVE_VOLATILE(bank, VOLATILE_PRANKSTERED);
    battle_master->b_moves[index].infiltrates = false;
    battle_master->b_moves[index].chance_self = moves[move_id].procs->chance_self;
    battle_master->b_moves[index].chance_target = moves[move_id].procs->chance_target;
    if (moves[move_id].multi_hit[0]) {
        u8 hit_times = 0;
        if ((moves[move_id].multi_hit[0] == 2) && (moves[move_id].multi_hit[1] == 5)) {
            switch(rand_range(0, 3)) {
                case 0:
                    hit_times = 2;
                    break;
                case 1:
                    hit_times = 3;
                    break;
                case 2:
                    hit_times = rand_range(4, 5);
                    break;
            };
        } else {
            hit_times = ((rand_range(moves[move_id].multi_hit[0], moves[move_id].multi_hit[1])) | 1);
        }
        battle_master->b_moves[index].hit_times = hit_times;
        battle_master->b_moves[index].hit_counter = 0;
    }
    
    u8 i;
    for (i = 0; i < 6; i++) {
        battle_master->b_moves[bank].stat_self[i] = moves[move_id].procs->stat_self[i];
        battle_master->b_moves[bank].stat_target[i] = moves[move_id].procs->stat_target[i];
        battle_master->b_moves[bank].amount_self[i] = moves[move_id].procs->amount_self[i];
        battle_master->b_moves[bank].amount_target[i] = moves[move_id].procs->amount_target[i];
    }
}

void reset_turn_bits(u8 bank)
{
    p_bank[bank]->b_data.is_running = 0;
    p_bank[bank]->b_data.is_switching = 0;
    p_bank[bank]->b_data.first_turn = 1;
    memset((void*)(&battle_master->b_moves[B_MOVE_BANK(bank)]), 0x0, sizeof(struct move_used));
    
}

u8 set_target_bank(u8 user_bank, u16 move_id)
{
    // check who the move targets
    if (moves[move_id].m_flags & FLAG_ONSELF) {
        p_bank[user_bank]->b_data.my_target = user_bank;
        return user_bank;
    } else {
        p_bank[user_bank]->b_data.my_target = FOE_BANK(user_bank);
        return FOE_BANK(user_bank);
    }
}

bool target_exists(u8 bank)
{
    /* TODO this should be more thorough */
    // target has hp remaining
    if (B_CURRENT_HP(TARGET_OF(bank)))
        return true;
    return false;
}



