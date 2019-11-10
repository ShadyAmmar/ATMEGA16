/*
 * APP.c
 *
 * Created: 9/2/2018 3:06:08 PM
 *  Author: Shady
 */ 

#define F_CPU 8000000UL
#include "APP.h"
#include "KEYPAD.h"
#include "LCD.h"
#include "BTN.h"
#include <stdio.h>
#include "LED.h" //debug
#include "SPI.h" /*simple commmunication protocols (unlike CAN,LIN,..) can be used in APP without interface*/
#include <avr/io.h> //debugging
#include <util/delay.h>

void APP_vdWelcome(){
	LCD_vdWriteStringPos("Counter:",LCD_ROW_1,0);
	LCD_vdWriteStringPos("Button:",LCD_ROW_2,0);
}

void APP_vdCounter(){
	char buffer[5];
	static unsigned char count = 0;
	//SPI_vdSendByte('c');
	//_delay_ms(100);
	//SPI_vdSendByte(count);
	sprintf(buffer,"%d",count);
	LCD_vdWriteStringPos(buffer,LCD_ROW_1,8);
	count++;
}

void APP_vdBTN(){
	static unsigned char btnoldstatus = released;
	char buffer[5];
	static unsigned char count = 0; 
	unsigned char btnstatus = BTN_u8getStatus('A',0);
	
	if(btnoldstatus == pressed && btnstatus==released){
		count++;
		sprintf(buffer,"%d",count);
		LCD_vdWriteStringPos(buffer,LCD_ROW_2,8);
		//SPI_vdSendByte('b');
		//_delay_ms(100);
		SPI_vdSendByte(count);
	}
	
	btnoldstatus = btnstatus;
}

