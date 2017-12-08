#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 user, enum battle_string_ids id, u16 effect);

u8 before_move_charge_frame(u8 user, u8 string_id)
{
    if (HAS_VOLATILE(user, VOLATILE_CHARGING)) {
        CLEAR_VOLATILE(user, VOLATILE_CHARGING);
        return true;
    } else {
        enqueue_message(0, user, string_id, 0);
        ADD_VOLATILE(user, VOLATILE_CHARGING);
        return true; // don't fire move if charging
    }
}

/* Basic one turn charge, then simple attack moves */
u8 freeze_shock_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (src != user) return true;
    return before_move_charge_frame(user, STRING_FREEZE_SHOCK);
}

u8 solarbeam_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (src != user) return true;
    return before_move_charge_frame(user, STRING_SOLARBEAM);
}

u8 solarblade_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (src != user) return true;
    return before_move_charge_frame(user, STRING_SOLARBEAM);
}

u8 ice_burn_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (src != user) return true;
    return before_move_charge_frame(user, STRING_ICE_BURN);
}

u8 razor_wind_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (src != user) return true;
    return before_move_charge_frame(user, STRING_RAZORWIND);
}

u8 sky_attack_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (src != user) return true;
    return before_move_charge_frame(user, STRING_CHARGE_SKY_ATTACK);
}

/* Moves with some effect during the charging turn */

u8 fly_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (src != user) return true;
    if (HAS_VOLATILE(user, VOLATILE_GRAVITY)) {
        CLEAR_VOLATILE(user, VOLATILE_FLYING);
        CLEAR_VOLATILE(user, VOLATILE_SEMI_INVULNERABLE);
        enqueue_message(MOVE_FLY, user, STRING_ATTACK_USED, NULL);
        return false;
    }
    before_move_charge_frame(user, STRING_CHARGE_FLY);
    if (HAS_VOLATILE(user, VOLATILE_CHARGING)) {
        ADD_VOLATILE(user, VOLATILE_FLYING);
        ADD_VOLATILE(user, VOLATILE_SEMI_INVULNERABLE);
        return true;
    }
    CLEAR_VOLATILE(user, VOLATILE_FLYING);
    CLEAR_VOLATILE(user, VOLATILE_SEMI_INVULNERABLE);
    return true;
}

u8 bounce_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (src != user) return true;
    if (HAS_VOLATILE(user, VOLATILE_GRAVITY)) {
        CLEAR_VOLATILE(user, VOLATILE_BOUNCE);
        CLEAR_VOLATILE(user, VOLATILE_SEMI_INVULNERABLE);
        enqueue_message(MOVE_BOUNCE, user, STRING_ATTACK_USED, NULL);
        return false;
    }
    before_move_charge_frame(user, STRING_CHARGE_BOUNCE);
    if (HAS_VOLATILE(user, VOLATILE_CHARGING)) {
        ADD_VOLATILE(user, VOLATILE_BOUNCE);
        ADD_VOLATILE(user, VOLATILE_SEMI_INVULNERABLE);
        return true;
    }
    CLEAR_VOLATILE(user, VOLATILE_BOUNCE);
    CLEAR_VOLATILE(user, VOLATILE_SEMI_INVULNERABLE);
    return true;
}
