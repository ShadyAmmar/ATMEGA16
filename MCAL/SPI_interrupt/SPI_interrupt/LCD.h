/*
 * LCD.h
 *
 * Created: 12/09/2015 12:47:33 م
 *  Author: eslam
 */ 


#ifndef LCD_H_
#define LCD_H_

//Pins: Vss(Ground) - Vdd(Power 5v) - Contrast Voltage (usually less than 1V) -
//		"R/S" Register Select ( 1 for Data Write, 0 for Command Write)
//		"R/W" Read/Write (1 for Read, 0 for Write) usually grounded for write only
		//The read function is usually used to poll the "Busy Flag" which appears on D7 while
		//the device is incapable of accepting a command (it's busy..get it).
		//However, this function may be ignored by simply waiting the maximum amount of time for each
		//command to complete (most are completed in less than 200us).
//		"EN" Enable line (Pulsing high latches a command or data _|¯|_ )
//		Data Pins (D0­D7)
//		(Optional) Back­light Anode and Cathode, NC, or Not There at All


#define MODE_8_BITS 0
#define MODE_4_BITS 1

//Clear Display and Home the Cursor
#define CLEAR_HOME 0x01
//Return Cursor and LCD to Home Position
#define RETURN_CURSOR_HOME 0x02					//don't Clear
//Set Cursor Move Direction
#define SHIFT_CURSOR_ON_SHIFT_DISPLAY_OFF 0x06	//shift cursor right
#define SHIFT_CURSOR_ON_SHIFT_DISPLAY_ON 0x07	//display will be shifted when write so nothing will appear
//Enable Display/Cursor
#define DISPLAY_ON_CURSOR_ON_BLINK_OFF 0x0E
#define DISPLAY_ON_CURSOR_ON_BLINK_ON 0x0F
//Set Interface Length
#define BIT4_2LINES_5_7FONT 0x28
#define BIT8_2LINES_5_7FONT 0x38
//Move Cursor into CGRAM	0b01AA AAAA
//Move Cursor into Display	0b1AAA AAAA
#define LCD_ROW_1 0x80	  //0b1000 0000
#define LCD_ROW_2 0xC0	  //0b1100 0000
#define LCD_ROW_3 0x94
#define LCD_ROW_4 0xD4



void LCD_vdInit(unsigned char MODE);
void LCD_vdSendCom(unsigned char);		
void LCD_vdWriteChar(unsigned char data);
void LCD_vdWriteCharPos(unsigned char,unsigned char row,unsigned char col);
void LCD_vdWriteString(char*);
void LCD_vdWriteStringPos(char*,unsigned char row,unsigned char col);
void LCD_vdClear();
void LCD_Custom_Char (unsigned char loc, unsigned char *msg);

#endif /* LCD_H_ */