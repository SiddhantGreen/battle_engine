#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_state.h"
#include "move_override.h"
#include "../abilities/ability_override.h"
#include "moves.h"

extern rand_range(u16 min, u16 max);

void volatile_flash_fire_nullsub()
{
    // the flash fire volatile doesn't have an internal callback. It's handled by the move.
    return;
}


void volatile_confused_before_move(u8 bank)
{
    enqueue_message(0, bank, STRING_CONFUSED, 0, 0);
    if (rand_range(0, 100) <= 33) {
        battle_master-b_moves[(B_MOVE_BANK(bank)].move_id = 0;
        battle_master-b_moves[(B_MOVE_BANK(bank)].power = 40;
        battle_master-b_moves[(B_MOVE_BANK(bank)].category = MOVE_PHYSICAL;
        battle_master-b_moves[(B_MOVE_BANK(bank)].type[0] = MTYPE_EGG;
        battle_master-b_moves[(B_MOVE_BANK(bank)].type[1] = MTYPE_EGG;
        
    }
}


