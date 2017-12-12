#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);

u8 minimize_on_effect_cb(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (!(HAS_VOLATILE(user, VOLATILE_MINIMIZE))) {
        ADD_VOLATILE(user, VOLATILE_MINIMIZE);
    }
    return true;
}


u8 stomp_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_MINIMIZE)) {
        B_MOVE_ACCURACY(user) = 101;
        B_MOVE_POWER(user) *= 2;
    }
    return true;
}

u8 bodyslam_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_MINIMIZE)) {
        B_MOVE_ACCURACY(user) = 101;
        B_MOVE_POWER(user) *= 2;
    }
    return true;
}
