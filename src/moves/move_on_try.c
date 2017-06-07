#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_state.h"
#include "moves/moves.h"
#include "../battle_text/battle_pick_message.h"

extern u8 get_target_bank(u8 user_bank, u16 move_id);
extern u16 rand_range(u16 min, u16 max);
extern u8 get_ability(struct Pokemon* p);
extern void task_add_bmessage(u8 task_id);
extern bool ignoring_item(struct Pokemon* p);
extern u8 get_side(u8 bank);

void ally_switch_tryhit(u8 user_bank)
{
    /* TODO: Double battles not implemented yet */
}


void aurora_veil_tryhit(u8 user_bank)
{
    if (battle_master->field_state.is_hail) {
        battle_master->field_state.aurora_veil = get_side(user_bank) + 1;
        battle_master->field_state.aurora_veil_turns[get_side(user_bank)] = 5; // TODO: Fix for extended weather rock thing
    } else {
        u8 t_id = task_add(task_add_bmessage, 0x1);
        tasks[t_id].priv[3] = super.multi_purpose_state_tracker + 1;
        tasks[t_id].priv[4] = STRING_FAILED_ALONE;
        super.multi_purpose_state_tracker = 99;
    }
}

void protection_tryhit(u8 user_bank)
{
    if (p_bank[user_bank]->user_action.times_protected) {
        if (!(rand_range(0, 100) < (p_bank[user_bank]->user_action.times_protected * 2))) {
            u8 t_id = task_add(task_add_bmessage, 0x1);
            tasks[t_id].priv[3] = super.multi_purpose_state_tracker + 1;
            tasks[t_id].priv[4] = STRING_FAILED_ALONE;
            super.multi_purpose_state_tracker = 99;
        }
    }
    p_bank[user_bank]->user_action.times_protected++;
    p_bank[user_bank]->user_action.used_protect = true;
}

void brick_break_tryhit(u8 user_bank)
{
    u8 opp_bank = user_bank ? 0 : 2;
    if (battle_master->field_state.reflect & (get_side(opp_bank) + 1))
        battle_master->field_state.reflect &= !(get_side(opp_bank) + 1);
        
    if (battle_master->field_state.lightscreen & (get_side(opp_bank) + 1))
        battle_master->field_state.lightscreen &= !(get_side(opp_bank) + 1);
        
    if (battle_master->field_state.aurora_veil & (get_side(opp_bank) + 1))
        battle_master->field_state.aurora_veil &= !(get_side(opp_bank) + 1);

    
    battle_master->field_state.reflect_turns[get_side(opp_bank)] = 0;
    battle_master->field_state.lightscreen_turns[get_side(opp_bank)] = 0;
    battle_master->field_state.aurora_veil_turns[get_side(opp_bank)] = 0;

}



















