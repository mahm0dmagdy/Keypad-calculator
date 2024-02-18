/*
 * GIE_program.c
 *
 * Created: 9/13/2023 2:34:59 AM
 *  Author: mahmo
 */ 

#include "../../Library/BIT_MATH.h"
#include "../../Library/STD_TYPES.h"

#include "GIE_interface.h"
#include "GIE_reg.h"

void GIE_voidEnableGlobal(void){
	//SET_BIT(SREG,SREG_I);
		__asm __volatile("SEI");  /*Inline assembly instruction to set I bit*/

}

void GIE_voidDisableGlobal(void){
		//CLR_BIT(SREG,SREG_I);
		__asm __volatile("CLI"); /*Inline assembly instruction to clear I bit*/

}
