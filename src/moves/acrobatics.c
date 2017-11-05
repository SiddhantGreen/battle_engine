#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
u8 acrobatics_on_base_power_move(u8 base_power, u8 user, u8 target, u16 move)
{
    if (B_GET_ITEM(user) != 0) {
        dprintf("User was holding item %d. 55 BP\n", B_GET_ITEM(user));
        return 55;
    } else {
		dprintf("User was not holding an item, 110 BP!");
        return 110;
    }
}