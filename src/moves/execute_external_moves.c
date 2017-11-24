#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void set_attack_battle_master(u8 bank, u8 index, s8 priority);
extern u16 rand_range(u16 min, u16 max);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void dprintf(const char * str, ...);

const static u16 metronome_disallow[] = {
	MOVE_AFTER_YOU, MOVE_ASSIST, MOVE_BELCH, MOVE_BESTOW,
	MOVE_CELEBRATE, MOVE_CHATTER, MOVE_COPYCAT, MOVE_COUNTER,
	MOVE_COVET, MOVE_CRAFTY_SHIELD, MOVE_DESTINY_BOND, MOVE_DETECT,
	MOVE_DIAMOND_STORM, MOVE_DRAGON_ASCENT, MOVE_ENDURE, MOVE_FEINT,
	MOVE_FOCUS_PUNCH, MOVE_FOLLOW_ME, MOVE_FREEZE_SHOCK, MOVE_HAPPY_HOUR,
	MOVE_HELPING_HAND, MOVE_HOLD_HANDS, MOVE_HYPERSPACE_FURY,
	MOVE_HYPERSPACE_HOLE, MOVE_ICE_BURN, MOVE_KINGS_SHIELD,
	MOVE_LIGHT_OF_RUIN, MOVE_MAT_BLOCK, MOVE_ME_FIRST, MOVE_METRONOME,
	MOVE_MIMIC, MOVE_MIRROR_COAT, MOVE_MIRROR_MOVE, MOVE_NATURE_POWER,
	MOVE_ORIGIN_PULSE, MOVE_PRECIPICE_BLADES, MOVE_PROTECT, MOVE_QUASH,
	MOVE_QUICK_GUARD, MOVE_RAGE_POWDER, MOVE_RELIC_SONG, MOVE_SECRET_SWORD,
	MOVE_SKETCH, MOVE_SLEEP_TALK, MOVE_SNARL, MOVE_SNATCH,
	MOVE_SNORE, MOVE_SPIKY_SHIELD, MOVE_STEAM_ERUPTION, MOVE_STRUGGLE,
	MOVE_SWITCHEROO, MOVE_TECHNO_BLAST, MOVE_THIEF, MOVE_THOUSAND_ARROWS,
	MOVE_THOUSAND_WAVES, MOVE_TRANSFORM, MOVE_TRICK,
	MOVE_VCREATE, MOVE_WIDE_GUARD, MOVE_MAX,
};

u16 pick_rand_metronome_move()
{
	bool unusable_move = true;
    u16 selected_move = MOVE_NONE;
	while (unusable_move) {
		selected_move = rand_range(1, MOVE_MAX);
		for (u8 i = 0; i < (sizeof(metronome_disallow) / sizeof(u16)); i++) {
			if (metronome_disallow[i] == selected_move) {
				unusable_move = false;
				break;
			}
		}
		unusable_move = (unusable_move) ? false : true;
	}
	return selected_move;
}

u8 metronome_on_modify_move(u8 bank, u8 target, u16 move_metronome)
{
    CURRENT_MOVE(bank) = pick_rand_metronome_move();
 	set_attack_battle_master(bank, B_MOVE_BANK(bank), MOVE_PRIORITY(CURRENT_MOVE(bank)));
    enqueue_message(CURRENT_MOVE(bank), bank, STRING_ATTACK_USED, 0);
    return true;
}



