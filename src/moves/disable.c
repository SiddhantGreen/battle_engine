#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern u8 move_pp_count(u16 move_id, struct Pokemon* p);
extern u8 get_move_index(u16 move_id, struct Pokemon* p);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

u8 disable_on_effect_cb(u8 user, u8 target, u16 move)
{
	u16 last_move = p_bank[target]->b_data.last_move;

	// fail if opponent hasn't used a move yet
	if (last_move == MOVE_NONE)
		return false;
	
	// fail if move has 0 PP remaining
	if (move_pp_count(last_move, p_bank[target]->this_pkmn) < 1)
		return false;
	
	// fail if move index not found
	u8 index = get_move_index(last_move, p_bank[target]->this_pkmn);
	if (index == 255)
		return false;
	
	// fail if a move has already been disabled
	if (p_bank[target]->b_data.disable_used_on_slot < 4)
		return false;
	
	// add the move to the disabled moves array in pbank
	if (p_bank[target]->b_data.disabled_moves[index] == 0) {
		p_bank[target]->b_data.disabled_moves[index] = 4; // disable move index for 4 turns
		p_bank[target]->b_data.disable_used_on_slot = index; // disable move index for 4 turns
		enqueue_message(last_move, user, STRING_DISABLED, 0);
		return true;
	} else {
		return false; // move is already disabled
	}
}



