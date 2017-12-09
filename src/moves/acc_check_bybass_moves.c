#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

/* Miracle eye */
u16 miracle_eye_on_effectiveness(u8 target_type, u8 defender, u16 move_type, struct anonymous_callback* acb)
{
    u8 user = (u8)(acb->data_ptr >> 16);
    u16 effectiveness = ((acb->data_ptr << 16) >> 16);
    if (user == defender) return effectiveness;
    if ((target_type == MTYPE_DARK) && (move_type == MTYPE_PSYCHIC)) {
        return 100;
    } else {
        return effectiveness;
    }
}

u16 miracle_eye_on_evasion(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if ((user != src) || (stat_id != EVASION_MOD)) return (u16)acb->data_ptr;
    return 100;
}

u8 miracle_eye_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->in_use) {
        acb->in_use = false;
        enqueue_message(MOVE_MIRACLE_EYE, user, STRING_MOVE_ENDED, NULL);
        CLEAR_VOLATILE(src, VOLATILE_MIRACLE_EYE);
    }
    return true;
}

u8 miracle_eye_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_MIRACLE_EYE)) return false;
    ADD_VOLATILE(TARGET_OF(user), VOLATILE_MIRACLE_EYE);
    add_callback(CB_ON_STAT_MOD, 0, 5, TARGET_OF(user), (u32)miracle_eye_on_evasion);
    add_callback(CB_ON_EFFECTIVENESS, 0, 5, TARGET_OF(user), (u32)miracle_eye_on_effectiveness);
    u8 id = add_callback(CB_ON_RESIDUAL, 0, 0, TARGET_OF(user), (u32)miracle_eye_on_residual);
    CB_MASTER[id].delay_before_effect = 5;
    enqueue_message(MOVE_MIRACLE_EYE, TARGET_OF(user), STRING_IDENTIFIED, NULL);
    return true;
}


/* Odor Sleuth */
u16 odor_sleuth_on_effectiveness(u8 target_type, u8 defender, u16 move_type, struct anonymous_callback* acb)
{
    u8 user = (u8)(acb->data_ptr >> 16);
    u16 effectiveness = ((acb->data_ptr << 16) >> 16);
    if (user == defender) return effectiveness;
    if ((target_type == MTYPE_GHOST) && ((move_type == MTYPE_NORMAL) || (move_type == MTYPE_FIGHTING))) {
        return 100;
    } else {
        return effectiveness;
    }
}


u8 odor_sleuth_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->in_use) {
        acb->in_use = false;
        enqueue_message(MOVE_ODOR_SLEUTH, user, STRING_MOVE_ENDED, NULL);
        CLEAR_VOLATILE(src, VOLATILE_ODOR_SLEUTH);
    }
    return true;
}

u8 odor_sleuth_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_ODOR_SLEUTH)) return false;
    ADD_VOLATILE(TARGET_OF(user), VOLATILE_ODOR_SLEUTH);
    add_callback(CB_ON_STAT_MOD, 0, 5, TARGET_OF(user), (u32)miracle_eye_on_evasion);
    add_callback(CB_ON_EFFECTIVENESS, 0, 5, TARGET_OF(user), (u32)odor_sleuth_on_effectiveness);
    u8 id = add_callback(CB_ON_RESIDUAL, 0, 0, TARGET_OF(user), (u32)odor_sleuth_on_residual);
    CB_MASTER[id].delay_before_effect = 5;
    enqueue_message(MOVE_ODOR_SLEUTH, TARGET_OF(user), STRING_IDENTIFIED, NULL);
    return true;
}


/* Foresight */
u8 foresight_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->in_use) {
        acb->in_use = false;
        enqueue_message(MOVE_FORESIGHT, user, STRING_MOVE_ENDED, NULL);
        CLEAR_VOLATILE(src, VOLATILE_FORESIGHT);
    }
    return true;
}

u8 foresight_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_FORESIGHT)) return false;
    ADD_VOLATILE(TARGET_OF(user), VOLATILE_FORESIGHT);
    add_callback(CB_ON_STAT_MOD, 0, 5, TARGET_OF(user), (u32)miracle_eye_on_evasion);
    add_callback(CB_ON_EFFECTIVENESS, 0, 5, TARGET_OF(user), (u32)odor_sleuth_on_effectiveness);
    u8 id = add_callback(CB_ON_RESIDUAL, 0, 0, TARGET_OF(user), (u32)foresight_on_residual);
    CB_MASTER[id].delay_before_effect = 5;
    enqueue_message(MOVE_FORESIGHT, TARGET_OF(user), STRING_IDENTIFIED, NULL);
    return true;
}
/* Mind Reader */
