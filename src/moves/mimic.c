#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern u8 get_move_index(u16 move_id, u8 bank);


static const u16 mimic_disallow[] = {
        MOVE_CHATTER, MOVE_SKETCH, MOVE_STRUGGLE,
        MOVE_TRANSFORM, MOVE_NONE, MOVE_MAX,
};

u8 mimic_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
        if (user != src) return true;
        // fail if target hasn't used a move yet
        u16 target_move = LAST_MOVE(TARGET_OF(user));
        // fail on banned moves list
        for (u8 i = 0; i < (sizeof(mimic_disallow) / sizeof(u16)); i++) {
            if (mimic_disallow[i] == target_move)
                return false;
        }

        // set move slot of mimic to the target's last used move
        u8 slot = get_move_index(MOVE_MIMIC, user);
        B_GET_MOVE(user, slot) = target_move;
        B_GET_MOVE_PP(user, slot) = moves[target_move].pp;
        enqueue_message(target_move, user, STRING_LEARNED_MOVE, NULL);
        return true;
}
