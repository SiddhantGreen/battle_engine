#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void do_heal(u8 bank_index, u8 percent_heal);

/* Ingrain */
u8 ingrain_on_residual(u8 user, u8 src, u16 status_id, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (B_CURRENT_HP(user) != TOTAL_HP(user)) {
        do_heal(user, 6);
        enqueue_message(NULL, user, STRING_HEAL, 0);
        p_bank[user]->b_data.is_grounded = true;
    }
    return true;
}

u8 ingrain_on_effect(u8 user, u8 src, u16 status_id, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (has_callback_src((u32)ingrain_on_residual, user)) return false;
    add_callback(CB_ON_RESIDUAL, 0, 0xFF, user, (u32)ingrain_on_residual);
    enqueue_message(NULL, user, STRING_ROOTS_PLANTED, 0);
    return true;
}

/* Smack down */
/* Roost */
/* Rotiller */
/* Thousand Arrows */
