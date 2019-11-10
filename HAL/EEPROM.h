/*
 * EEPROM.h
 *
 * Created: 9/22/2018 9:25:22 PM
 *  Author: Shady
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

void EEPROM_vdInit ();
unsigned char EEPROM_u8WriteByte (int u16Location , unsigned char u8Data);
unsigned char EEPROM_u8ReadByte (int u16Location , unsigned char *ptr);
unsigned char EEPROM_u8WriteString (int u16Location , char* data);
unsigned char EEPROM_u8ReadString(int u16Location , unsigned char *ptr);

#endif /* EEPROM_H_ */