#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern u16 rand_range(u16, u16);
const static u8 chances_protect[] = {100, 33, 3, 1};

// on tryhit try to see if protect will fail
u8 protect_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 chance_land = 0;
    if (PROTECTION_TURNS(user) < 4) {
        chance_land = chances_protect[PROTECTION_TURNS(user)];
    }
    if (rand_range(0, 100) > chance_land) {
        PROTECTION_TURNS(user) = 0;
        return false; // move failed to land
    } else {
        // move landed
        return true;
    }
}

u8 protect_on_tryhit_anon(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != source) return true;
    dprintf("protect in ID: %d\n", id_by_func((u32)(protect_on_tryhit_anon)));
    if (IS_PROTECTABLE(move)) {
        return false; // fail the move
    }
    return true;
}

u8 protect_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    // msg: X protected itself
    // queue an anon func to read and interrupt
    if (user != src) return true;
    add_callback(CB_ON_TRYHIT_MOVE, 0, 0, user, (u32)(protect_on_tryhit_anon));
    dprintf("protect added to ID: %d\n", id_by_func((u32)(protect_on_tryhit_anon)));
    return true;
}
