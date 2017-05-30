#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"

void buffer_write_pkmn_nick(pchar* buffer, u8 bank)
{
    memcpy(buffer, p_bank[bank]->this_pkmn->base.nick, sizeof(p_bank[bank]->this_pkmn->base.nick));
    buffer[sizeof(p_bank[bank]->this_pkmn->base.nick)] = 0xFF;

}

void buffer_write_player_name(pchar* buffer)
{
    pstrcpy(buffer, saveblock2->name);
}



