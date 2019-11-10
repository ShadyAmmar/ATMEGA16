/*
 * Sch.c
 *
 * Created: 8/17/2018 12:11:47 PM
 *  Author: Shady
 */ 
#include "DIO.h"
#include "TIMER0.h"
#include "BTN.h"
#include "LED.h"
#include "config.h"
#include "Sch.h"
#include "KEYPAD.h"
#include "LCD.h"
#include "APP.h"
#include "BTN.h"
#include "SPI.h"
#include <avr/io.h>  //for debugging	

static unsigned char c = 0;

void Sch_vdInit(){
	
	DIO_vdInit();
	TIMER0_vdInit(SCH_vdTick);
	LCD_vdInit(MODE_4_BITS);
	SPI_vdInit(MASTER);
	APP_vdWelcome();
	SPI_vdSSenable();
}

void SCH_vdTick(){
	c++;
}
	
void Sch_vdEngine(){
	static unsigned char temp = 0;
	if(((c%2)==0) && (c-temp)){
		BTN_vdRead('A',0);
		APP_vdBTN();
		
		temp = c;
	}
	if( ((c%400)==0) && ( (c-temp)|((c%2)==0) ) ){
		APP_vdCounter();
		
		temp = c;
	}	
}