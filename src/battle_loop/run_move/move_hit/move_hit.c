#include <pokeagb/pokeagb.h>
#include "../../../battle_data/pkmn_bank.h"
#include "../../../battle_data/pkmn_bank_stats.h"
#include "../../../battle_data/battle_state.h"
#include "../../../moves/moves.h"
#include "../../../battle_text/battle_pick_message.h"
#include "../../move_chain_states.h"


extern void run_decision(void);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool peek_message(void);
extern void run_move(void);
extern bool try_hit(u8 bank);
extern bool target_exists(u8 bank);
extern bool is_immune(u8 attacker, u8 defender, u16 move);
extern u16 get_damage(u8 attacker, u8 defender, u16 move);
extern void hp_anim_change(u8 bank, s16 delta);
extern void hpbar_apply_dmg(u8 task_id);
extern void set_status(u8 bank, u8 source, enum Effect status);

#define MOVE_TRYHIT 0
#define MOVE_TRYHIT_SIDE 0
#define MOVE_ON_HEAL 0

void damage_result_msg(u8 bank_index)
{
    // effectiveness msgs
    switch (B_MOVE_EFFECTIVENESS(bank_index)) {
        case TE_IMMUNE:
            enqueue_message(0, bank_index, STRING_MOVE_IMMUNE, 0);
            super.multi_purpose_state_tracker = S_PP_REDUCTION;
            set_callback1(run_move);
            return;
            break;
        case TE_NOT_VERY_EFFECTIVE:
            enqueue_message(0, 0, STRING_MOVE_NVE, 0);
            break;
        case TE_SUPER_EFFECTIVE:
            enqueue_message(0, 0, STRING_MOVE_SE, 0);
            break;
        default:
            break;
    };
    
    // crit msg if crit
    if (B_MOVE_WILL_CRIT(bank_index))
        enqueue_message(0, bank_index, STRING_MOVE_CRIT, 0);
}

void move_hit()
{
    if (task_is_running(hpbar_apply_dmg))
        return;
    while (peek_message())
        return;
        
    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    u16 move = CURRENT_MOVE(bank_index);
    switch (super.multi_purpose_state_tracker) {
        case S_MOVE_TRYHIT: 
            if (MOVE_TRYHIT) {
                // move try hit callback exec
                super.multi_purpose_state_tracker = S_PP_REDUCTION;
                set_callback1(run_move);
                return;
            } else if (MOVE_TRYHIT_SIDE) {
                // move tryhit side callback exec
                super.multi_purpose_state_tracker = S_PP_REDUCTION;
                set_callback1(run_move);
                return;
            }
            super.multi_purpose_state_tracker = S_ABILITY_TRYHIT;
            break;
        case S_ABILITY_TRYHIT:
            // run ability tryhits
            if (HAS_VOLATILE(bank_index, VOLATILE_MOLDBREAKER)) {
                // moldbreaker means we skip ability tryhits
                super.multi_purpose_state_tracker = S_GENERAL_TRYHIT;
                break;
            }
            if (ability_on_tryhit(bank_index, TARGET_OF(bank_index), move)) {
                super.multi_purpose_state_tracker = S_GENERAL_TRYHIT;
            } else {
                super.multi_purpose_state_tracker = S_PP_REDUCTION;
                set_callback1(run_move);
                return;
            }
            break;
        case S_GENERAL_TRYHIT:
            if (!try_hit(bank_index)) {
                // move has missed
                super.multi_purpose_state_tracker = S_PP_REDUCTION;
                set_callback1(run_move);
                return;
            }
            super.multi_purpose_state_tracker = S_IMMUNITY_CHECK;
            break;
        case S_IMMUNITY_CHECK:
            // check immunity
            if (is_immune(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index))) {
                enqueue_message(0, bank_index, STRING_MOVE_IMMUNE, 0);
                super.multi_purpose_state_tracker = S_PP_REDUCTION;
                set_callback1(run_move);
                return;
            }
            super.multi_purpose_state_tracker = S_DAMAGE_CALC_AND_APPLY;
            break;
        case S_DAMAGE_CALC_AND_APPLY:
            // Skip damage checks if move doesn't do damage
            if (B_MOVE_POWER(bank_index) < 1) {
                super.multi_purpose_state_tracker = S_HEAL_CALC_AND_APPLY;
                return;
            }
            // get dmg
            u16 dmg = get_damage(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index));
            damage_result_msg(bank_index);
            battle_master->b_moves[B_MOVE_BANK(bank_index)].dmg = dmg;
            
            // HP bar damage animation
            s16 delta = B_CURRENT_HP(TARGET_OF(bank_index)) - dmg;
            delta = MAX(delta, 0);
            hp_anim_change(TARGET_OF(bank_index), delta);
            super.multi_purpose_state_tracker = S_HEAL_CALC_AND_APPLY;
            break;
        case S_HEAL_CALC_AND_APPLY:
            /* TODO calc healing */
            if (MOVE_ON_HEAL) {
                // execute callback
                battle_master->b_moves[B_MOVE_BANK(bank_index)].heal = 0;
            }
            super.multi_purpose_state_tracker = S_STATUS_CHANGE;
            break;
        case S_STATUS_CHANGE:
            // something about statuses
            super.multi_purpose_state_tracker = S_MOVE_EFFECT;
            break;
        case S_MOVE_EFFECT:
        {
            /* execute move effect */
            /*if (moves[CURRENT_MOVE(bank_index)].move_cb->on_effect_cb) {
                moves[CURRENT_MOVE(bank_index)].move_cb->on_effect_cb(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index));
            }*/
            super.multi_purpose_state_tracker = S_RECOIL_APPLY;
            break;
        }
        case S_RECOIL_APPLY:
            // check for recoil
            if (battle_master->b_moves[B_MOVE_BANK(bank_index)].dmg != 0 && moves[CURRENT_MOVE(bank_index)].recoil > 0) {
                u16 recoil = NUM_MOD(battle_master->b_moves[B_MOVE_BANK(bank_index)].dmg, moves[CURRENT_MOVE(bank_index)].recoil);
                s16 delta = B_CURRENT_HP(bank_index) - recoil;
                delta = MAX(delta, 0);
                hp_anim_change(bank_index, delta);
                enqueue_message(CURRENT_MOVE(bank_index), bank_index, STRING_RECOIL, 0);
            } else if (moves[CURRENT_MOVE(bank_index)].recoil_struggle) {
                // struggle recoil is based off max health
                u16 recoil = NUM_MOD(TOTAL_HP(bank_index), 25);
                s16 delta = B_CURRENT_HP(bank_index) - recoil;
                delta = MAX(delta, 0);
                hp_anim_change(bank_index, delta);
                enqueue_message(CURRENT_MOVE(bank_index), bank_index, STRING_RECOIL, 0);
            }
            super.multi_purpose_state_tracker = S_DRAIN_APPLY;
            break;
        case S_DRAIN_APPLY:
        {
            if (battle_master->b_moves[B_MOVE_BANK(bank_index)].dmg != 0 && moves[CURRENT_MOVE(bank_index)].drain > 0 ){
                u16 drain = NUM_MOD(battle_master->b_moves[B_MOVE_BANK(bank_index)].dmg, moves[CURRENT_MOVE(bank_index)].drain);
                s16 delta = B_CURRENT_HP(bank_index) + drain;
                delta = MIN(delta, TOTAL_HP(bank_index));
                hp_anim_change(bank_index, delta);
                enqueue_message(CURRENT_MOVE(bank_index), bank_index, STRING_DRAIN, 0);
            }
            super.multi_purpose_state_tracker = S_SECONDARY_ROLL_CHANCE;            
            break;
        }
        case S_SECONDARY_ROLL_CHANCE: /* TODO perhaps bundle secondary effects into own file. It will be rather large */
        // Roll secondary boosts self  
            super.multi_purpose_state_tracker = S_SECONDARY_ON_HIT;
            
        case S_SECONDARY_ON_HIT:
        // secondary on hit callback (i.e contrary)
        
        case S_AFTER_MOVE_SECONDARY:
        // after_move_secondary

        case S_AFTER_MOVE:
        // after move
        
        super.multi_purpose_state_tracker = S_PP_REDUCTION;
        set_callback1(run_move);
        break;
    };
}


