#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"

extern u16 rand_range(u16, u16);
extern bool b_pkmn_has_type(u8 bank, enum PokemonType type);
extern void dprintf(const char * str, ...);
extern u8 exec_anonymous_callback(u8 CB_id, u8 attacker, u8 defender, u16 move);

u16 type_effectiveness_mod(u8 attacker, u8 defender, u16 move)
{
    u8 i, j;
    u16 percent = 100;
    // for each type of the attacker's move
    for (i = 0; i < sizeof(battle_master->b_moves[B_MOVE_BANK(attacker)].type); i++) {
        // get the type effectiveness for each type of the defender
        for (j = 0; j < sizeof(p_bank[defender]->b_data.type); j++) {
            if ((B_MOVE_TYPE(attacker, i) != MTYPE_EGG) && (B_PKMN_TYPE(defender, j) != MTYPE_EGG)) {
                u8 target_type = B_PKMN_TYPE(defender, j);
                u8 move_type = B_MOVE_TYPE(attacker, i);
				if (move_type == MTYPE_NONE)
					return percent;
                u16 move_effectiveness = MOVE_EFFECTIVENESS(target_type, move_type);
                if (move_effectiveness > 0) {
                    percent = NUM_MOD(percent, move_effectiveness);
                } else {
                    // target has an immunity, return 0
                    return 0;
                }
            }
        }
    }
    return percent;
}


u16 weather_dmg_mod(u16 damage, u8 attacker)
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

/* TODO utilize priority */
u16 move_on_base_power_move(u8 base_power, u8 attacker, u8 defender, u16 move)
{
    if (moves[move].on_base_power_move) {
        return moves[move].on_base_power_move(base_power, attacker, defender, move);
    } else {
        return base_power;
    }
}

u16 move_on_damage_callback(u16 damage_taken, u8 attacker, u8 defender, u16 move)
{
    if (moves[move].on_damage_move) {
        return moves[move].on_damage_move(damage_taken, attacker, defender, move);
    }
    return 0;
}


u16 get_base_damage(u8 attacker, u8 defender, u16 move)
{
    // moves like counter/bide/seismic toss calc damage outside of the formula & ignore type immunities
    u16 predmg = move_on_damage_callback(p_bank[attacker]->b_data.last_damage, attacker, defender, move);
    if (predmg) {
        return predmg;
    }

    if (B_MOVE_IS_STATUS(attacker))
        return 0;


    u8 base_power = B_MOVE_POWER(attacker);
    u8 new_power = exec_anonymous_callback(CB_ON_BASE_POWER_MOVE, attacker, TARGET_OF(attacker), move);
    if (new_power) {
      base_power = new_power;
    }
    base_power = move_on_base_power_move(base_power, attacker, defender, move);

    // get defending and attacking stats
    enum MoveCategory atk_category = B_MOVE_CATEGORY(attacker);
    enum MoveCategory def_category;
    if (CAT_OVERRIDE(move)) {
        def_category = B_MOVE_IS_PHYSICAL(attacker) ? MOVE_SPECIAL : MOVE_PHYSICAL;
    } else {
        def_category = B_MOVE_CATEGORY(attacker);
    }

    s8 atk_mod[2] = {0, 0};
    s8 def_mod[2] = {0, 0};
    u16 atk_stat, def_stat;

    // temporarily remove effects of boosts
    if (B_MOVE_IGNORE_ATK(attacker)) {
        atk_mod[0] = p_bank[attacker]->b_data.attack;
        atk_mod[1] = p_bank[attacker]->b_data.sp_atk;
        p_bank[attacker]->b_data.attack = 0;
        p_bank[attacker]->b_data.sp_atk = 0;
    }

    if (B_MOVE_IGNORE_DEF(attacker)) {
        def_mod[0] = p_bank[defender]->b_data.attack;
        def_mod[1] = p_bank[defender]->b_data.sp_atk;
        p_bank[defender]->b_data.attack = 0;
        p_bank[defender]->b_data.sp_atk = 0;
    }

    // foul play sets this flag
    if (STEAL_OFFENSIVE(move)) {
        atk_stat = (atk_category == MOVE_PHYSICAL) ? B_ATTACK_STAT(defender) : B_SPATTACK_STAT(defender);
    } else {
        atk_stat = (atk_category == MOVE_PHYSICAL) ? B_ATTACK_STAT(attacker) : B_SPATTACK_STAT(attacker);
    }
    def_stat = (def_category == MOVE_PHYSICAL)? B_DEFENSE_STAT(defender) : B_SPDEFENSE_STAT(defender);

    // restore boosts if they were removed
    if (B_MOVE_IGNORE_ATK(attacker)) {
        p_bank[attacker]->b_data.attack = atk_mod[0];
        p_bank[attacker]->b_data.sp_atk = atk_mod[1];
    }

    if (B_MOVE_IGNORE_DEF(attacker)) {
        p_bank[defender]->b_data.attack = def_mod[0];
        p_bank[defender]->b_data.sp_atk = def_mod[1];
    }

    // Calc base damage - broken up for readability
    u16 dmg = ((B_LEVEL(attacker) * 2) / 5) + 2;
    dmg *= base_power;
    dmg = NUM_MOD(dmg, ((atk_stat * 100) / def_stat));
    dmg = (dmg/ 50) + 2;
    return dmg;
}

u16 modify_damage(u16 base_damage, u8 attacker, u8 defender, u16 move)
{
    /* record message queue properties - setting them back after the function completes
    is a way to suppress messages */
    u8 q_size = battle_master->queue_size;
    u8 q_front = battle_master->queue_front_index;

    u16 modded_base = base_damage;

    // Targets mod
    u8 targets_mod;
    switch (battle_type_flags) {
        case BATTLE_FLAG_PARTNER:
            /* TODO : Check if other targets are alive & move is spread */
            targets_mod = 75;
            break;
        default:
            targets_mod = 100;
    };
    modded_base = NUM_MOD(modded_base, targets_mod);

    // Weather Mod
    modded_base = weather_dmg_mod(modded_base, attacker);

    // critical Mod
    if (!B_MOVE_CAN_CRIT(attacker)) {
        p_bank[attacker]->b_data.crit_mod += MOVE_CRIT(move);
        if ((rand_range(0, 100)) <= B_CRITCHANCE_STAT(attacker)) {
            B_MOVE_WILL_CRIT_SET(attacker, true);
            modded_base = NUM_MOD(modded_base, 150);
        }
    }
    // random factor
    modded_base = NUM_MOD(modded_base, rand_range(85, 100));

    // stab calc
    u8 i;
    for (i = 0; i < 2; i++) {
        if ((B_MOVE_TYPE(attacker, i) != MTYPE_EGG) && (b_pkmn_has_type(attacker, B_MOVE_TYPE(attacker, i)))) {
            modded_base = NUM_MOD(modded_base, B_MOVE_STAB(attacker));
            break;
        }
    }

    // type modifications
    u16 type_effect_percent = type_effectiveness_mod(attacker, defender, move);
    if (type_effect_percent > 100) {
        B_MOVE_EFFECTIVENESS(attacker) = TE_SUPER_EFFECTIVE;
    } else if (type_effect_percent == 100) {
        B_MOVE_EFFECTIVENESS(attacker) = TE_EFFECTIVE;
    } else if (type_effect_percent > 0) {
        B_MOVE_EFFECTIVENESS(attacker) = TE_NOT_VERY_EFFECTIVE;
    } else {
        B_MOVE_EFFECTIVENESS(attacker) = TE_IMMUNE;
    }
    modded_base = NUM_MOD(modded_base, type_effect_percent);

    // burn ailment attack reduction
    if ((B_STATUS(attacker) == AILMENT_BURN) &&
        (B_MOVE_CATEGORY(attacker) == MOVE_PHYSICAL) &&
        (BANK_ABILITY(attacker) != ABILITY_GUTS) &&
        (move != MOVE_FACADE) && (!B_MOVE_WILL_CRIT(attacker))) {
        modded_base = NUM_MOD(modded_base, 50);
    }

    battle_master->queue_size = q_size;
    battle_master->queue_front_index = q_front;
    return modded_base;
}

s16 get_damage(u8 attacker, u8 defender, u16 move)
{
	if (B_MOVE_DMG(attacker)) {
        u16 percent = type_effectiveness_mod(attacker, defender, move);
        if (percent) {
            B_MOVE_EFFECTIVENESS(attacker) = TE_EFFECTIVE;
            return B_MOVE_DMG(attacker);
        } else {
            B_MOVE_EFFECTIVENESS(attacker) = TE_IMMUNE;
            return (0);
        }
    }

    if (IS_OHKO(move)) {
        battle_master->b_moves[B_MOVE_BANK(attacker)].effectiveness = TE_OHKO;
        return (TOTAL_HP(defender));
    }
    // get base damage
    u16 base_dmg = get_base_damage(attacker, defender, move);

    // if base damage is 0, target is immune. Display text and exit TODO
    if (base_dmg == 0)
        return 0;

    // return damage
    u16 result = modify_damage(base_dmg, attacker, defender, move);
    return MAX(result, 1);
}
