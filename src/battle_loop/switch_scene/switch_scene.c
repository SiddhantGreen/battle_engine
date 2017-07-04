#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/battle_state.h"

#define OBJID_HIDE(objid) objects[objid].final_oam.affine_mode = 2; dprintf("hiding 0x%x\n", objid)

extern void option_selection(void);

void switch_scene_main(void)
{
    switch(super.multi_purpose_state_tracker)
    {
        case 0:
            if(!pal_fade_control.active) {
                fade_screen(0xFFFFFFFF, 0, 16, 0, 0xFFFF);
                gpu_tile_bg_drop_all_sets(0);
                gpu_tile_bg_drop_all_sets(1);
                gpu_tile_bg_drop_all_sets(2);
                gpu_tile_bg_drop_all_sets(3);
                for(u8 i = 0; i < BANK_MAX; ++i){
                    if(p_bank[i]) {
                        for(u8 j = 0; j < 1; ++j) {
                            if((p_bank[i]->objid_hpbox[j]) < 0x3F) {
                                OBJID_HIDE(p_bank[i]->objid_hpbox[j]);
                            }   
                        }
                    }
                }
                super.multi_purpose_state_tracker++;
            }
        break;
        case 1:
            if(!pal_fade_control.active) {
                //set_callback1(option_selection);
                //super.multi_purpose_state_tracker = 1;
            }
        break;        
    }
}