/*
 * TWI.c
 *
 * Created: 9/16/2018 6:44:33 PM
 *  Author: Shady
 */ 

#include <avr/io.h>
#include "TWI.h"

void TWI_vdInit(){
	//clk = 200 KHz
	TWBR = 24;	
	TWSR &= ~(1<<TWPS1)|~(1<<TWPS0);
	
	//set address for slave mode
	TWSR = 10;
	
	//Enable Ack ( has no use here we can set it in ReceiveWithAck or ReceiveWithNoAck )
	//TWCR |= (1<<TWEA);
	
	//Enable TWI
	TWCR |= (1<<TWEN);
}

void TWI_vdSendStart(){
	//Enable TWI , Clear interrupt flag to start operation , Send Start
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN) ;
	//waiting until Start is transmitted 
	while (!(TWCR & (1<<TWINT)));
}

void TWI_vdSendStop(){
	//Enable TWI , Clear interrupt flag to start operation , Send Stop
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void TWI_vdWrite(unsigned char data){
	//writing data in TWDR
	TWDR = data;
	//Enable TWI , Clear interrupt flag to start operation
	TWCR = (1<<TWINT)|(1<<TWEN);
	//wait until data is transmitted & ACK or NACK has been received
	while (!(TWCR & (1<<TWINT)));
}

unsigned char TWI_u8CheckStatus(unsigned char status){
	if ( (TWSR & 0b11111000) == status)
	{
		return True ;
	}
	else
	{
		return False ;
	}
}

unsigned char TWI_u8ReadwithNoAck(){
	//Enable TWI , No ACK , Clear interrupt flag to start operation
	TWCR &= ~(1<<TWEA);		//No ACK will be transmitted from me(master) after receiving
	TWCR = (1 << TWEN) | (1 << TWINT) ;
	//wait until data is transmitted & ACK or NACK has been received
	while ( !( TWCR&(1 << TWINT) ) ) ;
	return TWDR ;
}

unsigned char TWI_u8ReadwithAck(){
	//Enable TWI , ACK , Clear interrupt flag to start operation
	TWCR |= (1<<TWEA);		// ACK will be transmitted from me(master) after receiving
	TWCR = (1 << TWEN) | (1 << TWINT) ;
	//wait until data is transmitted & ACK or NACK has been received
	while ( !( TWCR&(1 << TWINT) ) ) ;
	return TWDR ;
}
