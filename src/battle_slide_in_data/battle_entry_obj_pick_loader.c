#include <pokeagb/pokeagb.h>
#include "battle_obj_sliding.h"
#include "../battle_data/pkmn_bank.h"

extern void wild_battle_slidein(void);
extern u8 get_bank_ability(u8);

SuperCallback object_slidein_table[11] =
{
    (SuperCallback)wild_battle_slidein,
};

void wild_battle_initializer()
{
    p_bank[PLAYER_SINGLES_BANK]->this_pkmn = &party_player[0];
    p_bank[OPPONENT_SINGLES_BANK]->this_pkmn = &party_opponent[0];
}

void pick_obj_creator()
{
    /*
    darken sprites only

    This is a trick in which by putting BG3 in the destination, sprites which have semi-transparent
    mode activated will not be effected by the darken, since the lowest BG layer is lower in
    priority, thus the transparency will take place instead.
    */

    REG_BLDCNT = (BLDCNT_SPRITES_SRC |  BLDCNT_BG3_DST | BLDCNT_DARKEN);

    // darken factor
    REG_BLDY = 0x7;

    p_bank[0]->objid = 0x3F;
    p_bank[1]->objid = 0x3F;
    p_bank[2]->objid = 0x3F;
    p_bank[3]->objid = 0x3F;

    wild_battle_initializer();

    switch (battle_type_flags) {
        case BATTLE_FLAG_WILD:
        default:
            object_slidein_table[0]();
            break;
    };
}
