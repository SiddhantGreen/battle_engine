#ifndef movesABLE_DATA_H_
#define movesABLE_DATA_H_

#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "move_override.h"
#include "../abilities/ability_override.h"
#include "../anonymous_callbacks/anonymous_callbacks.h"

/* Ailment names and order:

    AILMENT_NONE
    AILMENT_SLEEP
    AILMENT_POISON
    AILMENT_BURN
    AILMENT_FREEZE
    AILMENT_PARALYZE
    AILMENT_BAD_POISON
    AILMENT_CONFUSION
    AILMENT_CURE
*/

/*  Order of stat boosts:

    Attack - 0
    Defense - 1
    Speed - 2
    Special Attack - 3
    Special Defense - 4
    Accuracy - 5
    Evasion - 6
    Critical chance - 7
*/

struct move_procs {
    u8 chance_user[8];
    s8 user_amounts[8];

    u8 chance_target[8];
    s8 target_amounts[8];

    enum StatusAilments ailment_user;
    enum StatusAilments ailment_target;
    u8 ailment_user_chance;      //
    u8 ailment_target_chance;    // Chance the ailment affects the user
};

#define MOVE_AILMENT_PROCS_CHANCE_USER(move) moves[move].ailment_user_chance
#define MOVE_AILMENT_PROCS_CHANCE_TARGET(move) moves[move].ailment_target_chance
#define MOVE_AILMENT_PROCS_STATUS_USER(move) moves[move].ailment_user
#define MOVE_AILMENT_PROCS_STATUS_TARGET(move) moves[move].ailment_target


#include "../battle_data/battle_state.h"

/*
 * Field data fetch macros
 *
 */
#define MOVE_PRIORITY(move) moves[move].priority
#define MOVE_POWER(move) moves[move].base_power
#define MOVE_CATEGORY(move) moves[move].category
#define MOVE_ACCURACY(move) moves[move].accuracy
#define MOVE_CRIT(move) moves[move].crit_ratio
#define M_FLINCH(move) moves[move].flinch_chance
#define MAKES_CONTACT(move, bank) (((moves[move].m_flags) & (1 << 3)) & (!battle_master->b_moves[(bank == battle_master->first_bank) ? 0 : 1].remove_contact))
#define MOVE_TYPE(move) moves[move].type
#define IS_MOVE_STATUS(move) (moves[move].category == MOVE_STATUS)
#define IS_MOVE_PHYSICAL(move) (moves[move].category == MOVE_PHYSICAL)
#define IS_MOVE_SPECIAL(move) (moves[move].category == MOVE_SPECIAL)
#define IS_DEFROST(move) ((moves[move].m_flags) & (1 << 4))
#define IS_PROTECTABLE(move) ((moves[move].m_flags) & (1 << 9))
#define IS_REFLECTABLE(move) ((moves[move].m_flags) & (1 << 12))
#define IS_SNATCHABLE(move) ((moves[move].m_flags) & (1 << 13))
#define IS_CHARGE(move) ((moves[move].m_flags) & (1 << 1))
#define IS_RECHARGE(move) ((moves[move].m_flags) & (1 << 2))
#define IS_DANCE(move) ((moves[move].m_flags) & (1 << 21))
#define IS_TRIAGE(move) ((moves[move].m_flags) & (1 << 20))
#define IS_SOUND_BASE(move) ((moves[move].m_flags) & (1 << 14))
#define IS_PULSE(move) ((moves[move].m_flags) & (1 << 22))
#define IS_STRONG_JAW(move) ((moves[move].m_flags) & (1 << 15))
#define IS_BULLET(move) ((moves[move].m_flags) & (1 << 16))
#define IS_SEMI_INVUL(move) ((moves[move].m_flags) & (1 << 23))
#define IS_OHKO(move) ((moves[move].m_flags) & (1 << 24))
#define CAT_OVERRIDE(move) ((moves[move].m_flags) & (1 << 25))
#define STEAL_OFFENSIVE(move) ((moves[move].m_flags) & (1 << 26))
#define STEAL_BOOSTS(move) ((moves[move].m_flags) & (1 << 27))
#define IS_MIRRORABLE(move) ((moves[move].m_flags) & (1 << 7))
#define M_HITS_SIDE(move) ((moves[move].m_flags) & (1 << 28))
#define M_HITS_TARGET(move) ((moves[move].m_flags) & (1 << 18))


#define DEF_CATEGORY(move) ((CAT_OVERRIDE(move)) ? ((IS_MOVE_PHYSICAL(move) ? MOVE_SPECIAL : MOVE_PHYSICAL)) : MOVE_CATEGORY(move))
#define MOVE_SECONDARY_STATUS_CHANCE(move, bank) moves[move].procs->secondary_status_chance[SIDE_OF(bank)]
#define MOVE_SECONDARY_STATUS(move, bank) moves[move].procs->secondary_status[SIDE_OF(bank)]


#define FLAG_CHARGE (1 << 1)
#define FLAG_RECHARGE (1 << 2)
#define FLAG_CONTACT (1 << 3)
#define FLAG_DEFROST (1 << 4)
#define FLAG_GRAVITY (1 << 5)
#define FLAG_HEAL (1 << 6)
#define FLAG_MIRROR (1 << 7)
#define FLAG_POWDER (1 << 8)
#define FLAG_PROTECT (1 << 9)
#define FLAG_AUTHENTIC (1 << 10)
#define FLAG_PUNCH (1 << 11)
#define FLAG_REFLECTABLE (1 << 12)
#define FLAG_SNATCH (1 << 13)
#define FLAG_SOUND (1 << 14)
#define FLAG_BITE (1 << 15) // strongjaw
#define FLAG_BULLET (1 << 16)
#define FLAG_ONSELF (1 << 17)
#define FLAG_TARGET (1 << 18)
#define FLAG_HITS_ALL (1 << 19)
#define FLAG_TRIAGE (1 << 20)
#define FLAG_DANCE (1 << 21)
#define FLAG_PULSE (1 << 22)
#define FLAG_SEMI_INVUL (1 << 23)
#define FLAG_OHKO (1 << 24)
#define FLAG_CATEGORY_OVERRIDE (1 << 25)
#define FLAG_STEAL_OFFENSIVE (1 << 26)
#define FLAG_STEAL_BOOSTS (1 << 27)
#define FLAG_HITS_SIDE (1 << 28)
#define FLAGS_UNUSED (1 << 29)


enum MoveTypes {
    MTYPE_NORMAL = 0,
    MTYPE_FIGHTING,
    MTYPE_FLYING,
    MTYPE_POISON,
    MTYPE_GROUND,
    MTYPE_ROCK,
    MTYPE_BUG,
    MTYPE_GHOST,
    MTYPE_STEEL,
    MTYPE_EGG,
    MTYPE_FIRE,
    MTYPE_WATER,
    MTYPE_GRASS,
    MTYPE_ELECTRIC,
    MTYPE_PSYCHIC,
    MTYPE_ICE,
    MTYPE_DRAGON,
    MTYPE_DARK,
    MTYPE_FAIRY,
    MTYPE_NONE,
};

enum MoveCategory {
    MOVE_PHYSICAL,
    MOVE_SPECIAL,
    MOVE_STATUS,
};

enum PokemonStat {
    STAT_NONE,
    STAT_ATTACK,
    STAT_DEFENSE,
    STAT_SPEED,
    STAT_SPECIAL_ATTACK,
    STAT_SPECIAL_DEFENSE,
    STAT_ACCURACY,
    STAT_EVASION,
    STAT_CRIT,
};

/*

List of flags and their descriptions:

authentic: Ignores a target's substitute.
bite: Power is multiplied by 1.5 when used by a Pokemon with the Ability Strong Jaw.
bullet: Has no effect on Pokemon with the Ability Bulletproof.
charge: The user is unable to make a move between turns.
contact: Makes contact.
defrost: Thaws the user if executed successfully while the user is frozen.
gravity: Prevented from being executed or selected during Gravity's effect.
heal: Prevented from being executed or selected during Heal Block's effect.
mirror: Can be copied by Mirror Move.
powder: Has no effect on Grass-type Pokemon, Pokemon with the Ability Overcoat, and Pokemon holding Safety Goggles.
protect: Blocked by Detect, Protect, Spiky Shield, and if not a Status move, King's Shield.
pulse: Power is multiplied by 1.5 when used by a Pokemon with the Ability Mega Launcher.
punch: Power is multiplied by 1.2 when used by a Pokemon with the Ability Iron Fist.
recharge: If this move is successful, the user must recharge on the following turn and cannot make a move.
reflectable: Bounced back to the original user by Magic Coat or the Ability Magic Bounce.
snatch: Can be stolen from the original user and instead used by another Pokemon using Snatch.
sound: Has no effect on Pokemon with the Ability Soundproof.

*/



typedef void (*MoveBeforeTurnCallback)(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
typedef void (*MoveBeforeSwitchOutCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef void (*MoveOnStartCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*MoveBeforeMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*MoveOnFailCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*MoveOnModifyMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*MoveOnTryHitMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*MoveOnInvulnerableTryHitMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef void (*MoveOnBasePowerCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef void (*MoveOnDamageCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*MoveOnEffectCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef void (*MoveOnAfterMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);

struct move_data {
    pchar name[22];
    u8 accuracy;
    u8 base_power;
    pchar* description;
    u8 pp;
    s8 priority;
    u8 crit_ratio;
    enum MoveCategory category;
    enum MoveTypes type;
    u32 m_flags;
    u8 drain;
    u8 recoil;
    u8 heal;
    u8 multi_hit[2];
    u8 recoil_struggle : 1;
    u8 flinch_chance : 7;

    struct move_procs* procs;

    MoveBeforeTurnCallback before_turn;
    MoveBeforeSwitchOutCallback before_switch;
    MoveOnStartCallback on_start;
    MoveBeforeMoveCallback before_move;
    MoveOnFailCallback on_move_fail;
    MoveOnModifyMoveCallback on_modify_move;
    MoveOnTryHitMoveCallback on_tryhit_move;
    MoveOnInvulnerableTryHitMoveCallback on_inv_tryhit_move;
    MoveOnBasePowerCallback on_base_power_move;
    MoveOnDamageCallback on_damage_move;
    MoveOnEffectCallback on_effect_cb;
    MoveOnAfterMoveCallback on_after_move;
};

extern struct move_data moves[];


/* Move callback funcs */
extern void payday_ondmg(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 ohko_tryhit_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 solarbeam_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 solarblade_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 freeze_shock_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 ice_burn_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 razor_wind_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 sky_attack_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 fly_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 gust_on_modify(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 whirlwind_on_tryhit_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 whirlwind_on_effect_cb(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void acrobatics_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 bind_on_effect_cb(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 minimize_on_effect_cb(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 stomp_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 jump_kick_on_move_fail(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 bodyslam_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 thrash_on_tryhit_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 thrash_on_move_fail(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void thrash_on_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void sonic_boom_on_dmg(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 disable_on_effect_cb(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 rollout_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 rollout_on_move_fail(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void rollout_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 metronome_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 mirror_move_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 sleep_talk_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 sleep_talk_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 assist_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 copycat_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 clear_smog_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 magic_coat_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 me_first_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 snatch_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 conversion_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 conversion_two_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 reflect_type_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 soak_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 flying_press_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void flying_press_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 trick_or_treat_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 rest_on_tryhit_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 ion_deluge_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 electrify_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 electrify_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void psywave_on_damage_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 burn_up_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 burn_up_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 protect_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 protection_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void seismic_toss_on_damage_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 cotton_spore_on_tryhit_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void endure_on_damage(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern u8 endure_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 wide_guard_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 mat_block_on_tryhit(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern u8 mat_block_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 crafty_shield_on_tryhit(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern u8 crafty_shield_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 feint_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 hyperspace_hole_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 shadow_force_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 phantom_force_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 present_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 reflect_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 light_screen_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 aurora_veil_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 aurora_veil_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 rain_dance_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 sunny_day_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 hail_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 sandstorm_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 brickbreak_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 future_sight_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 wish_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 yawn_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 yawn_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 charge_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 doom_desire_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void counter_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 counter_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 mirror_coat_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void mirror_coat_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 metal_burst_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void metal_burst_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 hurricane_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 hurricane_on_tryhit_inv(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 weather_ball_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 electric_terrain_on_effect(u8 bank, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 grassy_terrain_on_effect(u8 bank, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 misty_terrain_on_effect(u8 bank, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 psychic_terrain_on_effect(u8 bank, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 secret_power_on_modify(u8 bank, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 floral_healing_on_modify(u8 bank, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 camouflage_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);


/* User stats */
extern struct move_procs user_lower_atk_1;
extern struct move_procs user_lower_def_1;
extern struct move_procs user_lower_spAtk_1;
extern struct move_procs user_lower_spDef_1;
extern struct move_procs user_lower_spd_1;
extern struct move_procs user_lower_acc_1;

extern struct move_procs user_lower_atk_2;
extern struct move_procs user_lower_def_2;
extern struct move_procs user_lower_spAtk_2;
extern struct move_procs user_lower_spDef_2;
extern struct move_procs user_lower_spd_2;
extern struct move_procs user_lower_acc_2;

extern struct move_procs user_raise_atk_1;
extern struct move_procs user_raise_def_1;
extern struct move_procs user_raise_spAtk_1;
extern struct move_procs user_raise_spDef_1;
extern struct move_procs user_raise_spd_1;
extern struct move_procs user_raise_acc_1;
extern struct move_procs user_raise_evn_1;

extern struct move_procs user_raise_atk_2;
extern struct move_procs user_raise_def_2;
extern struct move_procs user_raise_spAtk_2;
extern struct move_procs user_raise_spDef_2;
extern struct move_procs user_raise_spd_2;
extern struct move_procs user_raise_acc_2;

/* Target stats */
extern struct move_procs target_lower_atk_1;
extern struct move_procs target_lower_def_1;
extern struct move_procs target_lower_spAtk_1;
extern struct move_procs target_lower_spDef_1;
extern struct move_procs target_lower_spd_1;
extern struct move_procs target_lower_acc_1;

extern struct move_procs target_lower_atk_2;
extern struct move_procs target_lower_def_2;
extern struct move_procs target_lower_spAtk_2;
extern struct move_procs target_lower_spDef_2;
extern struct move_procs target_lower_spd_2;
extern struct move_procs target_lower_acc_2;
extern struct move_procs target_lower_evn_2;

extern struct move_procs target_raise_atk_1;
extern struct move_procs target_raise_def_1;
extern struct move_procs target_raise_spAtk_1;
extern struct move_procs target_raise_spDef_1;
extern struct move_procs target_raise_spd_1;
extern struct move_procs target_raise_acc_1;

extern struct move_procs target_raise_atk_2;
extern struct move_procs target_raise_def_2;
extern struct move_procs target_raise_spAtk_2;
extern struct move_procs target_raise_spDef_2;
extern struct move_procs target_raise_spd_2;
extern struct move_procs target_raise_acc_2;

/* Move Specific procs */
extern struct move_procs poison_20_procs;
extern struct move_procs poison_30_procs;
extern struct move_procs poison_40_procs;
extern struct move_procs poison_100_procs;
extern struct move_procs toxic_procs;
extern struct move_procs supersonic_procs;
extern struct move_procs burn_10_procs;
extern struct move_procs freeze_10_procs;
extern struct move_procs confuse_10_procs;
extern struct move_procs confuse_20_procs;
extern struct move_procs confuse_30_procs;
extern struct move_procs confuse_100_procs;
extern struct move_procs paralyze_10_procs;
extern struct move_procs paralyze_30_procs;
extern struct move_procs shell_smash_procs;
extern struct move_procs dragon_ascent_procs;
extern struct move_procs shift_gear_procs;
extern struct move_procs paralyze_100_procs;
extern struct move_procs bubble_beam_procs;
extern struct move_procs aurora_beam_procs;
extern struct move_procs shadow_ball_procs;
extern struct move_procs psychic_procs;
extern struct move_procs target_lower_acc_1_chance_50;
extern struct move_procs sing_procs;
extern struct move_procs rest_procs;
extern struct move_procs target_raise_atk_2_confuse;
extern struct move_procs user_raise_atk_1_10;
extern struct move_procs target_burn_50;
extern struct move_procs target_lower_def_1_30;
extern struct move_procs user_raise_def_1_10;
#endif /* movesABLE_DATA_H_ */
