#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

u8 solarbeam_before_move(u8 bank)
{
    dprintf("Executing callback solarbeam\n");
    if (HAS_VOLATILE(bank, VOLATILE_CHARGING)) {
        REMOVE_VOLATILE(bank, VOLATILE_CHARGING);
        return true;
    } else {
        enqueue_message(0, bank, STRING_CHARGE_SOLARBEAM, 0);
        ADD_VOLATILE(bank, VOLATILE_CHARGING);
        return false; // don't fire move if charging
    }
}
