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

#define NO_OF_REVERSAL_THRESHOLDS 6
struct basepower_threshold_table reversal_slab[NO_OF_REVERSAL_THRESHOLDS] = {
                            {20,    66, 96},
                            {40,    34, 96},
                            {80,    20, 96},
                            {100,   10, 96},
                            {150,   4,  96},
                            {200,   0,  1},
                        };

void reversal_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u16 current_hp = B_CURRENT_HP(user);
    u16 total_hp = TOTAL_HP(user);
    for (u8 i=0; i<NO_OF_REVERSAL_THRESHOLDS-1; i++)
    {
        if(current_hp >= ((total_hp * reversal_slab[i].numerator)/ reversal_slab[i].denominator))
        {
             B_MOVE_POWER(user) = reversal_slab[i].value;
             break;
        }
    }
}

#define NO_OF_HEAVY_SLAM_THRESHOLDS 5
struct basepower_threshold_table heavy_slam_slab[NO_OF_HEAVY_SLAM_THRESHOLDS] = {
                            {40,    1, 2},
                            {60,    1, 3},
                            {80,    1, 4},
                            {100,   1, 5},
                            {120,   0, 1},
                        };

void heavy_slam_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u8 defender = TARGET_OF(user);
    u16 user_weight = B_WEIGHT(user);
    u16 defender_weight = B_WEIGHT(defender);
    for (u8 i = 0; i < NO_OF_HEAVY_SLAM_THRESHOLDS - 1; i++)
    {
        if((defender_weight * heavy_slam_slab[i].denominator) >= (user_weight * heavy_slam_slab[i].numerator))
        {
             B_MOVE_POWER(user) = heavy_slam_slab[i].value;
             break;
        }
    }
}

#define NO_OF_LOW_KICK_THRESHOLDS 6
struct basepower_threshold_table low_kick_slab[NO_OF_LOW_KICK_THRESHOLDS] = {
                            {20,    0,   0},
                            {40,    10,  0},
                            {60,    25,  0},
                            {80,    50,  0},
                            {100,   100, 0},
                            {120,   200, 0},
                        };

void low_kick_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if(user != src) return;
    u8 defender = TARGET_OF(user);
    u16 defender_weight = B_WEIGHT(defender);
    for (u8 i = NO_OF_HEAVY_SLAM_THRESHOLDS; i > 0; i--)
    {
        if(defender_weight  >= low_kick_slab[i].numerator)
        {
             B_MOVE_POWER(user) = low_kick_slab[i].value;
             break;
        }
    }
};
