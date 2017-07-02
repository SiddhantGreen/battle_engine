#include <pokeagb/pokeagb.h>
#include "../../../battle_data/pkmn_bank.h"
#include "../../../battle_data/pkmn_bank_stats.h"
#include "../../../battle_data/battle_state.h"
#include "../../../moves/moves.h"
#include "../../../battle_text/battle_pick_message.h"
#include "../../move_chain_states.h"

extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool peek_message(void);
extern void run_decision(void);
extern void dprintf(const char * str, ...);
extern void run_switch(void);
extern bool bank_trapped(u8 bank);
extern u16 rand_range(u16, u16);

bool can_flee_by_random(u8 bank)
{
    p_bank[bank]->b_data.flee_count++;

    u16 reference = B_SPEED_STAT_UMOD(bank) * 128;
    reference /= B_SPEED_STAT_UMOD(FOE_BANK(bank));
    reference += (30 * p_bank[bank]->b_data.flee_count);
    reference = reference & 0xFF;

    u16 random = rand_range(0,255);
    return random < reference;
}

void run_flee()
{
    while (peek_message())
        return;
    
    u8 bank_index = (battle_master->execution_index) ? battle_master->second_bank : battle_master->first_bank;
    switch (super.multi_purpose_state_tracker) {
        case 0:
            // check if the bank is fleeing
            if (p_bank[bank_index]->b_data.is_running) {
                super.multi_purpose_state_tracker = 2;
                break;
            }
            super.multi_purpose_state_tracker++;
            break;
        case 1:
            // return to caller
            dprintf("no one fleeing\n");
            set_callback1(run_switch);
            super.multi_purpose_state_tracker = 1;
            break;
        case 2:
            ability_on_before_switch(bank_index);
            if (!bank_trapped(bank_index)) {
                enqueue_message(MOVE_NONE, bank_index, STRING_FLEE_FAILED, 0);
                extern void option_selection(void);
                set_callback1(option_selection);
                super.multi_purpose_state_tracker = 0;
            } else {
                if (!can_flee_by_random(bank_index)) {
                    //we cannot flee because we failed the dice roll
                    enqueue_message(MOVE_NONE, bank_index, STRING_FLEE_FAILED, 0);
                    set_callback1(run_decision);
                    super.multi_purpose_state_tracker = S_RUN_SWITCH_ALTERNATE_BANK;
                } else {
                    //we can finally flee
                    enqueue_message(MOVE_NONE, bank_index, STRING_FLEE, 0);
                    super.multi_purpose_state_tracker = S_END_BATTLE;
                    set_callback1(run_decision);
                }
            }
            break;
    };
}