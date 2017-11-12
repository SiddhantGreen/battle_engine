#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../battle_loop/move_chain_states.h"
#include "../volatile/residual_effects.h"

extern void dprintf(const char * str, ...);
extern u8 add_residual_cb(ResidualFunc to_add);
extern void run_decision(void);
extern u16 rand_range(u16 min, u16 max);
extern void apply_residual_dmg(u8 id);


u8 thrash_on_before_move(u8 attacker)
{
    if ((p_bank[attacker]->b_data.skip_move_select) && (p_bank[attacker]->b_data.move_lock_counter < 1)) {
        p_bank[attacker]->b_data.skip_move_select = false;
        p_bank[attacker]->b_data.move_lock_counter = 0;
        REMOVE_VOLATILE(attacker, VOLATILE_MULTI_TURN);
    } else if (p_bank[attacker]->b_data.skip_move_select) {
        p_bank[attacker]->b_data.move_lock_counter--;
    } else {
        p_bank[attacker]->b_data.move_lock_counter = rand_range(1, 2);
        p_bank[attacker]->b_data.skip_move_select = true;
        ADD_VOLATILE(attacker, VOLATILE_MULTI_TURN);
    }
    return 1;
}

u8 thrash_on_move_fail(u8 attacker, u8 defender, u16 move)
{
    p_bank[attacker]->b_data.skip_move_select = false;
    p_bank[attacker]->b_data.move_lock_counter = 0;
    return 1;
}

void thrash_on_after_move(u8 attacker)
{
    if (p_bank[attacker]->b_data.skip_move_select == false) {
        if (!(HAS_VOLATILE(attacker, VOLATILE_CONFUSION))) {
            ADD_VOLATILE(attacker, VOLATILE_CONFUSION);
        }
    }
    return;
}

