#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

// Rain
u8 rain_init_effect(u8 user)
{
    // if another weather condition is present, remove it TODO
    battle_master->field_state.is_raining = true;
    add_callback(CB_ON_RESIDUAL, 1, 5, NULL); // rain continues to fall, or The rain stopped

}

u16 rain_dmg_mod(u8 user, u16 damage)
{
    if ((battle_master->field_state.is_raining) && (B_MOVE_HAS_TYPE(user, MTYPE_WATER))) {
        return NUM_MOD(damage, 150);
    } else if (B_MOVE_HAS_TYPE(attacker, MTYPE_FIRE)) {
        return NUM_MOD(damage, 50);
    }
}

u16 sweather_dmg_mod(u16 damage, u8 attacker)
{
    if (battle_master->field_state.is_raining || battle_master->field_state.is_primordial_sea) {
        if (B_MOVE_HAS_TYPE(attacker, MTYPE_WATER)) {
            return NUM_MOD(damage, 150);
        } else if (B_MOVE_HAS_TYPE(attacker, MTYPE_FIRE)) {
            return NUM_MOD(damage, 50);
        }
    } else if (battle_master->field_state.is_sunny || battle_master->field_state.is_desolate_land) {
        if (B_MOVE_HAS_TYPE(attacker, MTYPE_FIRE)) {
            return NUM_MOD(damage, 150);
        } else if (B_MOVE_HAS_TYPE(attacker, MTYPE_WATER)) {
            return NUM_MOD(damage, 50);
        }
    } else {
        return damage;
    }
    return damage;
}
