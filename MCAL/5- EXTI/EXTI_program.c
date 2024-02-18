/*
 * EXTI_program.c
 *
 * Created: 9/12/2023 10:40:39 PM
 *  Author: mahmo
 */


#include "../../Library/BIT_MATH.h"
#include "../../Library/STD_TYPES.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_reg.h"
#include "EXTI_private.h"
#include "../../Library/defines.h"

static void (*EXTI_pfINTFuncPtr[3])(void) = {NULL}; /*array of pointer to function to hold ISR Callbacks*/

void EXTI_voidinit0(void)
{

    /*implement INT0 sense control configuration*/

#if INT0_SENSE_CTRL == EXTI_u8LOW_LEVEL
    CLR_BIT(MCUCR,MCUCR_ISC00);
    CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE_CTRL == EXTI_u8ON_CHANGE
    SET_BIT(MCUCR,MCUCR_ISC00);
    CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE_CTRL == EXTI_u8FALLING_EDGE
    SET_BIT(MCUCR,MCUCR_ISC01);
    CLR_BIT(MCUCR,MCUCR_ISC00);

#elif INT0_SENSE_CTRL == EXTI_u8RISING_EDGE
    SET_BIT(MCUCR,MCUCR_ISC01);
    SET_BIT(MCUCR,MCUCR_ISC00);

#else
#error Wrong INT0_SENSE_CTRL configuration option
#endif

    /*implement INT0 initial state configuration*/
#if INT0_INITIAL_STATE == ENABLED
    SET_BIT(GICR,GICR_INT0);

#elif INT0_INITIAL_STATE == DISABLED
    CLR_BIT(GICR,GICR_INT0);

#else
#error Wrong INT0_INITIAL_STATE configuration option
#endif

}

void EXTI_voidinit1(void)
{
    /*implement INT1 sense control configuration*/

#if INT1_SENSE_CTRL == EXTI_u8LOW_LEVEL
    CLR_BIT(MCUCR,MCUCR_ISC11);
    CLR_BIT(MCUCR,MCUCR_ISC10);

#elif INT1_SENSE_CTRL == EXTI_u8ON_CHANGE
    CLR_BIT(MCUCR,MCUCR_ISC11);
    SET_BIT(MCUCR,MCUCR_ISC10);

#elif INT1_SENSE_CTRL == EXTI_u8FALLING_EDGE
    SET_BIT(MCUCR,MCUCR_ISC11);
    CLR_BIT(MCUCR,MCUCR_ISC10);

#elif INT1_SENSE_CTRL == EXTI_u8RISING_EDGE
    SET_BIT(MCUCR,MCUCR_ISC11);
    SET_BIT(MCUCR,MCUCR_ISC10);
#else
#error Wrong INT1_SENSE_CTRL configuration option
#endif

    /*implement INT1 initial state configuration*/

#if INT1_INITIAL_STATE == ENABLED
    SET_BIT(GICR,GICR_INT1);

#elif INT1_INITIAL_STATE == DISABLED
    CLR_BIT(GICR,GICR_INT1);

#else
#error Wrong INT1_INITIAL_STATE configuration option
#endif

}
void EXTI_voidinit2(void)
{
    /*implement INT2 sense control configuration*/

#if INT2_SENSE_CTRL == EXTI_u8FALLING_EDGE
    CLR_BIT(MCUCSR,MCUCSR_ISC2);

#elif INT2_SENSE_CTRL == EXTI_u8RISING_EDGE
    SET_BIT(MCUCSR,MCUCSR_ISC2);
#else
#error Wrong INT2_SENSE_CTRL configuration option
#endif

    /*implement INT2 initial state configuration*/
#if INT2_INITIAL_STATE == ENABLED
    SET_BIT(GICR,GICR_INT2);

#elif INT2_INITIAL_STATE == DISABLED
    CLR_BIT(GICR,GICR_INT2);
#else
#error Wrong INT2_INITIAL_STATE configuration option
#endif
}

uint8 EXTI_u8SetSenseCtrl(uint8 Copy_u8IntNum,uint8 Copy_u8Sense)
{
    uint8 Local_u8ErrorState = OK;
    switch(Copy_u8IntNum)
    {
    case EXTI_u8INT0:
        if(Copy_u8Sense == EXTI_u8LOW_LEVEL)
        {
            CLR_BIT(MCUCR,MCUCR_ISC00);
            CLR_BIT(MCUCR,MCUCR_ISC01);
        }
        else if(Copy_u8Sense ==EXTI_u8ON_CHANGE)
        {
            SET_BIT(MCUCR,MCUCR_ISC00);
            CLR_BIT(MCUCR,MCUCR_ISC01);
        }
        else if(Copy_u8Sense ==EXTI_u8FALLING_EDGE)
        {
            SET_BIT(MCUCR,MCUCR_ISC01);
            CLR_BIT(MCUCR,MCUCR_ISC00);
        }
        else if(Copy_u8Sense ==EXTI_u8RISING_EDGE)
        {
            SET_BIT(MCUCR,MCUCR_ISC01);
            SET_BIT(MCUCR,MCUCR_ISC00);
        }
        else
        {
            Local_u8ErrorState = NOK;
        }
        break;

    case EXTI_u8INT1:
        if (Copy_u8Sense == EXTI_u8LOW_LEVEL)
        {
            CLR_BIT(MCUCR,MCUCR_ISC11);
            CLR_BIT(MCUCR,MCUCR_ISC10);
        }

        else if (Copy_u8Sense == EXTI_u8ON_CHANGE)
        {
            CLR_BIT(MCUCR,MCUCR_ISC11);
            SET_BIT(MCUCR,MCUCR_ISC10);
        }

        else if (Copy_u8Sense == EXTI_u8FALLING_EDGE)
        {
            SET_BIT(MCUCR,MCUCR_ISC11);
            CLR_BIT(MCUCR,MCUCR_ISC10);
        }

        else if (Copy_u8Sense == EXTI_u8RISING_EDGE)
        {
            SET_BIT(MCUCR,MCUCR_ISC11);
            SET_BIT(MCUCR,MCUCR_ISC10);
        }
        else
        {
            Local_u8ErrorState = NOK;
        }
        break;

    case EXTI_u8INT2:
        if (Copy_u8Sense == EXTI_u8FALLING_EDGE)
        {
            CLR_BIT(MCUCSR,MCUCSR_ISC2);
        }

        else if(Copy_u8Sense == EXTI_u8RISING_EDGE)
        {
            SET_BIT(MCUCSR,MCUCSR_ISC2);
        }

        else
        {
            Local_u8ErrorState = NOK;
        }
        break;

    default:
        Local_u8ErrorState = NOK;
        break;

    }
    return Local_u8ErrorState;
}

uint8 EXTI_u8IntEnable(uint8 Copy_u8IntNum)
{
    uint8 Local_u8ErrorState = OK;
    switch(Copy_u8IntNum)
    {

    case EXTI_u8INT0:
        SET_BIT(GICR,GICR_INT0);
        break;
    case EXTI_u8INT1:
        SET_BIT(GICR,GICR_INT1);
        break;
    case EXTI_u8INT2:
        SET_BIT(GICR,GICR_INT2);
        break;
    default:
        Local_u8ErrorState = NOK;
    }

    return Local_u8ErrorState;
}

uint8 EXTI_u8IntDisable(uint8 Copy_u8IntNum)
{
    uint8 Local_u8ErrorState = OK;
    switch(Copy_u8IntNum)
    {

    case EXTI_u8INT0:
        CLR_BIT(GICR,GICR_INT0);
        break;
    case EXTI_u8INT1:
        CLR_BIT(GICR,GICR_INT1);
        break;
    case EXTI_u8INT2:
        CLR_BIT(GICR,GICR_INT2);
        break;
    default:
        Local_u8ErrorState = NOK;
    }

    return Local_u8ErrorState;
}

uint8 EXTI_u8SetCallBack(uint8 Copy_u8IntNum, void (*Copy_ofFuncPtr)(void)){
	uint8 Local_u8ErrorState = OK;
	if(Copy_ofFuncPtr != NULL){
		EXTI_pfINTFuncPtr[Copy_u8IntNum] = Copy_ofFuncPtr;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
		
	return Local_u8ErrorState;
}
/**
* @brief INT0 ISR 
*/
void __vector_1 (void) __attribute__((signal));
void __vector_1 (void){
	
if(EXTI_pfINTFuncPtr[EXTI_u8INT0] != NULL){
	EXTI_pfINTFuncPtr[EXTI_u8INT0]();
	}
}

/**
* @brief INT1 ISR
*/

void __vector_2 (void) __attribute__((signal));
void __vector_2 (void){
	
	if(EXTI_pfINTFuncPtr[EXTI_u8INT1] != NULL){
		EXTI_pfINTFuncPtr[EXTI_u8INT1]();
	}
}

/**
* @brief INT2 ISR
*/

void __vector_3 (void) __attribute__((signal));
void __vector_3 (void){
	
	if(EXTI_pfINTFuncPtr[EXTI_u8INT2] != NULL){
		EXTI_pfINTFuncPtr[EXTI_u8INT2]();
	}
}