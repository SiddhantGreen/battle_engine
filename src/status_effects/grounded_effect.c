#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_loop/move_chain_states.h"

extern bool b_pkmn_has_type(u8 bank, enum PokemonType type);
/* Largely TODO. Must revist as these effects are implemented. */
bool is_grounded(u8 bank) {
    // gravity in effect, true
    // ingrain in effect true
    // smackdown in effect on bank true
    // ironball active true
    // roost active true
    // levitate active here false
    // Magnet rise here false
    // telekinesis here false
    // if air balloon true
    // false
    if (b_pkmn_has_type(bank, MTYPE_FLYING)) return false;
    return true;
}
