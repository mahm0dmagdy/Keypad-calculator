/*
 * TIMERS_reg.h
 *
 * Created: 9/30/2023 11:29:21 AM
 *  Author: mahmo
 */ 


#ifndef TIMERS_REG_H_
#define TIMERS_REG_H_

/*Timer0 Registers*/
#define OCR0              *((volatile uint8*)0x5C)        /* Output compare match register         */

#define TIMSK             *((volatile uint8*)0x59)	      /* Timer mask register                   */
#define TIMSK_TOIE0         0                             /* Timer0 overflow interrupt enable      */
#define TIMSK_OCIE0         1                             /* Timer0 compare match interrupt enable */

#define TCCR0             *((volatile uint8*)0x53)        /*    Timer counter control register 0   */
#define TCCR0_COM01         5						      /*    Compare match output mode bit 1    */
#define TCCR0_COM00         4                             /*    Compare match output mode bit 0    */
#define TCCR0_WGM00         6                             /*    Waveform generation mode bit 0     */
#define TCCR0_WGM01         3                             /*    Waveform generation mode bit 1     */

#define TCNT0             *((volatile uint8*)0x52)        /*    Timer counter 0 register           */

/*End of timer0 registers*/

/*Timer1 Registers*/
#define TCCR1A            *((volatile uint8*)0x4F)    
#define TCCR1A_WGM10      0 
#define TCCR1A_WGM11      1
#define TCCR1A_COM1B0     4
#define TCCR1A_COM1A0     6
#define TCCR1A_COM1B1     5
#define TCCR1A_COM1A1     7

#define TCCR1B			  *((volatile uint8*)0x4E) 
#define TCCR1B_WGM12      3
#define TCCR1B_WGM13      4	

#define OCR1A            *((volatile uint16*)0x4A)
#define OCR1B            *((volatile uint16*)0x48)

#define ICR1             *((volatile uint16*)0x46) 

#define TCNT1			 *((volatile uint16*)0x4C)


#endif /* TIMERS_REG_H_ */