/*
 * MAP.c
 *
 * Created: 9/19/2023 8:04:18 AM
 *  Author: mahmo
 */ 
#include "STD_TYPES.h"
#include "MAP.h"
sint32 Map(sint32 Copy_s32InputRangeMin,sint32 Copy_s32InputRangeMax,sint32 Copy_s32OutputRangeMin, sint32 Copy_s32OutputRangeMax, sint32 Copy_s32InputValue){
	return (((( Copy_s32InputValue - Copy_s32InputRangeMin)*(Copy_s32OutputRangeMax - Copy_s32OutputRangeMin))/(Copy_s32InputRangeMax - Copy_s32InputRangeMin)) + Copy_s32OutputRangeMin);
}