#include <pokeagb/pokeagb.h>
#include "moves/moves.h"
#include "battle_abilities.h"


struct ability_data abilities[] = {
	{
		// None - Example
		.before_turn = NULL,
		.before_switch = NULL,
		.before_move = NULL,
		.on_fail = NULL,
		.on_modify_move = NULL,
		.on_tryhit = NULL,
		.on_base_power = NULL,
		.on_damage = NULL,
		.on_effect = ability_none_on_effect,
		.on_after_move = NULL,
		.on_status = NULL,
	},
	{
		// Stench
		.on_damage = stench_on_damage,
	},
	{
		// Drizzle
		.on_start = drizzle_on_start,
	},
	{
		// Speed Boost
		.on_residual = speedboost_on_residual,
	},
	{
		// BATTLEARMOR
	},
	{
		// STURDY
	},
	{
		// DAMP
	},
	{
		// Limber
		.on_status = limber_on_status,
	},
	{
		// SANDVEIL
	},
	{
		// Static
		.on_effect = static_on_effect,
	},
	{
		// VOLTABSORB
	},
	{
		// WATERABSORB
	},
	{
		// OBLIVIOUS
		.on_tryhit = oblivous_on_tryhit,
		.on_status = oblivious_on_status,
	},
	{
		// CLOUDNINE
	},
	{
		// COMPOUNDEYES
	},
	{
		// Insomnia
		.on_status = insomnia_on_status,
	},
	{
		// Color Change
		.on_after_move = colorchange_on_after_move,
	},
	{
		// Immunity
		.on_status = immunity_on_status,
	},
	{
		// FLASHFIRE
	},
	{
		// SHIELDDUST
	},
	{
		// OWNTEMPO
		.on_status = own_tempo_on_status,
	},
	{
		// SUCTIONCUPS
	},
	{
		// INTIMIDATE
	},
	{
		// SHADOWTAG
	},
	{
		// ROUGHSKIN
		.on_effect = rough_skin_on_effect,
	},
	{
		// WONDERGUARD
	},
	{
		// LEVITATE
	},
	{
		// EFFECTSPORE
		.on_effect = effect_spore_effect,
	},
	{
		// SYNCHRONIZE
	},
	{
		// CLEARBODY
		.on_stat_boost_mod = clear_body_on_stat_boost,
	},
	{
		// NATURALCURE
	},
	{
		// LIGHTNINGROD
	},
	{
		// SERENEGRACE
	},
	{
		// SWIFTSWIM
	},
	{
		// CHLOROPHYLL
	},
	{
		// Illuminate
		/* Note: This Ability has not in battle effect */
	},
	{
		// TRACE
	},
	{
		// HUGEPOWER
	},
	{
		// Poison Point
		.on_effect = poisonpoint_on_effect,
	},
	{
		// INNERFOCUS
	},
	{
		// Magma Armor
		.on_status = magmaarmor_on_status,
	},
	{
		// Water Veil
		.on_status = waterveil_on_status,
	},
	{
		// MAGNETPULL
	},
	{
		// SOUNDPROOF
	},
	{
		// RAINDISH
	},
	{
		// Sand Stream
		.on_start = sandstream_on_start,
	},
	{
		// PRESSURE
	},
	{
		// THICKFAT
	},
	{
		// EARLYBIRD
	},
	{
		// Flame Body
		.on_effect = flamebody_on_effect,
	},
	{
		// RUNAWAY
	},
	{
		// KEENEYE
		.on_stat_boost_mod = keen_eye_on_stat_boost,
		.on_stat = keen_eye_on_stat,
	},
	{
		// HYPERCUTTER
		.on_stat_boost_mod = hyper_cutter_on_stat_boost,
	},
	{
		// PICKUP
	},
	{
		// TRUANT
	},
	{
		// HUSTLE
	},
	{
		// CUTECHARM
		.on_effect = cute_charm_on_effect,
	},
	{
		// PLUS
	},
	{
		// MINUS
	},
	{
		// FORECAST
	},
	{
		// STICKYHOLD
	},
	{
		// SHEDSKIN
	},
	{
		// GUTS
	},
	{
		// MARVELSCALE
	},
	{
		// LIQUIDOOZE
		.on_drain = liquid_ooze_on_drain,
	},
	{
		// OVERGROW
	},
	{
		// BLAZE
	},
	{
		// TORRENT
	},
	{
		// SWARM
	},
	{
		// ROCKHEAD
	},
	{
		// Drought
		.on_start = drought_on_start,
	},
	{
		// ARENATRAP
	},
	{
		// Vital Spirit
		.on_status = vitalspirit_on_status,
	},
	{
		// WHITESMOKE
		.on_stat_boost_mod = white_smoke_on_stat_boost,
	},
	{
		// PUREPOWER
	},
	{
		// SHELLARMOR
	},
	{
		// AIRLOCK
	},
	{
		// TANGLEDFEET
	},
	{
		// MOTORDRIVE
	},
	{
		// RIVALRY
	},
	{
		// STEADFAST
	},
	{
		// SNOWCLOAK
	},
	{
		// GLUTTONY
	},
	{
		// ANGERPOINT
	},
	{
		// UNBURDEN
	},
	{
		// Heatproof
        	.on_base_power = heatproof_on_base_power,
	},
    	{
		// Simple
		.on_stat_boost_mod = simple_on_stat_boost_mod,
	},
	{
		// DRYSKIN
	},
	{
		// DOWNLOAD
	},
	{
		// Iron Fist
		.on_base_power = ironfist_on_base_power,
	},
	{
		// POISONHEAL
		.on_effect = poison_heal_on_effect,
	},
	{
		// Adaptability
		.on_base_power = adaptability_on_base_power,
	},
	{
		// SKILLLINK
	},
	{
		// HYDRATION
	},
	{
		// SOLARPOWER
	},
	{
		// QUICKFEET
	},
	{
		// NORMALIZE
	},
	{
		// SNIPER
	},
	{
		// MAGICGUARD
	},
	{
		// NOGUARD
	},
	{
		// STALL
	},
	{
		// Technician
		.on_base_power = technician_on_base_power,
	},
	{
		// LEAFGUARD
	},
	{
		// KLUTZ
	},
	{
		// MOLDBREAKER
	},
	{
		// SUPERLUCK
	},
	{
		// AFTERMATH
		.on_effect = aftermath_on_effect,
	},
	{
		// ANTICIPATION
	},
	{
		// FOREWARN
	},
	{
		// UNAWARE
	},
	{
		// Tinted Lens
		.on_damage = tintedlens_on_damage,
	},
	{
		// Filter
		.on_damage = filter_variations_on_damage,
	},
	{
		// SLOWSTART
	},
	{
		// SCRAPPY
		.on_effectiveness = scrappy_on_effectiveness,
	},
	{
		// STORMDRAIN
	},
	{
		// ICEBODY
	},
	{
		// Soild Rock
		.on_damage = filter_variations_on_damage,
	},
	{
		// Snow Warning
		.on_start = snowwarning_on_start,
	},
	{
		// Honey Gather
		/* Note: This Ability has not in battle effect */
	},
	{
		// FRISK
	},
	{
		// Reckless
		.on_base_power = reckless_on_base_power,
	},
	{
		// MULTITYPE
	},
	{
		// FLOWERGIFT
	},
	{
		// BADDREAMS
	},
	{
		// PICKPOCKET
		.after_stat_boost_mod = pick_pocket_on_secondary,
	},
	{
		// SHEERFORCE
	},
	{
		// Contary
		.on_stat_boost_mod = contrary_on_stat_boost_mod,
	},
	{
		// UNNERVE
	},
	{
		// Defiant
		.after_stat_boost_mod = defiant_after_stat_boost_mod,
	},
	{
		// DEFEATIST
	},
	{
		// CURSEDBODY
		.on_effect = cursed_body_on_effect,
	},
	{
		// HEALER
	},
	{
		// FRIENDGUARD
	},
	{
		// WEAKARMOR
		.on_effect = weak_armor_on_effect,
	},
	{
		// HEAVYMETAL
	},
	{
		// LIGHTMETAL
	},
	{
		// MULTISCALE
	},
	{
		// TOXICBOOST
	},
	{
		// FLAREBOOST
	},
	{
		// HARVEST
	},
	{
		// TELEPATHY
	},
	{
		// MOODY
	},
	{
		// OVERCOAT
	},
	{
		// POISONTOUCH
		.on_effect = poison_touch_on_effect,
	},
	{
		// REGENERATOR
	},
	{
		// BIGPECKS
		.on_stat_boost_mod = big_pecks_on_stat_boost,
	},
	{
		// SANDRUSH
	},
	{
		// WONDERSKIN
	},
	{
		// ANALYTIC
	},
	{
		// ILLUSION
	},
	{
		// IMPOSTER
	},
	{
		// INFILTRATOR
		.on_modify_move = infiltrator_modify_move,
	},
	{
		// MUMMY
		.on_effect = mummy_on_effect,
	},
	{
		// MOXIE
		.on_damage = moxie_on_damage,
	},
	{
		// JUSTIFIED
		.on_effect = justified_on_effect,
	},
	{
		// RATTLED
	},
	{
		// MAGICBOUNCE
	},
	{
		// SAPSIPPER
	},
	{
		// PRANKSTER
		.before_turn = prankser_before_turn,
	},
	{
		// SANDFORCE
	},
	{
		// IRONBARBS
		// rough skin clone
		.on_effect = rough_skin_on_effect,
	},
	{
		// ZENMODE
	},
	{
		// VICTORYSTAR
	},
	{
		// TURBOBLAZE
	},
	{
		// TERAVOLT
	},
	{
		// AROMAVEIL
	},
	{
		// FLOWERVEIL
		.on_stat_boost_mod = flower_veil_on_stat_boost,
		.on_status = flower_veil_on_status,
	},
	{
		// CHEEKPOUCH
	},
	{
		// PROTEAN
	},
	{
		// FURCOAT
	},
	{
		// MAGICIAN
	},
	{
		// BULLETPROOF
	},
	{
		// Competitive
		.after_stat_boost_mod = competitive_after_stat_boost_mod,
	},
	{
		// Strong Jaw
		.on_base_power = strongjaw_on_base_power,
	},
	{
		// REFRIGERATE
	},
	{
		// SWEETVEIL
		.on_status = sweet_veil_on_status,
	},
	{
		// STANCECHANGE
	},
	{
		// GALEWINGS
		.before_turn = gale_wings_before_turn,
	},
	{
		// Mega Launcher
		.on_base_power = megalauncher_on_base_power,
	},
	{
		// GRASSPELT
	},
	{
		// SYMBIOSIS
	},
	{
		// TOUGHCLAWS
	},
	{
		// PIXILATE
	},
	{
		// GOOEY
		.on_effect = gooey_on_effect,
	},
	{
		// AERILATE
	},
	{
		// PARENTALBOND
	},
	{
		// DARKAURA
	},
	{
		// FAIRYAURA
	},
	{
		// AURABREAK
	},
	{
		// PRIMORDIALSEA
	},
	{
		// DESOLATELAND
	},
	{
		// DELTASTREAM
	},
	{
		// STAMINA
		.on_effect = stamina_on_effect,
	},
	{
		// WIMPOUT
	},
	{
		// EMERGENCYEXIT
	},
	{
		// WATERCOMPACTION
		.on_effect = water_compaction_on_effect,
	},
	{
		// MERCILESS
	},
	{
		// SHIELDSDOWN
	},
	{
		// STAKEOUT
	},
	{
		// WATERBUBBLE
	},
	{
		// Steel Worker
		.on_base_power = steelworker_on_base_power,
	},
	{
		// BERSERK
	},
	{
		// SLUSHRUSH
	},
	{
		// LONGREACH
	},
	{
		// LIQUIDVOICE
	},
	{
		// TRIAGE
	},
	{
		// GALVANIZE
	},
	{
		// SURGESURFER
	},
	{
		// SCHOOLING
	},
	{
		// DISGUISE
	},
	{
		// BATTLEBOND
	},
	{
		// POWERCONSTRUCT
	},
	{
		// CORROSION
		/* Implemented in on_status.c*/
	},
	{
		// COMATOSE
	},
	{
		// QUEENLYMAJESTY
	},
	{
		// INNARDSOUT
	},
	{
		// DANCER
	},
	{
		// BATTERY
	},
	{
		// FLUFFY
	},
	{
		// DAZZLING
	},
	{
		// SOULHEART
		.on_faint = soul_heart_on_faint,
	},
	{
		// TANGLINGHAIR
		// gooey clone
		.on_effect = gooey_on_effect,
	},
	{
		// RECEIVER
	},
	{
		// POWEROFALCHEMY
	},
	{
		// BEASTBOOST
	},
	{
		// RKSSYSTEM
	},
	{
		// ELECTRICSURGE
	},
	{
		// PSYCHICSURGE
	},
	{
		// MISTYSURGE
	},
	{
		// GRASSYSURGE
	},
	{
		// FULLMETALBODY
		.on_stat_boost_mod = clear_body_on_stat_boost,
	},
	{
		// SHADOWSHIELD
	},
	{
		// Prism Armor
		.on_damage = filter_variations_on_damage,
	},
	{
		// NEUROFORCE
	},
};
