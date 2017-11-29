#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern bool b_pkmn_has_type(u8 bank, enum PokemonType type);

u8 cotton_spore_on_tryhit_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (b_pkmn_has_type(TARGET_OF(src), MTYPE_GRASS)) {
        return 0;
    } else {
        return 1;
    }
}
