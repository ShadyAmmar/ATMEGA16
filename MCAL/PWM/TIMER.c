#include "avr/io.h"
#include "TIMER.h"
#include <avr/interrupt.h>	

unsigned char duty;
//***************************************************************************************
void TIMER_vdSetDutyCycle(unsigned char input)
{
	if(input>=0&&input<=100)
	{
		duty=(input*256)/100;
	}
	else
		duty=128;		//50% duty cycle
}
//***************************************************************************************
void TIMER_vdInit(unsigned char mode)
{
	if(mode == NORMAL)
	{
		
	}
	else if(mode == CTC)
	{
		
	}
	else if(mode == FAST_PWM)
	{
		//OVERFLOW FOR TIMER 0
		TIMSK=1;
		DDRB |= (1<<PB3);
		
		//50% duty cycle
		OCR0=128;
		
		//SELECT MODE OF OPREATION(NORMAL / CTC /FAST_PWM /PHASE_CORRECT_PWM)
		TCCR0|=(1<<3);
		TCCR0|=(1<<6);
		
		//TIMER CLK TO 1KHZ
		TCCR0|=(1<<0);
		TCCR0&=~(1<<1);
		TCCR0|=(1<<2);
		
		//CHOOSE THE MODE OF FAST_PWM (INVERTING /NON_INVERTING)
		TCCR0&=~(1<<4);
		TCCR0|=(1<<5);
		
		//GLOBAL INTERUPT ENABLE
		SREG |=(1<<7);
	}
	else if (mode == PHASE_CORRECT_PWM)
	{
		
	}
}
//***************************************************************************************
ISR(TIMER0_OVF_vect)
{
	OCR0 = duty;
}
