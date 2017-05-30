#ifndef BATTLE_TURN_DATA_PKMN
#define BATTLE_TURN_DATA_PKMN

#include <pokeagb/pokeagb.h>

struct user_turn_action {
    u16 move_id;
    u8 user_bank;
    u8 target_bank;
    s8 priority;
    u16 speed;
    
    u8 is_running : 1;
    u8 using_item : 1;
    u8 is_switching : 1;
    u16 item_to_use;
    u8 switching_slot;
};

#endif /* BATTLE_TURN_DATA_PKMN */

