#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern void do_damage(u8 bank_index, u16 dmg);

u8 jump_kick_on_move_fail(u8 user, u8 target, u16 move)
{
    if (B_CURRENT_HP(user) < (TOTAL_HP(user) >> 1)) {
        do_damage(user, B_CURRENT_HP(user));
    } else {
        do_damage(user, (TOTAL_HP(user) >> 1));
    }
    return 1;
}


