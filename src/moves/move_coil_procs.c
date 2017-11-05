#include <pokeagb/pokeagb.h>
#include "moves.h"

/* Boosts atk, def and accuracy sharply */

/* Boosts evasion for some reason instead right now? */

struct move_procs coil_proc = {
    100,              // Chance to boost self, 0-100
    0,              // Chance to boost opponent, 0-100
    {STAT_ATTACK, STAT_DEFENSE, STAT_NONE, STAT_NONE, STAT_NONE, STAT_ACCURACY},  // Stat to boost self
    {STAT_NONE, STAT_NONE, STAT_NONE, STAT_NONE, STAT_NONE, STAT_NONE},  // Stat to boost opponent
    {1, 1, 0, 0, 0, 1},  // Amount to boost self on proc (signed)
    {0, 0, 0, 0, 0, 0},  // Amount to boost opponent on proc (signed)
    {AILMENT_NONE, AILMENT_NONE},
    {0, 0},
};