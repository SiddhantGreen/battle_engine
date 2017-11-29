#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../battle_loop/move_chain_states.h"

extern void dprintf(const char * str, ...);
extern u16 rand_range(u16 min, u16 max);
extern void do_damage(u8 bank_index, u16 dmg);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

void bind_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user == src) return true;
    if (acb->duration == 0) {
        CLEAR_VOLATILE(user, VOLATILE_BIND);
        return;
    }
    enqueue_message(MOVE_BIND, user, STRING_RESIDUAL_DMG, 0);
    do_damage(user, MAX(1, (TOTAL_HP(user) / 8)));
}

u8 bind_on_effect_cb(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 defender = TARGET_OF(user);
    // the bind effect timer does not reset upon using bind again
    if (HAS_VOLATILE(defender, VOLATILE_BIND)) {
        return true;
    }
    add_callback(CB_ON_RESIDUAL, 0, rand_range(4, 6), src, (u32)bind_on_residual);
    return true;
}
