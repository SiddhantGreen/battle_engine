#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../battle_loop/move_chain_states.h"

extern void dprintf(const char * str, ...);
extern void run_decision(void);

u8 bind_on_effect_cb(u8 attacker, u8 defender, u16 move)
{
    ADD_VOLATILE(defender, VOLATILE_BIND);
    return 1;
}


bool bind_volatile_dmg(u8 bank)
{
    // TODO: how can residual effects be implemented better? Does is suffice to check volatiles when needed?
    u16 hp_to_lose = TOTAL_HP(attacker) / 8;
    hp_anim_change(bank, MIN(CURRENT_HP(bank), hp_to_lose));
    enqueue_message(CURRENT_MOVE(bank_index), bank_index, STRING_RECOIL, 0);
}


