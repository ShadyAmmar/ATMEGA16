/*
 * SPI_interrupt.c
 *
 * Created: 9/9/2018 8:36:53 PM
 * Author : Shady
 */ 

#include "DIO.h"
#include "BTN.h"
#include "LED.h"
#include "config.h"
#include "LCD.h"
#include "BTN.h"
#include "SPI.h"
#include <stdio.h>
#include <avr/io.h>  //for debugging

void APP_vdCall(unsigned char msg){
	char buffer[5];
	
	sprintf(buffer,"%d",msg);
	LCD_vdWriteStringPos(buffer,LCD_ROW_2,8);
}

int main(void)
{
	/*initialization*/
    DIO_vdInit();
    LCD_vdInit(MODE_4_BITS);
    SPI_vdInit(SLAVE,APP_vdCall);
	
	LCD_vdWriteStringPos("Button:",LCD_ROW_2,0);
	
    while (1) 
    {
    }
}

