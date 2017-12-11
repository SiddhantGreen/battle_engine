#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

u8 shell_trap_ontryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    return false;
}

void shell_trap_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return;
    if (B_MOVE_IS_PHYSICAL(user) && (B_MOVE_DMG(user) > 0)) {
        delete_callback_src((u32)shell_trap_ontryhit, src);
    }
}

void shell_trap_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    add_callback(CB_ON_DAMAGE_MOVE, 0, 0, user, (u32)shell_trap_on_damage);
    add_callback(CB_ON_TRYHIT_MOVE, 0, 0, user, (u32)shell_trap_ontryhit);
    enqueue_message(NULL, user, STRING_SETUP_SHELL_TRP, NULL);
}
