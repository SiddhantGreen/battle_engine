#include <pokeagb/pokeagb.h>
#include "../moves/moves.h"

// set anon callback for
bool add_anon_cb(u8 CB_id, s8 priority, u8 delay, u8 dur, u8 src, void* func)
{
  struct anonymous_callback* a_cb = (struct anonymous_callback*)malloc_and_clear(sizeof(struct anonymous_callback));
  struct anonymous_callback* a_cb_start;

  a_cb->priority = priority;
  a_cb->delay_before_effect = delay;
  a_cb->duration = dur;
  a_cb->source_bank = src;
  a_cb->func = func;

  switch (CB_id) {
    case CB_ON_BEFORE_TURN:
      a_cb_start = &(battle_master->anon_cbs.before_turn[0]);
      break;
    case CB_ON_BEFORE_SWITCH:
      a_cb_start = &(battle_master->anon_cbs.before_switch[0]);
      break;
    case CB_ON_BEFORE_MOVE:
      a_cb_start = &(battle_master->anon_cbs.before_move[0]);
      break;
    case CB_ON_MOVE_FAIL:
      a_cb_start = &(battle_master->anon_cbs.on_move_fail[0]);
      break;
    case CB_ON_MODIFY_MOVE:
      a_cb_start = &(battle_master->anon_cbs.on_modify_move[0]);
      break;
    case CB_ON_TRYHIT_MOVE:
      a_cb_start = &(battle_master->anon_cbs.on_tryhit_move[0]);
      break;
    case CB_ON_BASE_POWER_MOVE:
      a_cb_start = &(battle_master->anon_cbs.on_base_power_move[0]);
      break;
    case CB_ON_DAMAGE_MOVE:
      a_cb_start = &(battle_master->anon_cbs.on_damage_move[0]);
      break;
    case CB_ON_EFFECT:
      a_cb_start = &(battle_master->anon_cbs.on_effect_cb[0]);
      break;
    case CB_ON_AFTER_MOVE:
      a_cb_start = &(battle_master->anon_cbs.on_after_move[0]);
      break;
    default:
      return false;
  };

  for (u8 i = 0; i < 4; i++) {
    if (a_cb_start == NULL) {
      a_cb_start = a_cb;
      return true;
    }
    a_cb_start++;
  }
  return false;
}
