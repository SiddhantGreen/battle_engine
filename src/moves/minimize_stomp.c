#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);

u8 minimize_on_effect_cb(u8 attacker, u8 defender, u16 move)
{
    if (!(HAS_VOLATILE(attacker, VOLATILE_MINIMIZE))) {
        ADD_VOLATILE(attacker, VOLATILE_MINIMIZE);
    }
    return 1;
}


u8 stomp_on_modify_move(u8 user, u8 target, u16 move)
{
    if (HAS_VOLATILE(target, VOLATILE_MINIMIZE)) {
        B_MOVE_ACCURACY(user) = 101;
        B_MOVE_POWER(user) *= 2;
    }
    return 1;
}

