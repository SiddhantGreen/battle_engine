#ifndef RESIDUAL_CBS_H_
#define RESIDUAL_CBS_H_

#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"

typedef void(*ResidualFunc)(u8 index);

struct residual_callback {
    ResidualFunc func;
    u8 effective_bank;
    u8 active_counter;
    u16 move_id; // or effect id
    enum VolatileStatus status;
    u16 hp_delta;
};

struct residual_callback residual_callbacks[20];


#endif /* RESIDUAL_CBS_H_ */

