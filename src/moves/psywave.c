#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern u16 rand_range(u16 min, u16 max);

void psywave_on_damage_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	u8 level = B_LEVEL(user);
    u16 damage = NUM_MOD(level, rand_range(50, 151));
    damage = MAX(1, damage);
    B_MOVE_DMG(user) = damage;
}
