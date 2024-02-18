/*
 * TIMERS_program.c
 *
 * Created: 9/30/2023 11:29:42 AM
 *  Author: mahmo
 */ 

#include "../../Library/STD_TYPES.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/defines.h"

#include "TIMERS_config.h"
#include "TIMERS_interface.h"
#include "TIMERS_reg.h"

#include "TIMERS_private.h"
 
static	void (*TIMERS_pvCallBackFuncArr[8])(void) = {NULL}; /*Array of pointers to function*/

void TIMER0_voidInit(void){
	
	/*Waveform generation mode: Normal mode*/
	#if TIMER0_MODE == NORMAL
		CLR_BIT(TCCR0,TCCR0_WGM00);
		CLR_BIT(TCCR0,TCCR0_WGM01);
	
		/*Enable PIE of timer0, compare match event*/
		SET_BIT(TIMSK,TIMSK_OCIE0);
	
	/*Waveform generation mode: CTC*/
	#elif TIMER0_MODE == CTC
		CLR_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);
		
		/*OC0 pin mode*/
		TCCR0 &= OC0_MASK;
		TCCR0 |= OC0_MODE;
	
		/*Enable PIE of timer0, compare match event*/
		SET_BIT(TIMSK,TIMSK_OCIE0);
	
	/*Waveform generation mode: FASTPWM*/
	#elif TIMER0_MODE == FASTPWM
		SET_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);
		
	     	/*OC0 pin mode*/
			TCCR0 &= OC0_MASK;
			TCCR0 |= OC0_MODE
			
	#else
	#error Wrong TIMER0_MODE configuration option
	#endif
	
	/*Clear the PRESACALER bits*/
	TCCR0 &= PRESCALER_MASK;
	
	/*Select PRESACALER: division by 64*/
	TCCR0 |= PRESCALER;
}

uint8 TIMERS_u8SetCallBack(TIMERS_Int_Scr_t Copy_TmrIntSource, void(*Copy_pvCallBackFunc) (void)){
	uint8 Local_u8ErrorState = OK;
	 if(Copy_pvCallBackFunc != NULL){
		 TIMERS_pvCallBackFuncArr[Copy_TmrIntSource] = Copy_pvCallBackFunc;
	 }
	 else
	 {
		 Local_u8ErrorState = NULL_PTR_ERR;
	 }
	return Local_u8ErrorState;
}

void TIMER0_voidSetTimerVal(uint8 Copy_u8Val){
	TCNT0 = Copy_u8Val;
}

void TIMER0_voidSetComp(uint8 Copy_u8Val){
	OCR0 = Copy_u8Val;
}

void TIMER1_voidInit(void){
	
	/*Fast PWM, ICR1 as top value*/
	//CLR_BIT(TCCR1A.TCCR1A_WGM10);
	//SET_BIT(TCCR1A.TCCR1A_WGM11);

	/*Set on top*/
//	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	//CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	
}

void Timer1_voidSetTimerVal(uint16 Copy_u16Val){
	TCNT1 = Copy_u16Val;
}

void TIMER1_voidSetComp(uint16 Copy_u8Val){
	OCR1A = Copy_u8Val;
}

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void) {
	if(TIMERS_pvCallBackFuncArr[TIMER0_COMP] != NULL){
		TIMERS_pvCallBackFuncArr[TIMER0_COMP]();  
	}
}