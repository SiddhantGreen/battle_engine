#include <pokeagb/pokeagb.h>
#include "../moves/moves.h"

extern void dprintf(const char * str, ...);

struct anonymous_callback* get_anonymous_callback(u8 CB_id) {
  struct anonymous_callback* a_cb_start = NULL;
  switch (CB_id) {
    case CB_ON_BEFORE_TURN:
      a_cb_start = battle_master->anon_cbs.before_turn;
      break;
    case CB_ON_BEFORE_SWITCH:
      a_cb_start = battle_master->anon_cbs.before_switch;
      break;
    case CB_ON_BEFORE_MOVE:
      a_cb_start = battle_master->anon_cbs.before_move;
      break;
    case CB_ON_MOVE_FAIL:
      a_cb_start = battle_master->anon_cbs.on_move_fail;
      break;
    case CB_ON_MODIFY_MOVE:
      a_cb_start = battle_master->anon_cbs.on_modify_move;
      break;
    case CB_ON_TRYHIT_MOVE:
      a_cb_start = battle_master->anon_cbs.on_tryhit_move;
      break;
    case CB_ON_BASE_POWER_MOVE:
      a_cb_start = battle_master->anon_cbs.on_base_power_move;
      break;
    case CB_ON_DAMAGE_MOVE:
      a_cb_start = battle_master->anon_cbs.on_damage_move;
      break;
    case CB_ON_EFFECT:
      a_cb_start = battle_master->anon_cbs.on_effect_cb;
      break;
    case CB_ON_AFTER_MOVE:
      a_cb_start = battle_master->anon_cbs.on_after_move;
      break;
  };
  return a_cb_start;
}

// set anon callback for
bool add_anon_cb(u8 CB_id, s8 priority, u8 delay, u8 dur, u8 src, u32 func)
{
  struct anonymous_callback* a_cb_start = get_anonymous_callback(CB_id);
  if (a_cb_start) {
    for (u8 i = 0; i < 4; i++) {
      if (!a_cb_start[i].in_use) {
        a_cb_start[i].priority = priority;
        a_cb_start[i].delay_before_effect = delay;
        a_cb_start[i].duration = dur;
        a_cb_start[i].source_bank = src;
        a_cb_start[i].func = func;
        a_cb_start[i].in_use = true;
        return true;
      }
    }
    return false; // full
  } else {
    return false; // invalid CB_id
  }
}


u8 exec_anonymous_callback(u8 CB_id, u8 attacker, u8 defender, u16 move)
{
  struct anonymous_callback* a_cb_start = get_anonymous_callback(CB_id);
  if (!a_cb_start->in_use) {
    return false; // invalid CB id
  }
  // sort by priority
  for (u8 i = 0; i < 4; i++) {
    if (!a_cb_start[i].in_use)
      break;
    for (u8 j = i + 1; j < 4; j++) {
      if (!a_cb_start[j].in_use)
        break;
      if (a_cb_start[i].priority > a_cb_start[j].priority) {
        struct anonymous_callback temp = a_cb_start[i];
        a_cb_start[i] = a_cb_start[j];
        a_cb_start[j] = temp;
      }
    }
  }
  // execute in order
  for (u8 i = 0; i < 4; i++) {
    if (!a_cb_start[i].in_use)
      return false;
    AnonymousCallback func = (AnonymousCallback)a_cb_start[i].func;
    if (a_cb_start[i].delay_before_effect < 1) {
      if (a_cb_start[i].duration == 0) {
        a_cb_start[i].in_use = false;
      } else {
        a_cb_start[i].duration--;
      }
    } else {
      a_cb_start[i].delay_before_effect--;
    }
    return func(attacker, a_cb_start[i].source_bank, move);
  }
  return false;
}
