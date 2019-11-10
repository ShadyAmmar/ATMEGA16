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
#include "LED.h" //debug
#include "SPI.h" /*simple communication protocols (unlike CAN,LIN,..) can be used in APP without interface*/
#include <stdio.h>
#include <avr/io.h> //debugging
#include <util/delay.h>

void APP_vdWelcome(){
	LCD_vdWriteStringPos("Counter:",LCD_ROW_1,0);
	LCD_vdWriteStringPos("Button:",LCD_ROW_2,0);
}

void APP_vdCall(){
	unsigned char msg;
	static unsigned char btn;
	static unsigned char counter;
	char buffer[5];
	msg = SPI_u8Receive();
	switch(msg){
		case 'b':
		btn = SPI_u8Receive();
		break;
		case 'c':
		counter = SPI_u8Receive();
		break;
	}
	sprintf(buffer,"%d",counter);
	LCD_vdWriteStringPos(buffer,LCD_ROW_1,8);	
	sprintf(buffer,"%d",btn);
	LCD_vdWriteStringPos(buffer,LCD_ROW_2,8);
}

