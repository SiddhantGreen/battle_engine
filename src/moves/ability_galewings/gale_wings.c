#include <pokeagb/pokeagb.h>
#include "../../battle_data/pkmn_bank.h"
#include "../../battle_state.h"
#include "../moves.h"

void priority_gale_wings_mod(u8 ability, u16 move_id, u8 bank)
{
    if (ability != ABILITY_GALE_WINGS)
        return;

    if (move_t[move_id].type == MTYPE_FLYING) {
        p_bank[bank]->user_action.priority++;
    }
    return;
}
