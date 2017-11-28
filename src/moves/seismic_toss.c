#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

u8 seismic_toss_on_modify_move(u8 user, u8 target, u16 move)
{
    B_MOVE_DMG(user) = B_LEVEL(user);
    B_MOVE_POWER(user) = 1;
    return 1;
}
