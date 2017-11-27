#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool b_pkmn_has_type(u8 bank, enum PokemonType type);
extern bool b_pkmn_set_type(u8 bank, enum PokemonType type);
extern bool b_pkmn_add_type(u8 bank, enum PokemonType type);

u8 conversion_on_effect(u8 attacker, u8 defender, u16 move)
{
    // get type of move in first slot
    u16 first_move = pokemon_getattr(B_PKMN(attacker), REQUEST_MOVE1, NULL);
    u8 type = moves[first_move].type;
    if (b_pkmn_has_type(attacker, type)) {
        return false;
    }

    // X transformed\ninto the Y type!
    enqueue_message(move, attacker, STRING_CONVERSION_TYPE, type);
    return b_pkmn_set_type(attacker, type);
}
