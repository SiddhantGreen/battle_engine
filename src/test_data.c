#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/pkmn_bank_stats.h"
#include "battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
void set_player_battle_components()
{
    /* Change these variables to change what the player's first pokemon has */
	u16 species = SPECIES_CATERPIE;
    //u16 species = pokemon_getattr(&party_player[0], REQUEST_SPECIES, NULL);
    u16 move_1 = MOVE_WATER_GUN;
    u16 move_2 = MOVE_CONVERSION;
    u16 move_3 = MOVE_FRENZY_PLANT;
    u16 move_4 = MOVE_GIGA_IMPACT;
    u8 level = 80;

    pokemon_setattr(&party_player[0], REQUEST_SPECIES, &species);
    pokemon_setattr(&party_player[0], REQUEST_NICK, &pokemon_names[species]);
    u32 species_exp_index = (pokemon_base_stats[species].exp_growth * 0x194);
    u32 *exp_needed = (u32*) (0x8253AE4 + (species_exp_index + (level * 4)));
    pokemon_setattr(&party_player[0], REQUEST_EXP_POINTS, exp_needed);
    recalculate_stats(&party_player[0]);
    pokemon_setattr(&party_player[0], REQUEST_MOVE1, &move_1);
    pokemon_setattr(&party_player[0], REQUEST_MOVE2, &move_2);
    pokemon_setattr(&party_player[0], REQUEST_MOVE3, &move_3);
    pokemon_setattr(&party_player[0], REQUEST_MOVE4, &move_4);
    pokemon_setattr(&party_player[0], REQUEST_PP1, &moves[move_1].pp);
    pokemon_setattr(&party_player[0], REQUEST_PP2, &moves[move_2].pp);
    pokemon_setattr(&party_player[0], REQUEST_PP3, &moves[move_3].pp);
    pokemon_setattr(&party_player[0], REQUEST_PP4, &moves[move_4].pp);
}

void set_opponent_battle_components()
{
    /* Change these variables to change what the player's first pokemon has */
    u16 species = SPECIES_BLISSEY;
    //u16 species = pokemon_getattr(&party_opponent[0], REQUEST_SPECIES, NULL);
    u16 move_1 = MOVE_EMBER;
    u16 move_2 = MOVE_EMBER;
    u16 move_3 = MOVE_EMBER;
    u16 move_4 = MOVE_EMBER;
    u8 level = 47;

    pokemon_setattr(&party_opponent[0], REQUEST_SPECIES, &species);
    pokemon_setattr(&party_opponent[0], REQUEST_NICK, &pokemon_names[species]);
    u32 species_exp_index = (pokemon_base_stats[species].exp_growth * 0x194);
    u32 *exp_needed = (u32*) (0x8253AE4 + (species_exp_index + (level * 4)));
    pokemon_setattr(&party_opponent[0], REQUEST_EXP_POINTS, exp_needed);
    recalculate_stats(&party_opponent[0]);
    pokemon_setattr(&party_opponent[0], REQUEST_MOVE1, &move_1);
    pokemon_setattr(&party_opponent[0], REQUEST_MOVE2, &move_2);
    pokemon_setattr(&party_opponent[0], REQUEST_MOVE3, &move_3);
    pokemon_setattr(&party_opponent[0], REQUEST_MOVE4, &move_4);
    pokemon_setattr(&party_opponent[0], REQUEST_PP1, &moves[move_1].pp);
    pokemon_setattr(&party_opponent[0], REQUEST_PP2, &moves[move_2].pp);
    pokemon_setattr(&party_opponent[0], REQUEST_PP3, &moves[move_3].pp);
    pokemon_setattr(&party_opponent[0], REQUEST_PP4, &moves[move_4].pp);
}


void test_battle_data()
{
  set_player_battle_components();
  set_opponent_battle_components();
}
