#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_state.h"
#include "moves/moves.h"
#include "../abilities/battle_abilities.h"

typedef u16 (*StatCallback)(u8, u16);

struct b_item {
    StatCallback on_priority;
    StatCallback on_attack;
    StatCallback on_defense;
    StatCallback on_speed;
    StatCallback on_sp_attack;
    StatCallback on_sp_defense;
    StatCallback on_accuracy;
    StatCallback on_evasion;
    StatCallback on_critchance;
};

struct b_item empty_item = {
};

#define ITEMS_MAX 1
struct b_item* b_items_table[1] = {
    &empty_item,
};

void update_moves(u8 bank, u16 move_id)
{
    if (p_bank[bank]->b_data.last_move) {
        p_bank[bank]->b_data.last_move = p_bank[bank]->b_data.current_move;
        p_bank[bank]->b_data.current_move = move_id;
        return;
    }
    p_bank[bank]->b_data.current_move = move_id;
    return;
}
 

/* 
 * Ability stat modifier callback execution
 */
s8 ability_priority_mod(u8 bank, u16 move_id) {
    if (p_bank[bank]->b_data.ability > ABILITIES_MAX)
        return 0;
    if (abilities_table[p_bank[bank]->b_data.ability]->on_priority) {
        return abilities_table[p_bank[bank]->b_data.ability]->on_priority(bank, move_id);
    }
    return 0;
}

s8 ability_attack_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.ability > ABILITIES_MAX)
        return 0;
    if (abilities_table[p_bank[bank]->b_data.ability]->on_attack) {
        return abilities_table[p_bank[bank]->b_data.ability]->on_attack(bank, stat);
    }
    return 0;
}

s8 ability_defense_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.ability > ABILITIES_MAX)
        return 0;
    if (abilities_table[p_bank[bank]->b_data.ability]->on_defense) {
        return abilities_table[p_bank[bank]->b_data.ability]->on_defense(bank, stat);
    }
    return 0;
}

s8 ability_speed_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.ability > ABILITIES_MAX)
        return 0;
    if (abilities_table[p_bank[bank]->b_data.ability]->on_speed) {
        return abilities_table[p_bank[bank]->b_data.ability]->on_speed(bank, stat);
    }
    return 0;
}

s8 ability_sp_defense_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.ability > ABILITIES_MAX)
        return 0;
    if (abilities_table[p_bank[bank]->b_data.ability]->on_sp_defense) {
        return abilities_table[p_bank[bank]->b_data.ability]->on_sp_defense(bank, stat);
    }
    return 0;
}

s8 ability_sp_attack_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.ability > ABILITIES_MAX)
        return 0;
    if (abilities_table[p_bank[bank]->b_data.ability]->on_sp_attack) {
        return abilities_table[p_bank[bank]->b_data.ability]->on_sp_attack(bank, stat);
    }
    return 0;
}

s8 ability_critchance_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.ability > ABILITIES_MAX)
        return 0;
    if (abilities_table[p_bank[bank]->b_data.ability]->on_critchance) {
        return abilities_table[p_bank[bank]->b_data.ability]->on_critchance(bank, stat);
    }
    return 0;
}

s8 ability_accuracy_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.ability > ABILITIES_MAX)
        return 0;
    if (abilities_table[p_bank[bank]->b_data.ability]->on_accuracy) {
        return abilities_table[p_bank[bank]->b_data.ability]->on_evasion(bank, stat);
    }
    return 0;
}

s8 ability_evasion_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.ability > ABILITIES_MAX)
        return 0;
    if (abilities_table[p_bank[bank]->b_data.ability]->on_evasion) {
        return abilities_table[p_bank[bank]->b_data.ability]->on_evasion(bank, stat);
    }
    return 0;
}

/* 
 * item stat modifier callback execution
 */

s8 item_attack_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.item > ABILITIES_MAX)
        return 0;
    if (b_items_table[p_bank[bank]->b_data.item]->on_attack) {
        return b_items_table[p_bank[bank]->b_data.item]->on_attack(bank, stat);
    }
    return 0;
}

s8 item_defense_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.item > ABILITIES_MAX)
        return 0;
    if (b_items_table[p_bank[bank]->b_data.item]->on_defense) {
        return b_items_table[p_bank[bank]->b_data.item]->on_defense(bank, stat);
    }
    return 0;
}

s8 item_speed_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.item > ABILITIES_MAX)
        return 0;
    if (b_items_table[p_bank[bank]->b_data.item]->on_speed) {
        return b_items_table[p_bank[bank]->b_data.item]->on_speed(bank, stat);
    }
    return 0;
}

s8 item_sp_defense_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.item > ABILITIES_MAX)
        return 0;
    if (b_items_table[p_bank[bank]->b_data.item]->on_sp_defense) {
        return b_items_table[p_bank[bank]->b_data.item]->on_sp_defense(bank, stat);
    }
    return 0;
}

s8 item_sp_attack_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.item > ABILITIES_MAX)
        return 0;
    if (b_items_table[p_bank[bank]->b_data.item]->on_sp_attack) {
        return b_items_table[p_bank[bank]->b_data.item]->on_sp_attack(bank, stat);
    }
    return 0;
}

s8 item_critchance_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.item > ABILITIES_MAX)
        return 0;
    if (b_items_table[p_bank[bank]->b_data.item]->on_critchance) {
        return b_items_table[p_bank[bank]->b_data.item]->on_critchance(bank, stat);
    }
    return 0;
}

s8 item_accuracy_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.item > ABILITIES_MAX)
        return 0;
    if (b_items_table[p_bank[bank]->b_data.item]->on_accuracy) {
        return b_items_table[p_bank[bank]->b_data.item]->on_accuracy(bank, stat);
    }
    return 0;
}

s8 item_evasion_mod(u8 bank, u16 stat) {
    if (p_bank[bank]->b_data.item > ABILITIES_MAX)
        return 0;
    if (b_items_table[p_bank[bank]->b_data.item]->on_evasion) {
        return b_items_table[p_bank[bank]->b_data.item]->on_evasion(bank, stat);
    }
    return 0;
}
/*
 * Returns the stat after stage modifications have been done. Id represents which stat has been modified
 * 0 - atk; 1 - def; 2 - speed; 3 - spatk; 4 - spdef; 5 - accuracy; 6 - evasion; 7 - Crit chance
 */
u16 stage_modify_stat(u16 stat, s8 mod, u8 id, u8 bank)
{
    u16 stat_total;
    
    /* atk, def, spd, spa, spdef */
    if (id < 5) {
        if (mod < 0) {
                stat_total = ((stat * (200 / (ABS(mod) + 2))) / 100);
            } else {
                stat_total = ((stat * ((200 + (100 * mod)) / 2)) / 100);
            }
    } else if (id < 7) {
        /* Accuracy and Evasion */
        if (mod < 0) {
            stat_total = 300 / (ABS(mod) + 3);
        } else {
            stat_total = (300 + (100 * mod)) / 3;
        }
    } else {
        /* crit chance */
        switch (mod) {
            case 0:
                stat_total = 625;
            case 1:
                stat_total = 1250;
            case 2:
                stat_total = 5000;
            default:
                stat_total = 10000;
            };
    }
    
    
    // apply modifiers to stat via callback. Example: Ability Huge Power
    switch (id) {
        case 0:
            stat_total = ability_attack_mod(bank, stat_total);
            stat_total = item_attack_mod(bank, stat_total);
            break;
        case 1:
            stat_total = ability_defense_mod(bank, stat_total);
            stat_total = item_defense_mod(bank, stat_total);
            break;
        case 2:
            stat_total = ability_speed_mod(bank, stat_total);
            stat_total = item_speed_mod(bank, stat_total);
            break;
        case 3:
            stat_total = ability_sp_attack_mod(bank, stat_total);
            stat_total = item_sp_attack_mod(bank, stat_total);
            break;
        case 4:
            stat_total = ability_sp_defense_mod(bank, stat_total);
            stat_total = item_sp_defense_mod(bank, stat_total);
            break;
        case 5:
            stat_total = ability_accuracy_mod(bank, stat_total);
            stat_total = item_accuracy_mod(bank, stat_total);
            break;
        case 6:
            stat_total = ability_evasion_mod(bank, stat_total);
            stat_total = item_evasion_mod(bank, stat_total);
            break;
        case 7:
            stat_total = ability_critchance_mod(bank, stat_total);
            stat_total = item_critchance_mod(bank, stat_total);
            break;
    };
    
    return stat;
}



















