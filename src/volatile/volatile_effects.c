#include <pokeagb/pokeagb.h>
#include "residual_effects.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern void hp_anim_change(u8 bank, s16 delta);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

void residual_cbs_init()
{
    for (u8 i = 0; i < 20; i++) {
        residual_callbacks[i].func = NULL;
    }
}


u8 residual_cb_find_free()
{
    for (u8 i = 0; i < 20; i++) {
        if (residual_callbacks[i].func == NULL) {
            return i;
        }
    }
    return 0xFF;
}


u8 add_residual_cb(ResidualFunc to_add)
{
    u8 available_index = residual_cb_find_free();
    if (available_index != 0xFF) {
        residual_callbacks[available_index].func = to_add;
    }
    return available_index;
}


void remove_residual_cb(u8 id)
{
    residual_callbacks[id].func = NULL;
    return;
}


void run_residual_cbs(u8 attacker)
{
    for (u8 i = 0; i < 20; i++) {
        if (residual_callbacks[i].func) {
            if (residual_callbacks[i].effective_bank == attacker) {
                residual_callbacks[i].func(i);
            }
        }
    }
    return;
}


void apply_residual_dmg(u8 id)
{
    u8 bank = residual_callbacks[id].effective_bank;
    battle_master->b_moves[B_MOVE_BANK(bank)].dmg += residual_callbacks[id].hp_delta;
    
    // HP bar damage animation
    s16 delta = B_CURRENT_HP(bank) - residual_callbacks[id].hp_delta;
    delta = MAX(delta, 0);
    hp_anim_change(bank, delta);
    enqueue_message(residual_callbacks[id].move_id, bank, STRING_RESIDUAL_DMG, 0);
    residual_callbacks[id].active_counter--;
    if (residual_callbacks[id].active_counter < 1) {
        residual_callbacks[id].func = NULL;
        REMOVE_VOLATILE(bank, residual_callbacks[id].status);
    }
}


void apply_residual_heal(u8 id)
{
    u8 bank = residual_callbacks[id].effective_bank;
    
    // HP bar damage animation
    s16 delta = B_CURRENT_HP(bank) + residual_callbacks[id].hp_delta;
    delta = MAX(delta, 0);
    hp_anim_change(bank, delta);
    enqueue_message(residual_callbacks[id].move_id, bank, STRING_RESIDUAL_DMG, 0);
    residual_callbacks[id].active_counter--;
    if (residual_callbacks[id].active_counter < 1) {
        residual_callbacks[id].func = NULL;
        REMOVE_VOLATILE(bank, residual_callbacks[id].status);
    }
}



