#include "../generated/images/battle_terrains/grass/grass_bg.h"
#include "../generated/images/switch/switch_bg.h"
#include "../generated/images/type_icons.h"
#include "../generated/images/PSS_icons.h"
#include "battle_data/battle_state.h"
#include "battle_data/pkmn_bank.h"
#include "battle_text/battle_textbox_gfx.h"
#include <pokeagb/pokeagb.h>

#define OBJID_HIDE(objid) objects[objid].final_oam.affine_mode = 2
#define OBJID_SHOW(objid) objects[objid].final_oam.affine_mode = 0
#define rgb5(r, g, b) (u16)((r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10))
#define STAT_COLOR(stat, pkmn)                                                                                                                       \
    (nature_stat_boosted(stat, pkmn) ? &switch_color_green : (nature_stat_nerved(stat, pkmn) ? &switch_color_red : &switch_color))

#define SWB_ABILITY 0
#define SWB_ITEM 1
#define SWB_ATK 2
#define SWB_DEF 3
#define SWB_SPA 4
#define SWB_SPD 5
#define SWB_SPE 6
#define SWB_MOVES 7
#define SWB_POW 8
#define SWB_ACC 9
#define SWB_PP 10
#define SWB_NAME 11

extern void option_selection(void);
extern u8 get_ability(struct Pokemon *p);
extern u8 load_dmg_type_icon(u8 type, s16 x, s16 y, u8 tag);
extern u8 load_dmg_category_icon(u8 category, s16 x, s16 y, u8 tag);

static const pchar str_no_item[] = _("None");

static u16 switch_text_pal[] = {rgb5(255, 0, 255),   rgb5(248, 248, 248), rgb5(112, 112, 112), rgb5(96, 96, 96),
                                rgb5(208, 208, 208), rgb5(76, 154, 38),   rgb5(102, 194, 66),  rgb5(168, 75, 76),
                                rgb5(224, 114, 75),  rgb5(180, 124, 41),  rgb5(241, 188, 60),  rgb5(255, 0, 255),
                                rgb5(255, 0, 255),   rgb5(255, 0, 255),   rgb5(255, 0, 255),   rgb5(255, 0, 255)};

static struct TextColor switch_color = {0, 3, 4};
static struct TextColor switch_color_bg = {0, 1, 2};
static struct TextColor switch_color_red = {0, 7, 8};
static struct TextColor switch_color_green = {0, 5, 6};
static struct TextboxTemplate switch_boxes[] = {
    {
        /*ability*/
        .bg_id = 0,
        .x = 8,
        .y = 4,
        .width = 9,
        .height = 2,
        .pal_id = 15,
        .charbase = 1,
    },
    {
        /*item*/
        .bg_id = 0,
        .x = 20,
        .y = 4,
        .width = 9,
        .height = 2,
        .pal_id = 15,
        .charbase = 31,
    },
    {
        /*atk*/
        .bg_id = 0,
        .x = 6,
        .y = 5,
        .width = 3,
        .height = 3,
        .pal_id = 15,
        .charbase = 61,
    },
    {
        /*def*/
        .bg_id = 0,
        .x = 11,
        .y = 5,
        .width = 3,
        .height = 3,
        .pal_id = 15,
        .charbase = 76,
    },
    {
        /*spa*/
        .bg_id = 0,
        .x = 16,
        .y = 5,
        .width = 3,
        .height = 3,
        .pal_id = 15,
        .charbase = 96,
    },
    {
        /*spd*/
        .bg_id = 0,
        .x = 21,
        .y = 5,
        .width = 3,
        .height = 3,
        .pal_id = 15,
        .charbase = 106,
    },
    {
        /*spe*/
        .bg_id = 0,
        .x = 26,
        .y = 5,
        .width = 3,
        .height = 3,
        .pal_id = 15,
        .charbase = 121,
    },
    {
        /*moves*/
        .bg_id = 0,
        .x = 9,
        .y = 9,
        .width = 10,
        .height = 8,
        .pal_id = 15,
        .charbase = 136,
    },
    {
        /*power*/
        .bg_id = 0,
        .x = 20,
        .y = 9,
        .width = 2,
        .height = 8,
        .pal_id = 15,
        .charbase = 220,
    },
    {
        /*accuracy*/
        .bg_id = 0,
        .x = 22,
        .y = 9,
        .width = 3,
        .height = 8,
        .pal_id = 15,
        .charbase = 265,
    },
    {
        /*pp*/
        .bg_id = 0,
        .x = 25,
        .y = 9,
        .width = 2,
        .height = 8,
        .pal_id = 15,
        .charbase = 310,
    },
    {
        /*pkmn name*/
        .bg_id = 0,
        .x = 5,
        .y = 0,
        .width = 11,
        .height = 2,
        .pal_id = 15,
        .charbase = 355,
    },
    {
        .bg_id = 0xFF, /* marks the end of the tb array */
    },

};

void switch_setup(void) {
    struct BgConfig bg0_config = {
        .padding = 0, .b_padding = 0, .priority = 0, .palette = 0, .size = 0, .map_base = 31, .character_base = 0, .bgid = 0};
    struct BgConfig bg1_config = {
        .padding = 0, .b_padding = 0, .priority = 1, .palette = 0, .size = 0, .map_base = 30, .character_base = 2, .bgid = 1};
    struct BgConfig bg2_config = {
        .padding = 0, .b_padding = 0, .priority = 2, .palette = 0, .size = 0, .map_base = 29, .character_base = 1, .bgid = 2};
    struct BgConfig bg3_config = {
        .padding = 0, .b_padding = 0, .priority = 3, .palette = 0, .size = 1, .map_base = 28, .character_base = 3, .bgid = 3};
    struct BgConfig bg_config_data[4] = {bg0_config, bg1_config, bg2_config, bg3_config};
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
    gpu_sync_bg_hide(1);
    gpu_sync_bg_hide(0);
}

void switch_load_background(void) {
    /* load menu */
    void *sw_bgbackbuffer = malloc(0x800);
    gpu_pal_apply_compressed((void *)switch_bgPal, 0, 32);
    gpu_pal_apply((void *)(&switch_text_pal), 15 * 16, 32);
    LZ77UnCompWram((void *)switch_bgMap, (void *)sw_bgbackbuffer);
    lz77UnCompVram((void *)switch_bgTiles, (void *)0x06008000);

    bgid_set_tilemap(1, sw_bgbackbuffer);

    bgid_mark_for_sync(1);
    bgid_mark_for_sync(0);
}

void switch_type_update_icon(u8 objid, enum MoveTypes type) {
    void *vram = (void *)((0x06010000) + objects[objid].final_oam.tile_num * 32);
    memcpy(vram, (type * 256) + type_iconsTiles, 256);
}

void switch_category_update_icon(u8 objid, u8 category) {
    void *vram = (void *)((0x06010000) + objects[objid].final_oam.tile_num * 32);
    memcpy(vram, (category * 128) + PSS_iconsTiles, 128);
}

void switch_type_icon_load(u8 type, s16 x, s16 y, u8 id) {
    if (battle_master->switch_objid[id] != 0x3F) {
        switch_type_update_icon(battle_master->switch_objid[id], type);
    } else {
        battle_master->switch_objid[id] = load_dmg_type_icon(type, x, y, id + 4);
    }
}

void switch_cat_icon_load(u8 category, s16 x, s16 y, u8 id) {
    u8 array_idx = id + 6;
    if (battle_master->switch_objid[array_idx] != 0x3F) {
        switch_category_update_icon(battle_master->switch_objid[array_idx], category);
    } else {
        battle_master->switch_objid[array_idx] = load_dmg_category_icon(category, x,y, id + 4);
    }
}

bool nature_stat_boosted(u8 stat, struct Pokemon *pokemon) {
    u8 nature = get_nature(pokemon_getattr(pokemon, REQUEST_PID, NULL));
    if ((nature / 5) == (nature % 5))
        return false;
    return stat == (nature / 5);
}

bool nature_stat_nerved(u8 stat, struct Pokemon *pokemon) {
    u8 nature = get_nature(pokemon_getattr(pokemon, REQUEST_PID, NULL));
    if ((nature / 5) == (nature % 5))
        return false;
    return stat == (nature % 5);
}

void switch_load_pokemon_data(struct Pokemon *pokemon) {
    /*defensive programming*/
    if (pokemon == NULL)
        return;
    u8 species = pokemon_getattr(pokemon, REQUEST_SPECIES, NULL);
    if (species == 0)
        return;

    for (u32 i = SWB_ABILITY; i <= SWB_NAME; ++i) {
        rboxid_clear_pixels(i, 0);
    }

    (void)pokemon_getattr(pokemon, REQUEST_NICK, string_buffer);
    rboxid_print(SWB_NAME, 0, 0, 4, &switch_color_bg, 0, &string_buffer[0]);

    /* print the stats */

    fmt_int_10(string_buffer, pokemon_getattr(pokemon, REQUEST_ATK, NULL), 0, 4);
    rboxid_print(SWB_ATK, 0, 1, 7, STAT_COLOR(0, pokemon), 0, &string_buffer[0]);

    fmt_int_10(string_buffer, pokemon_getattr(pokemon, REQUEST_DEF, NULL), 0, 4);
    rboxid_print(SWB_DEF, 0, 2, 7, STAT_COLOR(1, pokemon), 0, &string_buffer[0]);

    fmt_int_10(string_buffer, pokemon_getattr(pokemon, REQUEST_SPATK, NULL), 0, 4);
    rboxid_print(SWB_SPA, 0, 3, 7, STAT_COLOR(3, pokemon), 0, &string_buffer[0]);

    fmt_int_10(string_buffer, pokemon_getattr(pokemon, REQUEST_SPDEF, NULL), 0, 4);
    rboxid_print(SWB_SPD, 0, 4, 7, STAT_COLOR(4, pokemon), 0, &string_buffer[0]);

    fmt_int_10(string_buffer, pokemon_getattr(pokemon, REQUEST_SPD, NULL), 0, 4);
    rboxid_print(SWB_SPE, 0, 5, 7, STAT_COLOR(2, pokemon), 0, &string_buffer[0]);

    /* print the ability */

    rboxid_print(SWB_ABILITY, 0, 3, 1, &switch_color, 0, &pokemon_ability_names[get_ability(pokemon)][0]);

    /* print the item */
    /* TODO: check on that item, there may be an internal routine for it */
    u8 item = pokemon_getattr(pokemon, REQUEST_HELD_ITEM, NULL) - 13;
    if (item == 0) {
        rboxid_print(SWB_ITEM, 0, 1, 1, &switch_color, 0, &str_no_item[0]);
    } else {
        rboxid_print(SWB_ITEM, 0, 1, 1, &switch_color, 0, &items[item].name[0]);
    }

    for (u32 i = 0; i < 4; ++i) {
        u8 move = pokemon_getattr(pokemon, REQUEST_MOVE1 + i, NULL);
        if (move == 0)
            continue;
        rboxid_print(SWB_MOVES, 0, 0, (4 + 14 * i), &switch_color, 0, &moves[move].name[0]);

        fmt_int_10(string_buffer, moves[move].base_power, 0, 4);
        rboxid_print(SWB_POW, 0, 1, (4 + 14 * i), &switch_color, 0, &string_buffer[0]);

        fmt_int_10(string_buffer, moves[move].accuracy, 0, 4);
        rboxid_print(SWB_ACC, 0, 5, (4 + 14 * i), &switch_color, 0, &string_buffer[0]);

        u8 pp = pokemon_getattr(pokemon, REQUEST_PP1 + i, NULL);
        fmt_int_10(string_buffer, pp, 0, 4);
        rboxid_print(SWB_PP, 0, 2, (4 + 14 * i), &switch_color, 0, &string_buffer[0]);

        /*the move type icon*/
        switch_type_icon_load(moves[move].type, 49, 84 + (14 * i), i + 2);
        switch_cat_icon_load(moves[move].category, 226, 84 + (14*i), i);
    }

    for (u32 i = SWB_ABILITY; i <= SWB_NAME; ++i) {
        rboxid_update(i, 3);
        rboxid_tilemap_update(i);
    }
    /* write those again, to overwrite empty space from stats */
    rboxid_update(SWB_ABILITY, 3);
    rboxid_tilemap_update(SWB_ABILITY);
    rboxid_update(SWB_ITEM, 3);
    rboxid_tilemap_update(SWB_ITEM);

    /* load the type icons */
    if ((enum MoveTypes)(pokemon_base_stats[species].type[0]) != MTYPE_EGG) {
        switch_type_icon_load(pokemon_base_stats[species].type[0], 47, 25, 0);
    }
    if (((enum MoveTypes)(pokemon_base_stats[species].type[1]) != MTYPE_EGG) &&
        (pokemon_base_stats[species].type[0] != pokemon_base_stats[species].type[1])) {
        switch_type_icon_load(pokemon_base_stats[species].type[1], 83, 25, 1);
    }
}

void switch_obj_hide_all(void) {
    for (u8 i = 0; i < 10; ++i) {
        if (battle_master->switch_objid[i] != 0x3F)
            OBJID_HIDE(battle_master->switch_objid[i]);
    }
}

void switch_obj_show_all(void) {
    for (u8 i = 0; i < 10; ++i) {
        if (battle_master->switch_objid[i] != 0x3F)
            OBJID_SHOW(battle_master->switch_objid[i]);
    }
}

void switch_scene_main(void) {
    switch (super.multi_purpose_state_tracker) {
    case 0:
        if (!pal_fade_control.active) {
            /* VRAM setup */
            rboxes_free();
            switch_setup();
            super.multi_purpose_state_tracker++;
        }
        break;
    case 1: {
        switch_load_background();
        rbox_init_from_templates(switch_boxes);
        switch_load_pokemon_data(&party_player[0]);
        switch_obj_hide_all();
        super.multi_purpose_state_tracker++;
        break;
    }
    case 2:
        gpu_sync_bg_show(1);
        gpu_sync_bg_show(0);
        switch_obj_show_all();
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