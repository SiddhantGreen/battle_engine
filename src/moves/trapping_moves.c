#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void do_damage(u8 bank_index, u16 dmg);

u8 infestation_on_residual(u8 user, u8 src, u16 status_id, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (B_CURRENT_HP(user) != TOTAL_HP(user)) {
        u16 dmg = MAX((TOTAL_HP(user) >> 3), 1);
        do_damage(user, dmg);
        enqueue_message(MOVE_INFESTATION, user, STRING_RESIDUAL_DMG, 0);
    }
    if (acb->duration == 0) {
        CLEAR_VOLATILE(user, VOLATILE_TRAPPED);
    }
    return true;
}

u8 infestation_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (has_callback_src((u32)infestation_on_residual, TARGET_OF(user))) return true;
    ADD_VOLATILE(TARGET_OF(user), VOLATILE_TRAPPED);
    add_callback(CB_ON_RESIDUAL, 0, rand_range(4, 6), TARGET_OF(user), (u32)infestation_on_residual);
    enqueue_message(NULL, TARGET_OF(user), STRING_INFESTATION, 0);
    return true;
}
