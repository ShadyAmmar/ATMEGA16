#include <avr/io.h>
#include "SPI.h"
#define F_CPU 8000000ul
#include "util/delay.h"
static unsigned char mode;

void SPI_vdInit(unsigned char App_mode)
{
	PORTB = 0;
	mode = App_mode;
	if(mode == MASTER)
	{
		DDRB |= (1<<PB4)|(1<<PB5)|(1<<PB7);
		PORTB |=(1<<PB4);
		SPSR = 0;
		SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
		/*
		//CHOOSE THE MODE (MASTER/SLAVE)   (1<<MSTR)
		SPCR|=(1<<4);
		
		//SET SPI PIN DIRECTIONS
		DDRB|=(1<<4);   //OUTPUT CONTROL THE SS OF THE SLAVE.
		DDRB|=(1<<5);   //MOSI
		DDRB&=~(1<<6);  //MISO
		DDRB|=(1<<7);   //CLK
		
		//CLOCK POLARITY/PHASE
		SPCR&=~(1<<3);	//(1<<CPOL)
		SPCR&=~(1<<2);	//(1<<CPHA)
		
		//BIT RATE (F/4)
		//SPCR&=~(1<<1);	//(1<<SPR1)
		//SPCR&=~(1<<0);	//(1<<SPR0)
		//SPSR&=~(1<<0);	//(1<<SPI2X)
		
		//DATA ORDER (WHEN 1-->LSB)/(WHEN 0-->MSB)
		SPCR|=(1<<5);	//(1<<DORD)
		
		//ENABLE SPI (1<<SPE)
		SPCR|=(1<<6);
		*/
	}
	else
	{
		DDRB |= (1<<PB6);
		DDRB &=~ ((1<<PB4)|(1<<PB5)|(1<<PB7));
		SPSR = 0;
		SPCR = (1<<SPE)|(1<<SPR0);
		/*
		//CHOOSE THE MODE (MASTER/SLAVE)   (1<<slave)
		SPCR&=~(1<<4);
		
		//SET SPI PIN DIRECTIONS
		DDRB&=~(1<<4);   //INPUT SS
		DDRB&=~(1<<5);   //MOSI
		DDRB|=(1<<6);  //MISO
		DDRB&=~(1<<7);   //CLK
		
		//CLOCK POLARITY/PHASE
		SPCR&=~(1<<3);	//(1<<CPOL)
		SPCR&=~(1<<2);	//(1<<CPHA)
		
		//BIT RATE (F/4)
		SPCR&=~(1<<1)|(1<<0);	//(1<<SPR1)
		//SPCR&=~(1<<0);	//(1<<SPR0)
		SPSR&=~(1<<0);	//(1<<SPI2X)
		
		//DATA ORDER (WHEN 1-->LSB)/(WHEN 0-->MSB)
		SPCR|=(1<<5);	//(1<<DORD)
		
		//ENABLE SPI (1<<SPE)
		SPCR|=(1<<6);
		*/
	}
}
//****************************************************************
void SPI_vdSend(unsigned char data )
{
	if(mode == MASTER)
	{
		//TELL THE RECIVER I WILL TRANSMIT.
		PORTB&=~(1<<4);
		
		// Start transmission
		SPDR = data;
		
		// Wait for transmission complete
		while(!(SPSR & (1<<SPIF)))
		;
		
		//TELL THE RECIVER I FINISHED THE TRANSMISSION.
		PORTB|=~(1<<4);
	}
	else
	{
		// Start transmission
		SPDR = data;
		
		// Wait for transmission complete
		while(!(SPSR & (1<<SPIF)))
		;
	}
}
//*****************************************************************
unsigned char SPI_u8Recev(void)
{
	if(mode ==MASTER)
	{
		/* Wait for reception complete */
		while(!(SPSR & (1<<SPIF)))
		;
		// Return data register
		return SPDR;
	}
	else
	{
		/* Wait for reception complete */
		while(!(SPSR & (1<<SPIF)))
		;
		// Return data register
		return SPDR;
		
	}
}
//****************************************************************