/*
 * TIMER_NormalMode.c
 *
 * Created: 8/16/2018 12:34:56 PM
 * Author : Shady
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
    DDRC = 0xFF;			//output for 7seg
	PORTC = 0;
	/*Timer initialization (Normal Mode)*/
	TCCR0 |= (1<<0); TCCR0 &= ~(1<<1); TCCR0 |= (1<<2);		//clock select: CLK/1024
	TIMSK |= (1<<0);										//Overflow Interrupt Enable
	SREG |= (1<<7);											//Global Interrupt Enable
	TCCR0 &= ~(1<<6); TCCR0 &= ~(1<<3);						//mode: Normal Mode
    while (1) 
    {
    }
}

ISR(TIMER0_OVF_vect){
	static unsigned char count = 0;
	if(count<10){
		PORTC = count;
		count++;
	}else{
		PORTC = 0;
		count = 1;
	}
}