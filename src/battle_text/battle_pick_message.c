#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_state.h"
#include "battle_pick_message.h"

extern void buffer_write_pkmn_nick(pchar* buff, u8 bank);
extern void buffer_write_move_name(pchar* buff, u16 move_id);
extern u8 get_side(u8 bank);

void pick_encounter_message(enum BattleFlag battle_type_flags)
{
    switch (battle_type_flags) {
        case BATTLE_FLAG_WILD:
        {
            pchar text[] = _("A wild {STR_VAR_1} appeared!\pGo! {STR_VAR_2}!");
            buffer_write_pkmn_nick(fcode_buffer3, PLAYER_SINGLES_BANK);
            buffer_write_pkmn_nick(fcode_buffer2, OPPONENT_SINGLES_BANK);
            fdecoder(string_buffer, text);
            break;
        }
        case BATTLE_FLAG_DOUBLE:
        case BATTLE_FLAG_LINK:
        case BATTLE_FLAG_TRAINER:
        case BATTLE_FLAG_OAK_TUTORIAL:
        case BATTLE_FLAG_PARTNER:
        case BATTLE_FLAG_SAFARI:
        case BATTLE_FLAG_OLD_MAN:
        case BATTLE_FLAG_ROAMING:
        case BATTLE_FLAG_GHOST:
        case BATTLE_FLAG_POKE_DUDE:
            break;
    };

}


extern void fdecoder_battle(const pchar* buffer, u8 bank, u16 move_id, u16 move_effect_id);
void pick_battle_message(u16 move_id, u8 user_bank, enum BattleFlag battle_type, enum battle_string_ids id, u16 move_effect_id)
{
    if (battle_type == BATTLE_FLAG_WILD) {
        switch (id) {
            case STRING_ATTACK_USED:
                fdecoder_battle(battle_strings[STRING_ATTACK_USED + get_side(user_bank)], user_bank, move_id, move_effect_id);
                break;
            case STRING_INFATUATED:
                fdecoder_battle(battle_strings[STRING_INFATUATED + get_side(user_bank)], user_bank, move_id, move_effect_id);
                break;
            case STRING_BIDE_CHARGE:
                fdecoder_battle(battle_strings[STRING_BIDE_CHARGE + get_side(user_bank)], user_bank, move_id, move_effect_id);
                break;
            case STRING_LOST_FOCUS:
                fdecoder_battle(battle_strings[STRING_LOST_FOCUS + get_side(user_bank)], user_bank, move_id, move_effect_id);
                break;
            case STRING_CANT_USE:
                fdecoder_battle(battle_strings[STRING_CANT_USE + get_side(user_bank)], user_bank, move_id, move_effect_id);
                break;
            case STRING_DISABLED:
                fdecoder_battle(battle_strings[STRING_DISABLED + get_side(user_bank)], user_bank, move_id, move_effect_id);
                break;
            case STRING_FAILED:
                fdecoder_battle(battle_strings[STRING_FAILED + get_side(user_bank)], user_bank, move_id, move_effect_id);
                break;
            default:
                break;
        };
    }
}

