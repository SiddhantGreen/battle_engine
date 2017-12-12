#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void do_heal(u8 bank_index, u8 heal);
void set_status(u8 bank, enum Effect status);
extern void flat_heal(u8 bank, u16 heal);

/* Purify */
void purify_on_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    do_heal(user, 50);
    enqueue_message(NULL, user, STRING_HEAL, 0);
}

u8 purify_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (B_STATUS(user) != AILMENT_NONE) {
        set_status(user, EFFECT_CURE);
        add_callback(CB_ON_AFTER_MOVE, 0, 0, user, (u32)purify_on_after_move);
        return true;
    } else {
        return false;
    }
}

/* Strength sap */
void strength_sap_on_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    flat_heal(user, acb->data_ptr);
    enqueue_message(NULL, user, STRING_HEAL, 0);
}

u8 strength_sap_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 id = add_callback(CB_ON_AFTER_MOVE, 0, 0, user, (u32)strength_sap_on_after_move);
    CB_MASTER[id].data_ptr = B_ATTACK_STAT(TARGET_OF(user));
    return true;
}
