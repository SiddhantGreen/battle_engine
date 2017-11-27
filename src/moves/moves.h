#ifndef movesABLE_DATA_H_
#define movesABLE_DATA_H_

#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "move_override.h"
#include "../abilities/ability_override.h"

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

    Attack
    Defense
    Speed
    Special Attack
    Special Defense
    Accuracy
    Evasion
    Critical chance
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
#define FLAGS_UNUSED (1 << 28)


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



typedef void (*MoveBeforeTurnCallback)(u8 bank);
typedef void (*MoveBeforeSwitchOutCallback)(u8 bank);
typedef void (*MoveOnStartCallback)(u8 bank);
typedef u8 (*MoveBeforeMoveCallback)(u8 bank);
typedef u8 (*MoveOnFailCallback)(u8 user, u8 target, u16 move);
typedef u8 (*MoveOnModifyMoveCallback)(u8 user, u8 target, u16 move);
typedef u8 (*MoveOnTryHitMoveCallback)(u8 user, u8 target, u16 move);
typedef u8 (*MoveOnInvulnerableTryHitMoveCallback)(u8 user, u8 target, u16 move);
typedef u8 (*MoveOnBasePowerCallback)(u8 base_power, u8 user, u8 target, u16 move);
typedef u16 (*MoveOnDamageCallback)(u16 dmg_taken, u8 user, u8 target, u16 move);
typedef u8 (*MoveOnEffectCallback)(u8 attacker, u8 defender, u16 move);
typedef void (*MoveOnAfterMoveCallback)(u8 attacker);

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
    MoveOnTryHitMoveCallback on_tryhit_side_move;
    MoveOnBasePowerCallback on_base_power_move;
    MoveOnDamageCallback on_damage_move;
    MoveOnEffectCallback on_effect_cb;
    MoveOnAfterMoveCallback on_after_move;
};

extern struct move_data moves[];


/* Move callback funcs */
extern u16 payday_ondmg(u16 dmg_taken, u8 user, u8 target, u16 move);
extern u8 ohko_tryhit_move(u8 user, u8 target, u16 move);
extern u8 solarbeam_before_move(u8 bank);
extern u8 solarblade_before_move(u8 bank);
extern u8 freeze_shock_before_move(u8 bank);
extern u8 ice_burn_before_move(u8 bank);
extern u8 razor_wind_before_move(u8 bank);
extern u8 sky_attack_before_move(u8 bank);
extern u8 fly_before_move(u8 bank);
extern u8 gust_on_modify(u8 user, u8 target, u16 move);
extern u8 whirlwind_on_tryhit_move(u8 user, u8 target, u16 move);
extern u8 whirlwind_on_effect_cb(u8 attacker, u8 defender, u16 move);
extern u8 acrobatics_on_base_power_move(u8 base_power, u8 user, u8 target, u16 move);
extern u8 bind_on_effect_cb(u8 attacker, u8 defender, u16 move);
extern u8 minimize_on_effect_cb(u8 attacker, u8 defender, u16 move);
extern u8 stomp_on_modify_move(u8 user, u8 target, u16 move);
extern u8 jump_kick_on_move_fail(u8 user, u8 target, u16 move);
extern u8 bodyslam_on_modify_move(u8 user, u8 target, u16 move);
extern u8 thrash_on_tryhit_move(u8 attacker, u8 target, u16 move);
extern u8 thrash_on_move_fail(u8 attacker, u8 defender, u16 move);
extern void thrash_on_after_move(u8 attacker);
extern u8 sonic_boom_on_modify_move(u8 user, u8 target, u16 move);
extern u16 sonic_boom_on_damage_move(u16 dmg_taken, u8 user, u8 target, u16 move);
extern u8 disable_on_effect_cb(u8 user, u8 target, u16 move);
extern u8 rollout_on_before_move(u8 attacker);
extern u8 rollout_on_move_fail(u8 attacker, u8 defender, u16 move);
extern u8 rollout_on_base_power_move(u8 base_power, u8 user, u8 target, u16 move);
extern u8 metronome_on_modify_move(u8 bank, u8 target, u16 move);
extern u8 mirror_move_on_modify_move(u8 bank, u8 target, u16 move);
extern u8 sleep_talk_before_move(u8 bank);
extern u8 sleep_talk_on_modify_move(u8 bank, u8 target, u16 sleep_talk);
extern u8 assist_on_modify_move(u8 bank, u8 target, u16 assist_move);
extern u8 copycat_on_modify_move(u8 bank, u8 target, u16 copycat_move);
extern u8 clear_smog_effect(u8 attacker, u8 defender, u16 move);
extern u8 magic_coat_on_tryhit(u8 bank, u8 defender, u16 move_mirror_coat);
extern u8 me_first_on_tryhit (u8 attacker, u8 defender, u16 move_me_first);
extern u8 snatch_on_effect(u8 attacker, u8 defender, u16 move);
extern u8 conversion_on_effect(u8 attacker, u8 defender, u16 move);

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
extern struct move_procs poison_30_procs;
extern struct move_procs poison_40_procs;
extern struct move_procs poison_20_procs;
extern struct move_procs supersonic_procs;
extern struct move_procs sing_procs;
extern struct move_procs burn_10_procs;
extern struct move_procs freeze_10_procs;
extern struct move_procs confuse_10_procs;
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
extern struct move_procs poison_100_procs;
extern struct move_procs toxic_procs;
extern struct move_procs psychic_procs;
#endif /* movesABLE_DATA_H_ */
