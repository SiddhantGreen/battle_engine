#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_state.h"

void set_active_movement(u8 t_id) {
    struct Task* t = &tasks[t_id];
   
    // calculate bank and delta
    u8 bank = t->priv[0];
    s8 amount = (t->priv[1]) ? -1 : 1;
    
    // apply delta
    if ((t->priv[2] == 10)) {
        objects[p_bank[bank]->objid].pos1.y += amount;
        t->priv[2]++;
    } else if (t->priv[2] == 20) {
        objects[p_bank[bank]->objid_hpbox[0]].pos1.y += amount;
        objects[p_bank[bank]->objid_hpbox[1]].pos1.y += amount;
        objects[p_bank[bank]->objid_hpbox[2]].pos1.y += amount;
        t->priv[2] = 0;
        // adjust direction of delta next time
        t->priv[1] = !(t->priv[1]);
    } else {
        t->priv[2]++;
        return;
    }
    
}

void obj_battler_fall_through(struct Object* obj)
{
    if (obj->priv[0] < 64) {
        obj->priv[1]++;
        obj->priv[0] += 8;
        obj->pos1.y += 8;
        
        // remove a tile layer from the bottom
        void* dst = (void*)((obj->final_oam.tile_num * 32) + 0x6010000);
        dst += 32 * 8 * (8 - obj->priv[1]);
        memset(dst, 0, 32 * 8 * obj->priv[1]); 
    } else {
        // free the hp bars too
        obj_free(&objects[obj->priv[2]]);
        obj_free(&objects[obj->priv[3]]);
        obj_free(&objects[obj->priv[4]]);
        obj_free(obj);
    }
}


