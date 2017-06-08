#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_state.h"
#include "moves/moves.h"
#include "../battle_text/battle_pick_message.h"

extern u8 get_target_bank(u8 user_bank, u16 move_id);
extern u16 rand_range(u16 min, u16 max);
extern u8 get_ability_bank(u8);
extern void task_add_bmessage(u8 task_id);
extern bool ignoring_item(struct Pokemon* p);
extern u8 get_side(u8 bank);

u8 ally_switch_tryhit(u8 user_bank)
{
    /* TODO: Double battles not implemented yet */
    return true;
}


u8 aurora_veil_tryhit(u8 user_bank)
{
    // fails if not hailing
    if (battle_master->field_state.is_hail) {
        battle_master->field_state.aurora_veil = get_side(user_bank) + 1;
        battle_master->field_state.aurora_veil_turns[get_side(user_bank)] = 5; // TODO: Fix for extended weather rock thing
        return true;
    } else {
        return false;
    }
}

u8 protection_tryhit(u8 user_bank)
{
    // higher chance to fail on consecutive protects
    if (p_bank[user_bank]->user_action.times_protected) {
        if (!(rand_range(0, 100) < (p_bank[user_bank]->user_action.times_protected * 2))) {
            return false;
        }
    }
    p_bank[user_bank]->user_action.times_protected++;
    p_bank[user_bank]->user_action.used_protect = true;
    return true;
}

u8 brick_break_tryhit(u8 user_bank)
{
    // breaks all barriers before calcs
    u8 opp_bank = user_bank ? 0 : 2;
    if (battle_master->field_state.reflect & (get_side(opp_bank) + 1))
        battle_master->field_state.reflect &= !(get_side(opp_bank) + 1);
        
    if (battle_master->field_state.lightscreen & (get_side(opp_bank) + 1))
        battle_master->field_state.lightscreen &= !(get_side(opp_bank) + 1);
        
    if (battle_master->field_state.aurora_veil & (get_side(opp_bank) + 1))
        battle_master->field_state.aurora_veil &= !(get_side(opp_bank) + 1);

    battle_master->field_state.reflect_turns[get_side(opp_bank)] = 0;
    battle_master->field_state.lightscreen_turns[get_side(opp_bank)] = 0;
    battle_master->field_state.aurora_veil_turns[get_side(opp_bank)] = 0;
    return true;
}

u8 captivate_tryhit(u8 user_bank)
{
    // fails if foe isn't opposite gender
    u8 target_bank = p_bank[user_bank]->user_action.target_bank;
    u8 target_gender =  pokemon_get_gender(p_bank[target_bank]->this_pkmn);
    u8 player_gender = pokemon_get_gender(p_bank[user_bank]->this_pkmn);
    
    if ((target_gender == PKMN_GENDER_NONE) || (player_gender == PKMN_GENDER_NONE)) {
        return false;
    }
    
    if ( target_gender != player_gender) {
        battle_master->b_moves[battle_master->execution_index].amount_target[0]  = -2;
        battle_master->b_moves[battle_master->execution_index].stat_target[0] = STAT_SPECIAL_ATTACK;
        return true;
    }
    return false;    
}

u8 counter_tryhit(u8 user_bank)
{
    // fails if no physical damage taken
    if (p_bank[user_bank]->user_action.physical_dmg_taken && 
    (p_bank[user_bank]->user_action.buff_tag & COUNTER_TAG)) {
        return true;
    }
    return false;
}


u8 crafty_shield_tryhit(u8 user_bank)
{
    // fails if moved second
    if ((p_bank[user_bank]->user_action.crafty_shield) || (battle_master->second_bank == user_bank)) {
        return false;
    } else {
        p_bank[user_bank]->user_action.crafty_shield = 1;
        return true;
    }
}

u8 curse_tryhit(u8 user_bank)
{
    // fails if curse already applied
    u8 target_bank = p_bank[user_bank]->user_action.target_bank;
    if (p_bank[target_bank]->user_action.buff_tag & CURSE_TAG) {
        return false;
    } else {
        p_bank[target_bank]->user_action.buff_tag |= CURSE_TAG;
        return true;
    }
}

u8 dream_eater_tryhit(u8 user_bank)
{
    // fails if target isn't asleep
    u8 target_bank = p_bank[user_bank]->user_action.target_bank;
    if (pokemon_getattr(p_bank[target_bank]->this_pkmn, REQUEST_STATUS_AILMENT, NULL) & STATUS_SLEEP_TURNS) {
        return true;
    } else if (get_ability_bank(target_bank) == ABILITY_COMATOSE) {
        return 2;
    } else {
        return false;
    }
}

u8 electrify_tryhit(u8 user_bank)
{
    // fails if moves second
    if (user_bank == battle_master->second_bank) {
        return false;
    }
    return true;
}

u8 endure_tryhit(u8 user_bank)
{
   // higher chance to fail on consecutive protects
    if (p_bank[user_bank]->user_action.times_protected) {
        if (!(rand_range(0, 100) < (p_bank[user_bank]->user_action.times_protected * 2))) {
            return false;
        }
    }
    p_bank[user_bank]->user_action.times_protected++;
    p_bank[user_bank]->user_action.used_endure = true;
    return true; 
}

u8 entrainment_tryhit(u8 user_bank)
{
    u8 user_ability = get_ability_bank(user_bank);
    u8 target_ability = get_ability_bank(p_bank[user_bank]->user_action.target_bank);
    
    if(user_ability == target_ability) {
        return false;
    }
    
    switch (target_ability) {
        case ABILITY_MULTITYPE:
        case ABILITY_STANCE_CHANGE:
        case ABILITY_TRUANT:
            return false;
        default:
            break;        
    };
    
    switch (user_ability) {
        case ABILITY_FLOWER_GIFT:
        case ABILITY_FORECAST:
        case ABILITY_ILLUSION:
        case ABILITY_IMPOSTER:
        case ABILITY_MULTITYPE:
        case ABILITY_STANCE_CHANGE:
        case ABILITY_TRACE:
        case ABILITY_ZEN_MODE:
            return false;
        default:
            break;
    };
    return true;
}

u8 follow_me_tryhit(u8 user_bank)
{
    // fails if single battle
    switch (battle_type_flags) {
        case BATTLE_FLAG_WILD:
        case BATTLE_FLAG_TRAINER:
        case BATTLE_FLAG_OAK_TUTORIAL:
        case BATTLE_FLAG_SAFARI:
        case BATTLE_FLAG_OLD_MAN:
        case BATTLE_FLAG_ROAMING:
        case BATTLE_FLAG_GHOST:
        case BATTLE_FLAG_POKE_DUDE:
            return false;
            break;
        default:
            return true;
    };
}


u8 foresight_tryhit(u8 user_bank)
{
    // fails if target is already under the affect
    u8 target = p_bank[user_bank]->user_action.target_bank;
    if (p_bank[target]->user_action.foresighted) {
        return false;
    }
    p_bank[target]->user_action.removed_immunities |= (TYPE_BITS_FIGHTING | TYPE_BITS_NORMAL);
    return true;
}

u8 gastro_acid_tryhit(u8 user_bank)
{
    // fails if uncompressable ability
    u8 target_ability = get_ability_bank(p_bank[user_bank]->user_action.target_bank);
    switch (target_ability) {
        case ABILITY_COMATOSE:
        case ABILITY_MULTITYPE:
        case ABILITY_STANCE_CHANGE:
        case ABILITY_SCHOOLING:
            return false;
            break;
        default:
            break;
    };
    
    p_bank[p_bank[user_bank]->user_action.target_bank]->user_action.ability = ABILITY_NONE;
    return true;
}

u8 healing_wish_tryhit(u8 user_bank)
{
    // this is probably wrong. Need to test
    // Fails if no switch in
    struct Pokemon* poke_bank = get_side(user_bank) ? party_player : party_opponent;
    u8 i;
    for (i = 0; i < 6; i++) {
        if (poke_bank[i].current_hp && (poke_bank[i].base.pid != p_bank[user_bank]->this_pkmn->base.pid)) {
            return true;
        }
    }
    return false;
    
}


u8 kings_shielf_tryhit(u8 user_bank)
{
    // fails if user moves last
    if (user_bank == battle_master->second_bank)
        return false;
        
    // fails inaccordance to protect mechanics
    if (p_bank[user_bank]->user_action.times_protected) {
        if (!(rand_range(0, 100) < (p_bank[user_bank]->user_action.times_protected * 2))) {
            return false;
        }
    }
    p_bank[user_bank]->user_action.kings_sheild = 1;
    p_bank[user_bank]->user_action.times_protected++;
    return true;
}

u8 last_resort_tryhit(u8 user_bank)
{
    // fails if user doesn't have atleast two moves
    if (pokemon_getattr(p_bank[user_bank]->this_pkmn, REQUEST_MOVE1, NULL) != MOVE_NONE)
        return false;
    if (pokemon_getattr(p_bank[user_bank]->this_pkmn, REQUEST_MOVE2, NULL) != MOVE_NONE)
        return false;
        
    // check if all moves were used. TODO
    return true;
}

u8 leech_seed_tryhit(u8 user_bank)
{
    u8 target_bank = p_bank[user_bank]->user_action.target_bank;
    if ((p_bank[target_bank]->user_action.type[0] == TYPE_GRASS) ||
    (p_bank[target_bank]->user_action.type[1] == TYPE_GRASS)) {
        return false;
    }
    return true;
}

u8 lockon_tryhit(u8 user_bank)
{
    u8 target_bank = p_bank[user_bank]->user_action.target_bank;
    if (p_bank[target_bank]->user_action.locked_on) {
        return false;
    } else {
        return true;
    }
}

u8 lunar_dance_tryhit(u8 user_bank)
{
    // healing wish clone
    return healing_wish_tryhit(user_bank);
}

u8 magic_coat_tryhit(u8 user_bank)
{
    /* TODO */
    // fails if move already reflected, or non-reflectable, or second to move
    return true;
}

u8 mat_block_tryhit(u8 user_bank)
{
    if (p_bank[user_bank]->user_action.not_first_turn)
        return false;
    return true;
}

u8 me_first_tryhit(u8 user_bank)
{
    // fails if not moved before opponent
    if(battle_master->first_bank != user_bank)
        return false;
        
    // fails if target's move is uncopyable
    u8 target_move = battle_master->b_moves[battle_master->second_bank].move_id;
    // ability IDs max range of switch.
    if ((target_move ==  MOVE_CHATTER) ||
        (target_move ==  MOVE_COUNTER) ||
        (target_move ==  MOVE_COVET) ||
        (target_move ==  MOVE_FOCUS_PUNCH) ||
        (target_move ==  MOVE_ME_FIRST) ||
        (target_move ==  MOVE_METAL_BURST) ||
        (target_move ==  MOVE_MIRROR_COAT) ||
        (target_move ==  MOVE_STRUGGLE) ||
        (target_move ==  MOVE_THIEF)) {
            return false;
    } else {
        return true;
    }
}

u8 metal_burst_tryhit(u8 user_bank)
{
    // fails if user took no damage this turn
    if (p_bank[user_bank]->user_action.special_dmg_taken ||
    p_bank[user_bank]->user_action.physical_dmg_taken) {
        return true;
    }
    return false;
}

u8 mind_reader_tryhit(u8 user_bank)
{
    // lock on clone
    return lockon_tryhit(user_bank);
}

u8 miracle_eye_tryhit(u8 user_bank)
{
    u8 target = p_bank[user_bank]->user_action.target_bank;
    if (p_bank[target]->user_action.foresighted) {
        return false;
    } else {
        p_bank[target]->user_action.removed_immunities |= TYPE_BITS_DARK;
        return true;
    }
}


u8 mirror_coat_tryhit(u8 user_bank)
{
    // fails if no special damage taken
    if (p_bank[user_bank]->user_action.special_dmg_taken && 
    (p_bank[user_bank]->user_action.buff_tag & MIRROR_COAT_TAG)) {
        return true;
    }
    return false;
}


u8 mirror_move_tryhit(u8 user_bank)
{
    // fails if moved first, or uncopyable move
    u16 target_move = p_bank[user_bank]->user_action.move_id;
    if (user_bank == battle_master->first_bank)
        return false;
    if (*(move_t[target_move].m_flags) & FLAG_REFLECTABLE)
        return true;
    return false;
}

u8 nature_power_tryhit(u8 user_bank)
{
    u16 move_id = MOVE_NONE;
    if (battle_master->field_state.electric_terrain) {
        move_id = MOVE_THUNDERBOLT;
    } else if (battle_master->field_state.grassy_terrain) {
        move_id = MOVE_ENERGY_BALL;
    } else if (battle_master->field_state.misty_terrain) {
        move_id = MOVE_MOONBLAST;
    } else if (battle_master->field_state.psychic_terrain) {
        move_id = MOVE_PSYCHIC;
    } else {
        move_id = MOVE_TRI_ATTACK;
    }
    
    p_bank[user_bank]->user_action.move_id = move_id;
    if (user_bank == battle_master->first_bank) {
        battle_master->b_moves[0].move_id = move_id;
    } else {
        battle_master->b_moves[0].move_id = move_id;
    }
    // use new move
    super.multi_purpose_state_tracker = 2;
    return true;
}

u8 odor_sleuth_tryhit(u8 user_bank)
{
    // clone of foresight
    return foresight_tryhit(user_bank);
}

u8 psychic_fangs_tryhit(u8 user_bank)
{
    // brick break clone
    return brick_break_tryhit(user_bank);
}












