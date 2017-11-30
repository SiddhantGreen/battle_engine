#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

void clear_other_weather()
{
  // todo
}

// Rain
void rain_init_effect()
{
    // if another weather condition is present, remove it TODO
    battle_master->field_state.is_raining = true;
    add_callback(CB_ON_RESIDUAL, 1, 5, 0, NULL); // rain continues to fall, or The rain stopped

}

u16 rain_dmg_mod(u8 user, u16 damage)
{
    if ((battle_master->field_state.is_raining) && (B_MOVE_HAS_TYPE(user, MTYPE_WATER))) {
        return NUM_MOD(damage, 150);
    } else if (B_MOVE_HAS_TYPE(user, MTYPE_FIRE)) {
        return NUM_MOD(damage, 50);
    } else {
        return damage;
    }
}

// Primordial sea
void primordial_sea_init_effect()
{
    battle_master->field_state.is_primordial_sea = true;
    add_callback(CB_ON_RESIDUAL, 1, 5, NULL, NULL);
}

u16 primordial_sea_dmg_mod(u8 user, u16 damage)
{
    // fire type failing handled in tryhit
    if ((battle_master->field_state.is_primordial_sea) && (B_MOVE_HAS_TYPE(user, MTYPE_WATER))) {
        return NUM_MOD(damage, 150);
    } else {
        return damage;
    }
}

u8 primordial_sea_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (B_MOVE_HAS_TYPE(user, MTYPE_FIRE)) {
        return false;
    }
    return true;
}

// sunny day
void sunny_day_init_effect()
{
    battle_master->field_state.is_sunny = true;
    add_callback(CB_ON_RESIDUAL, 1, 5, NULL, NULL);
}

u16 sunny_day_dmg_mod(u8 user, u16 damage)
{
    if (B_MOVE_HAS_TYPE(user, MTYPE_FIRE)) {
        return NUM_MOD(damage, 150);
    } else if (B_MOVE_HAS_TYPE(user, MTYPE_WATER)) {
        return NUM_MOD(damage, 50);
    } else {
        return damage;
    }
}

// desolate land
void desolate_land_init_effect()
{
    battle_master->field_state.is_desolate_land = true;
    add_callback(CB_ON_RESIDUAL, 1, 5, NULL, NULL);
}

u16 desolate_land_dmg_mod(u8 user, u16 damage)
{
    // fire type failing handled in tryhit
    if ((battle_master->field_state.is_desolate_land) && (B_MOVE_HAS_TYPE(user, MTYPE_FIRE))) {
        return NUM_MOD(damage, 150);
    } else {
        return damage;
    }
}

u8 desolate_land_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (B_MOVE_HAS_TYPE(user, MTYPE_WATER)) {
        return false;
    }
    return true;
}

// Sandstorm
void sand_storm_init_effect()
{
    battle_master->field_state.is_sandstorm = true;
    add_callback(CB_ON_RESIDUAL, 1, 5, NULL, NULL);
}




u16 sweather_dmg_mod(u16 damage, u8 attacker)
{


    return damage;
}
