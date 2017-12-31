#include <pokeagb/pokeagb.h>
#include "moves/moves.h"
#include "battle_abilities.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/pkmn_bank.h"
#include "../status_effects/stat_boost_info.h"
#include "../battle_data/battle_state.h"


extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool set_weather(enum WeatherTypes weather);
extern bool b_pkmn_set_type(u8 bank, enum PokemonType type);
extern void stat_boost(u8 bank, u8 stat_id, s8 amount, u8 inflicting_bank);
extern u16 rand_range(u16, u16);


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
	if (IS_CONTACT(move)) {
		if (rand_range(1,100) <= 30) {
			B_STATUS(user) = AILMENT_PARALYZE;
			enqueue_message(NULL, user, STRING_AILMENT_APPLIED, AILMENT_PARALYZE);
		}
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

// WONDERGUARD

// LEVITATE

// EFFECTSPORE

// SYNCHRONIZE

// CLEARBODY

// NATURALCURE

// LIGHTNINGROD

// SERENEGRACE

// SWIFTSWIM

// CHLOROPHYLL

// ILLUMINATE

// TRACE

// HUGEPOWER

// Poison Point
u8 poisonpoint_on_effect(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
	if (TARGET_OF(user) != source) return true;
	if (IS_CONTACT(move)) {
		if (rand_range(1,100) <= 30) {
			B_STATUS(user) = AILMENT_POISON;
			enqueue_message(NULL, user, STRING_AILMENT_APPLIED, AILMENT_POISON);
		}
	}
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
			enqueue_message(NULL, user, STRING_AILMENT_APPLIED, AILMENT_BURN);
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
u8 simple_on_stat_boost_mod(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != source) return 0;
    RETRIEVE_ADDITIONAL_DATA_FOR_STAT_BOOST_MOD();
    return STORE_STAT_BOOST_MOD_RESULT((macro_param_is_negative), (macro_param_amount*2));
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

// HONEYGATHER

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
u8 contrary_on_stat_boost_mod(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != source) return 0;
    RETRIEVE_ADDITIONAL_DATA_FOR_STAT_BOOST_MOD();
    return STORE_STAT_BOOST_MOD_RESULT((!macro_param_is_negative), (macro_param_amount));
}

// UNNERVE

// DEFIANT
void defiant_after_stat_boost_mod(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != source) return;
    RETRIEVE_ADDITIONAL_DATA_FOR_STAT_BOOST_MOD();
    if (SIDE_OF(macro_param_inflicting_bank) != SIDE_OF(user) && macro_param_is_negative && (macro_param_amount > 0))
        stat_boost(user, STAT_ATTACK - 1, 2, user);
}

// DEFEATIST

// CURSEDBODY

// HEALER

// FRIENDGUARD

// WEAKARMOR

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
    RETRIEVE_ADDITIONAL_DATA_FOR_STAT_BOOST_MOD();
    if (SIDE_OF(macro_param_inflicting_bank) != SIDE_OF(user) && macro_param_is_negative && (macro_param_amount > 0))
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

// WIMPOUT

// EMERGENCYEXIT

// WATERCOMPACTION

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
