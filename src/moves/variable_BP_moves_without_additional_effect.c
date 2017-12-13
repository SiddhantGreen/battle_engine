#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);

struct basepower_threshold_table
{
    u8 value;
    u8 numerator;
    u8 denominator;
};

void acrobatics_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (B_GET_ITEM(user) == 0)
        B_MOVE_POWER(user) *= 2;
}

void hex_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u8 defender = TARGET_OF(user);
    if (B_STATUS(defender))
        B_MOVE_POWER(user) *= 2;
}

void facade_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (B_STATUS(user))
        B_MOVE_POWER(user) *= 2;
}

void brine_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u8 defender = TARGET_OF(user);
    if ((B_CURRENT_HP(defender) * 2) <= TOTAL_HP(defender))
        B_MOVE_POWER(user) *= 2;
}

void reversal_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u16 current_hp = B_CURRENT_HP(user);
    u16 total_hp = TOTAL_HP(user);
    if((current_hp * 48) >= (total_hp * 33))
        B_MOVE_POWER(user) = 20;
    else if((current_hp * 48) >= (total_hp * 17))
        B_MOVE_POWER(user) = 40;
    else if((current_hp * 48) >= (total_hp * 10))
        B_MOVE_POWER(user) = 80;
    else if((current_hp * 48) >= (total_hp * 5))
        B_MOVE_POWER(user) = 100;
    else if((current_hp * 48) >= (total_hp * 2))
        B_MOVE_POWER(user) = 250;
    else
        B_MOVE_POWER(user) = 200;
}

void heavy_slam_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u16 user_weight = B_WEIGHT(user);
    u16 defender_weight = B_WEIGHT(TARGET_OF(user));
    if((defender_weight * 2) >= user_weight)
        B_MOVE_POWER(user) = 40;
    else if((defender_weight * 3) >= user_weight)
        B_MOVE_POWER(user) = 60;
    else if((defender_weight * 4) >= user_weight)
        B_MOVE_POWER(user) = 80;
    else if((defender_weight * 5) >= user_weight)
        B_MOVE_POWER(user) = 100;
    else
        B_MOVE_POWER(user) = 120;

}

void low_kick_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if(user != src) return;
    u16 defender_weight = B_WEIGHT(TARGET_OF(user));
    if(defender_weight >= 200)
        B_MOVE_POWER(user) = 120;
    else if(defender_weight >= 100)
        B_MOVE_POWER(user) = 100;
    else if(defender_weight >= 50)
        B_MOVE_POWER(user) = 80;
    else if(defender_weight >= 25)
        B_MOVE_POWER(user) = 60;
    else if(defender_weight >= 10)
        B_MOVE_POWER(user) = 40;
    else
        B_MOVE_POWER(user) = 20;
};


void stomping_tantrum_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (B_LAST_MOVE_FAILED(user)) {
        B_MOVE_POWER(user) *= 2;
    }
}


void water_shuriken_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (B_SPECIES(user) != SPECIES_ASH_GRENINJA) return;
    B_MOVE_POWER(user) = moves[move].base_power + 5;
}


/* Echoed voice */
void echoed_voice_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // don't make a duplicate for echoed voice's counter
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (CURRENT_MOVE(i) == MOVE_ECHOED_VOICE) {
            acb->duration += 1;
            acb->data_ptr += 1;
            acb->data_ptr = MIN(acb->data_ptr, 5); // clamp at 5
            return true;
        }
    }
    return true;
}

void echoed_voice_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (!callback_exists((u32)echoed_voice_after_move)) {
        u8 id = add_callback(CB_ON_AFTER_MOVE, 0, 0, user, (u32)echoed_voice_after_move);
        CB_MASTER[id].data_ptr = 1;
    }
    u8 counter = CB_MASTER[id_by_func((u32)echoed_voice_after_move)].data_ptr;
    B_MOVE_POWER(user) = 40 * counter;
    dprintf("power is: %d\n", B_MOVE_POWER(user));
}


/* Electro Ball */
void electro_ball_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u16 user_spe = B_SPEED_STAT(user);
    u16 target_spe = B_SPEED_STAT(TARGET_OF(user));
    u8 power = 40;
    if (user_spe >= target_spe) {
        power = 60;
    }
    if (user_spe >= (2 * target_spe)) {
        power = 80;
    }
    if (user_spe >= (3 * target_spe)) {
        power = 120;
    }
    if (user_spe >= (4 * target_spe)) {
        power = 150;
    }
    B_MOVE_POWER(user) = MAX(power, 40);
}
