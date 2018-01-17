#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../abilities/battle_abilities.h"
#include "status.h"

extern u16 rand_range(u16, u16);
extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern struct move_procs basic_proc;

extern void status_graphical_update(u8 bank, enum Effect status);
extern bool b_pkmn_has_type(u8 bank, enum PokemonType type);
void set_status(u8 bank, enum Effect status)
{
    bool status_applied = false;
    // lowest priority for override are types and current status
    switch (status) {
        case EFFECT_NONE:
            // no status to set
            return;
            break;
        case EFFECT_PARALYZE:
            // electric types are immune. Already status'd is immune
            if ((b_pkmn_has_type(bank, TYPE_ELECTRIC)) || (p_bank[bank]->b_data.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
            break;
        case EFFECT_BURN:
            // fire types are immune.  Already status'd is immune
            if ((b_pkmn_has_type(bank, TYPE_FIRE)) || (p_bank[bank]->b_data.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
            break;
        case EFFECT_POISON:
        case EFFECT_BAD_POISON:
            // poison and steel types are immune. Already status'd is immune
            if ((b_pkmn_has_type(bank, TYPE_POISON)) || (b_pkmn_has_type(bank, TYPE_STEEL)) ||
                (p_bank[bank]->b_data.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
			break;
        case EFFECT_SLEEP:
            // sleep isn't affected by type
            if ((p_bank[bank]->b_data.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
            break;
        case EFFECT_FREEZE:
            // fire types cannot be frozen
            if ((b_pkmn_has_type(bank, TYPE_FIRE)) || (p_bank[bank]->b_data.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
			break;
        case EFFECT_CONFUSION:
            // Confusion isn't affected by type
            if (p_bank[bank]->b_data.pseudo_ailment != AILMENT_CONFUSION)
                status_applied = true;
			break;
        case EFFECT_CURE:
            // cure status
			status_applied = true;
            break;
        case EFFECT_INFACTUATION:
        if (p_bank[bank]->b_data.pseudo_ailment != AILMENT_INFACTUATE)
            status_applied = true;
            break;
        default:
            return;
    };

    // back up cbs
    u8 old_index = CB_EXEC_INDEX;
    u32* old_execution_array = push_callbacks();
    bool executor = battle_master->executing;
    for (u8 i = 0; i < BANK_MAX; i++) {
        u8 ability = p_bank[i]->b_data.ability;
        if ((abilities[ability].on_status) && (ACTIVE_BANK(i)))
            add_callback(CB_ON_STATUS, 0, 0, i, (u32)abilities[ability].on_status);
    }

    // execute cbs
    build_execution_order(CB_ON_STATUS);
    battle_master->executing = true;
    while (battle_master->executing) {
        if (!pop_callback(bank, status)) {
            restore_callbacks(old_execution_array);
            CB_EXEC_INDEX = old_index;
            battle_master->executing = executor;
            enqueue_message(0, bank, STRING_AILMENT_IMMUNE, status);
            return;
        }
    }
    restore_callbacks(old_execution_array);
    CB_EXEC_INDEX = old_index;
    battle_master->executing = executor;

    if (status_applied) {
        if (statuses[status].on_inflict) {
            statuses[status].on_inflict(bank);
            status_graphical_update(bank, status);
        }
    } else {
        enqueue_message(0, bank, STRING_AILMENT_IMMUNE, status);
    }
}

u8 ailment_encode(u8 bank)
{
    switch(p_bank[bank]->b_data.status)
    {
        case AILMENT_SLEEP:
            return p_bank[bank]->b_data.status_turns;
        case AILMENT_POISON:
            return 1<<3;
        case AILMENT_BURN:
            return 1<<4;
        case AILMENT_FREEZE:
            return 1<<5;
        case AILMENT_PARALYZE:
            return 1<<6;
        case AILMENT_BAD_POISON:
            return 1<<7;
        default:
            return 0;
    }
}

void ailment_decode(u8 bank, u8 ailment)
{
    if ((ailment & 7) > 0) {
        p_bank[bank]->b_data.status = AILMENT_SLEEP;
        p_bank[bank]->b_data.status_turns = ailment & 7;
    } else if (ailment & (1<<3))
        p_bank[bank]->b_data.status = AILMENT_POISON;
    else if (ailment & (1<<4))
        p_bank[bank]->b_data.status = AILMENT_BURN;
    else if (ailment & (1<<5))
        p_bank[bank]->b_data.status = AILMENT_FREEZE;
    else if (ailment & (1<<6))
        p_bank[bank]->b_data.status = AILMENT_PARALYZE;
    else if (ailment & (1<<7))
        p_bank[bank]->b_data.status = AILMENT_BAD_POISON;
}
