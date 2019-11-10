
#include "DIO.h"
#include "LCD.h"
#define F_CPU 8000000ul
#include "util/delay.h"


void LCD_vdSendCom(unsigned int com)
{
	DIO_vdWritePin('C',6,0);        //reset the EN=0
	DIO_vdWritePin('C',7,0);		//set the R/S=0 for command
	DIO_vdWritePort('A',com);		//writing the command
	_delay_ms(200);
	DIO_vdWritePin('C',6,1);        //set the EN=1
	_delay_ms(200);
}

void LCD_vdInit()
{
	LCD_vdSendCom(MODE_8_BITS);
	LCD_vdSendCom(DISPLAY_ON_CURSOR);
	//LCD_vdSendCom(CLEAR);
}

void LCD_vdWriteChar(unsigned int data)
{
	DIO_vdWritePin('C',6,0);        //reset the EN=0
	DIO_vdWritePin('C',7,1);		//set the R/S=1 for data
	DIO_vdWritePort('A',data);		//writing the data
	_delay_ms(200);
	DIO_vdWritePin('C',6,1);       //set the EN=1
	_delay_ms(200);
}

void LCD_vdWriteString(char *ptr)
{
	for (int i=0;ptr[i]!='\0';i++)
	{
		LCD_vdWriteChar(ptr[i]);
	}
}