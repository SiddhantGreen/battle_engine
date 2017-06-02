#ifndef BATTLE_STATE_H_
#define BATTLE_STATE_H_

#include <pokeagb/pokeagb.h>

struct battle_selection_cursor {
    u8 objid;
    u8 objid_mv_crsr[2];
    u8 cursor_pos; // 0-3
    u8 cursor_x[6];
    u8 cursor_y[6];
    
};

struct battle_field_state {
    u8 is_raining : 1;
    u8 is_sunny : 1;
    u8 is_sandstorm : 1;
    u8 is_hail : 1;
    u8 is_desolate_land : 1;
    u8 is_primordial_sea : 1;
    u8 is_tailwind : 2; // side

};

struct moves_used {
    u8 move_id;
    u8 power_override;
    u8 type_override;
    u8 user_bank;
};

struct battle_main {
    struct battle_selection_cursor battle_cursor;
    struct battle_field_state field_state;
    u8 selected_option;
    u8 type_objid[4];
    u8 move_name_objid[4];
    u8 fight_menu_content_spawned;
    u8 first_bank;
    u8 second_bank;
    u8 execution_index;
    struct moves_used b_moves[2];
};

enum fight_menu {
    OPTION_FIGHT,
    OPTION_POKEMON,
    OPTION_BAG,
    OPTION_RUN
};



extern struct battle_main* battle_master;
extern u8 bs_anim_status;

#endif /* BATTLE_STATE_H_ */