#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/pkmn_bank_stats.h"
#include "battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
void set_player_battle_components()
{
    /* Change these variables to change what the player's first pokemon has */
    u16 species = SPECIES_CHARIZARD;
    //u16 species = pokemon_getattr(&party_player[0], REQUEST_SPECIES, NULL);
    u16 move_1 = MOVE_MAGIC_COAT;
    u16 move_2 = MOVE_TOXIC;
    u16 move_3 = MOVE_THUNDER_SHOCK;
    u16 move_4 = MOVE_THUNDERBOLT;

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
    dprintf("%d is size\n", sizeof(battle_master->anon_cbs));
}

void set_opponent_battle_components()
{
    /* Change these variables to change what the player's first pokemon has */
    u16 species = SPECIES_BULBASAUR;
    //u16 species = pokemon_getattr(&party_opponent[0], REQUEST_SPECIES, NULL);
    u16 move_1 = MOVE_EMBER;
    u16 move_2 = MOVE_TAIL_GLOW;
    u16 move_3 = MOVE_HOWL;
    u16 move_4 = MOVE_IRON_DEFENSE;

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
