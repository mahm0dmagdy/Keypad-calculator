/*
 * TIMERS_private.h
 *
 * Created: 9/30/2023 11:29:58 AM
 *  Author: mahmo
 */ 


#ifndef TIMERS_PRIVATE_H_
#define TIMERS_PRIVATE_H_


#define NORMAL		1u
#define CTC			2u
#define PWM			3u
#define FASTPWM		4u

#define PRESCALER_MASK 0b11111000
#define DIVISION_BY_1    0b001
#define DIVISION_BY_4    0b011
#define DIVISION_BY_8    0b010
#define DIVISION_BY_64   0b011
#define DIVISION_BY_256  0b110
#define DIVISION_BY_1024 0b110

#define OC0_MASK         0b11001111
#define INVERTING        1u
#define NONINVERTING     2u
#define DISCONNECTED     3u
#define SET              4u
#define TOGGLE           5u
#define CLEAR            6u

#endif /* TIMERS_PRIVATE_H_ */