#ifndef BATTLE_PKMN_BANK_H_
#define BATTLE_PKMN_BANK_H_

#include <pokeagb/pokeagb.h>
#include "battle_turn_data.h"

#define OPPONENT_SINGLES_BANK 2
#define PLAYER_SINGLES_BANK 0


// executed right before using a move. bm_cb(user_bank)
typedef void (*BeforeMoveCallback)(u8);
typedef void (*DamageCallback)(u8, u8);

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

enum VolatileStatus {
    VOLATILE_FLASH_FIRE = (1 << 0),
    VOLATILE_CONFUSION = (1 << 1),
};

struct local_battler_data {
    // Base stats in battle
    u8 gender;
    u16 current_hp;
    u16 total_hp;
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
    u8 accuracy;
    u8 evasion;
    u8 crit_mod;
    
    // This Pokemon's action this turn
    u8 is_running : 1;
    u8 using_item : 1;
    u8 is_switching : 1;
    u8 skip_move_select : 1;
    

    u8 my_target;
    u16 last_move;
    u16 current_move;
    u16 last_damage;
    u8 last_attacked_by;
    u16 last_used_item;
    
    
    // local user specific bitfield
    u8 is_trapped : 1;
    u8 is_disabled : 1;
    u8 illusion : 1;
    u8 fainted : 1;
    u8 ate_berry : 1;
    u8 is_taunted : 1;
    u8 is_charmed : 1;
    
    u8 status;
    u8 confusion_turns;
    enum VolatileStatus v_status;
    
    
    
    u16 disabled_moves[4];
    u16 semi_invulnerable_move_id;
    
    
    
    };


struct pkmn_bank {
    u16 species_id;
    u16 padding;
    struct Pokemon* this_pkmn;
    u8 objid;
    u8 objid_hpbox[3]; // Main box, tag on part and
    struct local_battler_data b_data;
};

extern struct pkmn_bank (*p_bank)[4];



#endif /* BATTLE_PKMN_BANK_H_ */
