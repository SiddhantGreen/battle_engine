#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

// Rain
u8 rain_init_effect(u8 user)
{
    // if another weather condition is present, remove it TODO
    battle_master->field_state.is_raining = true;
    add_callback(CB_ON_BEFORE_TURN, 0, 5, user, (u32)NULL);
    return 5;
}
