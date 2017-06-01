#ifndef MOVE_TABLE_DATA_H_
#define MOVE_TABLE_DATA_H_

#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_state.h"


// return base power given bank id and default power. bp_cb(user_bank, bp)
typedef u8 (*BasePowerCallback)(u8, u8);

// activate some p_bank flags for a Pokemon in a certain bank and/or target bank. bt_cb(user_bank, target_bank)
typedef u8 (*BeforeTurnCallback)(u8, u8);

// Executed before duration for something is applied, to modify duration. dur_cb(user bank, target bank, effect)
typedef u8 (*DurationCallback)(u8, u8, u8);

// executed before damage calculation, and skips dmg_calc. dmg_cb(user_bank, target_bank)
typedef u16 (*DamageCallback)(u8, u8);

// executed right before using a move. bm_cb(user_bank, target_bank)
typedef void (*BeforeMoveCallback)(u8, u8, u16);

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
};

enum MoveCategory {
    MOVE_PHYSICAL,
    MOVE_SPECIAL,
    MOVE_STATUS,
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
    BasePowerCallback bp_cb;
    BeforeTurnCallback bt_cb;
    DurationCallback dur_cb;
    DamageCallback dmg_cb;
    BeforeMoveCallback bm_cb;
    
};

struct move_flags {
    u32 flag_ignore_substitute : 1;
    u32 flag_chargeup : 1;
    u32 flag_recharge : 1;
    u32 flag_contact : 1;
    u32 flag_defrost : 1;
    u32 flag_gravity_disabled : 1;
    u32 flag_heal_block_disabled : 1;
    u32 flag_mirrorable : 1;
    u32 flag_powder : 1;
    u32 flag_protectable : 1;
    u32 flag_mega_launcher : 1;
    u32 flag_iron_fist : 1;
    u32 flag_reflectable : 1;
    u32 flag_snatch : 1;
    u32 flag_sound_based : 1;
    u32 flag_strong_jaw : 1;
    u32 flag_bullet_proof : 1;
    u32 flag_onself : 1;
    u32 flag_target : 1;
    u32 flag_hits_all : 1;
    u32 flag_triage_affected : 1;
    u32 flags_unused : 12; // repurposeable flags. Unused padding.  
};

struct move_boost {
    u32 self_atk : 3;
    u32 atk_boost_dir : 1;
    u32 self_def : 3;
    u32 def_boost_dir : 1;
    u32 self_spd : 3;
    u32 spd_boost_dir : 1;
    u32 self_spatk : 3;
    u32 spa_boost_dir : 1;
    u32 self_spdef : 3;
    u32 sdef_boost_dir : 1;
};


struct move_data {
    pchar name[30];
    u8 accuracy;
    u8 base_power;
    pchar* description;
    u8 pp;
    s8 priority;
    u8 crit_ratio;
    enum MoveCategory category;
    enum MoveTypes type; 
    u8 self_boost_chance_secondary;
    u8 target_boost_chance_secondary;
    struct move_flags* flags;
    struct move_boost* self_boost;
    struct move_boost* target_boost;    
    struct move_callbacks* move_cb;
};

extern struct move_data move_t[];


#endif /* MOVE_TABLE_DATA_H_ */
