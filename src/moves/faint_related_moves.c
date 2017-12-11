#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern u8 get_callback_src(u32 func, u8 src);

u8 perish_song_on_faint(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if ((battle_master->execution_index == 1) && (acb->data_ptr == true)) {
        if (p_bank[user]->b_data.perish_song_counter > 2)
            return false;
    }
    return true;
}

u8 perish_song_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (acb->duration == 0) {
        u8 id = get_callback_src((u32)perish_song_on_faint, src);
        CB_MASTER[id].data_ptr = true;
    }

    enqueue_message(0, user, STRING_COUNT_FELL, 3 - p_bank[user]->b_data.perish_song_counter);
    p_bank[user]->b_data.perish_song_counter += 1;
    return true;
}

u8 perish_song_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    add_callback(CB_ON_RESIDUAL, 0, 3, user, (u32)perish_song_on_residual);
    return true;
}

u8 perish_song_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    u8 id = get_callback_src((u32)perish_song_before_move, src);
    CB_MASTER[id].data_ptr = true;
    ADD_VOLATILE(user, VOLATILE_PERISH_SONG);
    p_bank[user]->b_data.perish_song_counter = 0;
    add_callback(CB_ON_FAINT_CHECK, 0, 3, user, (u32)perish_song_on_faint);
    return true;
}

void perish_song_on_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    u8 id = get_callback_src((u32)perish_song_before_move, src);
    if (CB_MASTER[id].data_ptr == true) {
        enqueue_message(0, user, STRING_PERISH_START, 0);
    } else {
        enqueue_message(0, user, STRING_FAILED, 0);
    }
}
