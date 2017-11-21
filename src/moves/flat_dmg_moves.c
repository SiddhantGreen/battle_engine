#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);

u8 sonic_boom_on_modify_move(u8 user, u8 target, u16 move)
{
	B_MOVE_DMG(user) = 20;
	B_MOVE_POWER(user) = 1; //dmg calc is skipped if power is 0.
	return 1;
}


