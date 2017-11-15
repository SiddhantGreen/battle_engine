#include <pokeagb/pokeagb.h>
#include "moves.h"

/* Basic proc format for moves like tackle */
struct move_procs basic_proc = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers target's attack 1 stage
struct move_procs target_lower_atk_1 = {
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{100, 0, 0, 0, 0, 0, 0, 0},
    {-1, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers target's attack 2 stages
struct move_procs target_lower_atk_2 = {
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {100, 0, 0, 0, 0, 0, 0, 0},
    {-2, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers target's defense 1 stage
struct move_procs target_lower_def_1 = {
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 100, 0, 0, 0, 0, 0, 0},
    {0, -1, 0, 0, 0, 0, 0, 0},
	AILMENT_BURN,
	AILMENT_PARALYZE,
	100,
	100,
};

//Lowers target's defense 2 stages
struct move_procs target_lower_def_2 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 100, 0, 0, 0, 0, 0, 0},
    {0, -2, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers target's sp. attack 1 stage
struct move_procs target_lower_spAtk_1 = {
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, -1, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers target's sp. attack 2 stages
struct move_procs target_lower_spAtk_2 = {
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, -2, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers target's sp. defense 1 stage
struct move_procs target_lower_spDef_1 = {
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, -1, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers target's sp. defense 2 stages
struct move_procs target_lower_spDef_2 = {
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, -2, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers target's speed 1 stage
struct move_procs target_lower_spd_1 = {
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, -1, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers target's speed 2 stages
struct move_procs target_lower_spd_2 = {
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, -2, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers target's ACCURACY 1 stage
struct move_procs target_lower_acc_1 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, -1, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers target's ACCURACY 2 stages
struct move_procs target_lower_acc_2 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, -2, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers user's attack 1 stage
struct move_procs user_lower_atk_1 = {
    {100, 0, 0, 0, 0, 0, 0, 0},
    {-1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers user's attack 2 stages
struct move_procs user_lower_atk_2 = {
    {100, 0, 0, 0, 0, 0, 0, 0},
    {-2, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers user's defense 1 stage
struct move_procs user_lower_def_1 = {
    {0, 100, 0, 0, 0, 0, 0, 0},
    {0, -1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers user's defense 2 stages
struct move_procs user_lower_def_2 = {
    {0, 100, 0, 0, 0, 0, 0, 0},
    {0, -2, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers user's sp. attack 1 stage
struct move_procs user_lower_spAtk_1 = {
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, -1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers user's sp. attack 2 stages
struct move_procs user_lower_spAtk_2 = {
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, -2, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers user's sp. defense 1 stage
struct move_procs user_lower_spDef_1 = {
    {0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, -1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers user's sp. defense 2 stages
struct move_procs user_lower_spDef_2 = {
    {0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, -2, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers user's speed 1 stage
struct move_procs user_lower_spd_1 = {
    {0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, -1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers user's speed 2 stages
struct move_procs user_lower_spd_2 = {
    {0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, -2, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers user's ACCURACY 1 stage
struct move_procs user_lower_acc_1 = {
    {0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, -1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Lowers user's ACCURACY 2 stages
struct move_procs user_lower_acc_2 = {
    {0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, -2, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises target's attack 1 stage
struct move_procs target_raise_atk_1 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{100, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises target's attack 2 stages
struct move_procs target_raise_atk_2 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{100, 0, 0, 0, 0, 0, 0, 0},
    {2, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises target's defense 1 stage
struct move_procs target_raise_def_1 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 100, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises target's defense 2 stages
struct move_procs target_raise_def_2 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 100, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises target's sp. attack 1 stage
struct move_procs target_raise_spAtk_1 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises target's sp. attack 2 stages
struct move_procs target_raise_spAtk_2 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, 2, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises target's sp. defense 1 stage
struct move_procs target_raise_spDef_1 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises target's sp. defense 2 stages
struct move_procs target_raise_spDef_2 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, 2, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises target's speed 1 stage
struct move_procs target_raise_spd_1 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises target's speed 2 stages
struct move_procs target_raise_spd_2 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, 2, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises target's ACCURACY 1 stage
struct move_procs target_raise_acc_1 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises target's ACCURACY 2 stages
struct move_procs target_raise_acc_2 = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, 2, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises user's attack 1 stage
struct move_procs user_raise_atk_1 = {
    {100, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises user's attack 2 stages
struct move_procs user_raise_atk_2 = {
    {100, 0, 0, 0, 0, 0, 0, 0},
    {2, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises user's defense 1 stage
struct move_procs user_raise_def_1 = {
    {0, 100, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises user's defense 2 stages
struct move_procs user_raise_def_2 = {
    {0, 100, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises user's sp. attack 1 stage
struct move_procs user_raise_spAtk_1 = {
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises user's sp. attack 2 stages
struct move_procs user_raise_spAtk_2 = {
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, 2, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises user's sp. defense 1 stage
struct move_procs user_raise_spDef_1 = {
    {0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises user's sp. defense 2 stages
struct move_procs user_raise_spDef_2 = {
    {0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, 2, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises user's speed 1 stage
struct move_procs user_raise_spd_1 = {
    {0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises user's speed 2 stages
struct move_procs user_raise_spd_2 = {
    {0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, 2, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises user's ACCURACY 1 stage
struct move_procs user_raise_acc_1 = {
    {0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

//Raises user's ACCURACY 2 stages
struct move_procs user_raise_acc_2 = {
    {0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, 2, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};