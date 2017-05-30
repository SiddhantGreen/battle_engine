#ifndef BATTLE_PKMN_BANK_H_
#define BATTLE_PKMN_BANK_H_

#include <pokeagb/pokeagb.h>
#include "battle_turn_data.h"

#define OPPONENT_SINGLES_BANK 2
#define PLAYER_SINGLES_BANK 0


struct pkmn_bank {
    u16 species_id;
    u16 padding;
    struct Pokemon* this_pkmn;
    u8 objid;
    u8 objid_hpbox[3]; // Main box, tag on part and
    struct user_turn_action user_turn;
};

extern struct pkmn_bank (*p_bank)[4];



#endif /* BATTLE_PKMN_BANK_H_ */
