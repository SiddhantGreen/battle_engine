#include "../generated/images/battle_terrains/grass/grass_bg.h"
#include "../generated/images/switch/switch_bg.h"
#include "battle_data/battle_state.h"
#include "battle_data/pkmn_bank.h"
#include "battle_text/battle_textbox_gfx.h"
#include <pokeagb/pokeagb.h>

#define OBJID_HIDE(objid) objects[objid].final_oam.affine_mode = 2

#define SWB_ABILITY 0
#define SWB_ITEM 1
#define SWB_ATK 2
#define SWB_DEF 3
#define SWB_SPA 4
#define SWB_SPD 5
#define SWB_SPE 6

extern void option_selection(void);

static struct TextColor switch_color = {0, 15, 3};
static struct TextboxTemplate switch_boxes[] = {
    {
        /*ability*/
        .bg_id = 0,
        .x = 8,
        .y = 4,
        .width = 9,
        .height = 2,
        .pal_id = 7,
        .charbase = 1,
    },
    {
        /*item*/
        .bg_id = 0,
        .x = 20,
        .y = 4,
        .width = 9,
        .height = 2,
        .pal_id = 7,
        .charbase = 31,
    },
    {
        /*atk*/
        .bg_id = 0,
        .x = 6,
        .y = 6,
        .width = 3,
        .height = 2,
        .pal_id = 7,
        .charbase = 61,
    },
    {
        /*def*/
        .bg_id = 0,
        .x = 11,
        .y = 6,
        .width = 3,
        .height = 2,
        .pal_id = 7,
        .charbase = 76,
    },
    {
        /*spa*/
        .bg_id = 0,
        .x = 16,
        .y = 6,
        .width = 3,
        .height = 2,
        .pal_id = 7,
        .charbase = 96,
    },
    {
        /*spd*/
        .bg_id = 0,
        .x = 21,
        .y = 6,
        .width = 3,
        .height = 2,
        .pal_id = 7,
        .charbase = 106,
    },
    {
        /*spe*/
        .bg_id = 0,
        .x = 27,
        .y = 6,
        .width = 3,
        .height = 2,
        .pal_id = 7,
        .charbase = 121,
    },

    {
        .bg_id = 0xFF, /* marks the end of the tb array */
    },

};

void switch_setup(void) {
    struct BgConfig bg0_config = {.padding = 0,
                                  .b_padding = 0,
                                  .priority = 0,
                                  .palette = 0,
                                  .size = 0,
                                  .map_base = 31,
                                  .character_base = 0,
                                  .bgid = 0};
    struct BgConfig bg1_config = {.padding = 0,
                                  .b_padding = 0,
                                  .priority = 1,
                                  .palette = 0,
                                  .size = 0,
                                  .map_base = 30,
                                   .character_base = 2,
                                  .bgid = 1};
    struct BgConfig bg2_config = {.padding = 0,
                                  .b_padding = 0,
                                  .priority = 2,
                                  .palette = 0,
                                  .size = 0,
                                  .map_base = 29,
                                  .character_base = 1,
                                  .bgid = 2};
    struct BgConfig bg3_config = {.padding = 0,
                                  .b_padding = 0,
                                  .priority = 3,
                                  .palette = 0,
                                  .size = 1,
                                  .map_base = 28,
                                  .character_base = 3,
                                  .bgid = 3};
    struct BgConfig bg_config_data[4] = {bg0_config, bg1_config, bg2_config,
                                         bg3_config};
    bgid_mod_x_offset(0, 0, 0);
    bgid_mod_y_offset(0, 0, 0);
    bgid_mod_x_offset(1, 0, 0);
    bgid_mod_y_offset(1, 0, 0);
    gpu_tile_bg_drop_all_sets(0);
    bg_vram_setup(0, (struct BgConfig *)&bg_config_data, 4);
    memset((void *)(ADDR_VRAM), 0x0, 0x10000);
    /* Hide all the objects on screen */
    for (u8 j = 0; j < 4; ++j) {
        if ((p_bank[OPPONENT_SINGLES_BANK]->objid_hpbox[j]) < 0x3F) {
            OBJID_HIDE(p_bank[OPPONENT_SINGLES_BANK]->objid_hpbox[j]);
        }
        if ((p_bank[PLAYER_SINGLES_BANK]->objid_hpbox[j]) < 0x3F) {
            OBJID_HIDE(p_bank[PLAYER_SINGLES_BANK]->objid_hpbox[j]);
        }
    }
    if ((p_bank[PLAYER_SINGLES_BANK]->objid) < 0x3F) {
        OBJID_HIDE(p_bank[PLAYER_SINGLES_BANK]->objid);
    }

    if ((p_bank[OPPONENT_SINGLES_BANK]->objid) < 0x3F) {
        OBJID_HIDE(p_bank[OPPONENT_SINGLES_BANK]->objid);
    }
    gpu_sync_bg_show(1);
    gpu_sync_bg_show(0);
}

void switch_load_background(void) {
    /* load menu */
    void *sw_bgbackbuffer = malloc(0x1000);
    LZ77UnCompWram((void *)switch_bgMap, (void *)sw_bgbackbuffer);
    lz77UnCompVram((void *)switch_bgTiles, (void *)0x06008000);
    gpu_pal_apply_compressed((void *)switch_bgPal, 0, 32);
    bgid_set_tilemap(1, sw_bgbackbuffer);

    bgid_mark_for_sync(1);
    bgid_mark_for_sync(0);
}

static const pchar test[] = _("TESTtest");

void switch_scene_main(void) {
    dprintf("current state: %d\n", super.multi_purpose_state_tracker);
    switch (super.multi_purpose_state_tracker) {
    case 0:
        if (!pal_fade_control.active) {
            switch_setup();
            /* VRAM setup */
            super.multi_purpose_state_tracker++;
        }
        break;
    case 1: {
        switch_load_background();

        rbox_init_from_templates(switch_boxes);
        rboxid_clear_pixels(SWB_ABILITY, 0);
        rboxid_clear_pixels(SWB_ITEM, 0);
        rboxid_clear_pixels(SWB_ATK, 0);
        rboxid_clear_pixels(SWB_DEF, 0);
        rboxid_clear_pixels(SWB_SPA, 0);
        rboxid_clear_pixels(SWB_SPD, 0);
        rboxid_clear_pixels(SWB_SPE, 0);

        rboxid_print(SWB_ABILITY, 0, 0, 0, &switch_color, 0, &test[0]);
        rboxid_print(SWB_ITEM, 0, 0, 0, &switch_color, 0, &test[0]);
        pchar buffer[3];
        fmt_int_10(&buffer[0], 10, 0, 3);

        rboxid_print(SWB_ATK, 0, 0, 0, &switch_color, 0, &buffer[0]);
        rboxid_print(SWB_DEF, 0, 0, 0, &switch_color, 0, &buffer[0]);
        rboxid_print(SWB_SPA, 0, 0, 0, &switch_color, 0, &buffer[0]);
        rboxid_print(SWB_SPD, 0, 0, 0, &switch_color, 0, &buffer[0]);
        rboxid_print(SWB_SPE, 0, 0, 0, &switch_color, 0, &buffer[0]);

        rboxid_update(SWB_ABILITY, 3);
        rboxid_update(SWB_ITEM, 3);
        rboxid_update(SWB_ATK, 3);
        rboxid_update(SWB_DEF, 3);
        rboxid_update(SWB_SPA, 3);
        rboxid_update(SWB_SPD, 3);
        rboxid_update(SWB_SPE, 3);

        rboxid_tilemap_update(SWB_ABILITY);
        rboxid_tilemap_update(SWB_ITEM);
        rboxid_tilemap_update(SWB_ATK);
        rboxid_tilemap_update(SWB_DEF);
        rboxid_tilemap_update(SWB_SPA);
        rboxid_tilemap_update(SWB_SPD);
        rboxid_tilemap_update(SWB_SPE);
        super.multi_purpose_state_tracker++;
        break;
    }
    case 2:
        fade_screen(0xFFFFFFFF, 0, 16, 0, 0x0000);
        super.multi_purpose_state_tracker++;
        break;
    case 3:
        if (!pal_fade_control.active) {
            switch (super.buttons_new_remapped & (KEY_A | KEY_B)) {
            case KEY_A:
                /* switch to selected pokemon */
                super.multi_purpose_state_tracker++;
                fade_screen(0xFFFFFFFF, 0, 0, 16, 0x0000);
                break;
            case KEY_B:
                /* switch back to normal menu */
                fade_screen(0xFFFFFFFF, 0, 0, 16, 0x0000);
                super.multi_purpose_state_tracker += 2;
                break;
            default:
                break;
            }
        }
        break;
    case 4:
        if (!pal_fade_control.active) {
            fade_screen(0xFFFFFFFF, 0, 16, 0, 0x0000);
        }
        break;
    case 5:
        break;
    }
}