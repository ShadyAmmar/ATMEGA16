/*
 * CFile1.c
 *
 * Created: 8/12/2018 1:25:34 PM
 *  Author: Shady
 */ 

#include <avr/io.h>
#include "DIO.h"

void DIO_vdInit(){
	DDRC = 0b00001111;		//Keypad
	DDRA = 0xF0; PORTA=0;	DDRB |=(1<<0)|(1<<1);	//btn + LCD
	/*PORTB 4 5 6 7 pins is for SPI*/	
	DDRD = 0xFF; PORTD=0;	//debug
	
}

unsigned char DIO_u8ReadPin(unsigned char port,unsigned char pin){
	switch(port){
		case 'A':
			return (PINA & (1<<pin))?1:0;
		case 'B':
			return (PINB & (1<<pin))?1:0;
		case 'C':
			return (PINC & (1<<pin))?1:0;
		case 'D':
			return (PIND & (1<<pin))?1:0;
	}
	return 0;
}

unsigned char DIO_u8ReadPort(unsigned char port){
	switch(port){
		case 'A':
		return (PINA);
		case 'B':
		return (PINB);
		case 'C':
		return (PINC);
		case 'D':
		return (PIND);
	}
	return 0;
}

void DIO_vdWritePin(unsigned char data,unsigned char port,unsigned char pin){
	switch(port){
		case 'A':
			if(data){
				PORTA |= (1<<pin); 
			}else{
				PORTA &= ~(1<<pin);
			}
			break;
		case 'B':
			if(data){
				PORTB |= (1<<pin);
			}else{
				PORTB &= ~(1<<pin);
			}
			break;
		case 'C':
			if(data){
				PORTC |= (1<<pin);
			}else{
				PORTC &= ~(1<<pin);
			}
			break;
		case 'D':
			if(data){
				PORTD |= (1<<pin);
			}else{
				PORTD &= ~(1<<pin);
			}
			break;
	}
}

void DIO_vdWritePort(unsigned char data,unsigned char port){
	switch(port){
		case 'A':
			if(data){
				PORTA = data;
			}else{
				PORTA = 0;
			}
			break;
		case 'B':
			if(data){
				PORTB = data;
			}else{
				PORTB = 0;
			}
			break;
		case 'C':
			if(data){
				PORTC = data;
			}else{
				PORTC = 0;
			}
			break;
		case 'D':
			if(data){
				PORTD = data;
			}else{
				PORTD = 0;
			}
			break;
	}
}