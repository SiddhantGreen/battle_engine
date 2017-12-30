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
		// STATIC
	},
	{
		// VOLTABSORB
	},
	{
		// WATERABSORB
	},
	{
		// OBLIVIOUS
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
	},
	{
		// WONDERGUARD
	},
	{
		// LEVITATE
	},
	{
		// EFFECTSPORE
	},
	{
		// SYNCHRONIZE
	},
	{
		// CLEARBODY
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
		// ILLUMINATE
	},
	{
		// TRACE
	},
	{
		// HUGEPOWER
	},
	{
		// POISONPOINT
	},
	{
		// INNERFOCUS
	},
	{
		// Magma Armor
		.on_status = magmaarmor_on_status,
	},
	{
		// WATERVEIL
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
		// FLAMEBODY
	},
	{
		// RUNAWAY
	},
	{
		// KEENEYE
	},
	{
		// HYPERCUTTER
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
		// HONEYGATHER
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
		// DEFIANT
		.after_stat_boost_mod = defiant_after_stat_boost_mod,
	},
	{
		// DEFEATIST
	},
	{
		// CURSEDBODY
	},
	{
		// HEALER
	},
	{
		// FRIENDGUARD
	},
	{
		// WEAKARMOR
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
	},
	{
		// REGENERATOR
	},
	{
		// BIGPECKS
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
	},
	{
		// MUMMY
	},
	{
		// MOXIE
	},
	{
		// JUSTIFIED
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
	},
	{
		// SANDFORCE
	},
	{
		// IRONBARBS
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
		// COMPETITIVE
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
	},
	{
		// STANCECHANGE
	},
	{
		// GALEWINGS
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
	},
	{
		// WIMPOUT
	},
	{
		// EMERGENCYEXIT
	},
	{
		// WATERCOMPACTION
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
		// SOUL
	},
	{
		// TANGLINGHAIR
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
		// FULLMETAL
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
