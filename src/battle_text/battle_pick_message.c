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
            pchar text[] = _"A wild {STR_VAR_1} appeared!\pGo! {STR_VAR_2}!";
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

static const pchar battle_strings[14][80] = {
    // Attack used string
    _"{STR_VAR_1} used\n{STR_VAR_2}!",
    _"Foe {STR_VAR_1} used\n{STR_VAR_2}!",

    // Infatuated by love string
    _"{STR_VAR_1} is in love\nwith Foe {STR_VAR_2}\p{STR_VAR_1}\nis immobolized by love!",
    _"The opposing {STR_VAR_1} is in love\nwith {STR_VAR_2}\pThe opposing {STR_VAR_1}\nis immobolized by love!",

    // Charging up bide string
    _"{STR_VAR_1} is charging up\n{STR_VAR_2}!",
    _"Foe {STR_VAR_1} is charging up\n{STR_VAR_2}!",

    // lost focus string
    _"{STR_VAR_1} lost its\nfocus and couldn’t move!",
    _"Foe {STR_VAR_1} lost its\nfocus and couldn’t more!",

    // cant use string
    _"{STR_VAR_1} can’t use\n{STR_VAR_2} because of {STR_VAR_3}!",
    _"Foe {STR_VAR_1} can’t use\n{STR_VAR_2} because of {STR_VAR_3}!",

    // disabled string
    _"{STR_VAR_1}’s {STR_VAR_2}\nwas disabled!",
    _"Foe {STR_VAR_1}’s {STR_VAR_2}\nwas disabled!",

    // failed string
    _"{STR_VAR_1} used {STR_VAR_2}\nBut it failed!",
    _"Foe {STR_VAR_1} used {STR_VAR_2}\nBut it failed"

};

void pick_battle_message(u16 move_id, u8 user_bank, enum BattleFlag battle_type, enum battle_string_ids id, u16 move_effect_id)
{
    if (battle_type == BATTLE_FLAG_WILD) {
        switch (id) {
            case STRING_ATTACK_USED:
                buffer_write_pkmn_nick(fcode_buffer2, user_bank);
                buffer_write_move_name(fcode_buffer3, move_id);
                fdecoder(string_buffer, battle_strings[STRING_ATTACK_USED + get_side(user_bank)]);
                break;
            case STRING_INFATUATED:
                buffer_write_pkmn_nick(fcode_buffer2, user_bank);
                buffer_write_pkmn_nick(fcode_buffer3, p_bank[user_bank]->user_action.target_bank);
                fdecoder(string_buffer, battle_strings[STRING_INFATUATED + get_side(user_bank)]);
                break;
            case STRING_BIDE_CHARGE:
                buffer_write_pkmn_nick(fcode_buffer2, user_bank);
                buffer_write_move_name(fcode_buffer3, move_id);
                fdecoder(string_buffer, battle_strings[STRING_BIDE_CHARGE + get_side(user_bank)]);
                break;
            case STRING_LOST_FOCUS:
                buffer_write_pkmn_nick(fcode_buffer2, user_bank);
                fdecoder(string_buffer, battle_strings[STRING_LOST_FOCUS + get_side(user_bank)]);
                break;
            case STRING_CANT_USE:
                buffer_write_pkmn_nick(fcode_buffer2, user_bank);
                buffer_write_move_name(fcode_buffer3, move_id);
                buffer_write_move_name(fcode_buffer4, move_effect_id);
                fdecoder(string_buffer, battle_strings[STRING_CANT_USE + get_side(user_bank)]);
                break;
            case STRING_DISABLED:
                buffer_write_pkmn_nick(fcode_buffer2, user_bank);
                buffer_write_move_name(fcode_buffer3, move_id);
                fdecoder(string_buffer, battle_strings[STRING_DISABLED + get_side(user_bank)]);
                break;
            case STRING_FAILED:
                buffer_write_pkmn_nick(fcode_buffer2, user_bank);
                buffer_write_move_name(fcode_buffer3, move_id);
                fdecoder(string_buffer, battle_strings[STRING_FAILED + get_side(user_bank)]);
                break;
            default:
                break;
        };
    }
}

