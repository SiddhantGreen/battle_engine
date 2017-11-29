#ifndef ANONYMOUS_CALLBACKS_H_
#define ANONYMOUS_CALLBACKS_H_

#include <pokeagb/pokeagb.h>


#define ANON_CB_MAX 40
#define ELE_NULL(i) (battle_master->anon_cb_master[i].in_use == false)
#define ELE_USED(i) (battle_master->anon_cb_master[i].in_use == true)
#define ANON_PRIORITY(i) battle_master->anon_cb_master[i].priority
#define CB_MASTER battle_master->anon_cb_master
#define CB_EXEC_ORDER battle_master->cb_execution_order
#define CB_EXEC_INDEX battle_master->current_cb_index

#define CB_ON_BEFORE_TURN 1
#define CB_ON_BEFORE_SWITCH 2
#define CB_ON_BEFORE_MOVE 3
#define CB_ON_START 11
#define CB_ON_MOVE_FAIL 4
#define CB_ON_MODIFY_MOVE 5
#define CB_ON_TRYHIT_MOVE 6
#define CB_ON_BASE_POWER_MOVE 7
#define CB_ON_DAMAGE_MOVE 8
#define CB_ON_EFFECT 9
#define CB_ON_AFTER_MOVE 10
#define CB_ON_TRYHIT_INV_MOVE 12
#define CB_ON_RESIDUAL 13



struct anonymous_callback {
	s8 priority;
	u8 delay_before_effect : 7;
	u8 in_use : 1;
	u8 duration;
	u8 source_bank; // source bank using the effect
	u8 cb_id; // execution timing, callback id
	void* data_ptr;
	u32 func;
};

typedef u16 (*AnonymousCallback)(u8 source, u8 target, u16 move, struct anonymous_callback* acb);

extern void add_callback(u8 CB_id, s8 priority, u8 dur, u8 src, u32 func);
extern void build_execution_order(u8 CB_id);
extern u16 pop_callback(u8 attacker, u16 move);
extern void update_callbacks(void);
extern u8 id_by_func(u32 func);

#endif /* ANONYMOUS_CALLBACKS_H_ */
