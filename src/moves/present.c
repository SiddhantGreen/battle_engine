#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern u16 rand_range(u16, u16);

u8 present_on_tryhit_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)

{
	if (user != src) return 1;
	u8 target = TARGET_OF(user);
	u16 rand_num = rand_range(0, 100);
	{
		if (rand_num < 20) {
			B_HEAL(TARGET_OF(user)) = 25;
		}
		else if (rand_num < 60) {
			B_MOVE_POWER(user) = 40;
		}
		else if (rand_num < 90) {
			B_MOVE_POWER(user) = 80;
		}
		else if (rand_num >= 90) {
			B_MOVE_POWER(user) = 120;
		}
	}
}
