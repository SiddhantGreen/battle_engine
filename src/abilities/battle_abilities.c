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
extern struct action *stat_boost(u8 bank, u8 stat_id, s8 amount, u8 inflicting_bank);
extern u16 rand_range(u16, u16);
extern bool disable_on_disable_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 move_pp_count(u16 move_id, u8 bank);
extern void set_status(u8 bank, enum Effect status);
extern void do_damage(u8 bank_index, u16 dmg);
extern void flat_heal(u8 bank, u16 heal);
extern bool b_pkmn_has_type(u8 bank, enum PokemonType type);

/* Note: Illuminate and Honey Gather have no In-Battle effect so they are not present here*/


// None
u8 ability_none_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    // This is just an example
    return true;
}

// Stench
void stench_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
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
u8 speedboost_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	stat_boost(user, SPEED_MOD, 1, user);
	return true;
}

// BATTLEARMOR

// STURDY

// DAMP

// Limber
u8 limber_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == AILMENT_PARALYZE) {
    	enqueue_message(NULL, user, STRING_IMMUNE_ABILITY, NULL);
       	return false;
    }
    return true;
}

// SANDVEIL

// STATIC
u8 static_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (TARGET_OF(user) != src) return true;
	if (!IS_CONTACT(move) || B_MOVE_REMOVE_CONTACT(user)) return true;
	if (rand_range(1, 100) <= 30) {
		set_status(user, EFFECT_PARALYZE);
	}
	return true;
}

// VOLTABSORB

// WATERABSORB

// OBLIVIOUS
u16 oblivious_disallow[] = {
    MOVE_TAUNT, MOVE_NONE, MOVE_MAX, MOVE_CAPTIVATE, MOVE_ATTRACT,
};

u8 oblivous_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
    for (u8 i = 0; i < (sizeof(oblivious_disallow)/sizeof(u16)); i++) {
        if (move == oblivious_disallow[i]) return false;
    }
    return true;
}

u8 oblivious_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == EFFECT_INFACTUATION) {
    	return false;
    }
    return true;
}


// CLOUDNINE

// COMPOUNDEYES

// Insomnia
u8 insomnia_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == AILMENT_SLEEP) {
    	enqueue_message(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// Color Change
void colorchange_on_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if ((B_MOVE_DMG(user) > 0) && (!B_MOVE_HAS_TYPE(user, MTYPE_NONE))) {
    	 u8 type = B_MOVE_TYPE(TARGET_OF(user), 0);
    	 b_pkmn_set_type(TARGET_OF(user), type);
    	 enqueue_message(NULL, user, STRING_CONVERSION_TYPE, type);
    }
    return;
}

// Immunity
u8 immunity_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == AILMENT_POISON) {
    	enqueue_message(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// FLASHFIRE

// SHIELDDUST

// OWNTEMPO
u8 own_tempo_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == EFFECT_CONFUSION) {
    	return false;
    }
    return true;
}

// SUCTIONCUPS

// INTIMIDATE

// SHADOWTAG

// ROUGHSKIN
u8 rough_skin_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (TARGET_OF(user) != src) return true;
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
bool clear_body_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // boost on self which isn't by the user
    return ((CURRENT_ACTION->action_bank == user) || (CURRENT_ACTION->priv[1] > 0));
}

// NATURALCURE

// LIGHTNINGROD

// SERENEGRACE

// SWIFTSWIM

// CHLOROPHYLL

// TRACE

// HUGEPOWER

// Poison Point
u8 poisonpoint_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (TARGET_OF(user) != src) return true;
	if (!IS_CONTACT(move) || B_MOVE_REMOVE_CONTACT(user)) return true;
    if (rand_range(0, 100) <= 30)
	   set_status(user, EFFECT_POISON);
	return true;
}

// INNERFOCUS

// Magma Armor
u8 magmaarmor_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == AILMENT_FREEZE) {
    	enqueue_message(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// Water Veil
u8 waterveil_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
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
u8 flamebody_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (TARGET_OF(user) != src) return true;
	if (!IS_CONTACT(move) || B_MOVE_REMOVE_CONTACT(user)) return true;
    if (rand_range(0, 100) <= 30)
	   set_status(user, EFFECT_BURN);
	return true;
}

// RUNAWAY

// KEENEYE
bool keen_eye_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    u8 attacker = CURRENT_ACTION->action_bank; // inflictor
    if (attacker == src) return true;
    return (!(CURRENT_ACTION->priv[0] == ACCURACY_MOD));
}

u16 keen_eye_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    // if pokemon getting stat accessed isn't the target of keeneye user or
    // if keeneye user is not the one attacking or
    // if keen eye bank is accessing it's evasion stat by itself
    if ((TARGET_OF(src) != user) || (CURRENT_ACTION->action_bank != src) || (user == src)) return acb->data_ptr;
    if (stat_id == EVASION_MOD)
        return 100;
    return acb->data_ptr;
}

// HYPERCUTTER
bool hyper_cutter_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (CURRENT_ACTION->action_bank == src) return true;
    return (!CURRENT_ACTION->priv[0] == ATTACK_MOD);
}

// PICKUP

// TRUANT

// HUSTLE

// CUTECHARM
u8 cute_charm_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (TARGET_OF(user) != src) return true;
	if (!IS_CONTACT(move) || B_MOVE_REMOVE_CONTACT(user)) return true;
    if (B_GENDER(user) == B_GENDER(src)) return true;
    if (rand_range(0, 100) <= 30)
	   set_status(user, EFFECT_INFACTUATION);
	return true;
}

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
u8 vitalspirit_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == AILMENT_SLEEP) {
    	enqueue_message(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// WHITESMOKE
bool white_smoke_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (CURRENT_ACTION->action_bank == src) return true;
    return false;
}

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
void heatproof_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return;
    if (B_MOVE_HAS_TYPE (user, MTYPE_FIRE)) {
        B_MOVE_POWER(user) = B_MOVE_POWER(user) >> 1;
    }
}

// Simple
bool simple_on_stat_boost_mod(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != src) return true;
    CURRENT_ACTION->priv[1] = ((CURRENT_ACTION->priv[1]) << 1);
    return true;
}

// DRYSKIN

// DOWNLOAD

// Iron Fist
void ironfist_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (IS_PUNCH(move)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 120);
    }
    return;
}

// POISONHEAL
extern u8 toxic_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 poison_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);

u8 poison_heal_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb) {
    if (user != src) return true;
    // the ability can change at some point. Since this is anonymous, the case must be handled
    if (BANK_ABILITY(src) != ABILITY_POISON_HEAL) return true;
    if ((B_STATUS(user) == AILMENT_POISON) || (B_STATUS(user) == AILMENT_BAD_POISON)) {
        u8 id = get_callback_src((u32)toxic_on_residual, user);
        CB_MASTER[id].delay_before_effect = 1;
        id = get_callback_src((u32)poison_on_residual, user);
        CB_MASTER[id].delay_before_effect = 1;
        flat_heal(user, MAX(1, (TOTAL_HP(user) >> 3)));
        p_bank[user]->b_data.status_turns++;
    } else {
        acb->in_use = false;
    }
    return true;
}

u8 poison_heal_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    add_callback(CB_ON_RESIDUAL, 2, 0, src, (u32)poison_heal_on_residual);
    return true;
}

// Adaptability
void adaptability_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (B_MOVE_STAB(user)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 133);
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
void technician_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (B_MOVE_POWER(user) <= 60) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 150);
	}
	return;
}

// LEAFGUARD

// KLUTZ

// MOLDBREAKER

// SUPERLUCK

// AFTERMATH
u8 aftermath_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (TARGET_OF(user) != src) return true;
	if (!IS_CONTACT(move) || B_MOVE_REMOVE_CONTACT(user)) return true;
    if (B_CURRENT_HP(src) < 1)
	   do_damage(user, TOTAL_HP(user) >> 2);
	return true;
}

// ANTICIPATION

// FOREWARN

// UNAWARE

// Tinted Lens
void tintedlens_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (B_MOVE_EFFECTIVENESS(user) == TE_NOT_VERY_EFFECTIVE) {
	    B_MOVE_DMG(user) = PERCENT(B_MOVE_DMG(user), 200);
    }
    return;
}

// Filter, Solid Rock and Prism Armor
void filter_variations_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return;
    if (B_MOVE_EFFECTIVENESS(user) == TE_SUPER_EFFECTIVE) {
        B_MOVE_DMG(user) = PERCENT(B_MOVE_DMG(user), 75);
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
void reckless_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (MOVE_RECOIL(move)) {
        B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 120);
    }
    return;
}

// MULTITYPE

// FLOWERGIFT

// BADDREAMS

// PICKPOCKET
void pick_pocket_on_secondary(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((B_ITEM(src) != ITEM_NONE) || (B_ITEM(user) == ITEM_NONE)) return;
    if (!IS_CONTACT(move) || B_MOVE_REMOVE_CONTACT(user)) return;
    if ((user == src) || (TARGET_OF(user) == src)) {
        B_ITEM(src) = B_ITEM(TARGET_OF(src));
        B_ITEM(TARGET_OF(src)) = ITEM_NONE;
        // TODO: message
    }
}

// SHEERFORCE

// Contary
bool contrary_on_stat_boost_mod(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != src) return true;
    CURRENT_ACTION->priv[1] = -CURRENT_ACTION->priv[1];
    return true;
}

// UNNERVE

// DEFIANT
void defiant_after_stat_boost_mod(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != src) return;
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
u8 poison_touch_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	if (!IS_CONTACT(move) || B_MOVE_REMOVE_CONTACT(user)) return true;
    if (rand_range(0, 100) <= 30)
	   set_status(TARGET_OF(user), EFFECT_POISON);
	return true;
}

// REGENERATOR

// BIGPECKS
bool big_pecks_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (CURRENT_ACTION->action_bank == src) return true;
    return (!(CURRENT_ACTION->priv[0] == DEFENSE_MOD));
}

// SANDRUSH

// WONDERSKIN

// ANALYTIC

// ILLUSION

// IMPOSTER

// INFILTRATOR

// MUMMY
u16 mummy_immune_abilities[] = {
    ABILITY_MUMMY, ABILITY_MULTITYPE, ABILITY_STANCE_CHANGE
};

u8 mummy_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb) {
    if (TARGET_OF(user) != src) return true;
    if (!IS_CONTACT(move) || B_MOVE_REMOVE_CONTACT(user)) return true;
    for (u8 i = 0; i < (sizeof(mummy_immune_abilities) / sizeof(u16)); i++) {
        if (mummy_immune_abilities[i] == BANK_ABILITY(user)) return true;
    }

    enqueue_message(move, user, STRING_ABILITY_CHANGED, BANK_ABILITY(user));
    // remove user's old ability callbacks
    delete_callback_src((u32)abilities[BANK_ABILITY(user)].on_effect, user);
    BANK_ABILITY(user) = ABILITY_MUMMY;
    if (abilities[BANK_ABILITY(user)].on_effect) {
        add_callback(CB_ON_EFFECT, 0, 0, user, (u32)abilities[BANK_ABILITY(user)].on_effect);
    }
    return true;
}

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
u8 prankster_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((user != src) || (TARGET_OF(user) == src)) return true;
    // priority boosted moves fail against those who are dark type
    return !(b_pkmn_has_type(TARGET_OF(user), MTYPE_DARK) && HAS_VOLATILE(user, VOLATILE_PRANKSTERED));
}

void prankser_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (IS_MOVE_STATUS(move)) {
        B_MOVE_PRIORITY(user) += 1;
        ADD_VOLATILE(user, VOLATILE_PRANKSTERED);
        add_callback(CB_ON_TRYHIT_MOVE, 1, 0, user, (u32)prankster_on_tryhit);
    }
}

// SANDFORCE

// IRONBARBS

// ZENMODE

// VICTORYSTAR

// TURBOBLAZE

// TERAVOLT

// AROMAVEIL

// FLOWERVEIL
bool flower_veil_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    u8 defender = CURRENT_ACTION->target;
    return (!((SIDE_OF(defender) == SIDE_OF(src)) && (b_pkmn_has_type(defender, MTYPE_GRASS))));
}

u8 flower_veil_on_status(u8 user, u8 src, u16 ailment, struct anonymous_callback* acb)
{
    switch (ailment) {
        case AILMENT_CURE:
        case AILMENT_CONFUSION:
        case AILMENT_NONE:
        case AILMENT_INFACTUATE:
            return true;
        default:
            return (!(SIDE_OF(user) == SIDE_OF(src)));
    }
}


// CHEEKPOUCH

// PROTEAN

// FURCOAT

// MAGICIAN

// BULLETPROOF

// COMPETITIVE
void competitive_after_stat_boost_mod(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != src) return;
    if (SIDE_OF((CURRENT_ACTION)->action_bank) != SIDE_OF(user) && ((CURRENT_ACTION)->priv[1] < 0))
        stat_boost(user, STAT_SPECIAL_ATTACK - 1, 2, user);
}

// Strong Jaw
void strongjaw_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (IS_BITE(move)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 150);
    }
    return;
}

// REFRIGERATE

// SWEETVEIL
u8 sweet_veil_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (SIDE_OF(user) != SIDE_OF(src)) return true;
    if (ailment == AILMENT_SLEEP) {
    	enqueue_message(NULL, user, STRING_AILMENT_IMMUNE, AILMENT_SLEEP);
    	return false;
    }
    return true;
}

// STANCECHANGE

// GALEWINGS
void gale_wings_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (((B_CURRENT_HP(user) << 1) >= TOTAL_HP(user)) && (MOVE_TYPE(move) == MTYPE_FLYING))
        B_MOVE_PRIORITY(user) += 1;
}

// Mega Launcher
void megalauncher_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (IS_PULSE(move)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 150);
    }
    return;
}

// GRASSPELT

// SYMBIOSIS

// TOUGHCLAWS

// PIXILATE

// GOOEY
u8 gooey_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return true;
	if (!IS_CONTACT(move) || B_MOVE_REMOVE_CONTACT(user)) return true;
    stat_boost(user, SPEED_MOD, -1, user);
    return true;
}

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
void steelworker_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (B_MOVE_HAS_TYPE(user, MTYPE_STEEL)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 150);
	}
	return;
}

// BERSERK

// SLUSHRUSH

// LONGREACH

// LIQUIDVOICE

// TRIAGE
void triage_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (IS_HEAL(move))
        B_MOVE_PRIORITY(user) += 1;
}

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
// clearbody clone

// SHADOWSHIELD

// NEUROFORCE
