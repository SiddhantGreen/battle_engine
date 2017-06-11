#ifndef BATTLE_ABILITIES_TABLE_H_
#define BATTLE_ABILITIES_TABLE_H_

#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_state.h"
#include "moves/moves.h"

typedef u16 (*StatCallback)(u8, u16);
typedef void (*AbilityModMoveCallback)(u8, u16);
typedef void (*AbilitySwitchInCallback)(u8);
typedef void (*AbilityResidualCallback)(u8);

struct b_ability {
    StatCallback on_priority;
    StatCallback on_attack;
    StatCallback on_defense;
    StatCallback on_speed;
    StatCallback on_sp_attack;
    StatCallback on_sp_defense;
    StatCallback on_accuracy;
    StatCallback on_evasion;
    StatCallback on_critchance;
    
    AbilitySwitchInCallback on_switch;
    AbilityModMoveCallback on_modify_move;
    AbilityResidualCallback on_residual;
    
};

#define ABILITIES_MAX 5
extern struct b_ability* abilities_table[5];








#endif /* BATTLE_ABILITIES_TABLE_H_ */
