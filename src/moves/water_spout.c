#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
void water_spout_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    B_MOVE_POWER(user) = (B_CURRENT_HP(user) * 150) / TOTAL_HP(user);
}
