#include <pokeagb/pokeagb.h>
#include "../moves.h"

extern void nullsub_move(void);
extern struct move_callbacks null_mbc;

struct move_procs pound_procs = {
    0,              // Chance to boost self, 0-100
    0,              // Chance to boost opponent, 0-100
    STAT_NONE,      // Stat to boost self
    STAT_NONE,      // Stat to boost opponent
    0,              // Amount to boost self on proc (signed)
    0,              // Amount to boost opponent on proc (signed)
    1,              // Lower bound for multi hit
    1               // Upper bound for multi hit
};

struct move_callbacks pound_cbs = {
    (BasePowerCallback)nullsub_move,
    (BeforeTurnCallback)nullsub_move,
    (DurationCallback)nullsub_move,
    (DamageCallback)nullsub_move,
    (BeforeMoveCallback)nullsub_move,
};