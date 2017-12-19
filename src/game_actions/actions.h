#ifndef GAME_ACTIONS_H_
#define GAME_ACTIONS_H_

#include <pokeagb/pokeagb.h>

/* The timings only serve as identifiers. Nothing more */
enum ActionTiming {
    ActionMove = 0, // Make a move
    ActionSwitch, // Make a switch
    ActionRun, // Attempt Flee
    ActionFaint, // Faint a bank
    ActionText, // Display game text
    ActionDamage, // Do damage
    ActionHeal, // Do heal
    ActionResidual,
    ActionHighPriority,
};

struct action {
    u8 action_bank;
    u8 target;
    enum ActionTiming type;
    u8 event_state; // which game loop function is under execution right now
    u16 move;
    s16 priv[5];
    struct action* prev_action;
    struct action* next_action;
};

typedef void (*EventCallback)(struct action* a);

/* Macros */
#define ACTION_HEAD battle_master->action_head
#define ACTION_TARGET ACTION_HEAD->target
#define ACTION_BANK ACTION_HEAD->action_bank
#define ACTION_TYPE ACTION_HEAD->type
#define EVENT_STATE ACTION_HEAD->event_state
#define CURRENT_ACTION battle_master->this_action

enum EventStatesWildBattle {
    EventFlee = 0, // 0
    EventSwitch, // 1
    EventBeforeMove, // 2
    EventMoveTargetConfig, // 3
    EventPreMoveHit, // 4
    EventMoveTryHit, // 5
    EventMoveDamage, // 6
    EventMoveHeal, // 7
    EventMoveEffect, // 8
    EventMoveRecoil, // 9
    EventMoveDrain, // 10
    EventMoveBoosts, // 11
    EventMoveAilments, // 12
    EventMoveMultiHitResolve, // 13
    EventMoveAfterMove, // 14
    EventDoFaints, // 15
    EventMoveFailed, // 16
    EventPeekMessage, // 17
    EventDamageAnim, // 18
    EventHealAnim, // 19
    EventFaint, // 20
    EventEndAction, // 21
    EventInactive, // 22
    EventResidualEffects, // 23
    EventWildBattleOver, // 24
    EventEndBattle, // 25
};


extern struct action* add_action(u8 bank, u8 target, u8 type, u8 event_state);
extern void end_action(struct action* a);
extern struct action* prepend_action(u8 bank, u8 target, u8 type, u8 event_state);
extern void clear_actions(void);

#endif /* GAME_ACTIONS_H_ */
