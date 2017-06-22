#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_state.h"
#include "moves/moves.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "battle_abilities.h"

extern void build_message(u8 state, u16 move_id, u8 user_bank, enum battle_string_ids id, u16 move_effect_id);
extern u16 rand_range(u16, u16);
extern bool b_pkmn_has_type(u8 bank, enum PokemonType type);
extern s8 move_effectiveness(u8 move_type, u8 target_bank);
extern void stat_boost(u8 bank, u8 high_stat, u8 amount);
extern void set_status(u8 bank, u8 source, enum Effect status);

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
    build_message(GAME_STATE, 0, 0, STRING_RAINING, 0);
}

struct b_ability b_drizzle = {
    .on_switch = drizzle_on_switch,
};


// Speed Boost
void speed_boost_on_residual(u8 bank)
{
    if (p_bank[bank]->b_data.speed < 6) {
        p_bank[bank]->b_data.speed++;
        build_message(GAME_STATE, 0, bank, STRING_GAINED_SPEED, 0);
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
u8 sturdy_tryhit(u8 bank, u8 target, u16 move)
{
    switch (move) {
        case MOVE_FISSURE:
        case MOVE_HORN_DRILL:
        case MOVE_GUILLOTINE:
        case MOVE_SHEER_COLD:
            build_message(GAME_STATE, move, bank, STRING_STURDY_IMMUNE, 0);
            return false;
            break;
        default:
            break;
    };
    return true;
}

u16 sturdy_on_damage(u8 bank, u8 tbank, u16 move, u16 damage, u8 ability, u16 item)
{
    if ((B_CURRENT_HP(bank) == TOTAL_HP(bank)) &&
        (damage >= B_CURRENT_HP(bank))) {
        return 1;
    }
    return damage;
}

struct b_ability b_sturdy = {
    .on_tryhit = sturdy_tryhit,
    .on_damage = sturdy_on_damage,
};


// Damp
u8 damp_tryhit(u8 bank, u8 target, u16 move)
{
    if ((move == MOVE_SELFDESTRUCT) || (move == MOVE_EXPLOSION)) {
        build_message(GAME_STATE, move, bank, STRING_DAMP_BLOCKED, 0);
        return false;
    }
    return true;
}

u16 damp_on_damage(u8 bank, u8 tbank, u16 move, u16 damage, u8 ability, u16 item)
{
    if (ability == ABILITY_AFTERMATH)
        return 0;
    return damage;
}

struct b_ability b_damp = {
    .on_tryhit = damp_tryhit,
    .on_damage = damp_on_damage,
};


// Limber

void limber_on_update(u8 bank)
{
    if (B_STATUS(bank) == AILMENT_PARALYZE) {
       p_bank[bank]->b_data.status = AILMENT_NONE;
       build_message(GAME_STATE, 0, bank, STRING_STATUS_CURED, 0);
    }
}

bool limber_on_set_status(u8 bank, u8 source, enum Effect effect, bool settable)
{
    if (bank == source)
        return false;
    if ((effect == EFFECT_PARALYZE) && (settable)) {
       p_bank[bank]->b_data.status = AILMENT_NONE;
       build_message(GAME_STATE, 0, bank, STRING_IMMUNE_ABILITY, ABILITY_LIMBER);
       return true;
    }
    return false;
}

struct b_ability b_limber = {
    .on_update = limber_on_update,
    .on_set_status = limber_on_set_status,
};


// Sand Veil
/* Sand Veil's immune clause to sandstorm to be handled in standstorm's residual damage*/
u16 sand_veil_on_evasion(u8 bank, u16 stat) {
    if (battle_master->field_state.is_sandstorm)
        return ((stat * 25) / 100);
    return stat;
}

struct b_ability b_sand_veil = {
    .on_evasion = sand_veil_on_evasion,
};


// Static
void static_on_after_damage(u8 bank, u8 target, u16 move, u16 dmg, u8 ability, u16 item)
{
    if (MAKES_CONTACT(move) && (target != bank)) {
        if (rand_range(0, 100) < 30) {
            p_bank[TARGET_OF(bank)]->b_data.status = AILMENT_PARALYZE;
        }
    }
}

struct b_ability b_static = {
    .on_after_damage = static_on_after_damage,
};


// Volt Absorb
u8 volt_absorb_tryhit(u8 bank, u8 target, u16 move)
{
    if ((target != bank) &&  (MOVE_TYPE(move) == MTYPE_ELECTRIC)) {
        build_message(GAME_STATE, 0, bank, STRING_IMMUNE_ABILITY, ABILITY_VOLT_ABSORB);
        p_bank[target]->b_data.current_hp += (TOTAL_HP(target) / 4);
        if (B_CURRENT_HP(target) > TOTAL_HP(target))
            p_bank[target]->b_data.current_hp = TOTAL_HP(target);
        return false;
    }
    return true;
}

struct b_ability b_volt_absorb = {
    .on_tryhit = volt_absorb_tryhit,
};


// Water Absorb
u8 water_absorb_tryhit(u8 bank, u8 target, u16 move)
{
    if ((target != bank) &&  (MOVE_TYPE(move) == MTYPE_WATER)) {
        build_message(GAME_STATE, 0, bank, STRING_IMMUNE_ABILITY, ABILITY_WATER_ABSORB);
        p_bank[target]->b_data.current_hp += (TOTAL_HP(target) / 4);
        if (B_CURRENT_HP(target) > TOTAL_HP(target))
            p_bank[target]->b_data.current_hp = TOTAL_HP(target);
        return false;
    }
    return true;
}

struct b_ability b_water_absorb = {
    .on_tryhit = water_absorb_tryhit,
};


// Oblivious
/* Attract and taunt immunity updated in the move's tryhits */
void oblivious_on_update(u8 bank)
{
    if (p_bank[bank]->b_data.is_taunted) {
        p_bank[bank]->b_data.is_taunted = false;
         build_message(GAME_STATE, MOVE_TAUNT, bank, STRING_EFFECT_ENDED, 0);
    }
    if (p_bank[bank]->b_data.is_charmed) {
        p_bank[bank]->b_data.is_charmed = false;
         build_message(GAME_STATE, MOVE_CHARM, bank, STRING_EFFECT_ENDED, 0);
    }
}

struct b_ability b_oblivious = {
    .on_update = oblivious_on_update,
};

    
// Cloud Nine
void cloud_nine_on_switch(u8 bank)
{
    battle_master->field_state.is_sunny = false;
    battle_master->field_state.is_raining = false;
    battle_master->field_state.is_sandstorm = false;
    battle_master->field_state.is_hail = false;
    battle_master->field_state.is_desolate_land = false;
    battle_master->field_state.is_primordial_sea = false;
    battle_master->field_state.suppress_weather = true;
    build_message(GAME_STATE, 0, 0, STRING_WEATHER_GONE, 0);
}

struct b_ability b_cloud_nine = {
    .on_switch = cloud_nine_on_switch,
};


// Compound Eyes
u16 compount_eyes_on_accuracy(u8 bank, u16 stat)
{
    return (stat + ((stat * 30) / 100));
}

struct b_ability b_compound_eyes = {
    .on_accuracy = compount_eyes_on_accuracy,
};


// Insomnia
void insomnia_on_update(u8 bank)
{
    if (B_STATUS(bank) == AILMENT_SLEEP) {
       p_bank[bank]->b_data.status = AILMENT_NONE;
       build_message(GAME_STATE, 0, bank, STRING_STATUS_CURED, 0);
    }
}

bool insomnia_on_set_status(u8 bank, u8 source, enum Effect effect, bool settable)
{
    if (bank == source)
        return false;
    if ((effect == EFFECT_SLEEP) && (settable)) {
       p_bank[bank]->b_data.status = AILMENT_NONE;
       build_message(GAME_STATE, 0, bank, STRING_IMMUNE_ABILITY, ABILITY_INSOMNIA);
       return true;
    }
    return false;
}

struct b_ability b_insomnia = {
    .on_update = insomnia_on_update,
    .on_set_status = insomnia_on_set_status,
};


// Color Change
void color_change_after_move_secondary(u8 bank, u8 target, u16 move, u8 ability, u16 item)
{
    // target exists
    if (B_CURRENT_HP(TARGET_OF(bank)) && (bank != target)) {
        if (IS_MOVE_STATUS(move)) {
            return;
            
        // target already has this type
        } else if((B_PKMN_TYPE(bank, 0) == MOVE_TYPE(move)) || 
            (B_PKMN_TYPE(bank, 1) == MOVE_TYPE(move)) ||
            (B_PKMN_TYPE(bank, 2) == MOVE_TYPE(move))) {
            return;
        }
        // set type if unique to target and non-status move
            B_PKMN_TYPE(bank, 0) = MOVE_TYPE(move);
            build_message(GAME_STATE, move, bank, STRING_GAINED_TYPE, 0);
            return;
    }
}

struct b_ability b_color_change = {
    .on_after_move_secondary = color_change_after_move_secondary,
};


// Immunity
void immunity_on_update(u8 bank)
{
    if (B_STATUS(bank) == AILMENT_SLEEP) {
       p_bank[bank]->b_data.status = AILMENT_NONE;
       build_message(GAME_STATE, 0, bank, STRING_STATUS_CURED, 0);
    }
}

bool immunity_on_set_status(u8 bank, u8 source, enum Effect effect, bool settable)
{
    if (bank == source)
        return false;
    if ((effect == EFFECT_POISON) && settable) {
       p_bank[bank]->b_data.status = AILMENT_NONE;
       build_message(GAME_STATE, 0, bank, STRING_IMMUNE_ABILITY, ABILITY_IMMUNITY);
       return true;
    }
    return false;
}

struct b_ability b_immunity = {
    .on_update = immunity_on_update,
    .on_set_status = immunity_on_set_status,
};

// Flash Fire
u8 flash_fire_tryhit(u8 bank, u8 target, u16 move)
{
    if ((target != bank) &&  (MOVE_TYPE(move) == MTYPE_FIRE)) {
        build_message(GAME_STATE, 0, bank, STRING_IMMUNE_ABILITY, ABILITY_FLASH_FIRE);
        ADD_VOLATILE(bank, VOLATILE_FLASH_FIRE);
        return false;
    }
    return true;
}

u16 flash_fire_on_attack(u8 bank, u16 stat)
{
    if (MOVE_TYPE(CURRENT_MOVE(bank)) == MTYPE_FIRE) {
        return ((stat * 150) / 100);
    }
    return stat;
}

struct b_ability b_flash_fire = {
    .on_tryhit = flash_fire_tryhit,
    .on_attack = flash_fire_on_attack,
    .on_sp_attack = flash_fire_on_attack, // spatk and atk are clones in functionality
    
};


// Shield Dust
void shield_dust_on_mod_secondary(u8 bank, u8 target, u16 move, u8 ability, u16 item)
{
    if ((move_t[move].procs) && (bank != target))  {
        // remove secondary effect chance
        battle_master->b_moves[B_MOVE_BANK(bank)].chance_self = 0;
        battle_master->b_moves[B_MOVE_BANK(bank)].chance_target = 0;
        battle_master->b_moves[B_MOVE_BANK(bank)].secondary_status_chance[0] = 0;
        battle_master->b_moves[B_MOVE_BANK(bank)].secondary_status_chance[1] = 0;
    }
}

struct b_ability b_shield_dust = {
    .on_mod_secondary = shield_dust_on_mod_secondary,
};


// Own Tempo
void own_tempo_on_update(u8 bank)
{
    if (HAS_VOLATILE(bank, VOLATILE_CONFUSION)) {
       REMOVE_VOLATILE(bank, VOLATILE_CONFUSION);
       SET_CONFUSION_TURNS(bank, 0);
       build_message(GAME_STATE, 0, bank, STRING_CONFUSION_ENDED, ABILITY_OWN_TEMPO);
    }
}


bool own_tempo_on_set_status(u8 bank, u8 source, enum Effect effect, bool settable)
{
    if (bank == source)
        return false;
    if ((effect == EFFECT_CONFUSION) && settable) {
       SET_CONFUSION_TURNS(bank, 0);
       build_message(GAME_STATE, 0, bank, STRING_IMMUNE_ABILITY, ABILITY_OWN_TEMPO);
        return true;
    }
    return false;
}

struct b_ability b_own_tempo = {
    .on_update = own_tempo_on_update,
    .on_set_status = own_tempo_on_set_status,
};


// Suction Cups
u8 suction_cups_on_dragout(u8 bank)
{
    build_message(GAME_STATE, 0, bank, STRING_DRAGGED_OUT_FAILED, ABILITY_SUCTION_CUPS);
    return false;
}

struct b_ability b_suction_cups = {
    .on_dragout = suction_cups_on_dragout,
};


// Intimidate
void intimidate_on_switch(u8 bank)
{
    u8 foe = FOE_BANK(bank);
    if (B_CURRENT_HP(foe) && (!(HAS_VOLATILE(foe, VOLATILE_SUBSTITUTE) || 
        HAS_VOLATILE(foe, VOLATILE_STAT_REDUC_IMMUNE))))  {
        build_message(GAME_STATE, 0, bank, STRING_INTIMIDATE, 0);
    }
}

struct b_ability b_intimidate = {
    .on_switch = intimidate_on_switch,
};


// SHADOW TAG
void shadow_tag_on_switch(u8 bank)
{
    u8 foe = FOE_BANK(bank);
    if (!(BANK_ABILITY(foe) == ABILITY_SHADOW_TAG) && !(b_pkmn_has_type(foe, TYPE_GHOST))) {
        ADD_VOLATILE(foe, VOLATILE_TRAPPED);
    }
    
    if (!(BANK_ABILITY(bank) == ABILITY_SHADOW_TAG) && !(b_pkmn_has_type(bank, TYPE_GHOST))) {
        ADD_VOLATILE(bank, VOLATILE_TRAPPED);
    }
}

struct b_ability b_shadow_tag = {
    .on_switch = shadow_tag_on_switch,
};


// ROUGH SKIN
void rough_skin_after_damage(u8 bank, u8 target, u16 move, u16 dmg, u8 ability, u16 item)
{
    if ((bank != target) && (MAKES_CONTACT(move))) {
        battle_master->b_moves[B_MOVE_BANK(bank)].after_dmg = TOTAL_HP(target) / 8;
    }
}

struct b_ability b_rough_skin = {
    .on_after_damage = rough_skin_after_damage,
};


// WONDER GUARD
u8 wonder_guard_on_tryhit(u8 bank, u8 target, u16 move)
{
    if ((bank == target) || (move == MOVE_STRUGGLE) || IS_MOVE_STATUS(move))
        return true;
    build_message(GAME_STATE, 0, bank, STRING_IMMUNE_ABILITY, ABILITY_WONDER_GUARD);
    return false;
}

struct b_ability b_wonder_gaurd = {
    .on_tryhit = wonder_guard_on_tryhit,
};


// LEVITATE
u8 levitate_on_tryhit(u8 bank, u8 target, u16 move)
{
    if (bank != target) {
        if ((MOVE_TYPE(move) == MTYPE_GROUND) && (!(battle_master->field_state.is_gravity) && !(B_IS_GROUNDED(target))))
            return false;
    }
    return true;
}

struct b_ability b_levitate = {
    .on_tryhit = levitate_on_tryhit,
};


// EFFECT SPORE
void effect_spore_on_after_damage(u8 bank, u8 target, u16 move, u16 dmg_taken, u8 ability, u16 item)
{
    

}

// SYNCHRONIZE
bool synchronize_on_set_status(u8 bank, u8 source, enum Effect effect, bool settable)
{
    if(source == bank)
        return false;
    if((effect == EFFECT_TOXIC_SPIKES) && settable)
        return false;
    if(B_STATUS(bank) == AILMENT_SLEEP || B_STATUS(bank) == AILMENT_FREEZE || B_STATUS(bank) == AILMENT_CONFUSION)
        return false;
    set_status(bank, source, B_STATUS(bank));
    return false;
}

struct b_ability b_synchronize = {
    .on_set_status = synchronize_on_set_status,
};

// CLEAR BODY

// NATURAL CURE

// LIGHTNING ROD

// SERENE GRACE

// SWIFT SWIM

// CHLOROPHYLL

// ILLUMINATE

// TRACE

// HUGE POWER

// POISON POINT

// INNER FOCUS

// MAGMA ARMOR

// WATER VEIL

// MAGNET PULL

// SOUNDPROOF

// RAIN DISH

// SAND STREAM

// PRESSURE

// THICK FAT

// EARLY BIRD

// FLAME BODY

// RUN AWAY

// KEEN EYE

// HYPER CUTTER

// PICKUP

// TRUANT

// HUSTLE

// CUTE CHARM

// PLUS

// MINUS

// FORECAST

// STICKY HOLD

// SHED SKIN

// GUTS

// MARVEL SCALE

// LIQUID OOZE

// OVERGROW

// BLAZE

// TORRENT

// SWARM

// ROCK HEAD

// DROUGHT

// ARENA TRAP

// VITAL SPIRIT

// WHITE SMOKE

// PURE POWER

// SHELL ARMOR

// AIR LOCK

// TANGLED FEET

// MOTOR DRIVE

// RIVALRY

// STEADFAST

// SNOW CLOAK

// GLUTTONY

// ANGER POINT

// UNBURDEN

// HEATPROOF

// SIMPLE

// DRY SKIN

// DOWNLOAD

// IRON FIST

// POISON HEAL

// ADAPTABILITY

// SKILL LINK

// HYDRATION

// SOLAR POWER

// QUICK FEET

// NORMALIZE

// SNIPER

// MAGIC GUARD

// NO GUARD

// STALL

// TECHNICIAN

// LEAF GUARD

// KLUTZ

// MOLD BREAKER

// SUPER LUCK

// AFTERMATH

// ANTICIPATION

// FOREWARN

// UNAWARE

// TINTED LENS

// FILTER

// SLOW START

// SCRAPPY

// STORM DRAIN

// ICE BODY

// SOLID ROCK

// SNOW WARNING

// HONEY GATHER

// FRISK

// RECKLESS

// MULTITYPE

// FLOWER GIFT

// BAD DREAMS

// PICKPOCKET

// SHEER FORCE

// CONTRARY

// UNNERVE

// DEFIANT

// DEFEATIST

// CURSED BODY

// HEALER

// FRIEND GUARD

// WEAK ARMOR

// HEAVY METAL

// LIGHT METAL

// MULTISCALE

// TOXIC BOOST

// FLARE BOOST

// HARVEST

// TELEPATHY

// MOODY

// OVERCOAT

// POISON TOUCH

// REGENERATOR

// BIG PECKS

// SAND RUSH

// WONDER SKIN

// ANALYTIC

// ILLUSION

// IMPOSTER

// INFILTRATOR

// MUMMY

// MOXIE

// JUSTIFIED

// RATTLED

// MAGIC BOUNCE

// SAP SIPPER

// PRANKSTER

// SAND FORCE

// IRON BARBS

// ZEN MODE

// VICTORY STAR

// TURBOBLAZE

// TERAVOLT

// AROMA VEIL

// FLOWER VEIL

// CHEEK POUCH

// PROTEAN

// FUR COAT

// MAGICIAN

// BULLETPROOF

// COMPETITIVE

// STRONG JAW

// REFRIGERATE

// SWEET VEIL

// STANCE CHANGE

// GALE WINGS

// MEGA LAUNCHER

// GRASS PELT

// SYMBIOSIS

// TOUGH CLAWS

// PIXILATE

// GOOEY

// AERILATE

// PARENTAL BOND

// DARK AURA

// FAIRY AURA

// AURA BREAK

// PRIMORDIAL SEA

// DESOLATE LAND

// DELTA STREAM

// STAMINA

// WIMP OUT

// EMERGENCY EXIT

// WATER COMPACTION

// MERCILESS

// SHIELDS DOWN

// STAKEOUT

// WATER BUBBLE

// STEELWORKER

// BERSERK

// SLUSH RUSH

// LONG REACH

// LIQUID VOICE



// TRIAGE
void triage_on_priority_mod(u8 bank, u16 move)
{
    if (IS_TRIAGE(move)) {
        B_MOVE_PRIORITY(bank) += 3;
    }
}

struct b_ability b_triage = {
    .on_priority_mod = triage_on_priority_mod,
};


// GALVANIZE
void galvanize_on_modify_move(u8 bank, u16 move)
{
    u8 i;
    for (i = 0; i < 2; i ++) {
        if ((B_MOVE_TYPE(bank, i) == MTYPE_NORMAL)) {
            B_MOVE_TYPE(bank, i) = MTYPE_ELECTRIC;
            B_MOVE_POWER(bank) = NUM_MOD(B_MOVE_POWER(bank), 120);
            return;
        }
    }
}

struct b_ability b_galvanize = {
    .on_modify_move = galvanize_on_modify_move,
};


// SURGE SURFER
u16 surge_surfer_on_speed(u8 bank, u16 amount)
{
    if (battle_master->field_state.electric_terrain)
        return amount * 2;
    return amount;
}

struct b_ability b_surge_surfer = {
    .on_speed = surge_surfer_on_speed,
};


// SCHOOLING
/* TODO : In battle pseudo forms are something planned for later */


// DISGUISE
/* TODO : In battle pseudo forms are something planned for later */


// BATTLE BOND
/* TODO : In battle pseudo forms are something planned for later */


// POWER CONSTRUCT
/* TODO : In battle pseudo forms are something planned for later */


// CORROSION
bool corrosion_on_set_status(u8 bank, u8 source, enum Effect effect, bool settable)
{
    // if attacker has corrosion, activate.
    if ((bank == source) && ((effect == EFFECT_POISON) || (effect == EFFECT_BAD_POISON))) {
        u8 ailment = (effect == EFFECT_POISON) ? AILMENT_POISON : AILMENT_BAD_POISON;
        p_bank[TARGET_OF(bank)]->b_data.status = ailment;
        build_message(GAME_STATE, 0, TARGET_OF(bank), STRING_AILMENT_APPLIED, ailment);
        return true;
    }
    return false;
}

struct b_ability b_corrosion = {
    .on_set_status = corrosion_on_set_status,
};


// COMATOSE
bool comatose_on_set_status(u8 bank, u8 source, enum Effect effect, bool settable)
{
    if (bank == source)
        return false;
    // if pokemon with the ability (bank) is being set a status, provide immunity
    p_bank[bank]->b_data.status = AILMENT_NONE;
    build_message(GAME_STATE, 0, bank, STRING_IMMUNE_ABILITY, ABILITY_COMATOSE);
    return true;
}

struct b_ability b_comatose = {
    .on_set_status = comatose_on_set_status,
};


// QUEENLY MAJESTY
u8 queenly_majesty_on_tryhit(u8 bank, u8 t_bank, u16 move)
{
    if (SIDE_OF(bank) != SIDE_OF(t_bank)) {
        if (battle_master->b_moves[B_MOVE_BANK(bank)].priority != 0)
            return false;
    }
    return true;
}

struct b_ability b_queenly_majesty = {
    .on_tryhit = queenly_majesty_on_tryhit,
};


// INNARDS OUT
void innards_out_after_damage(u8 bank, u8 target, u16 move, u16 dmg, u8 ability, u16 item)
{
    if ((bank != target) && (!B_CURRENT_HP(target))) {
        battle_master->b_moves[B_MOVE_BANK(bank)].after_dmg = dmg;
    }
}

struct b_ability b_innards_out = {
    .on_after_damage = innards_out_after_damage,
};


// DANCER
/* TODO : This is actually a special case of running an arbitrary move outside of a given Pokemon's turn. It ought to be enqueued and run after the current move */


// BATTERY
u16 battery_on_damage(u8 bank, u8 tbank, u16 move, u16 dmg, u8 ability, u16 item)
{
    if (bank == tbank)
        return dmg;
    if (IS_MOVE_SPECIAL(move))
        return ((dmg * 130) / 100);
    return dmg;
}

struct b_ability b_battery = {
    .on_damage = battery_on_damage,
};


// FLUFFY
u16 fluffy_on_damage(u8 bank, u8 tbank, u16 move, u16 dmg, u8 ability, u16 item)
{
    if (bank == tbank)
        return dmg;
    /* 50% more damage from fire moves */
    if ((battle_master->b_moves[B_MOVE_BANK(bank)].type[0] == MTYPE_FIRE) ||
        (battle_master->b_moves[B_MOVE_BANK(bank)].type[1] == MTYPE_FIRE)) {
        dmg = ((dmg * 150) / 100);
    }
    /* half damage from contact moves */
    if (MAKES_CONTACT(move)) {
        dmg = ((dmg * 50) / 100);
    }
    return dmg; 
}

struct b_ability b_fluffy = {
    .on_damage = fluffy_on_damage,
};


// DAZZLING
u8 dazzling_on_tryhit(u8 bank, u8 t_bank, u16 move)
{
    if (SIDE_OF(bank) != SIDE_OF(t_bank)) {
        if (battle_master->b_moves[B_MOVE_BANK(bank)].priority != 0)
            return false;
    }
    return true;
}

struct b_ability b_dazzling = {
    .on_tryhit = dazzling_on_tryhit,
};


// SOUL-HEART
void soul_heart_on_faint(u8 bank, u8 fainted_bank)
{
    if (bank != fainted_bank) {
        stat_boost(bank, REQUEST_SPATK, 1);
    }
}

struct b_ability b_soul_heart = {
    .on_faint = soul_heart_on_faint,
};

// TANGLING HAIR
void tangling_hair_on_after_damage(u8 bank, u8 target, u16 move, u16 dmg, u8 ability, u16 item)
{
    if (MAKES_CONTACT(move) && (target != bank)) {
        stat_boost(bank, REQUEST_SPD, -1);
    }
}

struct b_ability b_tangling_hair = {
    .on_after_damage = tangling_hair_on_after_damage,
};


// RECEIVER
/* Doesn't do anything in singles, skipped for now */


// POWER OF ALCHEMY
/* Doesn't do anything in singles, skipped for now */


// BEAST BOOST
void beast_boost_on_faint(u8 bank, u8 fainted_bank)
{
    if (bank ==  fainted_bank)
        return;
    u8 i;
    u16 current_highest = 0;
    u16 high_stat = REQUEST_ATK;
    for (i = REQUEST_ATK; i < REQUEST_ATK + 4; i++) {
        u8 this_stat = pokemon_getattr(p_bank[bank]->this_pkmn, i, NULL);
        if (this_stat > current_highest) {
            high_stat = i;
            current_highest = this_stat;
        }
    }
    stat_boost(bank, high_stat, 1);
}

struct b_ability b_beast_boost = {
    .on_faint = beast_boost_on_faint,
};

// RKS SYSTEM
struct b_ability b_RKS_system = {
    // the type change should be handled in the overworld
};

// ELECTRIC SURGE
void electric_surge_on_switch(u8 bank)
{
    battle_master->field_state.electric_terrain = 1;
    return;
}

struct b_ability b_electric_surge = {
    .on_switch = electric_surge_on_switch,
};

// PSYCHIC SURGE
void psychic_surge_on_switch(u8 bank)
{
    battle_master->field_state.psychic_terrain = 1;
    return;
}

struct b_ability b_psychic_surge = {
    .on_switch = psychic_surge_on_switch,
};


// MISTY SURGE
void misty_surge_on_switch(u8 bank)
{
    battle_master->field_state.misty_terrain = 1;
    return;
}

struct b_ability b_misty_surge = {
    .on_switch = misty_surge_on_switch,
};


// GRASSY SURGE
void grassy_surge_on_switch(u8 bank)
{
    battle_master->field_state.grassy_terrain = 1;
    return;
}

struct b_ability b_grassy_surge = {
    .on_switch = grassy_surge_on_switch,
};


// FULL METAL BODY

// SHADOW SHIELD
u16 shadow_shield_on_damage(u8 bank, u8 tbank, u16 move, u16 dmg, u8 ability, u16 item)
{
    if(bank == tbank)
        return dmg;
    if (B_CURRENT_HP(bank) == TOTAL_HP(bank))
        return dmg / 2;
    return dmg;
}

struct b_ability b_shadow_shield = {
    .on_damage = shadow_shield_on_damage,
};


// PRISM ARMOR
u16 prism_armor_on_damage(u8 bank, u8 tbank, u16 move, u16 dmg, u8 ability, u16 item)
{
    if (bank == tbank)
        return dmg;
    if (move_effectiveness(move_t[move].type, tbank) > 0)
        return ((dmg * 75) / 100);
    return dmg;
}

struct b_ability b_prism_armor = {
    .on_damage = prism_armor_on_damage,
};



struct b_ability* abilities_table[11] = {
    &empty,
    &b_stench,
    &b_drizzle,
    &b_speed_boost,
    &b_battle_armor,
    &b_sturdy,
    &b_damp,
    &b_limber,
    &b_sand_veil,
    &b_static,
    &b_volt_absorb,
    
    
};




// Adaptability
void adaptability_modify_move(u8 bank, u16 move)
{
   battle_master->b_moves[B_MOVE_BANK(bank)].stab = 200;
}

struct b_ability b_adaptability = {
    .on_modify_move = adaptability_modify_move,
};