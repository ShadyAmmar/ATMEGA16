
#ifndef LCD_H_
#define LCD_H_

#define MODE_8_BITS 0x38
#define DISPLAY_ON_CURSOR 0x0E
#define LCD_ROW_1 0x80
#define LCD_ROW_2 0xC0
#define LCD_MOVE_CURCER_RIGHT 0x06
#define CLEAR	0x01

void LCD_vdInit(void);
void LCD_vdWriteChar(unsigned int);
void LCD_vdSendCom(unsigned int);
void LCD_vdWriteString(char*);



#endif /* LCD_H_ */