#ifndef MOVE_CHAIN_STATES_H_
#define MOVE_CHAIN_STATES_H_

enum RunDecisionStates {
    S_RUN_SWITCH = 0,
    S_RUN_AFTER_SWITCH,
    S_RUN_SWITCH_ALTERNATE_BANK,
    S_RUN_MOVE,
    S_RUN_FAINT,
    S_RUN_MOVE_ALTERNATE_BANK,
    S_SOFT_RESET_BANK,
    S_END_BATTLE,
    
};

enum RunFaintStates {
    S_CHECK_BANK1_FAINT = 0,
    S_CHECK_BANK2_FAINT,
    S_RESOLVE_FAINTS,
};


enum RunFleeStates {
    S_CHECK_FLEEING = 0,
    S_NOT_FLEEING,
    S_TRY_FLEE,    
};


enum RunSwitchStates {
    S_RUN_FLEE = 0,
    S_RUN_SWITCH_CHECKS,
    S_SWITCH_LOGIC,
};


#endif /* MOVE_CHAIN_STATES_H_ */

