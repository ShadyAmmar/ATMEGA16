/*
 * ADC.c
 *
 * Created: 9/16/2018 11:19:48 PM
 *  Author: Shady
 */ 

#include <avr/io.h>

void ADC_vdInit(){
	ADMUX |= (1<<REFS0);	//AVCC with external capacitor at AREF pin
	
	//ADMUX |= (1<<ADLAR);	//left adjust the result
	
	//ADCSRA &= ~(1<<ADATE);  //NOT single mode which can be choosed by setting this to 1 and choosing the mode from ADTS0 in SFIOR
	
	//ADCSRA |= (1<<ADPS1);	//XTAL freq/4
	
	//SFIOR |= (1<<ADTS0);	//analog comprator mode
	
	ADCSRA |= (1<<ADEN);	//Enable ADC
}

int ADC_intRead(unsigned char pin){
	//pin : 0->ADC0 / 1->ADC1 / ...
	ADMUX |= (0b00011111)&(pin);	//Choosing analog channel
	ADCSRA |= (1<<ADSC);			//start conversion
	while (!(ADCSRA&(1<<4)));		//wait until finishing conversion
	
	int reading = 0;
	reading = ADCL;
	reading |= (ADCH<<8);
	return reading;
}
