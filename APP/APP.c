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
#include "EEPROM.h"
#include <stdio.h>
#include <avr/io.h> //debugging
#include <util/delay.h>


void APP_vdDefaultPASSinit(){
	char* defaultPASS = "1234";
	unsigned char PASS[10];
// 	unsigned char u16Location = ADDRESS_EEPROM;
// 	int i;
// 	for(i=0;defaultPASS[i]!='\0';i++){
// 		EEPROM_u8WriteByte(u16Location,defaultPASS[i]);
// 		_delay_ms(100);
// 		u16Location++;
// 	}
// 	EEPROM_u8WriteByte(u16Location,defaultPASS[i]);
// 	_delay_ms(100);
// 	u16Location = ADDRESS_EEPROM;
// 	unsigned char data = 1;
// 	for(i=0;data != '\0';i++){
// 		EEPROM_u8ReadByte(u16Location++,&data);
// 		_delay_ms(100);
// 		LCD_vdWriteChar(data);
// 	}
	EEPROM_u8WriteString(ADDRESS_EEPROM,defaultPASS);
	EEPROM_u8ReadString(ADDRESS_EEPROM,PASS);
	//LCD_vdWriteString(PASS);
}

void APP_vdDONE(){
	SPI_vdSendByte('D');
}

void APP_vdCall(){
	unsigned char msg,action;
	msg = SPI_u8Receive();
	if(msg == 'A'){
		LEDtoggle('D',4);
		action = SPI_u8Receive();
		switch(action){
			case LOCK:
				PORTD = LOCK;
				break;
			case UNLOCK:
				PORTD = UNLOCK;
				break;
			case LOCK_S:
				PORTD = LOCK_S;
				break;
			case CH_PASS:
				PORTD = CH_PASS;
				break;
			case WRONGPASS:
				PORTD = WRONGPASS;
				break;
			case GETPASS:
				PORTD = GETPASS;
				unsigned char password[10];
				unsigned char size; 
				size = EEPROM_u8ReadString(ADDRESS_EEPROM,password);
				for(int i=0;i<=size;i++){
					SPI_vdSendByte(password[i]);
					_delay_ms(1);
				}
				break;
		}
	}
	LEDtoggle('D',4);
}

