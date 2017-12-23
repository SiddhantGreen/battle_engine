#ifndef BATTLE_ABILITIES_TABLE_H_
#define BATTLE_ABILITIES_TABLE_H_

#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/battle_state.h"
#include "moves/moves.h"
#include "ability_override.h"

typedef u8 (*AbilityBeforeTurn)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityBeforeSwitchOutCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityBeforeMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityOnFailCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityOnModifyMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityOnTryhitCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityOnBasePowerCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityOnDamageCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityOnEffectCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityOnAfterMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityOnStatusCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);

struct ability_data {
    AbilityBeforeTurn before_turn;
    AbilityBeforeSwitchOutCallback before_switch;
    AbilityBeforeMoveCallback before_move;
    AbilityOnFailCallback on_fail;
    AbilityOnModifyMoveCallback on_modify_move;
    AbilityOnTryhitCallback on_tryhit;
    AbilityOnBasePowerCallback on_base_power;
    AbilityOnDamageCallback on_damage;
    AbilityOnEffectCallback on_effect;
    AbilityOnAfterMoveCallback on_after_move;
    AbilityOnStatusCallback on_status;
};

extern struct ability_data abilities[];
extern const pchar ability_names[][17];

/* Callback externs */
extern u8 ability_none_on_effect(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern u8 ability_limber_on_status(u8 user, u8 source, u16 alinment, struct anonymous_callback* acb);
extern u8 ability_insomnia_on_status(u8 user, u8 source, u16 alinment, struct anonymous_callback* acb);
extern u8 ability_immunity_on_status(u8 user, u8 source, u16 alinment, struct anonymous_callback* acb);
extern u8 ability_waterveil_on_status(u8 user, u8 source, u16 alinment, struct anonymous_callback* acb);
extern u8 ability_magmaarmor_on_status(u8 user, u8 source, u16 alinment, struct anonymous_callback* acb);
extern u8 ability_vitalspirit_on_status(u8 user, u8 source, u16 alinment, struct anonymous_callback* acb);

#endif /* BATTLE_ABILITIES_TABLE_H_ */
