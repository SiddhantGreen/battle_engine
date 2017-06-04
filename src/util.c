#include <pokeagb/pokeagb.h>
#include "moves/moves.h"

u16 rand_range(u16 min, u16 max)
{
    return (rand() / (0xFFFF / (max - min))) + min;
}

bool knows_move(u16 move_id, struct Pokemon* p)
{
    u8 i;
    for (i = REQUEST_MOVE1; i < (REQUEST_MOVE1 + 4); i++) {
        u16 move = pokemon_getattr(p, i, NULL);
        if (move == move_id)
            return true;
    }
    return false;
}

u8 get_side(u8 bank)
{
    return (bank > 1) ? 1 : 0;
}

u8 get_ability(struct Pokemon* p)
{
    u8 ability_bit = pokemon_getattr(p, REQUEST_ABILITY_BIT, NULL);
    return pokemon_base_stats[pokemon_getattr(p, REQUEST_SPECIES, NULL)].ability[ability_bit];
}

bool ignoring_item(struct Pokemon* p)
{
    return (get_ability(p) == ABILITY_KLUTZ);
}

/* TODO: Update this function. Hard coded and too short sighted */
u8 move_target(u8 bank, u16 move_id)
{
    if (*(move_t[move_id].m_flags) & FLAG_ONSELF) {
        return bank;
    } else {
        return (bank) ? 0 : 2;
    }
}
