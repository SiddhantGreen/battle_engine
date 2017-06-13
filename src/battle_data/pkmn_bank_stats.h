#ifndef PKMN_BANK_STAT_H_
#define PKMN_BANK_STAT_H_

#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_state.h"
#include "moves/moves.h"
#include "battle_text/battle_pick_message.h"


/* 
 * Get Pokemon's current battle stats based on stage changes to stat 
 *
 */
#define B_ATTACK_STAT(bank) stage_modify_stat(p_bank[bank]->this_pkmn->atk, p_bank[bank]->b_data.attack, 0, bank)
#define B_DEFENSE_STAT(bank) stage_modify_stat(p_bank[bank]->this_pkmn->def, p_bank[bank]->b_data.defense, 1, bank)
#define B_SPEED_STAT(bank) stage_modify_stat(p_bank[bank]->this_pkmn->spd, p_bank[bank]->b_data.speed, 2, bank)
#define B_SPATTACK_STAT(bank) stage_modify_stat(p_bank[bank]->this_pkmn->spatk, p_bank[bank]->b_data.sp_atk, 3, bank)
#define B_SPDEFENSE_STAT(bank) stage_modify_stat(p_bank[bank]->this_pkmn->spdef, p_bank[bank]->b_data.sp_def, 4, bank)
#define B_ACCURACY_STAT(bank) stage_modify_stat(1, p_bank[bank]->b_data.accuracy, 5, bank)
#define B_EVASION_STAT(bank) stage_modify_stat(1, p_bank[bank]->b_data.evasion, 6, bank)
#define B_CRITCHANCE_STAT(bank) stage_modify_stat(0, p_bank[bank]->b_data.crit_mod, 7, bank)

/*
 * P_bank b_data volatile macros
 */
#define ADD_VOLATILE(bank, v) p_bank[bank]->b_data.v_status |= v
#define REMOVE_VOLATILE(bank, v) p_bank[bank]->b_data.v_status ^= v
#define HAS_VOLATILE(bank, v) p_bank[bank]->b_data.v_status & v

/*
 * P_bank b_data set and fetch macros
 *
 */
#define CURRENT_MOVE(bank) p_bank[bank]->b_data.current_move
#define LAST_MOVE(bank) p_bank[bank]->b_data.last_move
#define BANK_ABILITY(bank) p_bank[bank]->b_data.ability
#define B_MOVE_BANK(bank) (bank == battle_master->first_bank) ? 0 : 1
#define B_PKMN_TYPE(bank, index) p_bank[bank]->b_data.type[index]
#define B_CURRENT_HP(bank) p_bank[bank]->this_pkmn->current_hp
#define TOTAL_HP(x) p_bank[x]->this_pkmn->total_hp
#define B_STATUS(bank) p_bank[bank]->b_data.status
#define TARGET_OF(bank) p_bank[bank]->b_data.my_target
#define SET_CONFUSION_TURNS(bank, v) p_bank[bank]->b_data.confusion_turns = v

/*
 * General Pbank macros
 */
#define FOE_BANK(bank) bank ? 0 : 2
 
 
 
extern void update_moves(u8 bank, u16 move_id);
extern s8 ability_priority_mod(u8 bank, u16 move_id);
extern s8 ability_attack_mod(u8 bank);
extern s8 ability_defense_mod(u8 bank);
extern s8 ability_speed_mod(u8 bank);
extern s8 ability_sp_defense_mod(u8 bank);
extern s8 ability_sp_attack_mod(u8 bank);
extern s8 ability_critchance_mod(u8 bank);
extern s8 item_attack_mod(u8 bank);
extern s8 item_defense_mod(u8 bank);
extern s8 item_speed_mod(u8 bank);
extern s8 item_sp_defense_mod(u8 bank);
extern s8 item_sp_attack_mod(u8 bank);
extern s8 item_critchance_mod(u8 bank);
extern s8 item_accuracy_mod(u8 bank);
extern u16 stage_modify_stat(u16 stat, s8 mod, u8 id, u8 bank);



#endif /* PKMN_BANK_STAT_H_ */
