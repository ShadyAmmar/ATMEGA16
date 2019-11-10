/*
 * LED.c
 *
 * Created: 8/12/2018 2:04:36 PM
 *  Author: Shady
 */ 

#include <avr/io.h>
#include "LED.h"
#include "DIO.h"

static unsigned char LEDstatus[8] = {0,0,0,0,0,0,0,0};

void LEDon(unsigned char port,unsigned char pin){
	DIO_vdWritePin(1,port,pin);
	LEDstatus[pin] = 1;
}

void LEDoff(unsigned char port,unsigned char pin){
	DIO_vdWritePin(0,port,pin);
	LEDstatus[pin] = 0;
}

void LEDtoggle(unsigned char port,unsigned char pin){
	if(LEDstatus[pin]){
		LEDoff(port,pin);
	}else{
		LEDon(port,pin);
	}
	
}

void LEDrefresh(unsigned char port,unsigned char pin){
	DIO_vdWritePin(LEDstatus[pin],port,pin);
}