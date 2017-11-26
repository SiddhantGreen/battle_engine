#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void set_attack_battle_master(u8 bank, u8 index, s8 priority);
extern u16 rand_range(u16 min, u16 max);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void dprintf(const char * str, ...);
extern u8 count_usable_moves(u8 bank);
extern u8 count_total_moves(u8 bank);

/* Metronome */

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

/* Mirror Move */
u8 mirror_move_on_modify_move(u8 bank, u8 target, u16 mirror_move)
{
    // fails if target hasn't made a move or target's move isn't mirrorable
    if ((LAST_MOVE(target) != MOVE_NONE) && (IS_MIRRORABLE(LAST_MOVE(target)))) {
        CURRENT_MOVE(bank) = LAST_MOVE(target);
        set_attack_battle_master(bank, B_MOVE_BANK(bank), MOVE_PRIORITY(CURRENT_MOVE(bank)));
        enqueue_message(CURRENT_MOVE(bank), bank, STRING_ATTACK_USED, 0);
        return true;
    }
    return false;
}

/* Sleep Talk */
const static u16 sleep_talk_disallow[] = {
    MOVE_ASSIST, MOVE_BEAK_BLAST, MOVE_BELCH,
    MOVE_BIDE, MOVE_CHATTER, MOVE_COPYCAT,
    MOVE_FOCUS_PUNCH, MOVE_ME_FIRST, MOVE_METRONOME,
    MOVE_MIMIC, MOVE_MIRROR_MOVE, MOVE_NATURE_POWER,
    MOVE_SHELL_TRAP, MOVE_SKETCH, MOVE_SLEEP_TALK, MOVE_UPROAR,

};

bool is_allowed_sleep_talk(u16 move)
{
    for (u8 i = 0; i < (sizeof(sleep_talk_disallow) / sizeof(u16)); i++) {
        if (move == sleep_talk_disallow[i])
            return false;
    }
    return true;
}

u8 sleep_talk_before_move(u8 bank)
{
    if ((B_STATUS(bank) == AILMENT_SLEEP) || (BANK_ABILITY(bank) == ABILITY_COMATOSE)) {
        REMOVE_VOLATILE(bank, VOLATILE_SLEEP_TURN);
        enqueue_message(0, bank, STRING_FAST_ASLEEP, 0);
    }
    return true;
}

u8 sleep_talk_on_modify_move(u8 bank, u8 target, u16 sleep_talk)
{
    if ((B_STATUS(bank) == AILMENT_SLEEP) || (BANK_ABILITY(bank) == ABILITY_COMATOSE)) {
        // fail if no moves learnt
        u8 move_set[4] = {MOVE_NONE, MOVE_NONE, MOVE_NONE, MOVE_NONE};
        u8 array_slot = 0;
        for (u8 i = 0; i < 4; i++) {
            u16 this_move = pokemon_getattr(p_bank[bank]->this_pkmn, REQUEST_MOVE1 + i, NULL);
            if ((this_move != MOVE_NONE) && (is_allowed_sleep_talk(this_move)) && (!(IS_CHARGE(this_move)))) {
                move_set[array_slot] = this_move;
                array_slot++;
            }
        }

        if (array_slot) {
            CURRENT_MOVE(bank) = move_set[rand_range(0, array_slot)];
            set_attack_battle_master(bank, B_MOVE_BANK(bank), MOVE_PRIORITY(CURRENT_MOVE(bank)));
            enqueue_message(CURRENT_MOVE(bank), bank, STRING_ATTACK_USED, 0);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}


/* Assist */
const static u16 assist_disallow[] = {
    MOVE_ASSIST, MOVE_BELCH, MOVE_BESTOW,
    MOVE_BOUNCE, MOVE_CHATTER, MOVE_CIRCLE_THROW,
    MOVE_COPYCAT, MOVE_COUNTER, MOVE_COVET,
    MOVE_DESTINY_BOND, MOVE_DETECT, MOVE_DIG,
    MOVE_DIVE, MOVE_DRAGON_TAIL, MOVE_ENDURE,
    MOVE_FEINT, MOVE_FLY, MOVE_FOCUS_PUNCH,
    MOVE_FOLLOW_ME, MOVE_HELPING_HAND, MOVE_KINGS_SHIELD,
    MOVE_MAT_BLOCK, MOVE_ME_FIRST, MOVE_METRONOME,
    MOVE_MIMIC, MOVE_MIRROR_COAT, MOVE_MIRROR_MOVE,
    MOVE_NATURE_POWER, MOVE_PHANTOM_FORCE, MOVE_PROTECT,
    MOVE_RAGE_POWDER, MOVE_ROAR, MOVE_SHADOW_FORCE,
    MOVE_SKETCH, MOVE_SKY_DROP, MOVE_SLEEP_TALK,
    MOVE_SNATCH, MOVE_SPIKY_SHIELD, MOVE_STRUGGLE,
    MOVE_SWITCHEROO, MOVE_THIEF, MOVE_TRANSFORM,
    MOVE_TRICK, MOVE_WHIRLWIND, MOVE_MAX, MOVE_NONE,
};

bool is_allowed_assist(u16 move)
{
    for (u8 i = 0; i < ((sizeof(assist_disallow)) / sizeof(u16)); i++) {
        if (assist_disallow[i] == move)
            return false;
    }
    return true;
}

u8 assist_on_modify_move(u8 bank, u8 target, u16 assist_move)
{
    u16 move_set[24] = {MOVE_NONE};
    u8 array_slot = 0;
    u8 poke_count = count_pokemon();
    struct Pokemon* bank_party = (SIDE_OF(bank)) ? (&party_opponent[0]) : (&party_player[0]);
    for (u8 i = 0; i < poke_count; i++) {
        if ((u32)&bank_party[i] == (u32)p_bank[bank]->this_pkmn)
            continue;
        for (u8 j = 0; j < 4; j++) {
            u16 this_move = pokemon_getattr(&bank_party[i], REQUEST_MOVE1 + j, NULL);
            if (is_allowed_assist(this_move)) {
                move_set[array_slot] = this_move;
                array_slot++;
            }
        }
    }

    if (array_slot) {
        CURRENT_MOVE(bank) = move_set[rand_range(0, array_slot)];
        set_attack_battle_master(bank, B_MOVE_BANK(bank), MOVE_PRIORITY(CURRENT_MOVE(bank)));
        enqueue_message(CURRENT_MOVE(bank), bank, STRING_ATTACK_USED, 0);
        return true;
    } else {
        return false;
    }
}


/* Copycat */
const static u16 copycat_disallow[] = {
    MOVE_ASSIST, MOVE_BANEFUL_BUNKER, MOVE_BESTOW, MOVE_CHATTER,
    MOVE_CIRCLE_THROW, MOVE_COPYCAT, MOVE_COUNTER, MOVE_COVET,
    MOVE_DESTINY_BOND, MOVE_DETECT, MOVE_DRAGON_TAIL, MOVE_ENDURE,
    MOVE_FEINT, MOVE_FOCUS_PUNCH, MOVE_FOLLOW_ME, MOVE_HELPING_HAND,
    MOVE_ME_FIRST, MOVE_METRONOME, MOVE_MIMIC, MOVE_MIRROR_COAT,
    MOVE_MIRROR_MOVE, MOVE_NATURE_POWER, MOVE_PROTECT,
    MOVE_RAGE_POWDER, MOVE_ROAR, MOVE_SKETCH, MOVE_SLEEP_TALK,
    MOVE_SNATCH, MOVE_STRUGGLE, MOVE_SWITCHEROO, MOVE_THIEF,
    MOVE_TRANSFORM, MOVE_TRICK, MOVE_WHIRLWIND, MOVE_NONE, MOVE_MAX
};

bool is_allowed_copycat(u16 move)
{
    for (u8 i = 0; i < ((sizeof(copycat_disallow)) / sizeof(u16)); i++) {
        if (copycat_disallow[i] == move)
            return false;
    }
    return true;
}

u8 copycat_on_modify_move(u8 bank, u8 target, u16 copycat_move)
{
    u16 last_move = battle_master->field_state.last_used_move;
    dprintf("Last move: %d\n", last_move);
    if (is_allowed_copycat(last_move)) {
        CURRENT_MOVE(bank) = last_move;
        set_attack_battle_master(bank, B_MOVE_BANK(bank), MOVE_PRIORITY(CURRENT_MOVE(bank)));
        enqueue_message(CURRENT_MOVE(bank), bank, STRING_ATTACK_USED, 0);
        return true;
    } else {
        return false;
    }
}

/* Mirror coat */
extern bool add_anon_cb(u8 CB_id, s8 priority, u8 delay, u8 dur, u8 src, u32 func);

u16 magic_coat_tryhit_anon(u8 user, u8 source, u16 move)
{
	if ((user == source) || B_MOVE_HAS_BOUNCED(user) || (!IS_REFLECTABLE(move)))
		return true;
	TARGET_OF(user) = user;
	enqueue_message(CURRENT_MOVE(user), user, STRING_BOUNCED_BACK, 0);
	return true;
}

u8 magic_coat_on_tryhit(u8 bank, u8 defender, u16 move_mirror_coat)
{
	enqueue_message(CURRENT_MOVE(bank), bank, STRING_SHROUDED_MAGICCOAT, 0);
	return add_anon_cb(CB_ON_TRYHIT_MOVE, 2, 0, 1, bank, (u32)(magic_coat_tryhit_anon));
}


/* Me first */
const static u16 me_first_disallow[] = {
	MOVE_CHATTER, MOVE_COUNTER, MOVE_COVET, MOVE_FOCUS_PUNCH,
	MOVE_ME_FIRST, MOVE_METAL_BURST, MOVE_MIRROR_COAT,
	MOVE_STRUGGLE, MOVE_THIEF, MOVE_MAX, MOVE_NONE
};

u8 me_first_on_base_power_anon(u8 attacker, u8 src, u16 move)
{
	u8 base_power = B_MOVE_POWER(attacker);
	if (attacker == src) {
		u8 bp = NUM_MOD(base_power, 150);
		if (bp < base_power)
			base_power = 255;
	}
	return base_power;
}

u8 me_first_on_tryhit (u8 attacker, u8 defender, u16 move_me_first)
{
	// fail if user hasn't moved before target
	if (attacker != battle_master->first_bank)
		return false;

	u16 move = CURRENT_MOVE(defender);
	if (IS_MOVE_STATUS(move))
		return false;
	for (u8 i = 0; i < (sizeof(me_first_disallow) / sizeof(u16)); i++) {
		if (me_first_disallow[i] == move)
			return false;
	}

	// move is valid to be copied
	CURRENT_MOVE(attacker) = move;
	set_attack_battle_master(attacker, B_MOVE_BANK(attacker),
	 												MOVE_PRIORITY(CURRENT_MOVE(attacker)));
	enqueue_message(CURRENT_MOVE(attacker), attacker, STRING_ATTACK_USED, 0);
	return add_anon_cb(CB_ON_BASE_POWER_MOVE, 0, 0, 0,
		 					attacker, (u32)me_first_on_base_power_anon);
}

/* Snatch */
extern void set_attack_battle_master(u8 bank, u8 index, s8 priority);
u16 statch_tryhit_anon(u8 user, u8 source, u16 move)
{
	if ((user == source) || (!IS_SNATCHABLE(move))) {
		return true;
	}
	if (battle_master->execution_index) {
		battle_master->second_bank = source;
	} else {
		battle_master->first_bank = source;
	}
	CURRENT_MOVE(source) = move;
	set_attack_battle_master(source, B_MOVE_BANK(source), 0);
	enqueue_message(0, source, STRING_SNATCHED_MOVE, 0);
	return true;
}

u8 snatch_on_effect(u8 attacker, u8 defender, u16 move)
{
	enqueue_message(CURRENT_MOVE(attacker), attacker, STRING_SNATCH_WAITING, 0);
	return add_anon_cb(CB_ON_TRYHIT_MOVE, 0, 0, 1, attacker, (u32)(statch_tryhit_anon));
}
