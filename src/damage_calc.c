#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/pkmn_bank_stats.h"
#include "battle_state.h"
#include "moves/moves.h"
#include "battle_text/battle_pick_message.h"

extern u16 rand_range(u16, u16);
extern u8 effectiveness_chart[342];
extern bool b_pkmn_has_type(u8 bank, enum PokemonType type);
extern void dprintf(const char * str, ...);

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

#define MOVE_ONDAMAGE_CALLBACK 0
#define MOVE_BASEPOWER_CALLBACK 0
u16 get_base_damage(u8 attacker, u8 defender, u16 move)
{
    if (IS_OHKO(move))
        return (TOTAL_HP(defender));
    
    // moves like counter/bide/seismic toss calc damage outside of the formula & ignore type immunities
    if (MOVE_ONDAMAGE_CALLBACK) {
        // return on damage callback's return value; TODO
    }
    
    if (B_MOVE_IS_STATUS(attacker))
        return 0;
    
    if (B_MOVE_DMG(attacker)) {
        return B_MOVE_DMG(attacker);
    }

    s8 base_power = B_MOVE_POWER(attacker);
    if (MOVE_BASEPOWER_CALLBACK) {
        // TODO Base power callback execution
        base_power = MOVE_BASEPOWER_CALLBACK;
    }
 
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
    p_bank[attacker]->b_data.crit_mod += MOVE_CRIT(move);
    if ((rand_range(0, 100)) <= B_CRITCHANCE_STAT(attacker)) {
        B_MOVE_WILL_CRIT_SET(attacker, true);
        modded_base = NUM_MOD(modded_base, 150);
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
        (move != MOVE_FACADE)) {
        modded_base = NUM_MOD(modded_base, 50);
    }
    
    battle_master->queue_size = q_size;
    battle_master->queue_front_index = q_front;
    return modded_base;
}

s16 get_damage(u8 attacker, u8 defender, u16 move)
{       
    // get base damage
    u16 base_dmg = get_base_damage(attacker, defender, move);

    // if base damage is 0, target is immune. Display text and exit TODO
    if (base_dmg == 0)
        return 0;

    // return damage
    u16 result = modify_damage(base_dmg, attacker, defender, move);
    return MAX(result, 1);
}



/*

	modifyDamage(baseDamage, pokemon, target, move, suppressMessages) {
		if (!move.type) move.type = '???';
		let type = move.type;

		baseDamage += 2;

		// multi-target modifier (doubles only)
		if (move.spreadHit) {
			let spreadModifier = move.spreadModifier || 0.75;
			this.debug('Spread modifier: ' + spreadModifier);
			baseDamage = this.modify(baseDamage, spreadModifier);
		}

		// weather modifier
		baseDamage = this.runEvent('WeatherModifyDamage', pokemon, target, move, baseDamage);

		// crit
		if (move.crit) {
			baseDamage = this.modify(baseDamage, move.critModifier || (this.gen >= 6 ? 1.5 : 2));
		}

		// this is not a modifier
		baseDamage = this.randomizer(baseDamage);

		// STAB
		if (move.hasSTAB || type !== '???' && pokemon.hasType(type)) {
			// The "???" type never gets STAB
			// Not even if you Roost in Gen 4 and somehow manage to use
			// Struggle in the same turn.
			// (On second thought, it might be easier to get a Missingno.)
			baseDamage = this.modify(baseDamage, move.stab || 1.5);
		}
		// types
		move.typeMod = target.runEffectiveness(move);

		move.typeMod = this.clampIntRange(move.typeMod, -6, 6);
		if (move.typeMod > 0) {
			if (!suppressMessages) this.add('-supereffective', target);

			for (let i = 0; i < move.typeMod; i++) {
				baseDamage *= 2;
			}
		}
		if (move.typeMod < 0) {
			if (!suppressMessages) this.add('-resisted', target);

			for (let i = 0; i > move.typeMod; i--) {
				baseDamage = Math.floor(baseDamage / 2);
			}
		}

		if (move.crit && !suppressMessages) this.add('-crit', target);

		if (pokemon.status === 'brn' && move.category === 'Physical' && !pokemon.hasAbility('guts')) {
			if (this.gen < 6 || move.id !== 'facade') {
				baseDamage = this.modify(baseDamage, 0.5);
			}
		}

		// Generation 5 sets damage to 1 before the final damage modifiers only
		if (this.gen === 5 && !Math.floor(baseDamage)) {
			baseDamage = 1;
		}

		// Final modifier. Modifiers that modify damage after min damage check, such as Life Orb.
		baseDamage = this.runEvent('ModifyDamage', pokemon, target, move, baseDamage);

		// TODO: Find out where this actually goes in the damage calculation
		if (move.isZ && move.zBrokeProtect) {
			baseDamage = this.modify(baseDamage, 0.25);
			this.add('-message', target.name + " couldn't fully protect itself and got hurt! (placeholder)");
		}

		if (this.gen !== 5 && !Math.floor(baseDamage)) {
			return 1;
		}

		return Math.floor(baseDamage);
	}
    */

