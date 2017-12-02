#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);

void sonic_boom_on_dmg(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	B_MOVE_DMG(user) = 20;
}
