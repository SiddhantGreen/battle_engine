#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_state.h"
#include "moves/moves.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "battle_abilities.h"

extern void build_message(u8 state, u16 move_id, u8 user_bank, enum battle_string_ids id, u16 move_effect_id);
extern u16 rand_range(u16, u16);

struct b_ability empty = {
};


// Stench
void stench_modify_move(u8 bank, u16 move)
{
    if (M_FLINCH(move)) {
        return;
    } else {
        battle_master->b_moves[B_MOVE_BANK(bank)].flinch = 10;
    }
}

struct b_ability b_stench = {
    .on_modify_move = stench_modify_move,
};


// Drizzle
void drizzle_on_switch(u8 bank)
{
    // if weather can't be changed, return
    if ((battle_master->field_state.is_raining) ||
        (battle_master->field_state.is_primordial_sea) ||
        (battle_master->field_state.is_desolate_land)) {
        return;
    }
    // set new weather
    battle_master->field_state.is_raining = 1;
    build_message(GAME_STATE, 0, 0, STRING_RAINING, 0);
}

struct b_ability b_drizzle = {
    .on_switch = drizzle_on_switch,
};


// Speed Boost
void speed_boost_on_residual(u8 bank)
{
    if (p_bank[bank]->b_data.speed < 6) {
        p_bank[bank]->b_data.speed++;
        build_message(GAME_STATE, 0, bank, STRING_GAINED_SPEED, 0);
    }
}

struct b_ability b_speed_boost = {
    .on_residual = speed_boost_on_residual,
};


// Battle Armor
u16 battle_armor_on_critchance(u8 bank, u16 move)
{
    return 0;
}

struct b_ability b_battle_armor = {
    .on_critchance = battle_armor_on_critchance,
};


// Sturdy
u8 sturdy_tryhit(u8 bank, u8 target, u16 move)
{
    switch (move) {
        case MOVE_FISSURE:
        case MOVE_HORN_DRILL:
        case MOVE_GUILLOTINE:
        case MOVE_SHEER_COLD:
            build_message(GAME_STATE, move, bank, STRING_STURDY_IMMUNE, 0);
            return false;
            break;
        default:
            break;
    };
    return true;
}

u16 sturdy_on_damage(u8 bank, u16 move, u16 damage, u8 ability, u16 item)
{
    if ((B_CURRENT_HP(bank) == B_TOTAL_HP(bank)) &&
        (damage >= B_CURRENT_HP(bank))) {
        return 1;
    }
    return damage;
}

struct b_ability b_sturdy = {
    .on_tryhit = sturdy_tryhit,
    .on_damage = sturdy_on_damage,
};


// Damp
u8 damp_tryhit(u8 bank, u8 target, u16 move)
{
    if ((move == MOVE_SELFDESTRUCT) || (move == MOVE_EXPLOSION)) {
        build_message(GAME_STATE, move, bank, STRING_DAMP_BLOCKED, 0);
        return false;
    }
    return true;
}

u16 damp_on_damage(u8 bank, u16 move, u16 damage, u8 ability, u16 item)
{
    if (ability == ABILITY_AFTERMATH)
        return 0;
    return damage;
}

struct b_ability b_damp = {
    .on_tryhit = damp_tryhit,
    .on_damage = damp_on_damage,
};


// Limber

void limber_on_update(u8 bank)
{
    if (B_STATUS(bank) == AILMENT_PARALYZE) {
       p_bank[bank]->b_data.status = AILMENT_NONE;
       build_message(GAME_STATE, 0, bank, STRING_STATUS_CURED, 0);
    }
}

void limber_on_set_status(u8 bank)
{
    if (B_STATUS(bank) == AILMENT_PARALYZE) {
       p_bank[bank]->b_data.status = AILMENT_NONE;
       build_message(GAME_STATE, 0, bank, STRING_IMMUNE_ABILITY, ABILITY_LIMBER);
    }
}

struct b_ability b_limber = {
    .on_update = limber_on_update,
    .on_set_status = limber_on_set_status,
};


// Sand Veil
/* Sand Veil's immune clause to sandstorm to be handled in standstorm's residual damage*/
u16 sand_veil_on_evasion(u8 bank, u16 stat) {
    if (battle_master->field_state.is_sandstorm)
        return ((stat * 25) / 100);
    return stat;
}

struct b_ability b_sand_veil = {
    .on_evasion = sand_veil_on_evasion,
};


// Static
void static_on_after_damage(u8 bank, u16 move, u16 dmg, u8 ability, u16 item)
{
    if (MAKES_CONTACT(move)) {
        if (rand_range(0, 100) < 30) {
            p_bank[TARGET_OF(bank)]->b_data.status = AILMENT_PARALYZE;
        }
    }
}

struct b_ability b_static = {
    .on_after_damage = static_on_after_damage,
};


// Volt Absorb
u8 volt_absorb_tryhit(u8 bank, u8 target, u16 move)
{
    if ((target != TARGET_OF(bank)) &&  (MOVE_TYPE(move) == MTYPE_ELECTRIC)) {
        build_message(GAME_STATE, 0, bank, STRING_IMMUNE_ABILITY, ABILITY_VOLT_ABSORB);
        p_bank[target]->b_data.current_hp += (B_TOTAL_HP(target) / 4);
        if (B_CURRENT_HP(target) > B_TOTAL_HP(target))
            p_bank[target]->b_data.current_hp = B_TOTAL_HP(target);
        return false;
    }
    return true;
}

struct b_ability b_volt_absorb = {
    .on_tryhit = volt_absorb_tryhit,
};



struct b_ability* abilities_table[11] = {
    &empty,
    &b_stench,
    &b_drizzle,
    &b_speed_boost,
    &b_battle_armor,
    &b_sturdy,
    &b_damp,
    &b_limber,
    &b_sand_veil,
    &b_static,
    &b_volt_absorb,
    
    
};




// Adaptability
void adaptability_modify_move(u8 bank, u16 move)
{
   battle_master->b_moves[B_MOVE_BANK(bank)].stab = 200;
}

struct b_ability b_adaptability = {
    .on_modify_move = adaptability_modify_move,
};