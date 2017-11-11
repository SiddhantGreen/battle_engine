#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);

u8 ohko_tryhit_move(u8 user, u8 target, u16 move)
{
    if (B_LEVEL(user) < B_LEVEL(target)) {
        return 0; // CANT_USE_MOVE
    } else {
        B_MOVE_ACCURACY(user) = B_LEVEL(user) - B_LEVEL(target) + 30;
        return 1; // USE_MOVE_NORMAL
    }
}

