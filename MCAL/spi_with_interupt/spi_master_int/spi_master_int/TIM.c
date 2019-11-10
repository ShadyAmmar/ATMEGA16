#include <avr/io.h>
#include <avr/interrupt.h>

static volatile void (*gptr)(void);
void TIM_vdInit(void (*ptr)(void))
{
	gptr=ptr;
	
	//OVERFLOW FOR TIMER 0
	TIMSK=(1<<OCIE0);
	
	//SELECT MODE OF OPREATION(NORMAL MODE / CTC MODE)
	TCCR0|=(1<<3);
	TCCR0&=~(1<<6);
	
	//TIMER CLK TO 1KHZ
	TCCR0|=(1<<0);
	TCCR0&=~(1<<1);
	TCCR0|=(1<<2);
	
	//SET THE COMPAR VALUE TO 10(MAKE INTURRPT EVERY 10ms )
	OCR0 =10;
	
	//GLOBAL INTERUPT ENABLE
	SREG |=(1<<7);
}

ISR(TIMER0_COMP_vect)
{
	gptr();
}