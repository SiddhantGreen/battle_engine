#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern u8 move_pp_count(u16 move_id, u8 bank);


const static u16 encore_disallow[] = {
    MOVE_ASSIST, MOVE_COPYCAT, MOVE_ENCORE, MOVE_ME_FIRST,
    MOVE_METRONOME, MOVE_MIMIC, MOVE_MIRROR_MOVE,
    MOVE_NATURE_POWER, MOVE_SKETCH, MOVE_SLEEP_TALK,
    MOVE_STRUGGLE, MOVE_TRANSFORM,
};

/* Encore */
u8 encore_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (move_pp_count(LAST_MOVE(TARGET_OF(user)), TARGET_OF(user)) < 1) return false;
    for (u8 i = 0; i < (sizeof(encore_disallow) / sizeof(u16)); i++) {
        if (LAST_MOVE(TARGET_OF(user)) == encore_disallow[i])
            return false;
    }
    return true;
}

u8 encore_on_disable(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (move_pp_count(LAST_MOVE(user), user) < 1) {
        acb->in_use = false;
        return true;
    }
    if (SIDE_OF(user) == 0) {
        u16 player_moveid = battle_master->battle_cursor.cursor_pos;
        if (player_moveid == 1) {
            player_moveid += 1;
        } else if (player_moveid == 2) {
            player_moveid -= 1;
        }
        if (B_GET_MOVE(PLAYER_SINGLES_BANK, player_moveid) != LAST_MOVE(user))
            return false;
    } else {
        p_bank[user]->b_data.skip_move_select = true;
        return false;
    }
    return true;
}

u8 encore_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (move_pp_count(CURRENT_MOVE(user), user) < 1) {
        acb->in_use = false;
        p_bank[user]->b_data.skip_move_select = false;
    } else if (acb->duration == 0) {
        p_bank[user]->b_data.skip_move_select = false;
    }
    return true;
}

u8 encore_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (LAST_MOVE(TARGET_OF(user)) == 0) return false;
    if (move_pp_count(LAST_MOVE(TARGET_OF(user)), TARGET_OF(user)) < 1) return false;
    CURRENT_MOVE(TARGET_OF(user)) = LAST_MOVE(TARGET_OF(user));
    add_callback(CB_ON_RESIDUAL, 0, 3, TARGET_OF(user), (u32)encore_on_residual);
    add_callback(CB_ON_DISABLE_MOVE, 0, 3, TARGET_OF(user), (u32)encore_on_disable);
    enqueue_message(NULL, TARGET_OF(user), STRING_RECIEVED_ENCORE, NULL);
    return true;
}


/* Torment */
u8 torment_on_disable(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (SIDE_OF(user) == 0) {
        u16 player_moveid = battle_master->battle_cursor.cursor_pos;
        if (player_moveid == 1) {
            player_moveid += 1;
        } else if (player_moveid == 2) {
            player_moveid -= 1;
        }
        if (B_GET_MOVE(PLAYER_SINGLES_BANK, player_moveid) == LAST_MOVE(user))
            return false;
    } else {
        extern u8 get_move_index(u16 move_id, u8 bank);
        u8 index = get_move_index(LAST_MOVE(user), user);
        p_bank[user]->b_data.disabled_moves[index] = 1;
        return false;
    }
    return true;
}

u8 torment_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (has_callback_src((u32)torment_on_disable, TARGET_OF(user))) return false;
    add_callback(CB_ON_DISABLE_MOVE, 0, 0xFF, TARGET_OF(user), (u32)torment_on_disable);
    enqueue_message(NULL, TARGET_OF(user), STRING_SUBJECTED_TORM, NULL);
    return true;
}


/* Taunt */
u8 taunt_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    return (B_MOVE_IS_STATUS(move));
}

u8 taunt_on_disable(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (SIDE_OF(user) == 0) {
        u16 player_moveid = battle_master->battle_cursor.cursor_pos;
        if (player_moveid == 1) {
            player_moveid += 1;
        } else if (player_moveid == 2) {
            player_moveid -= 1;
        }
        if (IS_MOVE_STATUS(B_GET_MOVE(PLAYER_SINGLES_BANK, player_moveid)))
            return false;
    } else {
        for (u8 i = 0; i < 4; i++) {
            if (IS_MOVE_STATUS(p_bank[user]->b_data.moves[i]))
                p_bank[user]->b_data.disabled_moves[i] = 1;
        }
        return false;
    }
    return true;
}

u8 taunt_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (has_callback_src((u32)taunt_on_disable, TARGET_OF(user))) return false;
    add_callback(CB_ON_DISABLE_MOVE, 0, 0x5, TARGET_OF(user), (u32)taunt_on_disable);
    add_callback(CB_ON_BEFORE_MOVE, 0, 0x1, TARGET_OF(user), (u32)taunt_on_before_move);
    enqueue_message(NULL, TARGET_OF(user), STRING_FELL_FOR_TAUNT, NULL);
    return true;
}
