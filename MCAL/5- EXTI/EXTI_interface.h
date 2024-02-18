/*
 * EXTI_interface.h
 *
 * Created: 9/12/2023 10:41:39 PM
 *  Author: mahmo
 */ 


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


#define EXTI_u8INT0					1u
#define EXTI_u8INT1					2u
#define EXTI_u8INT2					3u

#define EXTI_u8LOW_LEVEL			1u
#define EXTI_u8ON_CHANGE			2u
#define EXTI_u8FALLING_EDGE			3u
#define EXTI_u8RISING_EDGE			4u


void EXTI_voidinit0(void);
void EXTI_voidinit1(void);
void EXTI_voidinit2(void);

uint8 EXTI_u8SetSenseCtrl(uint8 Copy_u8IntNum,uint8 Copy_u8Sense);

uint8 EXTI_u8IntEnable(uint8 Copy_u8IntNum);

uint8 EXTI_u8IntDisable(uint8 Copy_u8IntNum);

uint8 EXTI_u8SetCallBack(uint8 Copy_u8IntNum, void (*Copy_ofFuncPtr)(void));

#endif /* EXTI_INTERFACE_H_ */