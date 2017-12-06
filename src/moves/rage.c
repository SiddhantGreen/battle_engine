#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern bool b_pkmn_has_type(u8 bank, enum PokemonType type);

u8 rage_on_effect_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (p_bank[user]->b_data.last_damage > 0) {
        // +1 atk if hit
        B_USER_STAT_MOD_CHANCE(user, 0) = 100;
        B_USER_STAT_MOD_AMOUNT(user, 0) = 1;
    }
    return true;
}
