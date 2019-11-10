/*
 * TIMER0.c
 *
 * Created: 8/17/2018 12:02:50 PM
 *  Author: Shady
 */ 
#include <avr/interrupt.h>
#include "TIMER0.h"

static void (*fptr)(void);

void TIMER0_vdInit(void (*ptr)(void)){
/*TIMER0 initialization*/
TCCR0 |= (1<<0); TCCR0 &= ~(1<<1); TCCR0 |= (1<<2);		//clock select: CLK/1024
TIMSK |= (1<<1);										//Output compare Interrupt Enable
TCCR0 &= ~(1<<6); TCCR0 |= (1<<3);						//mode: CTC
OCR0 = 10;												// F_CPU/pre_scalar * 10 ms
SREG |= (1<<7);											//Global Interrupt Enable

/*passing the Tick increasing function to ISR*/
fptr = ptr;
}

ISR(TIMER0_COMP_vect){
	fptr();
}