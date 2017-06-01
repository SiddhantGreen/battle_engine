#ifndef BATTLE_TURN_DATA_PKMN
#define BATTLE_TURN_DATA_PKMN

#include <pokeagb/pokeagb.h>

struct user_turn_action {
    u16 move_id;
    u8 target_bank;
    s8 priority;
    s8 speed;
    
    u8 is_running : 1;
    u8 using_item : 1;
    u8 is_switching : 1;
    u16 item_to_use;
    u8 switching_slot;
    u8 ability;
    u16 speed_current;
};

#endif /* BATTLE_TURN_DATA_PKMN */

