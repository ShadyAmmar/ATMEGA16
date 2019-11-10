
#include "DIO.h"
#include "LCD.h"
#define F_CPU 8000000UL
#include "util/delay.h"
#include <avr/io.h>	//debug
static unsigned char mode = 0;

void LCD_vdSendCom(unsigned char command){
	switch(mode){
		case MODE_8_BITS:
		DIO_vdWritePin(0,'B',0);        //reset the EN=0
		DIO_vdWritePort(command,'A');	//writing the command
		DIO_vdWritePin(0,'B',1);		//set the R/S=0 for command
		DIO_vdWritePin(1,'B',0);        //set the EN=1
		_delay_ms(1);					//wait at least 450ns
		DIO_vdWritePin(0,'B',0);        //reset the EN=0
		_delay_ms(6);					//Wait 5ms for command writes, and 200us for data writes
		break;
		
		case MODE_4_BITS:
		DIO_vdWritePin(0,'B',0);			//reset the EN=0
		DIO_vdWritePort((DIO_u8ReadPort('A') & 0x0F) | (command & 0xF0),'A');//Write the HIGHBYTE of data on (D7:4)
		DIO_vdWritePin(0,'B',1);			//set the R/S=0 for commands
		DIO_vdWritePin(1,'B',0);			//set the EN=1
		_delay_ms(1);						//wait at least 450ns
		DIO_vdWritePin(0,'B',0);			//reset the EN=0
		_delay_ms(6);						//Wait 5ms for command writes, and 200us for data writes.
		
		DIO_vdWritePort((DIO_u8ReadPort('A') & 0x0F) | (command << 4),'A');	//Write the LOWBYTE of data on (D7:4)
		DIO_vdWritePin(1,'B',0);			//set the EN=1
		_delay_ms(1);						//wait at least 450ns
		DIO_vdWritePin(0,'B',0);			//reset the EN=0
		_delay_ms(6);						//Wait 5ms for command writes, and 200us for data writes.
		break;
	}
}

void LCD_vdInit(unsigned char MODE){
	_delay_ms(20);
	mode = MODE;
	switch(mode){
		case MODE_8_BITS:
		LCD_vdSendCom(0x30);								/* send for 8 bit initialization of LCD  */
		LCD_vdSendCom(BIT8_2LINES_5_7FONT);					/* 2 line, 5*7 matrix in 8-bit mode */
		LCD_vdSendCom(DISPLAY_ON_CURSOR_ON_BLINK_OFF);		/* Display on - cursor on - blinking off */
		LCD_vdSendCom(SHIFT_CURSOR_ON_SHIFT_DISPLAY_OFF);   /* Increment cursor (shift cursor to right)*/
		LCD_vdSendCom(CLEAR_HOME);							/* Clear display screen*/
		_delay_ms(2);										/* Clear display command delay> 1.63 ms */
		LCD_vdSendCom(LCD_ROW_1);							/* Cursor at home position */
		break;
		
		case MODE_4_BITS:
		LCD_vdSendCom(0x02);								/* send for 4 bit initialization of LCD  */
		LCD_vdSendCom(BIT4_2LINES_5_7FONT);					/* 2 line, 5*7 matrix in 4-bit mode */
		LCD_vdSendCom(DISPLAY_ON_CURSOR_ON_BLINK_OFF);		/* Display on - cursor on - blinking off */
		LCD_vdSendCom(SHIFT_CURSOR_ON_SHIFT_DISPLAY_OFF);   /* Increment cursor (shift cursor to right)*/
		LCD_vdSendCom(CLEAR_HOME);							/* Clear display screen*/
		_delay_ms(2);										/* Clear display command delay> 1.63 ms */
		LCD_vdSendCom(LCD_ROW_1);							/* Cursor at home position */
		break;
	}
}


void LCD_vdWriteChar(unsigned char data)
{
	switch(mode){
		case MODE_8_BITS:
			DIO_vdWritePin(0,'B',0);        //reset the EN=0
			DIO_vdWritePort(data,'A');		//writing the data
			DIO_vdWritePin(1,'B',1);		//set the R/S=1 for data
			DIO_vdWritePin(1,'B',0);        //set the EN=1
			_delay_ms(1);					//wait at least 450ns
			DIO_vdWritePin(0,'B',0);        //reset the EN=0
			_delay_ms(1);					//Wait 5ms for command writes, and 200us for data writes.			
			break;
			
		case MODE_4_BITS:
			DIO_vdWritePin(0,'B',0);			//reset the EN=0
			DIO_vdWritePort((DIO_u8ReadPort('A') & 0x0F) | (data & 0xF0),'A');	//Write the HIGHBYTEof data on (D7:4)
			DIO_vdWritePin(1,'B',1);			//set the R/S=1 for data
			DIO_vdWritePin(1,'B',0);			//set the EN=1
			_delay_ms(1);						//wait at least 450ns
			DIO_vdWritePin(0,'B',0);			//reset the EN=0
			_delay_ms(1);						//Wait 5ms for command writes, and 200us for data writes.
			DIO_vdWritePin(1,'B',0);			//set the EN=1 (not written in datasheet but must be)
			DIO_vdWritePort((DIO_u8ReadPort('A') & 0x0F) | (data << 4),'A');		//Write the LOWBYTEof data on (D7:4)
			_delay_ms(1);						//wait at least 450ns
			DIO_vdWritePin(0,'B',0);			//reset the EN=0
			_delay_ms(1);						//Wait 5ms for command writes, and 200us for data writes.
			break;
	}
}

void LCD_vdWriteString(char *ptr)
{
	for (int i=0;ptr[i]!='\0';i++)
	{
		LCD_vdWriteChar(ptr[i]);
	}
}

void LCD_vdWriteCharPos(unsigned char data,unsigned char row,unsigned char col){
		LCD_vdSendCom(row|col);	//set the cursor
		LCD_vdWriteChar(data);
}

void LCD_vdWriteStringPos(char *ptr,unsigned char row,unsigned char col)
{
	unsigned char temp = col;
	for (int i=0;ptr[i]!='\0';i++)
	{
		LCD_vdWriteCharPos(ptr[i],row,temp++);
	}
}

void LCD_vdClear(){
	LCD_vdSendCom(CLEAR_HOME);
	_delay_ms(2);			/* Clear display command delay> 1.63 ms */
}

void LCD_Custom_Char (unsigned char loc, unsigned char *msg)
{
	unsigned char i;
	if(loc<8)
	{
		LCD_vdSendCom (0x40 + (loc*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)	/* Write 8 byte for generation of 1 character */
		LCD_vdWriteChar(msg[i]);
	}
}