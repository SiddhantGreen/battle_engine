#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/battle_state.h"


static const struct RotscaleFrame shrink_grow[] = {
    {-200, -200, 0, 1, 0},
    {0, 0, 48, 1, 0},
    {20, 20, 0, 10, 0}, // 30 right
    {0x7FFF, 0, 0, 0, 0}
};
static const struct RotscaleFrame (*shrink_grow_ptr)[] = (const struct RotscaleFrame(*)[])&shrink_grow;

void pkmn_sendingout_objc(struct Object* obj)
{
    obj->pos1.y = obj->priv[4];
    obj->priv[2]++;
    if (obj->priv[2] % obj->priv[1])
        return;
    if (!obj->priv[0]) {
        REG_BLDCNT = 0;
        obj->callback = oac_nullsub;
        obj->final_oam.affine_mode = 0;
        bs_anim_status = 0;
        return;
    }
    REG_BLDY = obj->priv[0];
    obj->priv[0]--;
}
extern void dprintf(const char * str, ...);
u8 send_out_backsprite(u8 bank)
{
    // send out pokemon's backsprite based on bank
    extern u8 spawn_pkmn_backsprite_obj_slot(u8 slot, u16 tag);
    u8 slot = GET_SLOT_FROM_PTR((u32)&party_opponent[0], (u32)p_bank[bank]->this_pkmn, 100);
    u8 objid = spawn_pkmn_backsprite_obj_slot(slot, 0x810);
    objects[objid].rotscale_table = (const struct RotscaleFrame(**)[])&shrink_grow_ptr;
    objects[objid].final_oam.affine_mode = 1;
    objects[objid].callback = pkmn_sendingout_objc;
    objects[objid].priv[0] = 0x10;
    objects[objid].priv[1] = 3; // delay
    objects[objid].priv[4] = objects[objid].pos1.y;
    objects[objid].pos1.y -= 64;
    p_bank[0]->objid = objid;
    u8 pal_slot = objects[objid].final_oam.palette_num;
    u32 pal_fade = ((1 << (pal_slot + 16)));
    
    // flash white for 4 frames
    fade_screen(pal_fade , 3, 0x10, 0x0, 0x7ADF);
    REG_BLDCNT = (BLDCNT_BG1_SRC | BLDCNT_BG2_SRC | BLDCNT_BG3_SRC | BLDCNT_LIGHTEN | BLDCNT_BG1_DST | BLDCNT_BG2_DST | BLDCNT_BG3_DST);
    return objid;
}

const s8 ball_throw_delta_y[] = {0, 0, 1, 1, 1, 2, 2, 3, 4, 5, 5, 7, 7, 8, 9, 9, 10, 12, 13, 16, 20, 24, 28, 28, 28, 28, 28, 28, 28, 28, 28};
void pokeball_player_throw_arc(struct Object* obj)
{
    obj->priv[6]++;
    if (obj->pos1.y < 120) {   
        obj->pos1.x++;
        obj->pos1.y += (ball_throw_delta_y[obj->priv[6]] >> 2);
    } else {
        obj->final_oam.affine_mode = 0;
        send_out_backsprite(obj->priv[0]);
        obj_free(obj);
    }

}

static const struct RotscaleFrame spin[] = {
    {0, 0, 0x00, 1, 0x0}, // wait
    {0, 0, 30, 255, 0x0}, // 30 right
    {0x7FFF, 0x0, 0x0, 0x0, 0x0}
};
static const struct RotscaleFrame (*spin_ptr)[] = (const struct RotscaleFrame(*)[])&spin;

void make_spinning_pokeball(s16 x, s16 y, u8 bank)
{
    // get pokeball index in table
    struct Pokemon* p = p_bank[bank]->this_pkmn;
    u16 ball_id = pokemon_getattr(p, REQUEST_POKEBALL, NULL);
    ball_id = ball_number_to_ball_processing_index(ball_id);
    gpu_tile_obj_decompress_alloc_tag_and_upload(&ball_tiles[ball_id]);
    gpu_pal_decompress_alloc_tag_and_upload(&ball_palettes[ball_id]);
    u8 objid = template_instanciate_forward_search((struct Template*)0x82606F4, x, y, 0);
    objects[objid].callback = pokeball_player_throw_arc;
    objects[objid].priv[0] = bank;
    
    objects[objid].priv[1] = 1; // object delta X during animation
    objects[objid].priv[2] = 2; // Delay to apply delta X
    objects[objid].priv[3] = -2; // Delta y
    objects[objid].priv[4] = 1; // Delta y modifier
    objects[objid].priv[5] = 2; // Delay to apply delta y
    objects[objid].priv[6] = 0; // Delay timer  
    
    objects[objid].rotscale_table = (const struct RotscaleFrame(**)[])&spin_ptr;
    objects[objid].final_oam.affine_mode = 1;
    
}


