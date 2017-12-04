#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
void stored_power_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;

    u8 boost_factor = 0;
    boost_factor += MAX(B_ATTACK_BUFF(user), 0);
    boost_factor += MAX(B_DEFENSE_BUFF(user), 0);
    boost_factor += MAX(B_SPEED_BUFF(user), 0);
    boost_factor += MAX(B_SPATTACK_BUFF(user), 0);
    boost_factor += MAX(B_SPDEFENSE_BUFF(user), 0);
    boost_factor += MAX(B_ACCURACY_BUFF(user), 0);
    boost_factor += MAX(B_EVASION_BUFF(user), 0);

    B_MOVE_POWER(user) = 20 + 20*(boost_factor);
}

void punishment_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;

    u8 boost_factor = 0;
    boost_factor += MAX(B_ATTACK_BUFF(src), 0);
    boost_factor += MAX(B_DEFENSE_BUFF(src), 0);
    boost_factor += MAX(B_SPEED_BUFF(src), 0);
    boost_factor += MAX(B_SPATTACK_BUFF(src), 0);
    boost_factor += MAX(B_SPDEFENSE_BUFF(src), 0);
    boost_factor += MAX(B_ACCURACY_BUFF(src), 0);
    boost_factor += MAX(B_EVASION_BUFF(src), 0);

    B_MOVE_POWER(user) = 60 + 20*(boost_factor);
}
