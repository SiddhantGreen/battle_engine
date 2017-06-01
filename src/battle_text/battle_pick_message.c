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

static const pchar battle_strings[2][50] = {
    _"{STR_VAR_1} used\n{STR_VAR_2}!",
    _"Foe {STR_VAR_1} used\n{STR_VAR_2}!",
};

void pick_battle_message(u16 move_id, u8 user_bank, enum BattleFlag battle_type, enum battle_string_ids id)
{

    if (battle_type == BATTLE_FLAG_WILD) {
        switch (id) {
            case STRING_ATTACK_USED:
                buffer_write_pkmn_nick(fcode_buffer2, user_bank);
                buffer_write_move_name(fcode_buffer3, move_id);
                fdecoder(string_buffer, battle_strings[id + get_side(user_bank)]);
                break;
        };
    }
   
}
