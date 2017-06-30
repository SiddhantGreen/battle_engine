#ifndef movesABLE_DATA_H_
#define movesABLE_DATA_H_

#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_state.h"
#include "move_override.h"
#include "ability_override.h"

/* 
 * Field data fetch macros
 *
 */
#define MOVE_PRIORITY(move) moves[move].priority
#define MOVE_POWER(move) moves[move].base_power
#define MOVE_CATEGORY(move) moves[move].category
#define MOVE_ACCURACY(move) moves[move].accuracy
#define MOVE_CRIT(move) moves[move].crit_ratio
#define M_FLINCH(move)(*(moves[move].procs)).flinch_chance
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


typedef u8 (*TryHitCallback)(u8);
typedef void (*BeforeTurnCallback)(u8);
typedef bool (*OnInvulnerableTryhit)(u16);
typedef u8 (*DurationCallback)(u8, u8, u8);
typedef void (*DamageCallback)(u8, u8);
typedef void (*BeforeMoveCallback)(u8);
typedef void (*ModifyMoveCallback)(u8);
typedef u16 (*OnHealCallback)(u8);
typedef void (*EffectCallback)(u8, u8, u16);


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
    AILMENT_PARALYZE,
    AILMENT_SLEEP,
    AILMENT_BURN,
    AILMENT_FREEZE,
    AILMENT_POISON,
    AILMENT_BAD_POISON,
    AILMENT_CONFUSION,
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

struct move_callbacks {
    BeforeTurnCallback bt_cb;
    BeforeMoveCallback bm_cb;
    ModifyMoveCallback mm_cb;
    TryHitCallback th_cb;
    DamageCallback bd_cb;
    OnHealCallback oheal_cb;
    OnInvulnerableTryhit inv_tryhit_cb;
    EffectCallback on_effect_cb;
    
    
};

struct move_procs {
    u8 chance_self;
    u8 chance_target;
    enum PokemonStat stat_self[6];
    enum PokemonStat stat_target[6];
    s8 amount_self[6];
    s8 amount_target[6];
    u8 multihit_lowest;
    u8 multihit_highest;
    u8 secondary_status[2];
    u8 secondary_status_chance[2];
    u8 flinch_chance;
};


struct move_data {
    pchar name[30];
    u8 accuracy;
    s8 base_power;
    pchar* description;
    u8 pp;
    s8 priority;
    u8 crit_ratio;
    enum MoveCategory category;
    enum MoveTypes type;
    u32 m_flags;
    u8 drain;
    u8 recoil;
    struct move_procs* procs;
    struct move_callbacks* move_cb;
    u8 recoil_struggle : 1;
};

extern struct move_data moves[];
extern u32 m_flags[672];



#endif /* movesABLE_DATA_H_ */	
