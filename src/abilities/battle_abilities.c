#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_state.h"
#include "moves/moves.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "battle_abilities.h"


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
}

struct b_ability b_drizzle = {
    .on_switch = drizzle_on_switch,
};


// Speed Boost
void speed_boost_on_residual(u8 bank)
{
    if (p_bank[bank]->b_data.speed < 6) {
        p_bank[bank]->b_data.speed++;
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
void sturdy_tryhit()
{
}

struct b_ability* abilities_table[5] = {
    &empty,
    &b_stench,
    &b_drizzle,
    &b_speed_boost,
    &b_battle_armor,
    
};




// Adaptability
void adaptability_modify_move(u8 bank, u16 move)
{
   battle_master->b_moves[B_MOVE_BANK(bank)].stab = 200;
}

struct b_ability b_adaptability = {
    .on_modify_move = adaptability_modify_move,
};