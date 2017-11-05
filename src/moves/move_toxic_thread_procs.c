#include <pokeagb/pokeagb.h>
#include "moves.h"

struct move_procs toxic_thread_proc = {
    0,              // Chance to boost self, 0-100
    100,              // Chance to boost opponent, 0-100
    {STAT_NONE, STAT_NONE, STAT_NONE, STAT_SPECIAL_ATTACK, STAT_NONE, STAT_NONE},  // Stat to boost self
    {STAT_ATTACK, STAT_DEFENSE, STAT_NONE, STAT_NONE, STAT_NONE, STAT_NONE},  // Stat to boost opponent
    {0, 0, 0, 0, 0, 0},  // Amount to boost self on proc (signed)
    {0, 0, -2, 0, 0, 0},  // Amount to boost opponent on proc (signed)
    {AILMENT_NONE, AILMENT_POISON},
    {0, 100},
};