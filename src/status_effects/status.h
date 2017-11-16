#ifndef STATUS_DATA_H_
#define STATUS_DATA_H_

#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "move_override.h"
#include "../abilities/ability_override.h"

typedef void (*StatusOnStart)(u8 bank);
typedef void (*StatusOnBeforeMove)(u8 bank);
typedef void (*StatusOnModSpeed)(u8 bank);
typedef void (*StatusOnHit)(u8 bank);
typedef void (*StatusOnInflict)(u8 bank);
typedef void (*StatusOnResidual)(u8 bank);



struct status_ailments {
	StatusOnStart on_start;
	StatusOnBeforeMove on_before_move;
	StatusOnModSpeed on_mod_speed;
	StatusOnHit on_hit;
	StatusOnInflict on_inflict;
	StatusOnResidual on_residual;
};


extern struct status_ailments statuses[];


#endif /* STATUS_DATA_H_ */

