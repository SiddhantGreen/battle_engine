#ifndef BATTLE_PKMN_BANK_H_
#define BATTLE_PKMN_BANK_H_

#include <pokeagb/pokeagb.h>

#define OPPONENT_SINGLES_BANK 2
#define PLAYER_SINGLES_BANK 0
#define PARTICIPANTS_AMOUNT_WILD 2

#define BANK_MAX 4
#define MTYPES_MAX 19
#define SPECIES_ARCEUS 1000
#define SPECIES_SILVALLY 1001
// executed right before using a move. bm_cb(user_bank)
typedef void (*BeforeMoveCallback)(u8);
typedef void (*DamageCallback)(u8, u8);


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

enum TypeBits {
    TYPE_BITS_NORMAL = (1 << 0),
    TYPE_BITS_FIGHTING = (1 << 1),
    TYPE_BITS_FLYING = (1 << 2),
    TYPE_BITS_POISON = (1 << 3),
    TYPE_BITS_GROUND = (1 << 4),
    TYPE_BITS_ROCK = (1 << 5),
    TYPE_BITS_BUG = (1 << 6),
    TYPE_BITS_GHOST = (1 << 7),
    TYPE_BITS_STEEL = (1 << 8),
    TYPE_BITS_FIRE = (1 << 9),
    TYPE_BITS_WATER = (1 << 10),
    TYPE_BITS_GRASS = (1 << 11),
    TYPE_BITS_ELECTRIC = (1 << 12),
    TYPE_BITS_PSYCHIC = (1 << 13),
    TYPE_BITS_ICE = (1 << 14),
    TYPE_BITS_DRAGON = (1 << 15),
    TYPE_BITS_DARK = (1 << 16),
};

/* Volatile definitions for Bitmasks -- enum is unsuitable */
#define VOLATILE_FLASH_FIRE (1 << 0)
#define VOLATILE_CONFUSION (1 << 1)
#define VOLATILE_SUBSTITUTE (1 << 2)
#define VOLATILE_STAT_REDUC_IMMUNE (1 << 3)
#define VOLATILE_TRAPPED (1 << 4)
#define VOLATILE_AROMA_VEIL (1 << 5)
#define VOLATILE_MOLDBREAKER (1 << 6)
#define VOLATILE_PRANKSTERED (1 << 7)
#define VOLATILE_SEMI_INVULNERABLE (1 << 8)
#define VOLATILE_CHARGING (1 << 9)
#define VOLATILE_INGRAIN (1 << 10)
#define VOLATILE_BIND (1 << 11)
#define VOLATILE_FLYING (1 << 12)
#define VOLATILE_MINIMIZE (1 << 13)
#define VOLATILE_MULTI_TURN (1 << 14)// disables PP reduction
#define VOLATILE_SLEEP_TURN (1 << 15)
#define VOLATILE_CONFUSE_TURN (1 << 16)
#define VOLATILE_ATK_SKIP_TURN (1 << 17)
#define VOLATILE_DEFENSE_CURL (1 << 18)
#define VOLATILE_RECHARGING (1 << 18)




struct local_battler_data {
    // Base stats in battle
    u16 species;
    u16 current_hp;
    u16 total_hp;
    u8 gender;
    u8 ability;
    u16 item;
    u8 level;
    u8 poke_ball;
    u8 type[3];

    // Delta applied to base stat. ex: -1 atk
    s8 attack;
    s8 defense;
    s8 speed;
    s8 sp_atk;
    s8 sp_def;
    s8 accuracy;
    s8 evasion;
    s8 crit_mod;

    // This Pokemon's action this turn
    u8 is_running : 1;
    u8 using_item : 1;
    u8 is_switching : 1;
    u8 skip_move_select : 1;
    u8 first_turn : 1;
    u8 move_failed : 1;

    u8 my_target;
    u8 pp_index;
    u16 last_move;
    u16 current_move;
    u16 last_damage;
    u16 moves_used[4];
    u16 last_used_item;
    u8 last_attacked_by;
    u8 move_lock_counter;

    // local user specific bitfield
    u8 illusion : 1;
    u8 fainted : 1;
    u8 ate_berry : 1;
    u8 is_taunted : 1;
    u8 is_charmed : 1;
    u8 is_grounded : 1;

    enum StatusAilments status;
    u8 confusion_turns;
    u8 status_turns;
    u16 substitute_health;
    u32 v_status; // enum volatile status

    u8 disable_used_on_slot;
    u16 disabled_moves[4];

    // counters
    u8 flee_count;
};

struct update_flags {
    u8 pass_status : 1;
    u8 pass_stats : 1;
    u8 pass_atk_history : 1;
    u8 pass_disables : 1;

};

struct pkmn_bank {
    struct Pokemon* this_pkmn;
    u8 objid;
    u8 objid_hpbox[4]; // Main box, tag on part and
    u8 pp_pal;
    u8 move_pal;
    struct local_battler_data b_data;
};

extern struct pkmn_bank *p_bank[BANK_MAX];
extern const pchar pkmn_type_names[MTYPES_MAX][13];
extern u8 effectiveness_chart[342];

#endif /* BATTLE_PKMN_BANK_H_ */
