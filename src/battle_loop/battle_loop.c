#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/pkmn_bank_stats.h"
#include "battle_data/battle_state.h"
#include "moves/moves.h"
#include "battle_text/battle_pick_message.h"
#include "move_chain_states.h"

extern void run_decision(void);
extern u16 rand_range(u16 min, u16 max);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool peek_message(void);
extern void run_move(void);
extern bool b_pkmn_has_type(u8 bank, u8 type);
extern u16 get_damage(u8, u8, u16);
extern void hp_anim_change(u8 bank, s16 delta);
extern void hpbar_apply_dmg(u8 task_id);
extern void dprintf(const char * str, ...);
extern bool target_exists(u8 bank);
extern void reset_turn_bits(u8 bank);


void battle_loop()
{
    extern void battle_set_order(void);
    battle_set_order();
    set_callback1(run_decision);
}


void run_after_switch()
{
    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    ability_on_switch(bank_index);
    super.multi_purpose_state_tracker = 2;
    set_callback1(run_decision);
    return;
}

bool try_hit(u8 attacker)
{
    // if moves never misses, exit early
    u8 move_accuracy = B_MOVE_ACCURACY(attacker);
    if (move_accuracy > 100)
        return true;
    
    // if target is in semi invulnerability do checks
    u8 defender = TARGET_OF(attacker);
    if (HAS_VOLATILE(defender, VOLATILE_SEMI_INVULNERABLE)) {
        //if (moves[LAST_MOVE(defender)].move_cb->inv_tryhit_cb) {
           // if (!(moves[LAST_MOVE(defender)].move_cb->inv_tryhit_cb(CURRENT_MOVE(attacker))))
                return false;
        //}
    }

    // standard accuracy formula check
    u16 target_evasion = B_EVASION_STAT(defender);
    u16 user_accuracy = B_ACCURACY_STAT(attacker);
    
    u16 result = (user_accuracy / target_evasion) * move_accuracy;
    if (rand_range(0, 100) <= result)
        return true;
    if (target_evasion > 100) {
        enqueue_message(0, attacker, STRING_ATTACK_AVOIDED, 0);
    } else {
        enqueue_message(0, attacker, STRING_ATTACK_MISSED, 0);
    }
    return false;
}

bool is_immune(u8 attacker, u8 defender, u16 move)
{
    return false;
}

#define MOVE_TRYHIT 0
#define MOVE_TRYHIT_SIDE 0
#define MOVE_ON_HEAL 0
void move_hit()
{
    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    u16 move = CURRENT_MOVE(bank_index);
    switch(super.multi_purpose_state_tracker) {
        case 0:
        {
            bool move_hits = true;
            if (MOVE_TRYHIT) {
                // move try hit callback exec
            } else if (MOVE_TRYHIT_SIDE) {
                // move tryhit side callback exec
            }
            if (move_hits) {
                super.multi_purpose_state_tracker = 2;
            } else {
                super.multi_purpose_state_tracker++;
            }
            break;
        }
        case 1:
            if (!peek_message()) {
                super.multi_purpose_state_tracker = 1;
                set_callback1(run_move);
            }
            break;
        case 2:
            // run ability tryhits
            if (!(HAS_VOLATILE(bank_index, VOLATILE_MOLDBREAKER))) {
                if (ability_on_tryhit(bank_index, TARGET_OF(bank_index), move)) {
                    super.multi_purpose_state_tracker++;
                } else {
                    super.multi_purpose_state_tracker = 1;
                }
            } else {
                // moldbreaker means we skip ability tryhits
                super.multi_purpose_state_tracker++;
            }
            break;
        case 3:
        {
            if (!peek_message()) {
                if (try_hit(bank_index)) {
                    // check immunity
                    if (is_immune(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index))) {
                        enqueue_message(0, bank_index, STRING_MOVE_IMMUNE, 0);
                        super.multi_purpose_state_tracker = 1;
                        return;
                    } else {
                        // Skip damage checks if move doesn't do damage
                        if (B_MOVE_POWER(bank_index) < 1) {
                            super.multi_purpose_state_tracker++;
                            return;
                        }
                        
                        // get dmg
                        u16 dmg = get_damage(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index));
                        
                        // effectiveness msgs
                        switch (B_MOVE_EFFECTIVENESS(bank_index)) {
                            case TE_IMMUNE:
                                enqueue_message(0, bank_index, STRING_MOVE_IMMUNE, 0);
                                super.multi_purpose_state_tracker++;
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
                        if (B_MOVE_WILL_CRIT(bank_index)) {
                            enqueue_message(0, bank_index, STRING_MOVE_CRIT, 0);
                        }
                        
                        battle_master->b_moves[B_MOVE_BANK(bank_index)].dmg = dmg;
                        s16 delta = B_CURRENT_HP(TARGET_OF(bank_index)) - dmg;
                        delta = MAX(delta, 0);
                        hp_anim_change(TARGET_OF(bank_index), delta);
                        super.multi_purpose_state_tracker++;
                    }
                } else {
                    // move has missed
                    super.multi_purpose_state_tracker = 16;
                    set_callback1(run_move);
                }
            }
            break;
        }
        case 4:
        {
            // calculate amount to heal after dmg animation and playing messages
            if (task_is_running(hpbar_apply_dmg))
                break;
            if (!peek_message()) {
                /* TODO calc healing */
                if (MOVE_ON_HEAL) {
                    // execute callback
                    battle_master->b_moves[B_MOVE_BANK(bank_index)].heal = 0;
                }
                super.multi_purpose_state_tracker++;
            }
            break;
        }
        case 5:
        {
            // something about statuses
            if (!peek_message()) {
                super.multi_purpose_state_tracker++;
            }
            break;
        }
        case 6:
        {
            /* execute move effect */
            /*if (moves[CURRENT_MOVE(bank_index)].move_cb->on_effect_cb) {
                moves[CURRENT_MOVE(bank_index)].move_cb->on_effect_cb(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index));
            }*/
            super.multi_purpose_state_tracker++;
            break;
        }
        case 7:
        {
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
            super.multi_purpose_state_tracker++;
            break;
        }

        case 8:
        {
            if (task_is_running(hpbar_apply_dmg))
                break;
            if (!peek_message()) {
                if(battle_master->b_moves[B_MOVE_BANK(bank_index)].dmg != 0 && moves[CURRENT_MOVE(bank_index)].drain > 0 ){
                    u16 drain = NUM_MOD(battle_master->b_moves[B_MOVE_BANK(bank_index)].dmg, moves[CURRENT_MOVE(bank_index)].drain);
                    s16 delta = B_CURRENT_HP(bank_index) + drain;
                    delta = MIN(delta, TOTAL_HP(bank_index));
                    hp_anim_change(bank_index, delta);
                    enqueue_message(CURRENT_MOVE(bank_index), bank_index, STRING_DRAIN, 0);
                }
                super.multi_purpose_state_tracker++;             
            }
            
            break;
        }
        case 9:
        {
            if (task_is_running(hpbar_apply_dmg))
                break;
            if (!peek_message()) {
                super.multi_purpose_state_tracker++;
            }
            break;
        }
        case 10:
        // self hit
        
            

        case 11:
        // secondary hit
        
            
        case 12:
        // secondary roll success
        
            
        case 13:
        // after_move_secondary
        
            
        case 14:
        // after move secondary onself

        case 15:
        // after move
        case 16:
        {
        // move has missed
            super.multi_purpose_state_tracker = 5;
            set_callback1(run_move);
            break;
        }
    };
}


#define BEFORE_MOVE_CALLBACK_0 0
void run_move()
{
    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    switch(super.multi_purpose_state_tracker) {
        case 0:
        {
            u16 move = CURRENT_MOVE(bank_index);
            if (!move) {
                set_callback1(run_decision);
                super.multi_purpose_state_tracker = 4;
                break;
            }
            /* TODO :  Before move callbacks */
            if (BEFORE_MOVE_CALLBACK_0) {
                // move failed
                super.multi_purpose_state_tracker = 1;
            } else {
                enqueue_message(CURRENT_MOVE(bank_index), bank_index, STRING_ATTACK_USED, 0);
                super.multi_purpose_state_tracker = 2;
            }
            break;
        }
        case 1:
            if (!peek_message()) {
                super.multi_purpose_state_tracker = 4; // exit
                set_callback1(run_decision);
            }
            break;
        case 2:
            // Modify move callbacks
            if (!peek_message()) {
                ability_on_modify_move(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index));
                super.multi_purpose_state_tracker++;
            }
            break;
        case 3:
            if (!peek_message()) {
                // check target exists
                if (!target_exists(bank_index)) {
                    enqueue_message(0, bank_index, STRING_FAILED, 0);
                    super.multi_purpose_state_tracker = 5; // PP reduction state
                } else {
                    super.multi_purpose_state_tracker++;
                }
            }
            break;
        case 4:
            if (!peek_message()) {
                set_callback1(move_hit); // move hit will advance the state when complete
                super.multi_purpose_state_tracker = 0;
            }
            break;
        case 5:
            if (!peek_message()) {
                // reduce PP
                u8 pp_index = p_bank[bank_index]->b_data.pp_index;
                u8 pp = pokemon_getattr(p_bank[bank_index]->this_pkmn, pp_index + REQUEST_PP1, NULL) - 1;
                pokemon_setattr(p_bank[bank_index]->this_pkmn, pp_index + REQUEST_PP1, &pp);
                super.multi_purpose_state_tracker = 4;
                set_callback1(run_decision);
            }
            break;
    };
}

extern void give_exp(u8 fainted, u8 reciever);
extern void option_selection(void);
extern void on_faint(void);
extern void run_switch(void);
extern void sync_battler_struct(u8 bank);

void run_decision(void)
{
    while (peek_message())
        return;

    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    switch (super.multi_purpose_state_tracker) {
       case 0:
            set_callback1(run_switch);
            super.multi_purpose_state_tracker = 0;
            break;
        case 1:
            set_callback1(run_after_switch);
            super.multi_purpose_state_tracker = 0;
            break;
        case 2:
        {
            // once first bank's run_switch and run_after_switch have exec'd, run second bank
            if (bank_index == battle_master->second_bank) {
                // if second bank run, switch back to first bank and go to next phase
                battle_master->execution_index = 0;
                super.multi_purpose_state_tracker++;
            } else {
                battle_master->execution_index = 1;
                super.multi_purpose_state_tracker = 0;
            }
            break;
        }
        case 3:
            set_callback1(run_move);
            super.multi_purpose_state_tracker = 0;
            break;
        case 4:
            // Run on faint stuff
            set_callback1(on_faint);
            super.multi_purpose_state_tracker = S_CHECK_BANK1_FAINT;
            break;
        case 5:
            // run move for second bank after first bank is run.
            if (bank_index == battle_master->second_bank) {
                battle_master->execution_index = 0;
                super.multi_purpose_state_tracker++;
            } else {
                battle_master->execution_index = 1;
                super.multi_purpose_state_tracker = 3;
            }
            break;
        case 6:
        {
            // reset turn based bits
            reset_turn_bits(battle_master->first_bank);
            reset_turn_bits(battle_master->second_bank);
            set_callback1(option_selection);
            super.multi_purpose_state_tracker = 0;
            battle_master->execution_index = 0;
            break;
        }
        case 7:
            // TODO: free resources
            if (!peek_message()) {
                sync_battler_struct(PLAYER_SINGLES_BANK);
                exit_to_overworld_2_switch();
                set_callback1(c1_overworld);
            }
            break;
        default:
            break;
    };
}






















