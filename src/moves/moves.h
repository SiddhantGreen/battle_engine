#ifndef movesABLE_DATA_H_
#define movesABLE_DATA_H_

#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/battle_state.h"
#include "move_override.h"
#include "../abilities/ability_override.h"

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


#define DEF_CATEGORY(move) ((CAT_OVERRIDE(move)) ? ((IS_MOVE_PHYSICAL(move) ? MOVE_SPECIAL : MOVE_PHYSICAL)) : MOVE_CATEGORY(move))
#define MOVE_SECONDARY_STATUS_CHANCE(move, bank) moves[move].procs->secondary_status_chance[bank]
#define MOVE_SECONDARY_STATUS(move, bank) moves[move].procs->secondary_status[bank]

    
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
};

enum StatusAilments {
    AILMENT_NONE,
    AILMENT_SLEEP,
    AILMENT_POISON,
    AILMENT_BURN,
    AILMENT_FREEZE,
    AILMENT_PARALYZE,
    AILMENT_BAD_POISON,
    AILMENT_CONFUSION,
    AILMENT_CURE,
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

struct move_procs {
    u8 chance_self;
    u8 chance_target;
    enum PokemonStat stat_self[6];
    enum PokemonStat stat_target[6];
    s8 amount_self[6];
    s8 amount_target[6];
    enum StatusAilments secondary_status[2]; // index 0 = player, index 1 = target
    u8 secondary_status_chance[2];
};

typedef void (*MoveBeforeTurnCallback)(u8 bank);
typedef void (*MoveBeforeSwitchOutCallback)(u8 bank);
typedef void (*MoveOnStartCallback)(u8 bank);
typedef u8 (*MoveBeforeMoveCallback)(u8 bank);
typedef u8 (*MoveFoeBeforeMoveCallback)(u8 bank);
typedef u8 (*MoveOnModifyMoveCallback)(u8 user, u8 target, u16 move);
typedef u8 (*MoveOnTryHitMoveCallback)(u8 user, u8 target, u16 move);
typedef u8 (*MoveOnBasePowerCallback)(u8 base_power, u8 user, u8 target, u16 move);
typedef u16 (*MoveOnDamageCallback)(u16 dmg_taken, u8 user, u8 target, u16 move);
typedef void (*MoveOnEffectCallback)(u8 attacker, u8 defender, u16 move);
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
    struct move_procs* procs;
    u8 recoil_struggle : 1;
    u8 flinch_chance : 7;
    MoveBeforeTurnCallback before_turn;
    MoveBeforeSwitchOutCallback before_switch;
    MoveOnStartCallback on_start;
    MoveBeforeMoveCallback before_move;
    MoveFoeBeforeMoveCallback foe_before_move;
    MoveOnModifyMoveCallback on_modify_move;
    MoveOnTryHitMoveCallback on_tryhit_move;
    MoveOnTryHitMoveCallback on_tryhit_side_move;
    MoveOnBasePowerCallback on_base_power_move;
    MoveOnDamageCallback on_damage_move;
    MoveOnEffectCallback on_effect_cb;
    MoveOnAfterMoveCallback on_after_move;
    u8 base_power_move_priority;
    u8 before_move_priority;
    u8 foe_before_move_priority;
    
};

extern struct move_data moves[];
extern u32 m_flags[672];

/* Move callback funcs */
extern u16 payday_ondmg(u16 dmg_taken, u8 user, u8 target, u16 move);
extern u8 ohko_tryhit_move(u8 user, u8 target, u16 move);
extern u8 solarbeam_before_move(u8 bank);
extern u8 solarblade_before_move(u8 bank);
extern u8 freeze_shock_before_move(u8 bank);
extern u8 ice_burn_before_move(u8 bank);
extern u8 razor_wind_before_move(u8 bank);

/* Move procs */
extern struct move_procs basic_10burn_proc;
extern struct move_procs basic_10freez_proc;
extern struct move_procs basic_10para_proc;


#endif /* movesABLE_DATA_H_ */	
