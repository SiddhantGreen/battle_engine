#ifndef GAME_ACTIONS_H_
#define GAME_ACTIONS_H_

#include <pokeagb/pokeagb.h>

#define ACTION_HEAD battle_master->action_head

enum ActionTiming {
    ActionMove = 0, // Make a move
    ActionSwitch, // Make a switch
    ActionFaint, // Faint a bank
    ActionText, // Display game text
    ActionDamage, // Do damage
    ActionHeal, // Do damage
};



struct action {
    u8 action_bank;
    u8 target;
    enum ActionTiming type;
    u8 action_state; // which game loop function is under execution right now
    struct action* next_action;
};


extern struct action* add_action(u8 bank, u8 target, u8 type, u8 action_state);
extern void delete_action(u8 type, u8 bank);

#endif /* GAME_ACTIONS_H_ */
