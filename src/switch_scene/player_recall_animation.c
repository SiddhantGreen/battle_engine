#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "battle_events/battle_events.h"
#include "../battle_slide_in_data/battle_obj_sliding.h"

extern void update_pbank(u8 bank, struct update_flags* flags);
extern void buffer_write_pkmn_nick(pchar* buff, u8 bank);
extern void make_spinning_pokeball(s16 x, s16 y, u8 bank);
extern void set_active_movement(u8 tid);
extern void player_hpbar_slidin_slow(u8 t_id);
extern u8 spawn_hpbox_player(u16 tag, s16 x, s16 y, u8 bank);

static const struct RotscaleFrame shrink[] = {
    {-20, -20, 0, 10, 0},
    {0x7FFF, 0, 0, 0, 0},
};

static const struct RotscaleFrame* shrink_ptr[] = {shrink};

void pkmn_recall_cb(struct Object* obj)
{
    if (obj->priv[0] < 10) {
        obj->pos1.y += 10;
    } else {
        p_bank[CURRENT_ACTION->action_bank]->objid = 0x3F;
        obj_free(obj);
        for (u8 j = 0; j < 4; j++) {
            if (p_bank[CURRENT_ACTION->action_bank]->objid_hpbox[j] < 0x3F) {
                u8 objid = p_bank[CURRENT_ACTION->action_bank]->objid_hpbox[j];
                p_bank[CURRENT_ACTION->action_bank]->objid_hpbox[j] = 0x3F;
                obj_free(&objects[objid]);
            }
        }
        spawn_hpbox_player(HPBOX_TAG_PLAYER_SINGLE, HPBOX_PLAYER_SINGLE_X, HPBOX_PLAYER_SINGLE_Y, CURRENT_ACTION->action_bank);
        objects[p_bank[PLAYER_SINGLES_BANK]->objid_hpbox[0]].pos1.x += 128;
        objects[p_bank[PLAYER_SINGLES_BANK]->objid_hpbox[1]].pos1.x += 128;
        objects[p_bank[PLAYER_SINGLES_BANK]->objid_hpbox[2]].pos1.x += 128;
    }
    obj->priv[0]++;
}

void pkmn_recall_animation()
{
    switch (super.multi_purpose_state_tracker) {
        case 0:
            {
                u8 bank = CURRENT_ACTION->action_bank;
                u8 objid = p_bank[bank]->objid;
                objects[objid].rotscale_table = shrink_ptr;
                objects[objid].priv[0] = 0;
                objects[objid].callback = pkmn_recall_cb;
                OBJID_SHOW_AFFINE(objid);
                rotscale_reset();
                // fade only this OAM's palette to pink
                u8 pal_slot = objects[objid].final_oam.palette_num;
                u32 pal_fade = ((1 << (pal_slot + 16)));
                fade_screen(pal_fade , 2, 0x10, 0x0, 0x7ADF);
                super.multi_purpose_state_tracker++;
                break;
            }
        case 1:
            {
                if (pal_fade_control.active) return;
                task_del(task_find_id_by_functpr(set_active_movement));
                struct update_flags* flags = (struct update_flags*)malloc_and_clear(sizeof(struct update_flags));
                flags->pass_status = true;
                flags->pass_stats = false;
                flags->pass_atk_history = false;
                flags->pass_disables = false;
                update_pbank(CURRENT_ACTION->action_bank, flags);
                free(flags);
                super.multi_purpose_state_tracker++;
                break;
            }
        case 2:
            {
                pchar text[] = _("Go! {STR_VAR_2}!");
                buffer_write_pkmn_nick(fcode_buffer3, CURRENT_ACTION->action_bank);
                fdecoder(string_buffer, text);
                battle_show_message((u8*)string_buffer, 0x18);
                bs_anim_status = 0;
                super.multi_purpose_state_tracker++;
                break;
            }
       case 3:
            if (!dialogid_was_acknowledged(0x18 & 0x3F)) {
                task_add(player_hpbar_slidin_slow, 1);
                bs_anim_status = 1;
                make_spinning_pokeball(53, 64, CURRENT_ACTION->action_bank);
                super.multi_purpose_state_tracker++;
            }
            break;
        case 4:
            break;
    };
}
