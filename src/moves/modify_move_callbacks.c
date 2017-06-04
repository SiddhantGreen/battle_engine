#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_state.h"
#include "moves/moves.h"
#include "../battle_text/battle_pick_message.h"

extern bool pkmn_has_type(u16 species, enum PokemonType type);
extern void add_residual_effect(ResidualEffectCallback effect, u8 bank, u8 t_bank, u8 priority);
extern u8 get_opponent_side(u8 bank);


void blizzard_modify_move_cb(u8 user_bank)
{
    if (battle_master->field_state.is_hail) {
        battle_master->b_moves[0].accuracy_override = -1;
    }
}



extern void curse_residual_effect(u8 task_id);
void curse_modfiy_move_cb(u8 user_bank)
{
    u16 species = pokemon_getattr(p_bank[user_bank]->this_pkmn, REQUEST_SPECIES, NULL);
    if (pkmn_has_type(species, TYPE_GHOST)) {
        add_residual_effect(curse_residual_effect, user_bank, get_opponent_side(user_bank), 10);
    } else {
        return;
    }
}

