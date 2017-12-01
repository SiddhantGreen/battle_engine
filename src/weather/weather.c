#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void clear_other_weather(void);

/* Rain */
u16 rain_dmg_mod(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((battle_master->field_state.is_raining) && (B_MOVE_HAS_TYPE(user, MTYPE_WATER))) {
        return 150;
    } else if (B_MOVE_HAS_TYPE(user, MTYPE_FIRE)) {
        return 50;
    } else {
        return 100;
    }
}

u16 rain_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->duration == 0) {
        enqueue_message(NULL, NULL, STRING_RAIN_STOPPED, NULL);
    } else {
        enqueue_message(NULL, NULL, STRING_RAIN_FALLING, NULL);
    }
    return true;
}

void rain_init_effect()
{
    battle_master->field_state.is_raining = true;
    add_callback(CB_ON_RESIDUAL, 1, 5, NULL, (u32)rain_on_residual);
    add_callback(CB_ON_WEATHER_DMG, 0, 5, 0, (u32)rain_dmg_mod);
    enqueue_message(0, 0, STRING_RAINING, 0);
    return true;
}

void clear_rain()
{
    delete_callback((u32)rain_dmg_mod);
    delete_callback((u32)rain_on_residual);
}


/* Primordial sea */
u16 primordial_sea_dmg_mod(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    // fire type failing handled in tryhit
    if ((battle_master->field_state.is_primordial_sea) && (B_MOVE_HAS_TYPE(user, MTYPE_WATER))) {
        return 150;
    } else {
        return 100;
    }
}

u8 primordial_sea_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (B_MOVE_HAS_TYPE(user, MTYPE_FIRE)) {
        enqueue_message(0, 0, STRING_HEAVY_RAIN_FIZZLE, 0);
        return 3;
    }
    return true;
}

void primordial_sea_end()
{
    u8 id = id_by_func((u32)primordial_sea_dmg_mod);
    CB_MASTER[id].in_use = false;
    id = id_by_func((u32)primordial_sea_tryhit);
    CB_MASTER[id].in_use = false;
    enqueue_message(0, 0, STRING_HEAVY_RAIN_LIFTED, 0);
}

void primordial_sea_init_effect()
{
    clear_other_weather();
    battle_master->field_state.is_primordial_sea = true;
    add_callback(CB_ON_WEATHER_DMG, 0, 0xFF, NULL, (u32)primordial_sea_dmg_mod);
    add_callback(CB_ON_TRYHIT_MOVE, 0, 0xFF, NULL, (u32)primordial_sea_tryhit);
    enqueue_message(0, 0, STRING_PRIMORDIAL_SEA, 0);
}

void clear_primordial_sea()
{
    if (battle_master->field_state.is_primordial_sea) {
        primordial_sea_end();
    } else {
        delete_callback((u32)primordial_sea_dmg_mod);
        delete_callback((u32)primordial_sea_tryhit);
    }
}


/* Sun */
u16 sun_dmg_mod(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (B_MOVE_HAS_TYPE(user, MTYPE_FIRE)) {
        return 150;
    } else if (B_MOVE_HAS_TYPE(user, MTYPE_WATER)) {
        return 50;
    } else {
        return 100;
    }
}

u16 sun_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->duration == 0) {
        enqueue_message(NULL, NULL, STRING_SUNLIGHT_FADE, NULL);
    } else {
        enqueue_message(NULL, NULL, STRING_SUNLIGHT_STRONG, NULL);
    }
    return true;
}

void sun_init_effect()
{
    battle_master->field_state.is_sunny = true;
    add_callback(CB_ON_WEATHER_DMG, 1, 5, NULL, (u32)sun_dmg_mod);
    add_callback(CB_ON_RESIDUAL, 1, 5, NULL, (u32)sun_on_residual);
    enqueue_message(0, 0, STRING_SUNLIGHT_HARSH, 0);
}


/* Desolate land */
u16 desolate_land_dmg_mod(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    // fire type failing handled in tryhit
    if ((battle_master->field_state.is_desolate_land) && (B_MOVE_HAS_TYPE(user, MTYPE_FIRE))) {
        return 150;
    } else {
        return 100;
    }
}

u8 desolate_land_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (B_MOVE_HAS_TYPE(user, MTYPE_WATER)) {
        enqueue_message(0, 0, STRING_HARSH_SUN_WATER, 0);
        return 3;
    }
    return true;
}

void desolate_land_end()
{
    u8 id = id_by_func((u32)desolate_land_dmg_mod);
    CB_MASTER[id].in_use = false;
    id = id_by_func((u32)desolate_land_tryhit);
    CB_MASTER[id].in_use = false;
    enqueue_message(0, 0, STRING_HARSH_SUN_END, 0);
}

void desolate_land_init_effect()
{
    clear_other_weather();
    battle_master->field_state.is_desolate_land = true;
    add_callback(CB_ON_WEATHER_DMG, 0, 0xFF, NULL, (u32)desolate_land_dmg_mod);
    add_callback(CB_ON_TRYHIT_MOVE, 0, 0xFF, NULL, (u32)desolate_land_tryhit);
    enqueue_message(0, 0, STRING_DESOLATE_LAND, 0);
}

void clear_desolate_land()
{
    if (battle_master->field_state.is_desolate_land) {
        desolate_land_end();
    } else {
        delete_callback((u32)desolate_land_dmg_mod);
        delete_callback((u32)desolate_land_tryhit);
    }
}

// Sandstorm
void sandstorm_init_effect()
{
    battle_master->field_state.is_sandstorm = true;
    add_callback(CB_ON_RESIDUAL, 1, 5, NULL, NULL);
    add_callback(CB_ON_STAT_MOD, 10, 5, NULL, NULL);
}





void clear_other_weather()
{
    // todo
    battle_master->field_state.is_raining = false;
    battle_master->field_state.is_sunny = false;
    battle_master->field_state.is_sandstorm = false;
    battle_master->field_state.is_hail = false;
    battle_master->field_state.is_desolate_land = false;
    battle_master->field_state.is_primordial_sea = false;
    battle_master->field_state.is_delta_stream = false;
    battle_master->field_state.suppress_weather = false;
    clear_rain();
    clear_primordial_sea();
}
