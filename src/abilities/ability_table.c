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
		// Battle Armor
		.on_modify_move = battle_armor_variations_on_modify_move,
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
		// Oblivios
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
		// Own Tempo
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
		// Rough Skin
		.on_effect = rough_skin_variations_on_effect,
	},
	{
		// WONDERGUARD
	},
	{
		// LEVITATE
	},
	{
		// Effect Spore
		.on_effect = effect_spore_effect,
	},
	{
		// SYNCHRONIZE
	},
	{
		// Clear Body
		.on_stat_boost_mod = clear_body_variations_on_stat_boost,
	},
	{
		// NATURALCURE
	},
	{
		// LIGHTNINGROD
	},
	{
		// SERENEGRACE
		.on_modify_move = serenegrace_on_modify_move,
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
		// Keen Eye
		.on_stat_boost_mod = keen_eye_on_stat_boost,
		.on_stat = keen_eye_on_stat,
	},
	{
		// Hyper Cutter
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
		// Cute Charm
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
		// Liquidooze
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
		// White Smoke
		.on_stat_boost_mod = white_smoke_on_stat_boost,
	},
	{
		// PUREPOWER
	},
	{
		// Shell Armor
		.on_modify_move = battle_armor_variations_on_modify_move,
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
		// Poison Heal
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
		// Normalize
		.before_turn = normalize_before_turn,
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
		// Aftermath
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
		// Scrappy
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
		// Pickpocket
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
		// Cursed Body
		.on_effect = cursed_body_on_effect,
	},
	{
		// HEALER
	},
	{
		// FRIENDGUARD
	},
	{
		// Weak Armor
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
		// Poison Touch
		.on_effect = poison_touch_on_effect,
	},
	{
		// REGENERATOR
	},
	{
		// Big Pecks
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
		// Infiltraotr
		.on_modify_move = infiltrator_modify_move,
	},
	{
		// Mummy
		.on_effect = mummy_on_effect,
	},
	{
		// Moxie
		.on_damage = moxie_on_damage,
	},
	{
		// Justified
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
		// Prankster
		.before_turn = prankser_before_turn,
	},
	{
		// SANDFORCE
	},
	{
		// Iron Barbs
		.on_effect = rough_skin_variations_on_effect,
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
		// Flower Veil
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
		// Refrigerate
		.before_turn = refrigerate_before_turn,
	},
	{
		// Sweet Veil
		.on_status = sweet_veil_on_status,
	},
	{
		// STANCECHANGE
	},
	{
		// Gale Wings
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
		// Pixilate
		.before_turn = pixilate_before_turn,
	},
	{
		// Gooey
		.on_effect = gooey_variations_on_effect,
	},
	{
		// Aerilate
		.before_turn = aerilate_before_turn,
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
		// Stamina
		.on_effect = stamina_on_effect,
	},
	{
		// WIMPOUT
	},
	{
		// EMERGENCYEXIT
	},
	{
		// Water Compaction
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
		// Liquid Voice
		.on_modify_move = liquid_voice_on_modify_move,
	},
	{
		// TRIAGE
	},
	{
		// Galvanize
		.before_turn = galvanize_before_turn,
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
		// Corrosion
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
		// Soul Heart
		.on_faint = soul_heart_on_faint,
	},
	{
		// Tangling Hair
		.on_effect = gooey_variations_on_effect,
	},
	{
		// Receiver
		.on_faint = receiver_variations_on_faint,
	},
	{
		// Power of Alchemy
		.on_faint = receiver_variations_on_faint,
	},
	{
		// Beast Boost
		.on_damage = beast_boost_on_damage,
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
		// Full Metal Body
		.on_stat_boost_mod = clear_body_variations_on_stat_boost,
	},
	{
		// Shadow Shield
		.on_damage = shadow_shield_on_damage,
	},
	{
		// Prism Armor
		.on_damage = filter_variations_on_damage,
	},
	{
		// Neuroforce
		.on_damage = neuro_force_on_damage, 
	},
};
