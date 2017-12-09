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
    u8 defender = TARGET_OF(user);
    u16 user_weight = B_WEIGHT(user);
    u16 defender_weight = B_WEIGHT(defender);
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
    u8 defender = TARGET_OF(user);
    u16 defender_weight = B_WEIGHT(defender);
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
