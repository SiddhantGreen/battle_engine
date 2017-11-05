#include <pokeagb/pokeagb.h>
#include "moves.h"

/* Boosts def and sp. def */
struct move_procs cosmic_power_proc = {
    100,              // Chance to boost self, 0-100
    0,              // Chance to boost opponent, 0-100
    {STAT_NONE, STAT_DEFENSE, STAT_NONE, STAT_NONE, STAT_SPECIAL_DEFENSE, STAT_NONE},  // Stat to boost self
    {STAT_NONE, STAT_NONE, STAT_NONE, STAT_NONE, STAT_NONE, STAT_NONE},  // Stat to boost opponent
    {0, 1, 0, 0, 1, 0},  // Amount to boost self on proc (signed)
    {0, 0, 0, 0, 0, 0},  // Amount to boost opponent on proc (signed)
    {AILMENT_NONE, AILMENT_NONE},
    {0, 0},
};