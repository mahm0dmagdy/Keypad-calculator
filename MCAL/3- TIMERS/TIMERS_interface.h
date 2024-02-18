/*
 * TIMERS_interface.h
 *
 * Created: 9/30/2023 11:29:09 AM
 *  Author: mahmo
 */ 


#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_

typedef enum {
	TIMER0_OVF=0,
	TIMER0_COMP
 	}TIMERS_Int_Scr_t;

void TIMER0_voidInit(void);

void TIMER0_voidSetTimerVal(uint8 Copy_u8Val);

void TIMER0_voidSetComp(uint8 Copy_u8Val);

void TIMER1_voidInit(void);

void TIMER1_voidSetComp(uint16 Copy_u8Val);

void Timer1_voidSetTimerVal(uint16 Copy_u16Val);

uint8 TIMERS_u8SetCallBack(TIMERS_Int_Scr_t Copy_TmrIntSource, void(*Copy_pvCallBackFunc) (void));

#endif /* TIMERS_INTERFACE_H_ */