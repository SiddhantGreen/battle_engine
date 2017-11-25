#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "battle_pick_message.h"

extern void dprintf(const char * str, ...);
extern void buffer_write_pkmn_nick(pchar* buff, u8 bank);
extern void buffer_write_move_name(pchar* buff, u16 move_id);

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
    u8 side = SIDE_OF(user_bank);
    remo_reset_acknowledgement_flags();
    if (battle_type_flags == BATTLE_FLAG_WILD) {
        switch (id) {
            case STRING_FAILED_ALONE:
            case STRING_DELTA_STREAM:
            case STRING_DESOLATE_LAND:
            case STRING_PRIMORDIAL_SEA:
            case STRING_ATTACK_AVOIDED:
            case STRING_ATTACK_MISSED:
            case STRING_FLEE_FAILED:
            case STRING_MOVE_CRIT:
            case STRING_MOVE_NVE:
            case STRING_MOVE_SE:
            case STRING_LEVEL_UP:
            case STRING_WEATHER_GONE:
            case STRING_OHKO:
                fdecoder_battle(battle_strings[id], 0, 0, 0);
                break;
            case STRING_RECOIL:
            case STRING_DRAIN:
                fdecoder_battle(battle_strings[id], user_bank, 0, 0);
                break;
            case STRING_EXP_GAIN:
            case STRING_MULTI_HIT:
                fmt_int_10(fcode_buffer2, move_effect_id, 0, 8);
                fdecoder_battle(battle_strings[id], user_bank, 0, 0);
                break;
            case STRING_ATTACK_USED:
            case STRING_INFATUATED:
            case STRING_BIDE_CHARGE:
            case STRING_LOST_FOCUS:
            case STRING_CANT_USE:
            case STRING_DISABLED:
            case STRING_FAILED:
            case STRING_CURSE_RESIDUAL:
            case STRING_MAGNITUDE_AMOUNT:
            case STRING_NO_TARGET:
            case STRING_IMMUNE_ABILITY:
            case STRING_RAZORWIND:
            case STRING_SOLARBEAM:
            case STRING_FREEZE_SHOCK:
            case STRING_ICE_BURN:
            case STRING_GOEMANCY:
            case STRING_SKULL_BASH:
            case STRING_RAINING:
            case STRING_GAINED_SPEED:
            case STRING_STATUS_CURED:
            case STRING_EFFECT_ENDED:
            case STRING_GAINED_TYPE:
            case STRING_CONFUSION_ENDED:
            case STRING_DRAGGED_OUT_FAILED:
            case STRING_INTIMIDATE:
            case STRING_STAT_MOD_HARSH_DROP:
            case STRING_STAT_MOD_DROP:
            case STRING_STAT_MOD_HARSH_RISE:
            case STRING_STAT_MOD_RISE:
            case STRING_AILMENT_APPLIED:
            case STRING_AILMENT_IMMUNE:
            case STRING_AILMENT_CURED:
            case STRING_PROTEAN:
            case STRING_ABILITY_CHANGE:
            case STRING_FLEE:
            case STRING_MOVE_IMMUNE:
            case STRING_FAINTED:
            case STRING_HEAL:
            case STRING_FLINCHED:
            case STRING_CHARGE_SKY_ATTACK:
            case STRING_CHARGE_FLY:
            case STRING_CHARGE_PHANTOM_FORCE:
            case STRING_CHARGE_SHADOW_FORCE:
            case STRING_CHARGE_BOUNCE:
            case STRING_CHARGE_SKY_DROP:
            case STRING_CHARGE_SOLAR_BLADE:
            case STRING_INVULNERABLE:
            case STRING_RESIDUAL_DMG:
            case STRING_STAT_MOD_CANT_GO_LOWER:
            case STRING_STAT_MOD_CANT_GO_HIGHER:
            case STRING_STAT_MOD_SEVERELY_FELL:
            case STRING_STAT_MOD_ROSE_DRASTICALLY:
			case STRING_FAST_ASLEEP:
			case STRING_WOKE_UP:
			case STRING_SNAPPED_OUT:
			case STRING_CONFUSION_HURT:
			case STRING_IS_CONFUSED:
			case STRING_FROZEN_SOLID:
			case STRING_FREEZE_THAWED:
			case STRING_FULL_PARA:
      case STRING_CLEAR_SMOG:
                fdecoder_battle(battle_strings[id + side], user_bank, move_id, move_effect_id);
                break;
            case STRING_RESIDUAL_STATUS_DMG:
			case STRING_NO_PP:
			case STRING_DISABLED_PICKED:
                fdecoder_battle(battle_strings[id], user_bank, move_id, move_effect_id);
                break;
            default:
                break;
        };
    }
}
