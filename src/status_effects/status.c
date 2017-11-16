#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern u16 rand_range(u16, u16);

void sleep_on_inflict(u8 bank)
{
	u8 ailment = rand_range(1, 3);
	p_bank[bank]->b_data.status_turns = ailment;
	pokemon_setattr(p_bank[bank]->this_pkmn,REQUEST_STATUS_AILMENT, &ailment);

}

void poison_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_POISON;
	pokemon_setattr(p_bank[bank]->this_pkmn,REQUEST_STATUS_AILMENT, &ailment);
}

void toxic_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_TOXIC;
	pokemon_setattr(p_bank[bank]->this_pkmn,REQUEST_STATUS_AILMENT, &ailment);
}

void burn_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_BURN;
	pokemon_setattr(p_bank[bank]->this_pkmn,REQUEST_STATUS_AILMENT, &ailment);

}

void freeze_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_FREEZE;
	pokemon_setattr(p_bank[bank]->this_pkmn,REQUEST_STATUS_AILMENT, &ailment);

}

void paralyze_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_PARALYZE;
	pokemon_setattr(p_bank[bank]->this_pkmn,REQUEST_STATUS_AILMENT, &ailment);

}

void confusion_on_inflict(u8 bank)
{
	p_bank[bank]->b_data.confusion_turns = rand_range(1, 5);
}


extern void status_graphical_update(u8 bank, enum Effect status);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
void effect_cure_on_inflict(u8 bank)
{
	p_bank[bank]->b_data.status = EFFECT_NONE;
	p_bank[bank]->b_data.status_turns = 0;
	p_bank[bank]->b_data.confusion_turns = 0;
	enqueue_message(0, bank, STRING_AILMENT_CURED, 0);
	status_graphical_update(bank, EFFECT_CURE);
}


void confusion_on_residual(u8 bank)
{
	if (p_bank[bank]->b_data.confusion_turns) {
		p_bank[bank]->b_data.confusion_turns--;
	}
}

void sleep_on_residual(u8 bank)
{
	if (p_bank[bank]->b_data.sleep_turns) {
		p_bank[bank]->b_data.sleep_turns--;
	}
}

void poison_on_residual(u8 bank)
{
	// do dmg
}

void toxic_on_residual(u8 bank)
{
	// do dmg

}

void burn_on_residual(u8 bank)
{
	// do dmg

}





