/*
 * UART.c
 *
 * Created: 9/1/2018 3:02:09 PM
 *  Author: Shady
 */ 

#include <avr/io.h>
#include "UART.h"

void UART_vdInit(unsigned int baud){
	/*set baud rate*/
	//UBBR = fosc/16/BAUD -1	//Asynch. Normal Mode
	//UBBR = fosc/8/BAUD -1		//Asynch. Double Speed Mode
	unsigned int temp = F_CPU/16/baud - 1; 
	UBRRH = (unsigned char) (temp>>8);
	UBRRL = (unsigned char) (temp);
	
	/*UCSRA Control and status register A*/
	//RXC-TXC-UDRE-FE-DOR-PE-U2X-MPCM

	/*UCSRB Control and status register B*/
	//RXCIE-TXCIE-UDRIE-RXEN-TXEN-UCSZ2-RXB8-TXB8
	UCSRB |= (1<<RXEN)|(1<<TXEN);					//Enables UART receiver & transmitter

	/*UCSRC Control and status register C*/
	//URSEL-UMSEL-UPM1-UPM0-USBS-UCSZ1:0-UCPOL-UCSRC
	//Must write 1 to URSEL before modifying because this register shares the same
	//location as UBRRH

}

void UART_vdSendByte(unsigned char data){
	while ( !( UCSRA & (1<<UDRE)) );		//wait for empty transmit buffer (NOTE:
											//it doesn't mean end of transmission because 
											//Transmission shift reg. may still transmitting the data
											//but i can write new data to transmit after the current 
											//in the UDR buffer reg.)
	UDR = data;
}

void UART_vdSendu8asASCI(unsigned char data){
	unsigned char temp[3]; unsigned char i; unsigned char temp2 = data;
	for(i=0;i<3;i++){
		temp[i] = temp2%10;
		temp2 /= 10;
	} 
	if(temp[2]==0){
		if(temp[1]==0){
			UART_vdSendByte(temp[0]+48);
		}else{
			UART_vdSendByte(temp[1]+48);
			UART_vdSendByte(temp[0]+48);
		}		
	}else{
		UART_vdSendByte(temp[2]+48);
		UART_vdSendByte(temp[1]+48);
		UART_vdSendByte(temp[0]+48);
	}
	
}

unsigned char UART_u8ReceiveByte(){
	while ( !(UCSRA & (1<<RXC)) );			//Wait for data to be received
	return UDR;
}