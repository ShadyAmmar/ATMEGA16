/*
 * EEPROM.c
 *
 * Created: 9/22/2018 9:25:11 PM
 *  Author: Shady
 */

#define  F_CPU 8000000UL
#include "EEPROM.h"
#include "TWI.h" 
#include <util/delay.h>
#include <stdio.h>	//debug
#include "LCD.h"	//debug
unsigned char x;

void EEPROM_vdInit (){
	TWI_vdInit() ;
}

//u16Location: A2,A1,A0,--8bit addr--
unsigned char EEPROM_u8WriteByte (int u16Location , unsigned char u8Data){
	TWI_vdSendStart() ;											//Send Start bit
	if (TWI_u8CheckStatus(Start)==True)							//if start transmitted successfully
	{
		x = 0xA0 ;												//EEPROM addr
		x |= ((u16Location&0x0700)>>7) ;						//addr + mask A2,A1,A0 + zero(for Write)
		TWI_vdWrite(x) ;										//Sending: 1010(EEPROM addr)+A2,A1,A0(page addr)+zero(write)
		if (TWI_u8CheckStatus(SLA_W_ACK_MT)==True)					//if addr+W/R transmitted successfully
		{
			TWI_vdWrite((unsigned char) u16Location) ;			//send address of word in the page (considered data)
			if (TWI_u8CheckStatus(DataACK_MT)==True)				//if data transmitted successfully
			{
				TWI_vdWrite(u8Data) ;							//send data to save in EEPROM
				if (TWI_u8CheckStatus(DataACK_MT)==True)			//if data transmitted successfully	
				{
					TWI_vdSendStop() ;							//send STOP
					return True ;								//return True to indicate succ. write in EEPROM
				}
				
			}
		}
	}
	return False ;
}


unsigned char EEPROM_u8ReadByte(int u16Location , unsigned char *ptr){
	TWI_vdSendStart() ;											//Send Start bit
	if (TWI_u8CheckStatus(Start)==True)							//if start transmitted successfully
	{
		x = 0xA0 ;												//EEPROM addr
		x |= ((u16Location&0x0700)>>7) ;						//addr + mask A2,A1,A0 + zero(for Write)
		TWI_vdWrite(x) ;										//Sending: 1010(EEPROM addr)+A2,A1,A0(page addr)+zero(write)
		if (TWI_u8CheckStatus(SLA_W_ACK_MT)==True)					//if addr+W/R transmitted successfully
		{
			TWI_vdWrite((unsigned char) u16Location) ;			//send address of word in the page (considered data)
			if (TWI_u8CheckStatus(DataACK_MT)==True)				//if data transmitted successfully
			{
				TWI_vdSendStart() ;								//Send Repeated Start to commun. again with EEPROM to receive
				if (TWI_u8CheckStatus(RStart)==True)			//if repeated start transmitted successfully
				{
					x = 0xA0 ;									//EEPROM addr		
					x|= ((u16Location&0x0700)>>7) ;				//addr + mask A2,A1,A0 + zero
					x |= READ;									//addr + mask A2,A1,A0 + 1(to Read)
					TWI_vdWrite(x) ;							//sending addr
					if (TWI_u8CheckStatus(SLA_R_ACK_MR)==True)		//if 
					{
						*ptr = TWI_u8ReadwithNoAck() ;
						if (TWI_u8CheckStatus(DataNACK_MR)==True)
						{
							TWI_vdSendStop() ;
							return True ;
						}
					}
					
				}
				
			}
		}
	}
	return False ;
}

unsigned char EEPROM_u8WriteString (int u16Location , char* data){
	int i;
	for(i=0;data[i]!='\0';i++){
		if(!EEPROM_u8WriteByte( u16Location++ , data[i])) return False;
		_delay_ms(100);
	}
	EEPROM_u8WriteByte( u16Location , data[i]);
	_delay_ms(100);
	return i;
}

unsigned char EEPROM_u8ReadString(int u16Location , unsigned char* ptr){
	unsigned char data = 1; int i=0;
	while(data != '\0'){
		if(!EEPROM_u8ReadByte(u16Location++,&ptr[i])) return False; 
		data = ptr[i];
		i++;
	}
	return (i-1);
}