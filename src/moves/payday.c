#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);

u16 payday_ondmg(u16 dmg_taken, u8 user, u8 target, u16 move)
{
    battle_master->field_state.payday_coins = B_LEVEL(user);
    dprintf("Payday coins bonus is %d", B_LEVEL(user));
    return dmg_taken;
}