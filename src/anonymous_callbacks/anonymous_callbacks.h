#include <pokeagb/pokeagb.h>
#include "../moves/moves.h"

#define CB_ON_BEFORE_TURN 1
#define CB_ON_BEFORE_SWITCH 2
#define CB_ON_BEFORE_MOVE 3
#define CB_ON_MOVE_FAIL 4
#define CB_ON_MODIFY_MOVE 5
#define CB_ON_TRYHIT_MOVE 6
#define CB_ON_BASE_POWER_MOVE 7
#define CB_ON_DAMAGE_MOVE 8
#define CB_ON_EFFECT 9
#define CB_ON_AFTER_MOVE 10
#define CB_BEFORE_MOVE 11


struct anonymous_callback {
	s8 priority;
	u8 delay_before_effect : 7;
	u8 in_use : 1;
	u8 duration;
	u8 source_bank; // source bank using the effect
	void* data_ptr;
	u32 func;
};

struct anonymous_callbacks_master {
	struct anonymous_callback before_turn[4];
	struct anonymous_callback before_switch[4];
	struct anonymous_callback before_move[4];
	struct anonymous_callback on_move_fail[4];
	struct anonymous_callback on_modify_move[4];
	struct anonymous_callback on_tryhit_move[4];
	struct anonymous_callback on_base_power_move[4];
	struct anonymous_callback on_damage_move[4];
	struct anonymous_callback on_effect_cb[4];
	struct anonymous_callback on_after_move[4];
};

typedef u8 (*AnonymousCallback)(u8 source, u8 target, u16 move, struct anonymous_callback* acb);
