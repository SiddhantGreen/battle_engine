#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_state.h"
#include "moves/moves.h"


void run_switch(u8 bank_id) {
    if (p_bank[bank_id]->user_turn.is_switching) {
        //battle_pkmm_switch(bank_id, p_bank[bank_id]->user_turn.switching_slot);
        /* TODO : RUN BEFORE SWITCH MOVES */
    }
}

void battle_loop()
{
    // register moves and assign execution speeds
    u8 bank_order[2] = {0, 1};
    s32 bank_speeds[2] = {0, 0};
    bank_speeds[0] += (1000 * p_bank[0]->user_turn.priority);
    bank_speeds[0] += p_bank[0]->user_turn.speed;
    bank_speeds[1] += (1000 * p_bank[1]->user_turn.priority);
    bank_speeds[1] += p_bank[1]->user_turn.speed;
    
    if (bank_speeds[0] < bank_speeds[1]) {
        bank_order[0] = 1;
        bank_order[1] = 0;
    }
    
    /* Execute each move's Before Turn callbacks */
    move_t[p_bank[bank_order[0]]->user_turn.move_id].move_cb->bt_cb(0, 0);
    move_t[p_bank[bank_order[1]]->user_turn.move_id].move_cb->bt_cb(0, 0);
    
    /* Run decisions */
    u8 i;
    for (i = 0; i < sizeof(bank_order); i++) {
        run_switch(i);
    }
    
    
    
}




/* Unused atm */
/* s8 cmp_move_speeds (struct to_exec_move* move1, struct to_exec_move* move2)
{
    if (move1->priority > move2->priority) {
        // move 1 is higher priority bracket
        return 1;
    } else if (move2->priority > move1_priority) {
        // move 2 is higher priority bracket
        return 0;
    } else if (move1->speed > move2->speed) {
        // same priority, move1 user is faster however
        return 1
    } else if (move2->speed < move1->speed) {
        // same priority, move1 user is slower
        return 0;
    } else {
        // same speed and same priority. Roll speed tie.
        return (rand() % 2);
    }
} */

/* Unused atm */
/* void speed_tiers(void)
{
    s32 bank_speeds[4] = {0, 0, 0, 0};
    u8 i, j;
    for (i = 0; i < 4; i++) {
        bank_speeds[i] += (1000 * p_bank[i]->user_turn.priority);
        bank_speeds[i] += p_bank[i]->user_turn.speed;
    }
    
    // sort bank speeds
    u8 bank_order = {0, 1, 2, 3};
    
    for (i = 0; i < 4; i ++) {
        s32 current_lowest = bank_speed[i];
        u8 current_lowest_bank = i;
        for (j = i; j < 4; j++) {
            // if speeds are equal, roll
            if (current_lowest == bank_speed[j]) {
                if (rand() % 2) {
                    current_lowest = bank_speed[j];
                    current_lowest_bank = j;
                }
            // if new lowest is found, set current lowest to that new lowest
            } else if (current_lowest < bank_speed[j]) {
                current_lowest = bank_speed[j];
                current_lowest_bank = j;
            }        
        }
        
        u8 temp = bank_order[i];
        bank_order[i] = bank_order[current_lowest_bank];
        bank_order[current_lowest_bank] = temp;
        
        s32 temp2 = bank_speeds[i];
        bank_speeds[i] = bank_speeds[current_lowest_bank];
        bank_speeds[current_lowest_bank] = temp2;
    }
} */