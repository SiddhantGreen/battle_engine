#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);

u8 rolling_kick_on_modify_move(u8 user, u8 target, u16 move)
{
    /* TODO How to handle substitute!*/
    return 1;
}