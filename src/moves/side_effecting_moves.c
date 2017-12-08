#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

/* Tailwind */
u16 tailwind_on_speed(u8 user, u8 src, u16 stat, struct anonymous_callback* acb)
{
    if (SIDE_OF(user) != SIDE_OF(src)) return acb->data_ptr;
    if (stat == 2)
        return (acb->data_ptr << 1);
    return acb->data_ptr;
}

u8 tailwind_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((acb->duration == 0) && (acb->in_use)) {
        acb->in_use = false;
        enqueue_message(NULL, src, STRING_TAILWIND_PETER, NULL);
    }
    return true;
}

u8 tailwind_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (callback_exists_side((u32)tailwind_on_speed, src) < ANON_CB_MAX)
        return false;
    add_callback(CB_ON_STAT_MOD, 0, 4, user, (u32)tailwind_on_speed);
    add_callback(CB_ON_RESIDUAL, 0, 4, user, (u32)tailwind_on_residual);
    enqueue_message(NULL, user, STRING_TAILWIND_BLEW, NULL);
    return true;
}

/* Trick room */
u8 trick_room_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((acb->duration == 0) && (acb->in_use)) {
        enqueue_message(NULL, user, STRING_TWISTED_DIM_NORM, NULL);
        acb->in_use = false;
        battle_master->field_state.speed_inverse = false;
    }
    return true;
}


u8 trick_room_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (callback_exists((u32)trick_room_on_residual)) {
        delete_callback((u32)trick_room_on_residual);
    }
    if (battle_master->field_state.speed_inverse) {
        enqueue_message(NULL, user, STRING_TWISTED_DIM_NORM, NULL);
        battle_master->field_state.speed_inverse = false;
        return true;
    } else {
        enqueue_message(NULL, user, STRING_TWISTED_DIM, NULL);
    }
    u8 id = add_callback(CB_ON_RESIDUAL, 0, 0, src, (u32)trick_room_on_residual);
    CB_MASTER[id].delay_before_effect = 5;
    battle_master->field_state.speed_inverse = true;
    return true;
}


/* Mist */
u8 mist_on_before_stat_mod(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if ((SIDE_OF(TARGET_OF(user)) != SIDE_OF(src)) || (user == src)) return true;
    bool dropped = false;
    for (u8 i = 0; i < 8; i++) {
        // drop boosts
        if (B_TARGET_STAT_MOD_CHANCE(user, i)) {
            dropped = true;
            B_TARGET_STAT_MOD_CHANCE(user, i) = 0;
        }
	}
    if (dropped)
        enqueue_message(MOVE_MIST, TARGET_OF(user), STRING_PROTECTED_MON, NULL);
        enqueue_message(NULL, TARGET_OF(user), STRING_MOVE_IMMUNE, NULL);
    return true;
}

u8 mist_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    add_callback(CB_ON_BEFORE_STAT_MOD, 0, 5, user, (u32)mist_on_before_stat_mod);
    enqueue_message(MOVE_MIST, user, STRING_PROTECTED_TEAM, NULL);
    return true;
}
