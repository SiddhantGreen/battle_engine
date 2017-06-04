#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../moves/moves.h"

void buffer_write_pkmn_nick(pchar* buffer, u8 bank)
{
    memcpy(buffer, p_bank[bank]->this_pkmn->base.nick, sizeof(p_bank[bank]->this_pkmn->base.nick));
    buffer[sizeof(p_bank[bank]->this_pkmn->base.nick)] = 0xFF;

}

void buffer_write_player_name(pchar* buffer)
{
    pstrcpy(buffer, saveblock2->name);
}

void buffer_write_move_name(pchar* buffer, u16 move_id)
{
    pstrcpy(buffer, move_t[move_id].name);
}


void fdecoder_battle(const pchar* buffer, u8 bank, u16 move_id, u16 move_effect_id)
{
    u16 len = pstrlen(buffer);
    pchar* result = (pchar*)malloc((len < 50) ? 100 : len * 2);
    u16 i, result_index;
    for (i = 0, result_index = 0; ((i < len) || (buffer[i] > 0xFE)); i++) {
        if (buffer[i] == 0xFD) {
            i++;
            switch (buffer[i]) {
                case 0xE:
                    // buffer Attacking Pokemon name
                    buffer_write_pkmn_nick(&(result[result_index]), bank);
                    result_index = pstrlen(result);
                    break;
                case 0xF:
                    // buffer move name
                    buffer_write_move_name(&(result[result_index]), move_id);
                    result_index = pstrlen(result);
                    break;
                case 0x10:
                    // buffer move effect name
                    buffer_write_move_name(&(result[result_index]), move_effect_id);
                    result_index = pstrlen(result);
                    break;
                case 0x11:
                    // buffer Defending Pokemon name 
                    buffer_write_pkmn_nick(&(result[result_index]), p_bank[bank]->user_action.target_bank);
                    result_index = pstrlen(result);
                    break;
                default:
                    break;
            };
        } else {
            result[result_index] = buffer[i];
            result_index++;
        }
    }
    fdecoder(string_buffer, result);
    free(result);
}

