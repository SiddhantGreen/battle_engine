#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern u8 get_move_index(u16 move_id, u8 bank);

void beatup_before_turn()
{
    if (user != src) return;
    // figure out how many hits to do
    struct Pokemon *p = SIDE_OF(user) ? (&party_opponent[0]) : (&party_player[0]);
    u8 user_slot;
    if (SIDE_OF(user)) {
        user_slot = ((u32)(p_bank[user]->this_pkmn) - (u32)(&party_opponent[0])) / 100;
    } else {
        user_slot = ((u32)(p_bank[user]->this_pkmn) - (u32)(&party_player[0])) / 100;
    }
    acb->data_ptr = (u32)malloc_and_clear(6);
    u8 indexes[6] = (u8*)acb->data_ptr;
    u8 hitters = 1;
    for (u8 i = 0; i < 6; i++) {
        if (i == slot) continue;
        if (pokemon_getattr(&p[i], REQUEST_SPECIES, NULL) == SPECIES_NONE) break;
        u8 status = pokemon_getattr(&p[i], REQUEST_STATUS_AILMENT, NULL);
        u8 hp = pokemon_getattr(&p[i], REQUEST_CURRENT_HP, NULL);
        if ((status != 0) || (hp < 1 )) continue;
        hitters++;
        acb->data_ptr
    }
    battle_master->b_moves[B_MOVE_BANK(user)].hit_times = hitters -1;
    battle_master->b_moves[B_MOVE_BANK(user)].hit_counter = 1;
}

void beatup_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;

    battle_master->b_moves[index].hit_times = hit_times - 1;
    battle_master->b_moves[index].hit_counter = 1;
}
