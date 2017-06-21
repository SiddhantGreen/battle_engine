#include <pokeagb/pokeagb.h>
#include "moves/moves.h"
#include "battle_data/pkmn_bank_stats.h"

u16 rand_range(u16 min, u16 max)
{
    return (rand() / (0xFFFF / (max - min))) + min;
}

bool knows_move(u16 move_id, struct Pokemon* p)
{
    u8 i;
    for (i = REQUEST_MOVE1; i < (REQUEST_MOVE1 + 4); i++) {
        u16 move = pokemon_getattr(p, i, NULL);
        if (move == move_id)
            return true;
    }
    return false;
}

u8 get_side(u8 bank)
{
    return (bank > 1) ? 1 : 0;
}


u8 get_opponent_side(u8 bank)
{
    return ((!(get_side(bank))) * 2);
}

u8 get_ability(struct Pokemon* p)
{
    u8 ability_bit = pokemon_getattr(p, REQUEST_ABILITY_BIT, NULL);
    return pokemon_base_stats[pokemon_getattr(p, REQUEST_SPECIES, NULL)].ability[ability_bit];
}

u8 get_ability_bank(u8 bank)
{
    return p_bank[bank]->b_data.ability;
}

bool ignoring_item(struct Pokemon* p)
{
    return (get_ability(p) == ABILITY_KLUTZ);
}

/* TODO: Update this function. Hard coded and too short sighted */
u8 move_target(u8 bank, u16 move_id)
{
    if (*(move_t[move_id].m_flags) & FLAG_ONSELF) {
        return bank;
    } else {
        return (bank) ? 0 : 2;
    }
}


bool pkmn_has_type(u16 species, enum PokemonType type)
{
    if ((pokemon_base_stats[species].type[0] == type) || (pokemon_base_stats[species].type[1] == type)) {
        return true;
    }
    return false;
}

bool b_pkmn_has_type(u8 bank, enum PokemonType type)
{
    u8 i;
    for (i = 0; i < 2; i++) {
        if (p_bank[bank]->b_data.type[i] == type) {
            return true;
        }
    }
    return false;
}

u8 get_base_power(u16 move_id)
{
    return move_t[move_id].base_power;
}

s8 move_effectiveness(u8 move_type, u8 target_bank)
{
    extern u8 effectiveness_chart[342];
    // -3 : 1/8x dmg
    // -2 : 1/4x dmg
    // -1 : 1/2x dmg
    //  0 : 1x damage
    // +1 : 2x dmg
    // +2 : 4x dmg
    // +3 : 6x dmg
    s8 effectiveness = 0;
    u8 i;
    for (i = 0; i < 3; i ++) {
        // if one of the types are immune, return 3
        u8 target_type = p_bank[target_bank]->b_data.type[i];
        if (MOVE_EFFECTIVENESS(target_type, move_type) == 3)
            return 0xFF;
        if (MOVE_EFFECTIVENESS(target_type, move_type) == 2)
            effectiveness--;
        if (MOVE_EFFECTIVENESS(target_type, move_type) == 1)
            effectiveness++;
    }
    return effectiveness;
}

void stat_boost(u8 bank, u8 stat_id, s8 amount)
{
    extern void build_message(u8 state, u16 move_id, u8 user_bank, enum battle_string_ids id, u16 move_effect_id);
    switch (stat_id) {
        case REQUEST_ATK:
            {
            p_bank[bank]->b_data.attack += amount;
            break;
            }
        case REQUEST_DEF:
            {
            p_bank[bank]->b_data.defense += amount;
            break;
            }
        case REQUEST_SPD:
            {
            p_bank[bank]->b_data.speed += amount;
            break;
            }
        case REQUEST_SPATK:
            {
            p_bank[bank]->b_data.sp_atk += amount;
            break;
            }
        case REQUEST_SPDEF:
            {
            p_bank[bank]->b_data.sp_def += amount;
            break;
            }
        case 51: // evasion
            {
            p_bank[bank]->b_data.evasion += amount;
            break;
            }
        case 52: // accuracy
            {
            p_bank[bank]->b_data.accuracy += amount;
            break;
            }
        case 53: // crit
            {
            p_bank[bank]->b_data.crit_mod += amount;
            break;
            }
    };

    amount += 6;
    switch (amount) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            build_message(GAME_STATE, 0, bank, STRING_STAT_MOD_HARSH_DROP, stat_id);
            break;
        case 5:
            build_message(GAME_STATE, 0, bank, STRING_STAT_MOD_DROP, stat_id);
            break;
        case 6:
            break;
        case 7:
            build_message(GAME_STATE, 0, bank, STRING_STAT_MOD_RISE, stat_id);
            break;
        default:
            build_message(GAME_STATE, 0, bank, STRING_STAT_MOD_HARSH_RISE, stat_id);
            break;
    };
    
}

