#include <pokeagb/pokeagb.h>
#include "../../battle_data/pkmn_bank.h"
#include "../../battle_data/pkmn_bank_stats.h"
#include "../../battle_data/battle_state.h"
#include "../../moves/moves.h"
#include "../../battle_text/battle_pick_message.h"
#include "../move_chain_states.h"

extern void run_decision(void);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool peek_message(void);
extern void move_hit(void);
extern bool target_exists(u8 bank);


#define BEFORE_MOVE_CALLBACK_0 0
void run_move()
{
    while (peek_message())
        return;
    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    switch(super.multi_purpose_state_tracker) {
        case S_BEFORE_MOVE:
        {
            u16 move = CURRENT_MOVE(bank_index);
            if (!move) {
                set_callback1(run_decision);
                super.multi_purpose_state_tracker = S_RUN_FAINT;
                break;
            }
            /* TODO :  Before move callbacks */
            if (BEFORE_MOVE_CALLBACK_0) {
                // move failed
                super.multi_purpose_state_tracker = S_RUN_FAINT;
                set_callback1(run_decision);
            } else {
                // display "Pokemon used move!"
                enqueue_message(CURRENT_MOVE(bank_index), bank_index, STRING_ATTACK_USED, 0);
                super.multi_purpose_state_tracker = S_BEFORE_MOVE_ABILITY;
            }
            break;
        }
        case S_BEFORE_MOVE_ABILITY: /* use_move() is inlined */
            // Modify move callbacks
            ability_on_modify_move(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index));
            super.multi_purpose_state_tracker++;
            break;
        case S_CHECK_TARGET_EXISTS:
            // check target exists
            if (!target_exists(bank_index)) {
                enqueue_message(0, bank_index, STRING_FAILED, 0);
                super.multi_purpose_state_tracker = S_PP_REDUCTION;
            } else {
                super.multi_purpose_state_tracker++;
            }
            break;
        case S_RUN_MOVE_HIT:
            set_callback1(move_hit); // move hit will advance the state when complete
            super.multi_purpose_state_tracker = 0;
            break;
        case S_PP_REDUCTION:
        {
            // reduce PP
            u8 pp_index = p_bank[bank_index]->b_data.pp_index;
            u8 pp = pokemon_getattr(p_bank[bank_index]->this_pkmn, pp_index + REQUEST_PP1, NULL) - 1;
            pokemon_setattr(p_bank[bank_index]->this_pkmn, pp_index + REQUEST_PP1, &pp);
            super.multi_purpose_state_tracker = S_RUN_FAINT;
            set_callback1(run_decision);
            break;
        }
    };
}






