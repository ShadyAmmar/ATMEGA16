
/*
 * SPI.c
 *
 * Created: 9/3/2018 12:23:04 PM
 *  Author: Shady
 */ 

#include <avr/io.h>
#include "SPI.h"
#include "LCD.h" //debug

static unsigned char mode;

//Registers summary in .h file
void SPI_vdInit(unsigned char MODE){
	mode = MODE;
	switch(mode){
		case MASTER:
			/*set DIO directions in DIO file*/
			//MOSI -> output	SCK->output
			//SS->output(even if I dont use to protect from driven low and turn the SPI to slave mode)
			//MISO ->input
			DDRB |=(1<<SS)|(1<<MOSI)|(1<<SCK);		PORTB |= (1<<SS);
			DDRB &= ~(1<<MISO);
			
			SPCR |= (1<<MSTR);		//Enable Master mode
			//SPCR |= (1<<DORD);		//LSB first
			//SPCR |= (1<<CPOL);		//Falling LE(Leading Edge)
			//SPCR |= (1<<CPHA);		//Sample @ TE
			//SPCR |= (1<<SPR0);		// fosc/16 clk rate (if SPI2X = 0) or fosc/8 clk rate (if SPI2X = 1)
			//SPCR |= (1<<SPIE);		//Enable SPI interrupt
			
			//SPSR |= (1<<SPI2X);		//Double clk rate of SPI
			break;
			
		case SLAVE:
			//SPCR |= (1<<SPIE);		//Enable SPI interrupt
			
			/*set DIO directions in DIO file*/
			//MOSI -> input		SCK->input
			//SS->input
			//MISO ->output
			DDRB |= (1<<MISO);
			DDRB &= ~((1<<MOSI)|(1<<SS)|(1<<SCK));
			break;
	}
	SPCR |= (1<<SPE);			//Enable SPI
}

void SPI_vdSendByte(unsigned char data){
	volatile unsigned char flush_buffer;
	SPDR = data;			/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));	/* Wait till transmission complete */
	LCD_vdWriteChar(data);
	flush_buffer = SPDR;		/* Flush received data.Note that to clear SPIF bit, need to read SPIF and SPDR registers */
}

void SPI_vdSend2Bytes(int data){
	/*send 1st byte */
	SPI_vdSendByte((unsigned char)data);
	/* send 2nd byte */
	SPI_vdSendByte((unsigned char)(data>>8));
}

unsigned char SPI_u8Receive(){
	if(mode == MASTER){
		SPDR = 0xFF;	/*Since writing to SPDR generates SCK for transmission, write dummy data in SPDR register.*/
	}
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}

void SPI_vdSSenable(){
	PORTB &= ~(1<<SS);
}