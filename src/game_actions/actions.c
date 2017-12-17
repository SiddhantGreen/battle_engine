#include <pokeagb/pokeagb.h>
#include "../moves/moves.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "actions.h"

extern void dprintf(const char * str, ...);
extern u16 rand_range(u16 min, u16 max);

void clear_actions()
{
    struct action* head = ACTION_HEAD;
    while(true) {
        if (head == NULL) return;
        struct action* next = head->next_action;
        free(head);
        head = next;
    }
}

void debug_print_action_banks()
{
    struct action* a = ACTION_HEAD;
    dprintf("head: %d\n", a->action_bank);
    while(a != NULL) {
        dprintf("action bank is %d\n", a->action_bank);
        a = a->next_action;
    }
}

struct action* add_action(u8 bank, u8 target, u8 type, u8 action_state)
{
    /* initialize action to insert */
    struct action* current_action = (struct action*)malloc_and_clear(sizeof(struct action));
    current_action->action_bank = bank;
    current_action->target = target;
    current_action->type = type;
    current_action->action_state = action_state;
    current_action->next_action = NULL;
    /* insert into next available location on linked list */
    struct action** this_action = &(ACTION_HEAD);
    while (true) {
        if ((*this_action) == NULL) {
            *this_action = current_action;
            break;
        } else if ((*this_action)->next_action == NULL) {
            (*this_action)->next_action = current_action;
            break;
        } else {
            this_action = &(*this_action)->next_action;
        }
    }
    return current_action; // given the parameters, this isn't needed most likely
}

void delete_action(u8 type, u8 bank)
{
    struct action** this_action = &(ACTION_HEAD);
    /* First element in linked list is what we're looking for, adjust head and free. */
    if ((*this_action) == NULL) return;
    if (((*this_action)->type == type) && ((*this_action)->action_bank == bank)) {
        struct action* to_free = *(this_action);
        ACTION_HEAD = (*this_action)->next_action;
        free(to_free);
        return;
    }
    while (true) {
        struct action** next = &((*this_action)->next_action);
        /* if next is what we're looking for, previous should point to next's next */
        if ((*next) == NULL) return;
        if (((*next)->type == type) && ((*next)->action_bank == bank))  {
            struct action* to_free = *(next);
            (*this_action)->next_action = (*next)->next_action;
            free(to_free);
            return;
        } else {
            this_action = next;
        }
    }
}
