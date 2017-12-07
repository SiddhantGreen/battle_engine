#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

/* Tailwind */
u16 tailwind_on_speed(u8 user, u8 src, u16 stat, struct anonymous_callback* acb)
{
    if (SIDE_OF(user) != SIDE_OF(src)) return acb->data_ptr;
    if (stat == 2)
        return (acb->data_ptr << 1);
    return acb->data_ptr;
}

u8 tailwind_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((acb->duration == 0) && (acb->in_use)) {
        acb->in_use = false;
        enqueue_message(NULL, src, STRING_TAILWIND_PETER, NULL);
    }
    return true;
}

u8 tailwind_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (callback_exists_side((u32)tailwind_on_speed, src) < ANON_CB_MAX)
        return false;
    add_callback(CB_ON_STAT_MOD, 0, 4, user, (u32)tailwind_on_speed);
    add_callback(CB_ON_RESIDUAL, 0, 4, user, (u32)tailwind_on_residual);
    enqueue_message(NULL, user, STRING_TAILWIND_BLEW, NULL);
    return true;
}

/* Trick room */
