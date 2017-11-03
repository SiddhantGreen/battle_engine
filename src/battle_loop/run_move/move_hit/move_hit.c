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
extern void dprintf(const char * str, ...);
extern void set_status(u8 bank, u8 source, enum Effect status);
extern u16 rand_range(u16, u16);
extern bool is_fainted(void);

#define MOVE_ON_HEAL 0

bool damage_result_msg(u8 bank_index)
{
    
    // effectiveness msgs
    bool effective = true;
    switch (B_MOVE_EFFECTIVENESS(bank_index)) {
        case TE_IMMUNE:
            if (!B_MOVE_MULTI(bank_index))
                enqueue_message(0, bank_index, STRING_MOVE_IMMUNE, 0);
            effective = false;
            break;
        case TE_NOT_VERY_EFFECTIVE:
            if (!B_MOVE_MULTI(bank_index))
                enqueue_message(0, 0, STRING_MOVE_NVE, 0);
            break;
        case TE_SUPER_EFFECTIVE:
            if (!B_MOVE_MULTI(bank_index))    
                enqueue_message(0, 0, STRING_MOVE_SE, 0);
            break;
        case TE_OHKO:
            if (!B_MOVE_MULTI(bank_index))    
                enqueue_message(0, 0, STRING_OHKO, 0);
            break;
        default:
            break;
    };

    if (effective) {
        // crit msg if crit
        if (B_MOVE_WILL_CRIT(bank_index)) {
            enqueue_message(0, bank_index, STRING_MOVE_CRIT, 0);
            B_MOVE_WILL_CRIT_SET(bank_index, 0);
        }
    }
    return effective;
}

enum TryHitMoveStatus {
    CANT_USE_MOVE = 0,
    USE_MOVE_NORMAL,
    TARGET_MOVE_IMMUNITY,
};

enum TryHitMoveStatus move_tryhit(u8 attacker, u8 defender, u16 move) 
{
    if (moves[move].on_tryhit_move) {
        return moves[move].on_tryhit_move(attacker, defender, move);
    }
    return USE_MOVE_NORMAL;
}

enum TryHitMoveStatus move_tryhit_side(u8 attacker, u8 defender, u16 move) 
{
    if (moves[move].on_tryhit_side_move) {
        return moves[move].on_tryhit_side_move(attacker, defender, move);
    }
    return USE_MOVE_NORMAL;
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
            // flinch means no moving
            if (rand_range(0, 100) < battle_master->b_moves[B_MOVE_BANK(bank_index)].flinch) {
                enqueue_message(0, bank_index, STRING_FLINCHED, 0);
                super.multi_purpose_state_tracker = S_RUN_FAINT;
                set_callback1(run_decision);
                return;
            }
            // move tryhit callback
            switch (move_tryhit(bank_index, TARGET_OF(bank_index), move)) {
                case CANT_USE_MOVE:
                    enqueue_message(move, bank_index, STRING_FAILED, move);
                    super.multi_purpose_state_tracker = S_PP_REDUCTION;
                    set_callback1(run_move);
                    return;
                case TARGET_MOVE_IMMUNITY:
                    enqueue_message(0, bank_index, STRING_MOVE_IMMUNE, 0);
                    super.multi_purpose_state_tracker = S_PP_REDUCTION;
                    set_callback1(run_move);
                    return;
                default:
                    break;
            };
            // move tryhit side callback
            switch (move_tryhit_side(bank_index, TARGET_OF(bank_index), move)) {
                case CANT_USE_MOVE:
                    enqueue_message(move, bank_index, STRING_FAILED, move);
                    super.multi_purpose_state_tracker = S_PP_REDUCTION;
                    set_callback1(run_move);
                    return;
                case TARGET_MOVE_IMMUNITY:
                    enqueue_message(0, bank_index, STRING_MOVE_IMMUNE, 0);
                    super.multi_purpose_state_tracker = S_PP_REDUCTION;
                    set_callback1(run_move);
                    return;
                default:
                    break;
            };
            // move landing is success
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
            if ((B_MOVE_POWER(bank_index) < 1) && (!IS_OHKO(move))) {
                super.multi_purpose_state_tracker = S_HEAL_CALC_AND_APPLY;
                return;
            }
            // get dmg
            u16 dmg = get_damage(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index));
            
            if (!damage_result_msg(bank_index)) {
                set_callback1(run_move);
                super.multi_purpose_state_tracker = S_PP_REDUCTION;
                return;
            }
            battle_master->b_moves[B_MOVE_BANK(bank_index)].dmg = dmg;
            
            // HP bar damage animation
            s16 delta = B_CURRENT_HP(TARGET_OF(bank_index)) - dmg;
            delta = MAX(delta, 0);
            hp_anim_change(TARGET_OF(bank_index), delta);
            super.multi_purpose_state_tracker = S_HEAL_CALC_AND_APPLY;
            break;
        case S_HEAL_CALC_AND_APPLY:
            /* TODO calc healing */
            if (moves[move].heal) {
                battle_master->b_moves[B_MOVE_BANK(bank_index)].heal = moves[move].heal;
            }
            
            if (battle_master->b_moves[B_MOVE_BANK(bank_index)].heal) {
                s16 delta = battle_master->b_moves[B_MOVE_BANK(bank_index)].heal;
                delta = MIN(B_CURRENT_HP(bank_index) + delta, TOTAL_HP(bank_index));
                hp_anim_change(bank_index, delta);
                enqueue_message(CURRENT_MOVE(bank_index), bank_index, STRING_HEAL, 0);
            }
            super.multi_purpose_state_tracker = S_STATUS_CHANGE;
            break;
        case S_STATUS_CHANGE:
            // something about statuses (??)
            super.multi_purpose_state_tracker = S_MOVE_EFFECT;
            break;
        case S_MOVE_EFFECT:
        {
            /* execute move effect */
            if (moves[CURRENT_MOVE(bank_index)].on_effect_cb) {
                if (!(moves[CURRENT_MOVE(bank_index)].on_effect_cb(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index)))) {
                    break;;
                }
            }
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
        {
            // set flinch chance of target
            battle_master->b_moves[B_MOVE_BANK(TARGET_OF(bank_index))].flinch = M_FLINCH(move);
            if (moves[move].procs) {
                extern void boost_procs(u8 attacker, u8 defender, u16 move);
                boost_procs(bank_index, TARGET_OF(bank_index), move);
           
                // roll secondary status chances player
                if (rand_range(0, 100) <= MOVE_SECONDARY_STATUS_CHANCE(move, bank_index)) {
                    p_bank[bank_index]->b_data.status = MOVE_SECONDARY_STATUS(move, bank_index);
                    set_status(bank_index, bank_index, MOVE_SECONDARY_STATUS(move, bank_index));
                }
                
                // roll secondary status chances target
                if (rand_range(0, 100) <= MOVE_SECONDARY_STATUS_CHANCE(move, TARGET_OF(bank_index))) {
                    p_bank[TARGET_OF(bank_index)]->b_data.status = MOVE_SECONDARY_STATUS(move, bank_index);
                    set_status(TARGET_OF(bank_index), bank_index, MOVE_SECONDARY_STATUS(move, bank_index));
                }
            }
            super.multi_purpose_state_tracker = S_AFTER_MOVE_SECONDARY;
            break;
        }
        case S_AFTER_MOVE_SECONDARY:
        // after_move_secondary
        // if multi-hit not satisfied call again
            if (battle_master->b_moves[B_MOVE_BANK(bank_index)].hit_times > 0) {
                battle_master->b_moves[B_MOVE_BANK(bank_index)].hit_times--;
                battle_master->b_moves[B_MOVE_BANK(bank_index)].hit_counter++;
                if (is_fainted()) {
                    dprintf("Fainted on %d hits\n", battle_master->b_moves[B_MOVE_BANK(bank_index)].hit_counter);
                    battle_master->b_moves[B_MOVE_BANK(bank_index)].hit_times = 0;
                    super.multi_purpose_state_tracker = S_AFTER_MOVE_SECONDARY;
                } else {
                    super.multi_purpose_state_tracker = S_MOVE_TRYHIT;
                }
            } else {
                if (battle_master->b_moves[B_MOVE_BANK(bank_index)].hit_counter > 0) {
                    u16 temp = battle_master->b_moves[B_MOVE_BANK(bank_index)].hit_counter;
                    battle_master->b_moves[B_MOVE_BANK(bank_index)].hit_counter = 1;
                    battle_master->b_moves[B_MOVE_BANK(bank_index)].hit_times = 1;
                    damage_result_msg(bank_index);
                    battle_master->b_moves[B_MOVE_BANK(bank_index)].hit_counter = temp;
                    enqueue_message(0, 0, STRING_MULTI_HIT, battle_master->b_moves[B_MOVE_BANK(bank_index)].hit_counter);
                }
                super.multi_purpose_state_tracker = S_AFTER_MOVE;
            }
            break;
        case S_AFTER_MOVE:
        // after move
            if (moves[move].on_after_move) {
                moves[move].on_after_move(bank_index);
            }
            super.multi_purpose_state_tracker = S_PP_REDUCTION;
            set_callback1(run_move);
            break;
    };
}


