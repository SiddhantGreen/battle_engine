#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../battle_events/battle_events.h"

extern void dprintf(const char * str, ...);
extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern u8 count_usable_pokemon(u8 side);
extern void forced_switch(u8 bank, u8 switch_method);
extern void stat_boost(u8 bank, u8 stat_id, s8 amount);

// Pursuit
void pursuit_on_basepower(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (p_bank[TARGET_OF(user)]->b_data.is_switching) {
        B_MOVE_POWER(user) *= 2; // double base power on switch
    }
}

void pursuit_on_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    for (u8 i = 0; i < 4; i++) {
        if ((SIDE_OF(i) != SIDE_OF(user)) && ((p_bank[i]->b_data.is_switching))) {
            B_MOVE_PRIORITY(user) = 7;
            TARGET_OF(user) = i;
            return;
        }
    }
}


bool forced_switch_effect_move(u8 target, u8 user)
{
    // fail if trapped
    if (HAS_VOLATILE(target, VOLATILE_TRAPPED) || HAS_VOLATILE(target, VOLATILE_INGRAIN) || B_IS_TRAPPED(target))
        return true;
    // continue faint event if this pokemon fainted, don't do switch logic.
    if (B_IS_FAINTED(target)) return true;
    // end the battle in wild battles if used against wild mon
    switch (battle_type_flag) {
        case BATTLE_MODE_WILD:
            // player
            if (SIDE_OF(target) == PLAYER_SIDE) {
                // if user's level is less than target's level, don't switch
                if (B_LEVEL(user) < B_LEVEL(target)) return true;
                // exit battle if selected mon is only one for player
                if (count_usable_pokemon(PLAYER_SIDE) < 2) {
                    prepend_action(target, target, ActionHighPriority, EventEndBattle);
                    end_action(CURRENT_ACTION);
                } else {
                    struct action* a = next_action(target, target, ActionSwitch, EventForcedSwitch);
                    a->priv[0] = 0;
                }
            } else {
                // opponent wild, end battle
                prepend_action(target, target, ActionHighPriority, EventEndBattle);
                end_action(CURRENT_ACTION);
            }
            break;
        case BATTLE_MODE_WILD_DOUBLE:
        case BATTLE_MODE_TRAINER:
        case BATTLE_MODE_TRAINER_DOUBLE:
        case BATTLE_MODE_PARTNER:
        default:
            dprintf("FAILED to select a valid battle mode.\n");
            break;
    };
    return true;
}


// Dragon Tail, Circle throw, Whirlwind
u8 dragon_tail_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 target = TARGET_OF(user);
    return forced_switch_effect_move(target, user);
}


// Volt switch, U-turn
u8 volt_switch_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // player
    if (user == PLAYER_SIDE) {
        // no switch effect if cannot switch into something
        if (count_usable_pokemon(PLAYER_SIDE) < 2) return true;
        struct action* a = next_action(user, user, ActionSwitch, EventForcedSwitch);
        a->priv[0] = 1;
    } else {
        if (count_usable_pokemon(OPPONENT_SIDE) < 2) return true;
        // TODO: Opponent switching(?)
    }
    return true;
}


// Parting shot
u8 parting_shot_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // stat drop on foe
    stat_boost(TARGET_OF(user), ATTACK_MOD, -1);
    stat_boost(TARGET_OF(user), SPATTACK_MOD, -1);
    // player
    if (user == PLAYER_SIDE) {
        // no switch effect if cannot switch into something
        struct action* a = next_action(user, user, ActionSwitch, EventForcedSwitch);
        a->priv[0] = 1;
    } else {
        if (count_usable_pokemon(OPPONENT_SIDE) < 2) return true;
        // TODO: Opponent switching(?)
    }
    return true;
}


// Momento
u8 memento_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // stat drop on foe
    for (u8 i = 0; i < BANK_MAX; i++) {
        if ((i == user) && (ACTIVE_BANK(i))) continue;
        stat_boost(i, ATTACK_MOD, -2);
        stat_boost(i, SPATTACK_MOD, -2);
    }
    B_FAINTED(user) = true;
    return true;
}
