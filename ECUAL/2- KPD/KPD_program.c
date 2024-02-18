/****************************************************************************/
/****************************************************************************/
/********************** Autor: Mahmoud Magdy ********************************/
/********************** File: KPD_program.c ********************************/
/**********************    Version: 1.00     ********************************/
/****************************************************************************/
/****************************************************************************/


#include "../../Library/STD_TYPES.h"
#include "../../Library/BIT_MATH.h"

#include "../../MCAL/1- DIO/DIO_interface.h"
#include "../../ECUAL/2- KPD/KPD_interface.h"
#include "../../ECUAL/2- KPD/KPD_config.h"
#include "../../ECUAL/2- KPD/KPD_private.h"

/*Required: All row pins are pulled up, All column pins are output high*/
	uint8 KPD_u8GetPressedKey(void){
		uint8 Local_u8PressedKey = KDP_u8NO_PRESSED_KEY_VAL;
		uint8 Local_u8ColCounter;
		uint8 Local_u8RowCounter;
		uint8 Local_u8KeyState;
		
		static uint8 Local_u8ColArr[KPD_u8COL_NUM] = {KPD_u8COL0_PIN , KPD_u8COL1_PIN , KPD_u8COL2_PIN , KPD_u8COL3_PIN};
		static uint8 Local_u8RowArr[KPD_u8ROW_NUM] = {KPD_u8ROW0_PIN , KPD_u8ROW1_PIN , KPD_u8ROW2_PIN , KPD_u8ROW3_PIN};
		static char Local_u8KPDArr[KPD_u8ROW_NUM][KPD_u8COL_NUM] = KPD_u8BUTTON_ARR;

		/*Activate column pins and read the rows*/ 
		for(Local_u8ColCounter = 0 ; Local_u8ColCounter < KPD_u8COL_NUM ; Local_u8ColCounter++)
		{
			/*Activate the current column*/
			DIO_u8SetPinValue(KPD_u8COL_PORT,Local_u8ColArr[Local_u8ColCounter],DIO_u8PIN_LOW);
			
			for(Local_u8RowCounter = 0 ; Local_u8RowCounter < KPD_u8ROW_NUM ; Local_u8RowCounter++){
				
				/*Read the current row*/
				DIO_u8GetValue(KPD_u8ROW_PORT,Local_u8RowArr[Local_u8RowCounter],&Local_u8KeyState);
				
				/*If current row is low, button is pressed*/
				if(Local_u8KeyState == DIO_u8PIN_LOW){
					
					/* Wait until key is releases */
					while(Local_u8KeyState == DIO_u8PIN_LOW){
						DIO_u8GetValue(KPD_u8ROW_PORT,Local_u8RowArr[Local_u8RowCounter],&Local_u8KeyState);
					}
					Local_u8PressedKey = Local_u8KPDArr[Local_u8RowCounter][Local_u8ColCounter];
					return Local_u8PressedKey;
				}
			}
			/*Deactivate the current column*/
				DIO_u8SetPinValue(KPD_u8COL_PORT,Local_u8ColArr[Local_u8ColCounter],DIO_u8PIN_HIGH);
		}
			return Local_u8PressedKey;
}
