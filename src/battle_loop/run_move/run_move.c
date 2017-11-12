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
extern void run_move_failed_cbs(u8 attacker, u8 defender, u16 move);

enum BeforeMoveStatus {
    CANT_USE_MOVE = 0,
    USE_MOVE_NORMAL,
    TARGET_MOVE_IMMUNITY,
};

enum BeforeMoveStatus move_before_move(u8 bank)
{
    u16 move = CURRENT_MOVE(bank);
    if (moves[move].before_move)
        return moves[move].before_move(bank);
    return USE_MOVE_NORMAL;
}

enum BeforeMoveStatus foe_move_before_move(u8 bank)
{
    u16 move = CURRENT_MOVE(FOE_BANK(bank));
    if (moves[move].foe_before_move)
        return moves[move].foe_before_move(FOE_BANK(bank));
    return USE_MOVE_NORMAL;
}

enum BeforeMoveStatus before_move_cb(u8 bank)
{
    u16 move_foe = CURRENT_MOVE(FOE_BANK(bank));
    u16 move = CURRENT_MOVE(bank);
    
    u8 result = USE_MOVE_NORMAL;
    if (moves[move].before_move_priority > moves[move_foe].foe_before_move_priority) {
        result = foe_move_before_move(bank);
        if (result == USE_MOVE_NORMAL) {
            result = move_before_move(bank);
        }
    } else {
        result = move_before_move(bank);
        if (result == USE_MOVE_NORMAL) {
            result = foe_move_before_move(bank);
        }
    }
    return result;
}

void move_on_modify_move(u8 attacker, u8 defender, u16 move)
{
    if (moves[move].on_modify_move)
        moves[move].on_modify_move(attacker, defender, move);
}

extern void run_residual_cbs(u8 bank);
extern void hpbar_apply_dmg(u8 task_id);
void run_move()
{
    if (task_is_running(hpbar_apply_dmg))
        return;
    while (peek_message())
        return;
    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    switch(super.multi_purpose_state_tracker) {
        case S_BEFORE_MOVE:
        {
            u8 result = before_move_cb(bank_index);
            switch (result) {
                case CANT_USE_MOVE:
                case TARGET_MOVE_IMMUNITY:
                    super.multi_purpose_state_tracker = S_PP_REDUCTION;
                    return;
            };
            u16 move = CURRENT_MOVE(bank_index);
            if (!move) {
                set_callback1(run_decision);
                super.multi_purpose_state_tracker = S_RUN_FAINT;
                break;
            }
            // display "Pokemon used move!"
            enqueue_message(CURRENT_MOVE(bank_index), bank_index, STRING_ATTACK_USED, 0);
            super.multi_purpose_state_tracker = S_BEFORE_MOVE_ABILITY;
            break;
        }
        case S_BEFORE_MOVE_ABILITY: /* use_move() is inlined */
            // Modify move callbacks
            move_on_modify_move(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index));
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
            super.multi_purpose_state_tracker = S_MOVE_TRYHIT;
            break;
        case S_PP_REDUCTION:
        {
            // reduce PP
            u8 pp_index = p_bank[bank_index]->b_data.pp_index;
            u8 pp = pokemon_getattr(p_bank[bank_index]->this_pkmn, pp_index + REQUEST_PP1, NULL) - 1;
            pokemon_setattr(p_bank[bank_index]->this_pkmn, pp_index + REQUEST_PP1, &pp);
            if (B_MOVE_FAILED(bank_index)) {
                run_move_failed_cbs(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index));
            }
            
            if (bank_index != battle_master->first_bank) {
                u16 player_speed = B_SPEED_STAT(PLAYER_SINGLES_BANK);
                u16 opponent_speed = B_SPEED_STAT(OPPONENT_SINGLES_BANK);
                if (player_speed > opponent_speed) {
                    run_residual_cbs(PLAYER_SINGLES_BANK);
                    run_residual_cbs(OPPONENT_SINGLES_BANK);
                } else {
                    run_residual_cbs(OPPONENT_SINGLES_BANK);
                    run_residual_cbs(PLAYER_SINGLES_BANK);
                }
            }
            super.multi_purpose_state_tracker = S_RUN_FAINT;
            set_callback1(run_decision);
            break;
        }
    };
}






