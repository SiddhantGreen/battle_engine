#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

void psywave_on_modify_move(u8 user, u8 target, u16 move)
{
	u8 level = B_LEVEL(user);
    u16 damage = NUM_MOD(level, rand_range(50, 151));
    damage = MAX(1, damage);
    B_MOVE_DMG(user) = damage;
	B_MOVE_POWER(user) = 1;
}
