#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/pkmn_bank_stats.h"
#include "battle_data/battle_state.h"

void set_player_battle_components()
{
    /* Change these variables to change what the player's first pokemon has */
    u16 species = SPECIES_CHARMANDER;
    //u16 species = pokemon_getattr(&party_player[0], REQUEST_SPECIES, NULL);
    u16 move_1 = MOVE_SUBMISSION;
    u16 move_2 = MOVE_STUN_SPORE;
    u16 move_3 = MOVE_SLEEP_POWDER;
    u16 move_4 = MOVE_POISON_POWDER;

    pokemon_setattr(&party_player[0], REQUEST_SPECIES, &species);
    pokemon_setattr(&party_player[0], REQUEST_NICK, &pokemon_names[species]);
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
    u16 species = SPECIES_SLOWBRO;
    //u16 species = pokemon_getattr(&party_opponent[0], REQUEST_SPECIES, NULL);
    u16 move_1 = MOVE_GROWL;
    u16 move_2 = MOVE_ASSIST;
    u16 move_3 = MOVE_EMBER;
    u16 move_4 = MOVE_GROWL;

    pokemon_setattr(&party_opponent[0], REQUEST_SPECIES, &species);
    pokemon_setattr(&party_opponent[0], REQUEST_NICK, &pokemon_names[species]);
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
