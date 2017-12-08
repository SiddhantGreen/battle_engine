#include <pokeagb/pokeagb.h>
#include "../../battle_data/pkmn_bank.h"
#include "../../battle_data/pkmn_bank_stats.h"
#include "../../battle_data/battle_state.h"
#include "../../moves/moves.h"
#include "../../battle_text/battle_pick_message.h"
#include "../move_chain_states.h"
#include "../../status_effects/status.h"

extern void run_decision(void);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool peek_message(void);
extern void move_hit(void);
extern void on_faint(void);
extern bool target_exists(u8 bank);
extern void run_move_failed_cbs(u8 attacker, u8 defender, u16 move);
extern void do_residual_status_effects(u8 order);
extern void dprintf(const char * str, ...);
extern void c1_residual_status_effects(void);
extern void hpbar_apply_dmg(u8 task_id);

enum BeforeMoveStatus {
    CANT_USE_MOVE = 0,
    USE_MOVE_NORMAL,
    TARGET_MOVE_IMMUNITY,
};


enum BeforeMoveStatus before_move_cb(u8 attacker)
{
    u16 move = CURRENT_MOVE(attacker);
    // add callbacks specific to field
    if (moves[move].before_move) {
        add_callback(CB_ON_BEFORE_MOVE, 0, 0, attacker, (u32)moves[move].before_move);
    }
    // run callbacks
    build_execution_order(CB_ON_BEFORE_MOVE);
    battle_master->executing = true;
    while (battle_master->executing) {
        enum BeforeMoveStatus status = pop_callback(attacker, move);
        if (status != USE_MOVE_NORMAL)
            return status;
    }
    return USE_MOVE_NORMAL;
}

bool on_modify_move(u8 attacker, u8 defender, u16 move)
{
    // add callbacks specific to field
    if (moves[move].on_modify_move) {
        add_callback(CB_ON_MODIFY_MOVE, 0, 0, attacker, (u32)moves[move].on_modify_move);
    }
    // run callbacks
    build_execution_order(CB_ON_MODIFY_MOVE);
    battle_master->executing = true;
    while (battle_master->executing) {
        if (!(pop_callback(attacker, move)))
            return false;
    }
    return true;
}


void run_move()
{
    while (peek_message())
        return;
    if (task_is_running(hpbar_apply_dmg))
        return;
    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    switch(super.multi_purpose_state_tracker) {
        case S_BEFORE_MOVE:
        {
            if (HAS_VOLATILE(bank_index, VOLATILE_RECHARGING)) {
                super.multi_purpose_state_tracker = S_RESIDUAL_MOVES;
                CLEAR_VOLATILE(bank_index, VOLATILE_RECHARGING);
                enqueue_message(0, bank_index, STRING_MUST_RECHARGE, 0);
                return;
            }
			/* status ailments before move callbacks */
			if (B_STATUS(bank_index) != AILMENT_NONE) {
				if (statuses[B_STATUS(bank_index)].on_before_move) {
					statuses[B_STATUS(bank_index)].on_before_move(bank_index);
				}
			}

            if (B_PSTATUS(bank_index) != AILMENT_NONE) {
                if (statuses[B_PSTATUS(bank_index)].on_before_move)
                    statuses[B_PSTATUS(bank_index)].on_before_move(bank_index);
            }
            u8 result = before_move_cb(bank_index);
            switch (result) {
                case CANT_USE_MOVE:
                case TARGET_MOVE_IMMUNITY:
                    enqueue_message(0, bank_index, STRING_FAILED, 0);
                    super.multi_purpose_state_tracker = S_MOVE_FAILED;
                    return;
            };

			/* Residual effects which cause turn ending */
			super.multi_purpose_state_tracker = S_RESIDUAL_STATUS;
			if (HAS_VOLATILE(bank_index, VOLATILE_SLEEP_TURN)) {
				enqueue_message(0, bank_index, STRING_FAST_ASLEEP, 0);
				return;
			} else if (HAS_VOLATILE(bank_index, VOLATILE_CONFUSE_TURN)) {
				return;
			} else if (HAS_VOLATILE(bank_index, VOLATILE_ATK_SKIP_TURN)) {
                CLEAR_VOLATILE(bank_index, VOLATILE_ATK_SKIP_TURN);
                return;
            } else if (HAS_VOLATILE(bank_index, VOLATILE_CHARGING)) {
                return;
            } else {
				// display "Pokemon used move!"
				enqueue_message(CURRENT_MOVE(bank_index), bank_index, STRING_ATTACK_USED, 0);
				super.multi_purpose_state_tracker = S_BEFORE_MOVE_ABILITY;
			}
            break;
        }
        case S_BEFORE_MOVE_ABILITY: /* use_move() is inlined */
            // Modify move callbacks
            if (on_modify_move(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index))) {
                super.multi_purpose_state_tracker++;
            } else {
                enqueue_message(0, bank_index, STRING_FAILED, 0);
                super.multi_purpose_state_tracker = S_MOVE_FAILED;
            }
            break;
        case S_CHECK_TARGET_EXISTS:
            // check target exists
            if (!target_exists(bank_index)) {
                enqueue_message(0, bank_index, STRING_FAILED, 0);
                super.multi_purpose_state_tracker = S_MOVE_FAILED;
            } else {
                super.multi_purpose_state_tracker++;
            }
            break;
        case S_RUN_MOVE_HIT:
            // reduce PP
            if (!(HAS_VOLATILE(bank_index, VOLATILE_MULTI_TURN))) {
                u8 pp_index = p_bank[bank_index]->b_data.pp_index;
                u8 pp = pokemon_getattr(p_bank[bank_index]->this_pkmn, pp_index + REQUEST_PP1, NULL) - 1;
                pokemon_setattr(p_bank[bank_index]->this_pkmn, pp_index + REQUEST_PP1, &pp);
            }
            set_callback1(move_hit); // move hit will advance the state when complete
            super.multi_purpose_state_tracker = S_MOVE_TRYHIT;
            break;
        case S_MOVE_FAILED:
        {
            if (B_MOVE_FAILED(bank_index)) {
                run_move_failed_cbs(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index));
            }
            battle_master->field_state.last_used_move = CURRENT_MOVE(bank_index);
            super.multi_purpose_state_tracker = S_RUN_FAINT;
            break;
        }
        case S_RUN_FAINT:
            // Run on faint stuff
            set_callback1(on_faint);
            super.multi_purpose_state_tracker = S_CHECK_BANK1_FAINT;
            break;
        case S_RESIDUAL_MOVES:
        {
            if (bank_index != battle_master->first_bank) {
                extern void c1_residual_callbacks(void);
                set_callback1(c1_residual_callbacks);
                super.multi_purpose_state_tracker = 0;
                return;
            }
            super.multi_purpose_state_tracker = S_RESIDUAL_STATUS;
            break;
        }
        case S_RESIDUAL_STATUS:
        {
            if (bank_index != battle_master->first_bank) {
                set_callback1(c1_residual_status_effects);
                super.multi_purpose_state_tracker = 0;
                return;
            }
            super.multi_purpose_state_tracker = S_WAIT_HPUPDATE_RUN_MOVE;
            break;
        }
        case S_WAIT_HPUPDATE_RUN_MOVE:
        {
          /* Passive residual effects from engine structs */
          for (u8 i = 0; i < 4; i++) {
          	if (p_bank[bank_index]->b_data.disabled_moves[i] > 0) {
          		p_bank[bank_index]->b_data.disabled_moves[i]--;
          	}
          }
          u8 index = p_bank[bank_index]->b_data.disable_used_on_slot;
          if (index < 4) {
          	if (!(p_bank[bank_index]->b_data.disabled_moves[index])) {
          		p_bank[bank_index]->b_data.disable_used_on_slot = 0xFF;
          	}
          }
          LAST_MOVE(bank_index) = CURRENT_MOVE(bank_index);
          // update moves used history
          for (u8 i = 0; i < 4; i++) {
          	if (p_bank[bank_index]->b_data.moves_used[i] == LAST_MOVE(bank_index))
          		break;;
          	if (p_bank[bank_index]->b_data.moves_used[i] == MOVE_NONE) {
          		p_bank[bank_index]->b_data.moves_used[i] = LAST_MOVE(bank_index);
          		break;
          	}
          }

          super.multi_purpose_state_tracker = S_RUN_MOVE_ALTERNATE_BANK;
          set_callback1(run_decision);
          break;
        }
    };
}


void c1_residual_callbacks()
{
    while (peek_message())
		return;
	if (task_is_running(hpbar_apply_dmg))
		return;

	switch (super.multi_purpose_state_tracker) {
        case 0:
        {
            u16 player_speed = B_SPEED_STAT(PLAYER_SINGLES_BANK);
            u16 opponent_speed = B_SPEED_STAT(OPPONENT_SINGLES_BANK);
            battle_master->bank_state = (player_speed < opponent_speed) ? PLAYER_SINGLES_BANK : OPPONENT_SINGLES_BANK;
            build_execution_order(CB_ON_RESIDUAL);
            battle_master->executing = true;
            super.multi_purpose_state_tracker++;
            break;
        }
        case 1:
        {
            if (battle_master->executing) {
                battle_master->bank_state  = FOE_BANK(battle_master->bank_state);
                run_callback(battle_master->bank_state , CURRENT_MOVE(battle_master->bank_state ));
                super.multi_purpose_state_tracker++;
            } else {
                super.multi_purpose_state_tracker = 3;
            }
            break;
        }
        case 2:
        {
            if (battle_master->executing) {
                battle_master->bank_state  = FOE_BANK(battle_master->bank_state);
                pop_callback(battle_master->bank_state , CURRENT_MOVE(battle_master->bank_state ));
                super.multi_purpose_state_tracker = 1;
            } else {
                super.multi_purpose_state_tracker = 3;
            }
            break;
        }
        case 3:
            set_callback1(run_move);
            super.multi_purpose_state_tracker = S_RESIDUAL_STATUS;
            break;
        };
}
