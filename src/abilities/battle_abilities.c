#include <pokeagb/pokeagb.h>
#include "moves/moves.h"
#include "battle_abilities.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/battle_state.h"


extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool set_weather(enum WeatherTypes weather);
extern bool b_pkmn_set_type(u8 bank, enum PokemonType type);
extern void stat_boost(u8 bank, u8 stat_id, s8 amount, u8 inflicting_bank);
extern u16 rand_range(u16, u16);
extern bool disable_on_disable_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 move_pp_count(u16 move_id, u8 bank);
extern void set_status(u8 bank, enum Effect status);
/* Note: Illuminate and Honey Gather have no In-Battle effect so they are not present here*/


// None
u8 ability_none_on_effect(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    // This is just an example
    return true;
}

// Stench
void stench_on_damage(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    if (user != source) return;
    if (B_MOVE_DMG(user) > 0) {
        B_MOVE_FLINCH(user) = 10;
    }
    return;
}

// Drizzle
void drizzle_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (HAS_VOLATILE(VOLATILE_DRIZZLE, src)) return;
    ADD_VOLATILE(VOLATILE_DRIZZLE, src);
    if (battle_master->field_state.is_raining) return;
    set_weather(WEATHER_RAIN);
}

// Speed Boost
u8 speedboost_on_residual(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
	if (user != source) return true;
	stat_boost(user, SPEED_MOD, 1, user);
	return true;
}

// BATTLEARMOR

// STURDY

// DAMP

// Limber
u8 limber_on_status(u8 user, u8 source, u16 ailment , struct anonymous_callback* acb)
{
    if (user != source) return true;
    if (ailment == AILMENT_PARALYZE) {
    	enqueue_message(NULL, user, STRING_IMMUNE_ABILITY, NULL);
       	return false;
    }
    return true;
}

// SANDVEIL

// STATIC
u8 static_on_effect(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
	if (TARGET_OF(user) != source) return true;
	if (!IS_CONTACT(move) || B_MOVE_REMOVE_CONTACT(user)) return true;
	if (rand_range(1, 100) <= 30) {
		set_status(user, EFFECT_PARALYZE);
	}
	return true;
}

// VOLTABSORB

// WATERABSORB

// OBLIVIOUS

// CLOUDNINE

// COMPOUNDEYES

// Insomnia
u8 insomnia_on_status(u8 user, u8 source, u16 ailment , struct anonymous_callback* acb)
{
    if (user != source) return true;
    if (ailment == AILMENT_SLEEP) {
    	enqueue_message(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// Color Change
void colorchange_on_after_move(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    if (user != source) return;
    if ((B_MOVE_DMG(user) > 0) && (!B_MOVE_HAS_TYPE(user, MTYPE_NONE))) {
    	 u8 type = B_MOVE_TYPE(TARGET_OF(user), 0);
    	 b_pkmn_set_type(TARGET_OF(user), type);
    	 enqueue_message(NULL, user, STRING_CONVERSION_TYPE, type);
    }
    return;
}

// Immunity
u8 immunity_on_status(u8 user, u8 source, u16 ailment , struct anonymous_callback* acb)
{
    if (user != source) return true;
    if (ailment == AILMENT_POISON) {
    	enqueue_message(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// FLASHFIRE

// SHIELDDUST

// OWNTEMPO

// SUCTIONCUPS

// INTIMIDATE

// SHADOWTAG

// ROUGHSKIN
u8 rough_skin_on_effect(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
	if (TARGET_OF(user) != source) return true;
	if (!IS_CONTACT(move) || B_MOVE_REMOVE_CONTACT(user)) return true;
	do_damage(user, TOTAL_HP(user) >> 3);
	return true;
}

// WONDERGUARD

// LEVITATE

// EFFECTSPORE
u8 effect_spore_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
    // Immunity in the case of overcoat
    if (BANK_ABILITY(user) == ABILITY_OVERCOAT) return true;
    if (!IS_CONTACT(move) || B_MOVE_REMOVE_CONTACT(user)) return true;
    u16 rand_num = rand_range(0, 100);
    if (rand_num < 10) {
        set_status(user, EFFECT_SLEEP);
    } else if (rand_num < 20) {
        set_status(user, EFFECT_PARALYZE);
    } else if (rand_num < 30) {
        set_status(user, EFFECT_POISON);
    }
    return true;
}

// SYNCHRONIZE

// CLEARBODY

// NATURALCURE

// LIGHTNINGROD

// SERENEGRACE

// SWIFTSWIM

// CHLOROPHYLL

// TRACE

// HUGEPOWER

// Poison Point
u8 poisonpoint_on_effect(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
	if (TARGET_OF(user) != source) return true;
	if (!IS_CONTACT(move) || B_MOVE_REMOVE_CONTACT(user)) return true;
    if (rand_range(0, 100) <= 30)
	   set_status(user, EFFECT_POISON);
	return true;
}

// INNERFOCUS

// Magma Armor
u8 magmaarmor_on_status(u8 user, u8 source, u16 ailment , struct anonymous_callback* acb)
{
    if (user != source) return true;
    if (ailment == AILMENT_FREEZE) {
    	enqueue_message(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// Water Veil
u8 waterveil_on_status(u8 user, u8 source, u16 ailment , struct anonymous_callback* acb)
{
    if (user != source) return true;
    if (ailment == AILMENT_BURN) {
    	enqueue_message(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// MAGNETPULL

// SOUNDPROOF

// RAINDISH

// Sand Stream
void sandstream_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (HAS_VOLATILE(VOLATILE_SANDSTREAM, src)) return;
    ADD_VOLATILE(VOLATILE_SANDSTREAM, src);
    if (battle_master->field_state.is_sandstorm) return;
    set_weather(WEATHER_SANDSTORM);
}

// PRESSURE

// THICKFAT

// EARLYBIRD

// Flame Body
u8 flamebody_on_effect(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
	if (TARGET_OF(user) != source) return true;
	if (IS_CONTACT(move)) {
		if (rand_range(1,100) <= 30) {
			B_STATUS(user) = AILMENT_BURN;
			enqueue_message(NULL, user, STRING_AILMENT_APPLIED, B_STATUS(user));
		}
	}
	return true;
}

// RUNAWAY

// KEENEYE

// HYPERCUTTER

// PICKUP

// TRUANT

// HUSTLE

// CUTECHARM

// PLUS

// MINUS

// FORECAST

// STICKYHOLD

// SHEDSKIN

// GUTS

// MARVELSCALE

// LIQUIDOOZE
void liquid_ooze_on_drain(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) !=  src) return;
    if (B_DRAIN(user))
        B_DRAIN(user) = -B_DRAIN(user);
}


// OVERGROW

// BLAZE

// TORRENT

// SWARM

// ROCKHEAD

// Drought
void drought_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (HAS_VOLATILE(VOLATILE_DROUGHT, src)) return;
    ADD_VOLATILE(VOLATILE_DROUGHT, src);
    if (battle_master->field_state.is_sunny) return;
    set_weather(WEATHER_SUN);
}

// ARENATRAP

// Vital Spirit
u8 vitalspirit_on_status(u8 user, u8 source, u16 ailment , struct anonymous_callback* acb)
{
    if (user != source) return true;
    if (ailment == AILMENT_SLEEP) {
    	enqueue_message(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// WHITESMOKE

// PUREPOWER

// SHELLARMOR

// AIRLOCK

// TANGLEDFEET

// MOTORDRIVE

// RIVALRY

// STEADFAST

// SNOWCLOAK

// GLUTTONY

// ANGERPOINT

// UNBURDEN

// HEATPROOF /* Not Completed Yet */
void heatproof_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != source) return;
    if (B_MOVE_HAS_TYPE (user, MTYPE_FIRE)) {
        B_MOVE_POWER(user) = B_MOVE_POWER(user) >> 1;
    }
}

// Simple
bool simple_on_stat_boost_mod(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != source) return true;
    CURRENT_ACTION->priv[1] = ((CURRENT_ACTION->priv[1]) << 1);
    return true;
}

// DRYSKIN

// DOWNLOAD

// Iron Fist
void ironfist_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    if (user != source) return;
	if (IS_PUNCH(move)) {
	    B_MOVE_POWER(user) = NUM_MOD(B_MOVE_POWER(user), 120);
    }
    return;
}

// POISONHEAL

// Adaptability
void adaptability_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    if (user != source) return;
	if (B_MOVE_STAB(user)) {
	    B_MOVE_POWER(user) = NUM_MOD(B_MOVE_POWER(user), 133);
    }
    return;
}


// SKILLLINK

// HYDRATION

// SOLARPOWER

// QUICKFEET

// NORMALIZE

// SNIPER

// MAGICGUARD

// NOGUARD

// STALL

// Technician
void technician_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    if (user != source) return;
	if (B_MOVE_POWER(user) <= 60) {
	    B_MOVE_POWER(user) = NUM_MOD(B_MOVE_POWER(user), 150);
	}
	return;
}

// LEAFGUARD

// KLUTZ

// MOLDBREAKER

// SUPERLUCK

// AFTERMATH

// ANTICIPATION

// FOREWARN

// UNAWARE

// Tinted Lens
void tintedlens_on_damage(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    if (user != source) return;
	if (B_MOVE_EFFECTIVENESS(user) == TE_NOT_VERY_EFFECTIVE) {
	    B_MOVE_DMG(user) = NUM_MOD(B_MOVE_DMG(user), 200);
    }
    return;
}

// Filter, Solid Rock and Prism Armor
void filter_variations_on_damage(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != source) return;
    if (B_MOVE_EFFECTIVENESS(user) == TE_SUPER_EFFECTIVE) {
        B_MOVE_DMG(user) = NUM_MOD(B_MOVE_DMG(user), 75);
    }
    return;
}

// SLOWSTART

// SCRAPPY

// STORMDRAIN

// ICEBODY

// Snow Warning
void snowwarning_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (HAS_VOLATILE(VOLATILE_SNOWWARNING, src)) return;
    ADD_VOLATILE(VOLATILE_SNOWWARNING, src);
    if (battle_master->field_state.is_hail) return;
    set_weather(WEATHER_HAIL);
}

// FRISK

// Reckless
void reckless_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    if (user != source) return;
	if (MOVE_RECOIL(move)) {
        B_MOVE_POWER(user) = NUM_MOD(B_MOVE_POWER(user), 120);
    }
    return;
}

// MULTITYPE

// FLOWERGIFT

// BADDREAMS

// PICKPOCKET

// SHEERFORCE

// Contary
bool contrary_on_stat_boost_mod(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != source) return true;
    CURRENT_ACTION->priv[1] = -CURRENT_ACTION->priv[1];
    return true;
}

// UNNERVE

// DEFIANT
void defiant_after_stat_boost_mod(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != source) return;
    if (SIDE_OF((CURRENT_ACTION)->action_bank) != SIDE_OF(user) && ((CURRENT_ACTION)->priv[1] < 0))
        stat_boost(user, STAT_ATTACK - 1, 2, user);
}

// DEFEATIST

// CURSEDBODY
u8 cursed_body_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    // no effect on self or if not targetted
    if ((TARGET_OF(user) != src) || (user == src)) return true;

    // 30% chance to disable move, if it did dmg
    if ((B_MOVE_DMG(user) != 0) && (rand_range(0, 100) <= 100)) {
        // fail if attacker's move has no PP left
        if (move_pp_count(move, user) < 1) return true;
        // fail if effect already active on target
        if (HAS_VOLATILE(user, VOLATILE_DISABLE)) return true;
        u8 id = add_callback(CB_ON_DISABLE_MOVE, 0, 4, user, (u32)disable_on_disable_move);
        ADD_VOLATILE(user, VOLATILE_DISABLE);
        CB_MASTER[id].data_ptr = move;
        enqueue_message(move, user, STRING_DISABLED, 0);
    }
    return true;
}

// HEALER

// FRIENDGUARD

// WEAKARMOR
u8 weak_armor_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return true;
    if (B_MOVE_IS_PHYSICAL(user)) {
        stat_boost(src, DEFENSE_MOD, -1, user);
        stat_boost(src, SPEED_MOD, 2, user);
    }
    return true;
}

// HEAVYMETAL

// LIGHTMETAL

// MULTISCALE

// TOXICBOOST

// FLAREBOOST

// HARVEST

// TELEPATHY

// MOODY

// OVERCOAT

// POISONTOUCH

// REGENERATOR

// BIGPECKS

// SANDRUSH

// WONDERSKIN

// ANALYTIC

// ILLUSION

// IMPOSTER

// INFILTRATOR

// MUMMY

// MOXIE

// JUSTIFIED
u8 justified_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return true;
    if (B_MOVE_HAS_TYPE(user, MTYPE_DARK))
        stat_boost(src, ATTACK_MOD, 1, user);
    return true;
}

// RATTLED

// MAGICBOUNCE

// SAPSIPPER

// PRANKSTER

// SANDFORCE

// IRONBARBS

// ZENMODE

// VICTORYSTAR

// TURBOBLAZE

// TERAVOLT

// AROMAVEIL

// FLOWERVEIL

// CHEEKPOUCH

// PROTEAN

// FURCOAT

// MAGICIAN

// BULLETPROOF

// COMPETITIVE
void competitive_after_stat_boost_mod(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != source) return;
    if (SIDE_OF((CURRENT_ACTION)->action_bank) != SIDE_OF(user) && ((CURRENT_ACTION)->priv[1] < 0))
        stat_boost(user, STAT_SPECIAL_ATTACK - 1, 2, user);
}

// Strong Jaw
void strongjaw_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    if (user != source) return;
	if (IS_BITE(move)) {
	    B_MOVE_POWER(user) = NUM_MOD(B_MOVE_POWER(user), 150);
    }
    return;
}

// REFRIGERATE

// SWEETVEIL

// STANCECHANGE

// GALEWINGS

// Mega Launcher
void megalauncher_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    if (user != source) return;
	if (IS_PULSE(move)) {
	    B_MOVE_POWER(user) = NUM_MOD(B_MOVE_POWER(user), 150);
    }
    return;
}

// GRASSPELT

// SYMBIOSIS

// TOUGHCLAWS

// PIXILATE

// GOOEY

// AERILATE

// PARENTALBOND

// DARKAURA

// FAIRYAURA

// AURABREAK

// PRIMORDIALSEA

// DESOLATELAND

// DELTASTREAM

// STAMINA
u8 stamina_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return true;
    if (B_MOVE_DMG(user) > 0)
        stat_boost(src, DEFENSE_MOD, 1, user);
    return true;
}

// WIMPOUT

// EMERGENCYEXIT

// WATERCOMPACTION
u8 water_compaction_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return true;
    if (B_MOVE_HAS_TYPE(user, MTYPE_WATER))
        stat_boost(src, DEFENSE_MOD, 2, user);
    return true;
}

// MERCILESS

// SHIELDSDOWN

// STAKEOUT

// WATERBUBBLE

// Steel Worker
void steelworker_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
    if (user != source) return;
	if (B_MOVE_HAS_TYPE(user, MTYPE_STEEL)) {
	    B_MOVE_POWER(user) = NUM_MOD(B_MOVE_POWER(user), 150);
	}
	return;
}

// BERSERK

// SLUSHRUSH

// LONGREACH

// LIQUIDVOICE

// TRIAGE

// GALVANIZE

// SURGESURFER

// SCHOOLING

// DISGUISE

// BATTLEBOND

// POWERCONSTRUCT

// CORROSION

// COMATOSE

// QUEENLYMAJESTY

// INNARDSOUT

// DANCER

// BATTERY

// FLUFFY

// DAZZLING

// SOUL

// TANGLINGHAIR

// RECEIVER

// POWEROFALCHEMY

// BEASTBOOST

// RKSSYSTEM

// ELECTRICSURGE

// PSYCHICSURGE

// MISTYSURGE

// GRASSYSURGE

// FULLMETAL

// SHADOWSHIELD

// NEUROFORCE
