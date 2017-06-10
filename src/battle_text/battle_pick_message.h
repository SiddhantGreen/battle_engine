#ifndef BATTLE_PICK_MESSAGES_H_
#define BATTLE_PICK_MESSAGES_H_

#include <pokeagb/pokeagb.h>

enum battle_string_ids {
    STRING_ATTACK_USED, // 0 -2
    STRING_INFATUATED = 2,
    STRING_BIDE_CHARGE = 4,
    STRING_LOST_FOCUS = 6,
    STRING_CANT_USE = 8,
    STRING_DISABLED = 10,
    STRING_FAILED = 12,
    STRING_CURSE_RESIDUAL = 14,
    STRING_MAGNITUDE_AMOUNT = 16,
    STRING_NO_TARGET = 18,
    STRING_FAILED_ALONE = 20,
    STRING_IMMUNE_ABILITY = 21,
    STRING_RAZORWIND = 23,
    STRING_SOLARBEAM = 25,
    STRING_FREEZE_SHOCK = 27,
    STRING_ICE_BURN = 29,
    STRING_GOEMANCY = 31,
};

static const pchar str_atk_used_p[] = _("{ATTACKING_MON} used\n{ATTACK_NAME}!");
static const pchar str_atk_used_o[] = _("Foe {ATTACKING_MON} used\n{ATTACK_NAME}!");
static const pchar str_infatuated_p[] = _("{ATTACKING_MON} is in love\nwith Foe {DEFENDING_MON}\p{ATTACKING_MON}\nis immobolized by love!");
static const pchar str_infatuated_o[] = _("The opposing {ATTACKING_MON} is in love\nwith {DEFENDING_MON}\pThe opposing {ATTACKING_MON}\nis immobolized by love!");
static const pchar str_bide_p[] = _("{ATTACKING_MON} is charging up\n{ATTACK_NAME}!");
static const pchar str_bide_o[] = _("Foe {ATTACKING_MON} is charging up\n{ATTACK_NAME}!");
static const pchar str_focus_lost_p[] = _("{ATTACKING_MON} lost its\nfocus and couldn’t move!");
static const pchar str_focus_lost_o[] = _("Foe {ATTACKING_MON} lost its\nfocus and couldn’t move!");
static const pchar str_cant_use_p[] = _("{ATTACKING_MON} can’t use\n{ATTACK_NAME} because of {EFFECT_NAME}!");
static const pchar str_cant_use_o[] = _("Foe {ATTACKING_MON} can’t use\n{ATTACK_NAME} because of {EFFECT_NAME}!");
static const pchar str_disabled_p[] = _("{ATTACKING_MON}’s {ATTACK_NAME}\nwas disabled!");
static const pchar str_disabled_o[] = _("Foe {ATTACKING_MON}’s {ATTACK_NAME}\nwas disabled!");
static const pchar str_failed_p[] = _("{ATTACKING_MON} used {ATTACK_NAME}\nBut it failed!");
static const pchar str_failed_o[] = _("Foe {ATTACKING_MON} used {ATTACK_NAME}\nBut it failed");
static const pchar str_curse_dmg_p[] = _("Foe {ATTACKING_MON} is afflicted\nby {ATTACK_NAME}");
static const pchar str_curse_dmg_o[] = _("{ATTACKING_MON} is afflicted\nby {ATTACK_NAME}");
static const pchar str_magnitude_amount_p[] = _("MAGNITUDE {EFFECT_NAME}!");
static const pchar str_magnitude_amount_o[] = _("MAGNITUDE {EFFECT_NAME}!");
static const pchar str_no_target_p[] = _("But there was no target!");
static const pchar str_no_target_o[] = _("But there was no target!");
static const pchar str_failed_alone[] = _("But it failed!");
static const pchar str_immunity_p[] = _("Foe {DEFENDING_MON}’s {ABILITY_NAME_OPPONENT}\nmade it immune!");
static const pchar str_immunity_o[] = _("{DEFENDING_MON}’s {ABILITY_NAME_PLAYER}\nmade it immune!");
static const pchar str_charging_up_razorwind_p[] = _("{ATTACKING_MON} whipped\nup a whirlwind!"); 
static const pchar str_charging_up_razorwind_o[] = _("Foe {DEFENDING_MON} whipped\nup a whirlwind!"); 
static const pchar str_solarbeam_p[] = _("{ATTACKING_MON} absorbed\nlight!");
static const pchar str_solarbeam_o[] = _("Foe {DEFENDING_MON} absorbed\nlight!");
static const pchar str_freeze_shock_p[] = _("{ATTACKING_MON} became cloaked\nin a freezing light!");
static const pchar str_freeze_shock_o[] = _("Foe {DEFENDING_MON} became cloaked\nin a freezing light!");
static const pchar str_ice_burn_p[] = _("{ATTACKING_MON} is radiating\na blazing aura!");
static const pchar str_ice_burn_o[] = _("Foe {DEFENDING_MON} is radiating\na blazing aura!");
static const pchar str_geomancy_p[] = _("{ATTACKING_MON} is absorbing\npower!");
static const pchar str_geomancy_o[] = _("Foe {DEFENDING_MON} is absorbing\npower!");

static const pchar* battle_strings[33] = {
   (pchar*)&str_atk_used_p, (pchar*)&str_atk_used_o,
   (pchar*)&str_infatuated_p, (pchar*)&str_infatuated_o,
   (pchar*)&str_bide_p, (pchar*)&str_bide_o,
   (pchar*)&str_focus_lost_p, (pchar*)&str_focus_lost_o,
   (pchar*)&str_cant_use_p, (pchar*)&str_cant_use_p,
   (pchar*)&str_disabled_p, (pchar*)&str_disabled_p,
   (pchar*)&str_failed_p, (pchar*)&str_failed_p,
   (pchar*)&str_curse_dmg_p, (pchar*)&str_curse_dmg_o,
   (pchar*)&str_magnitude_amount_p, (pchar*)str_magnitude_amount_o,
   (pchar*)&str_no_target_p, (pchar*)&str_no_target_o,
   (pchar*)&str_failed_alone, (pchar*)&str_immunity_p,
   (pchar*)&str_immunity_o, (pchar*)&str_charging_up_razorwind_p,
   (pchar*)&str_charging_up_razorwind_o, (pchar*)&str_solarbeam_p,
   (pchar*)&str_solarbeam_o, (pchar*)&str_freeze_shock_p,
   (pchar*)&str_freeze_shock_o, (pchar*)&str_ice_burn_p, // 30
   (pchar*)&str_ice_burn_o, (pchar*)&str_geomancy_p,
   (pchar*)&str_geomancy_o,
};


#endif /* BATTLE_PICK_MESSAGES_H_ */
