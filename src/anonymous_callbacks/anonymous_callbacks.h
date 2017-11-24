#include <pokeagb/pokeagb.h>
#include "../moves/moves.h"

/*
#define CB_BEFORE_TURN 1
#define CB_BEFORE_TURN 2
#define CB_BEFORE_MOVE 3
#define CB_BEFORE_MOVE 4
#define CB_BEFORE_MOVE 5
#define CB_BEFORE_MOVE 6
#define CB_BEFORE_MOVE 7
#define CB_BEFORE_MOVE 8
#define CB_BEFORE_MOVE 9
#define CB_BEFORE_MOVE 10
#define CB_BEFORE_MOVE 11*/


struct anonymous_callback {
	s8 priority;
	u8 delay_before_effect;
	u8 duration;
	void* data_ptr;
	void* func;
};


struct anonymous_callbacks_master {
	struct anonymous_callback before_turn[4];
	struct anonymous_callback before_switch[4];
	struct anonymous_callback on_start[4];
	struct anonymous_callback before_move[4];
	struct anonymous_callback on_move_fail[4];
	struct anonymous_callback on_modify_move[4];
	struct anonymous_callback on_tryhit_move[4];
	struct anonymous_callback on_base_power_move[4];
	struct anonymous_callback on_damage_move[4];
	struct anonymous_callback on_effect_cb[4];
	struct anonymous_callback on_after_move[4];
};












