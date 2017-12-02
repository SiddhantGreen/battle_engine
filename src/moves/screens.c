#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

// reflect
void reflect_on_damage_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return;
    if (B_MOVE_IS_PHYSICAL(CURRENT_MOVE(user)) && (!B_MOVE_WILL_CRIT(user))) {
        B_MOVE_DMG(user) = NUM_MOD(B_MOVE_DMG(user), 50);
    }
    return;
}

u8 reflect_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (callback_exists((u32)reflect_on_damage_move))
        return false;
    add_callback(CB_ON_DAMAGE_MOVE, 0, 5, user, (u32)reflect_on_damage_move);
    enqueue_message(0, user, STRING_REFLECT, 0);
    return true;
}


// lightscreen
void light_screen_on_damage_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return;
    if (B_MOVE_IS_SPECIAL(CURRENT_MOVE(user)) && (!B_MOVE_WILL_CRIT(user))) {
        B_MOVE_DMG(user) = NUM_MOD(B_MOVE_DMG(user), 50);
    }
    return;
}

u8 light_screen_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (callback_exists((u32)light_screen_on_damage_move))
        return false;
    add_callback(CB_ON_DAMAGE_MOVE, 0, 5, user, (u32)light_screen_on_damage_move);
    enqueue_message(0, user, STRING_LIGHTSCREEN, 0);
    return true;
}


// Aurora veil
u8 aurora_veil_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    return (battle_master->field_state.is_hail);
}

void aurora_veil_on_damage_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return;
    bool lightscreen_active = callback_exists((u32)light_screen_on_damage_move);
    bool reflect_active = callback_exists((u32)reflect_on_damage_move);
    // don't stack with reflect or lightscreen
    if ((lightscreen_active && B_MOVE_IS_SPECIAL(CURRENT_MOVE(user))) ||
        (reflect_active && B_MOVE_IS_PHYSICAL(CURRENT_MOVE(user))))
        return;

    if (!B_MOVE_WILL_CRIT(user))
        B_MOVE_DMG(user) = NUM_MOD(B_MOVE_DMG(user), 50);
}

u8 aurora_veil_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (src != user) return true;
    if (callback_exists((u32)aurora_veil_on_damage_move))
        return false;
    add_callback(CB_ON_DAMAGE_MOVE, 0, 5, user, (u32)aurora_veil_on_damage_move);
    enqueue_message(0, user, STRING_AURORA_VEIL, 0);
    return true;
}


// brickbreak
u8 brickbreak_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    bool broke = false;
    if (callback_exists((u32)aurora_veil_on_damage_move)) {
        broke = true;
        delete_callback((u32)aurora_veil_on_damage_move);
    }
    if (callback_exists((u32)light_screen_on_damage_move)) {
        broke = true;
        delete_callback((u32)light_screen_on_damage_move);
    }
    if (callback_exists((u32)reflect_on_damage_move)) {
        broke = true;
        delete_callback((u32)reflect_on_damage_move);
    }
    if (broke)
        enqueue_message(0, user, STRING_SHATTER_BARRIER, 0);
    return true;
}
