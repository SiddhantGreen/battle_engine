#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

u8 before_move_charge_frame(u8 bank, u8 string_id)
{
    if (HAS_VOLATILE(bank, VOLATILE_CHARGING)) {
        REMOVE_VOLATILE(bank, VOLATILE_CHARGING);
        return true;
    } else {
        enqueue_message(0, bank, string_id, 0);
        ADD_VOLATILE(bank, VOLATILE_CHARGING);
        return false; // don't fire move if charging
    }
}

/* Basic one turn charge, then simple attack moves */
u8 freeze_shock_before_move(u8 bank)
{
    return before_move_charge_frame(bank, STRING_FREEZE_SHOCK);
}

u8 solarbeam_before_move(u8 bank)
{
    return before_move_charge_frame(bank, STRING_SOLARBEAM);
}

u8 solarblade_before_move(u8 bank)
{
    return before_move_charge_frame(bank, STRING_SOLARBEAM);
}

u8 ice_burn_before_move(u8 bank)
{
    return before_move_charge_frame(bank, STRING_ICE_BURN);
}

u8 razor_wind_before_move(u8 bank)
{
    return before_move_charge_frame(bank, STRING_RAZORWIND);
}

u8 sky_attack_before_move(u8 bank)
{
    return before_move_charge_frame(bank, STRING_CHARGE_SKY_ATTACK);
}

/* Moves with some effect during the charging turn */
