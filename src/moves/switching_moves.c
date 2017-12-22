#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

void pursuit_on_basepower(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (p_bank[TARGET_OF(user)]->b_data.is_switching) {
        B_MOVE_POWER(user) *= 2; // double base power on switch
    }
}

void pursuit_on_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    for (u8 i = 0; i < 4; i++) {
        if ((SIDE_OF(i) != SIDE_OF(user)) && ((p_bank[i]->b_data.is_switching))) {
            B_MOVE_PRIORITY(user) = 7;
            TARGET_OF(user) = i;
            dprintf("adjusted\n");
            return;
        }
    }
}
