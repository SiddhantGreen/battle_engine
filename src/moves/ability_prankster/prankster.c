#include <pokeagb/pokeagb.h>
#include "../../battle_data/pkmn_bank.h"
#include "../../battle_state.h"
#include "../moves.h"

void priority_prankster_mod(u8 ability, u16 move_id, u8 bank)
{
    if (ability != ABILITY_PRANKSTER)
        return;

    if (move_t[move_id].category == MOVE_STATUS) {
        p_bank[bank]->user_action.priority++;
    }
    return;
}
