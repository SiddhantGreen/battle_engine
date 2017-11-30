#include <pokeagb/pokeagb.h>
#include "../moves/moves.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern void sort_priority_cbs(void);

// insert a new anonymous callback
void add_callback(u8 CB_id, s8 priority, u8 dur, u8 src, u32 func)
{
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        if (!(CB_MASTER[i].in_use)) {
            // initialize new callback here
            CB_MASTER[i].priority = priority;
            CB_MASTER[i].delay_before_effect = 0;
            CB_MASTER[i].in_use = true;
            CB_MASTER[i].duration = dur;
            CB_MASTER[i].source_bank = src;
            CB_MASTER[i].cb_id = CB_id;
            CB_MASTER[i].data_ptr = NULL;
            CB_MASTER[i].func = func;
            break;
        }
    }
}

// execution order building before executing a specific type of CB
void build_execution_order(u8 CB_id) {
    sort_priority_cbs();
    CB_EXEC_INDEX = 0;
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        if ((CB_MASTER[i].cb_id != CB_id) || (!CB_MASTER[i].in_use) || (CB_MASTER[i].delay_before_effect)) {
            continue;
        } else {
            CB_EXEC_ORDER[CB_EXEC_INDEX] = i;
            CB_EXEC_INDEX++;
        }
    }
    CB_EXEC_ORDER[CB_EXEC_INDEX] = ANON_CB_MAX;
    CB_EXEC_INDEX = 0;
}

// Run the next callback in the built list
u16 pop_callback(u8 attacker, u16 move) {
    u8 i = CB_EXEC_ORDER[CB_EXEC_INDEX];
    if (i != ANON_CB_MAX) {
        i = CB_EXEC_ORDER[CB_EXEC_INDEX];
        CB_EXEC_INDEX++;
        AnonymousCallback func = (AnonymousCallback)CB_MASTER[i].func;
        battle_master->executing = true;
        dprintf("executing a function at %x\n", CB_MASTER[i].func -1);
        return func(attacker, CB_MASTER[i].source_bank, move, &CB_MASTER[i]);

    }
    // callbacks are done executing here
    battle_master->executing = false;
    CB_EXEC_INDEX = 0;
    return true;
}


// turn end, drop counters of array elements
void update_callbacks() {
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        // Count down turn delay
        if (!CB_MASTER[i].in_use) continue;
        if (CB_MASTER[i].delay_before_effect) {
            CB_MASTER[i].delay_before_effect--;
        } else {
            // Count down duration if delay done
            if ((CB_MASTER[i].duration) && (CB_MASTER[i].duration < 0xFF)) {
                CB_MASTER[i].duration--;
            } else {
                CB_MASTER[i].in_use = false;
            }
        }
    }
    sort_priority_cbs();
}


/* Array sorting by struct element Priority */
void callbacks_swap(u8 i, u8 j)
{
    struct anonymous_callback temp = CB_MASTER[i];
    CB_MASTER[i] = CB_MASTER[j];
    CB_MASTER[j] = temp;
    return;
}

void sort_priority_cbs()
{
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        for (u8 j = i + 1; j < ANON_CB_MAX; j++) {
            if (ELE_NULL(i) && ELE_USED(j)) {
                callbacks_swap(i, j);
            } else if (ELE_USED(i) && ELE_USED(j)) {
                if (ANON_PRIORITY(i) < ANON_PRIORITY(j)) {
                    callbacks_swap(i, j);
                }
            }
        }
    }
}


u8 id_by_func(u32 func)
{
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        if (CB_MASTER[i].func == func)
            return i;
    }
    return 255;
}

u16 set_data_next_acb(u32 data) {
    u8 i = CB_EXEC_ORDER[CB_EXEC_INDEX];
    if (i != ANON_CB_MAX) {
        CB_MASTER[i].data_ptr = data;
    }
}
