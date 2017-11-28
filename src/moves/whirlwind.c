#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../battle_loop/move_chain_states.h"

extern void dprintf(const char * str, ...);
extern void run_decision(void);

u8 whirlwind_on_tryhit_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 target = TARGET_OF(user);
    if ((HAS_VOLATILE(target, VOLATILE_INGRAIN)) ||
     (BANK_ABILITY(target) == ABILITY_SUCTION_CUPS)) {
        return 0; // fail move
    } else {
        return 1; // use move
    }
}

u8 whirlwind_on_effect_cb(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // exit battle
    set_callback1(run_decision);
    super.multi_purpose_state_tracker = S_END_BATTLE;
    return 0;
}
