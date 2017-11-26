#include <pokeagb/pokeagb.h>
#include "moves/moves.h"
#include "battle_data/pkmn_bank_stats.h"
#include "abilities/battle_abilities.h"
#include "battle_data/pkmn_bank.h"
#include "battle_data/battle_state.h"

extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void dprintf(const char * str, ...);

u16 rand_range(u16 min, u16 max)
{
    return (rand() % (max - min)) + min;
}

bool knows_move(u16 move_id, struct Pokemon* p)
{
    for (u8 i = REQUEST_MOVE1; i < (REQUEST_MOVE1 + 4); i++) {
        u16 move = pokemon_getattr(p, i, NULL);
        if (move == move_id)
            return true;
    }
    return false;
}


u8 get_move_index(u16 move_id, struct Pokemon* p)
{
    for (u8 i = REQUEST_MOVE1; i < (REQUEST_MOVE1 + 4); i++) {
        u16 move = pokemon_getattr(p, i, NULL);
        if (move == move_id)
            return i - REQUEST_MOVE1;
    }
    return 255;
}

u8 move_pp_count(u16 move_id, struct Pokemon* p)
{
    for (u8 i = REQUEST_MOVE1; i < (REQUEST_MOVE1 + 4); i++) {
        u16 move = pokemon_getattr(p, i, NULL);
        if (move == move_id)
            return pokemon_getattr(p, ((i - REQUEST_MOVE1) + REQUEST_PP1), NULL);
    }
	// move not found
    return 0;
}

u8 get_ability(struct Pokemon* p)
{
    u8 ability_bit = pokemon_getattr(p, REQUEST_ABILITY_BIT, NULL);
    return pokemon_base_stats[pokemon_getattr(p, REQUEST_SPECIES, NULL)].ability[ability_bit];
}

bool ignoring_item(struct Pokemon* p)
{
    return (get_ability(p) == ABILITY_KLUTZ);
}

bool b_pkmn_has_type(u8 bank, enum PokemonType type)
{
    u8 i;
    for (i = 0; i < sizeof(p_bank[bank]->b_data.type); i++) {
        if (p_bank[bank]->b_data.type[i] == type) {
            return true;
        }
    }
    return false;
}

bool on_ground(u8 bank)
{
    if (b_pkmn_has_type(bank, TYPE_FLYING) ||
       (p_bank[bank]->b_data.ability == ABILITY_LEVITATE)) {
        if(p_bank[bank]->b_data.is_grounded)
            return true;
        return false;
    }
    return true;
}


void do_damage(u8 bank_index, u16 dmg)
{
    // HP bar damage animation
    extern void hp_anim_change(u8 bank, s16 delta);
    s16 delta = B_CURRENT_HP(bank_index) - dmg;
    delta = MAX(delta, 0);
    hp_anim_change(bank_index, delta);
}

void do_heal(u8 bank_index, u16 heal)
{
    // HP bar damage animation
    extern void hp_anim_change(u8 bank, s16 delta);
    s16 delta = B_CURRENT_HP(bank_index) + heal;
    delta = MIN(delta, TOTAL_HP(bank_index));
    hp_anim_change(bank_index, delta);
}

//TODO: IMPLEMENT
void set_ability(u8 bank, u8 source, u8 new_ability)
{

}

u8 count_usable_moves(u8 bank)
{
    u8 usable_moves = 0;
    for (u8 i = 0; i < 4; i++) {
        if (pokemon_getattr(p_bank[bank]->this_pkmn, REQUEST_MOVE1 + i, NULL)) {
            if (pokemon_getattr(p_bank[bank]->this_pkmn, REQUEST_PP1 + 1, NULL))
                usable_moves++;
        } else {
            break;
        }
    }
    return usable_moves;
}

u8 count_total_moves(u8 bank)
{
    u8 move_total = 0;
    for (u8 i = 0; i < 4; i++) {
        if (pokemon_getattr(p_bank[bank]->this_pkmn, REQUEST_MOVE1 + i, NULL)) {
            move_total++;
        } else {
            break;
        }
    }
    return move_total;
}
