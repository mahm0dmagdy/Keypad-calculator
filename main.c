/*
   Calculator_KDP.c

   Created: 11/21/2023 5:15:11 PM
   Author : mahmo
*/
#define  F_CPU 16000000U
#include <util/delay.h>
#include "Library/BIT_MATH.h"
#include "Library/STD_TYPES.h"
#include "MCAL/1- DIO/DIO_interface.h"
#include "MCAL/2- PORT/PORT_interface.h"
#include "ECUAL/1- CLCD/CLCD_interface.h"
#include "ECUAL/2- KPD/KPD_interface.h"
#include "ECUAL/2- KPD/KPD_config.h"
#include "MCAL/3- TIMERS/TIMERS_interface.h"

uint8 Local_u8Check(uint8 Copy_u8PressedKey);

int main(void)
{
  uint8 Local_u8PressedKey;
  uint8 Local_s8ArithmeticOperators=0;
  sint32 Local_s8Result;
  uint32 Local_s8FirstValue;
  uint32 Local_s8SecondValue;
  sint8 Local_s8SecondValueFlag;
  uint8 Local_u8ArithmeticOperatorsErr;

  PORT_voidInit();
  CLCD_voidInit();

	while (Local_u8PressedKey != 'C') {
		Local_u8PressedKey = KPD_u8GetPressedKey();
	}

	CLCD_u8Send_String("Welcome");
	_delay_ms(1500);

  while (1)
  {
	  Local_s8FirstValue = 0;
	  Local_s8SecondValue = 0;
	  Local_s8SecondValueFlag = 0;
	  Local_u8ArithmeticOperatorsErr=0;
	  Local_u8PressedKey  = KDP_u8NO_PRESSED_KEY_VAL;
	  CLCD_voidSendCmd(1);
	
    while (Local_u8PressedKey != '=' && Local_u8PressedKey != 'C' ) {
      if (Local_u8PressedKey != KDP_u8NO_PRESSED_KEY_VAL) {
        if (Local_u8Check(Local_u8PressedKey) && Local_s8SecondValueFlag == 0) {
          Local_s8FirstValue = (Local_s8FirstValue * 10) + (Local_u8PressedKey - '0');
        }

        else if (Local_s8SecondValueFlag == 1 && Local_u8Check(Local_u8PressedKey)) {
          Local_s8SecondValue =  (Local_s8SecondValue * 10) + (Local_u8PressedKey - '0');
        }

        else if (Local_u8PressedKey == '+' || Local_u8PressedKey == '-' || Local_u8PressedKey == '*' || Local_u8PressedKey == '/') {
		  if(Local_s8SecondValueFlag == 1){
			  if(Local_s8ArithmeticOperators == Local_u8PressedKey){
				  Local_s8ArithmeticOperators = Local_u8PressedKey;
			  }
			  else{
				  Local_u8ArithmeticOperatorsErr = 1;
			  }
		  }
			  else{
		  Local_s8ArithmeticOperators = Local_u8PressedKey;
          Local_s8SecondValueFlag = 1;
			  }
        }
		
		else{
		}
		
		CLCD_voidSendData(Local_u8PressedKey);
      }
	     Local_u8PressedKey = KPD_u8GetPressedKey();
	}
	
 if (Local_u8PressedKey == 'C' ) {
	 CLCD_voidSendCmd(1);
 }
 
 else {
    switch (Local_s8ArithmeticOperators) {
      case '+': Local_s8Result = Local_s8FirstValue + Local_s8SecondValue; break;
      case '-': Local_s8Result = Local_s8FirstValue - Local_s8SecondValue; break;
      case '/': Local_s8Result = (Local_s8FirstValue*1000) / Local_s8SecondValue; break;
      case '*': Local_s8Result = Local_s8FirstValue * Local_s8SecondValue; break;
      default: CLCD_u8Send_String("Undef, operation"); break;
    }
	CLCD_voidSendData('=');
	if(Local_u8ArithmeticOperatorsErr != 1){
	if(Local_s8ArithmeticOperators == '/'){
		if(Local_s8SecondValue != 0){
		CLCD_voidSendNumber(Local_s8Result/1000);
		CLCD_voidSendData('.');
		CLCD_voidSendNumber(Local_s8Result%1000);
		}
		
		else{
			CLCD_voidSendCmd(1);
			CLCD_u8Send_String("Math Error");
		}
	
	}
	else{
		CLCD_voidSendNumber(Local_s8Result);
	}
	}
	else{
		CLCD_voidSendCmd(1);
		CLCD_u8Send_String("Syntax Error");	 
	}
   while (Local_u8PressedKey != 'C') {
	   Local_u8PressedKey = KPD_u8GetPressedKey();
   }
	
  }
}
  }

uint8 Local_u8Check(uint8 Copy_u8PressedKey) {
  if (Copy_u8PressedKey != '+' && Copy_u8PressedKey != '-' && Copy_u8PressedKey != '*' && Copy_u8PressedKey != '/') {
    return 1;
  }
  else {
    return 0;
  }
}

