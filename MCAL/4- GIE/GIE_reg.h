/*
 * GIE_reg.h
 *
 * Created: 9/13/2023 2:35:43 AM
 *  Author: mahmo
 */ 


#ifndef GIE_REG_H_
#define GIE_REG_H_

#define SREG				*((volatile uint8*) 0x5F)		/* Status register */
#define SREG_I                7u							/* Interrupt bit */



#endif /* GIE_REG_H_ */