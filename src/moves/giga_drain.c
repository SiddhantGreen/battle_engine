#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

u8 giga_drain_on_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)

{
	if (user != src) return true;
	B_HEAL(user) = NUM_MOD((B_MOVE_DMG(user)) 1 / 2);
	return 1;
}
