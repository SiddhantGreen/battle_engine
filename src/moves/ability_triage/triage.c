#include <pokeagb/pokeagb.h>
#include "../../battle_data/pkmn_bank.h"
#include "../../battle_state.h"
#include "../moves.h"

void priority_triage_mod(u8 ability, u16 move_id, u8 bank)
{
    if (ability != ABILITY_TRIAGE)
        return;

    if (*(move_t[move_id].m_flags) | FLAG_TRIAGE_AFFECTED) {
        p_bank[bank]->user_action.priority++;
    }
    return;
}
