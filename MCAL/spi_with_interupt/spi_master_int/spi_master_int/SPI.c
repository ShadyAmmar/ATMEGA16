#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/common.h>
#include "SPI.h"
#include "LED.h"
static unsigned char mode;
volatile static unsigned char spi_status = READY;
static unsigned char rx_complete=0;
volatile static unsigned char new_transmission=1;

//*****************************************************************************************************************************************
void SPI_vdInit(unsigned char App_mode)
{
	PORTB = 0;
	mode = App_mode;
	if(mode == MASTER)
	{
		DDRB |= (1<<PB4)|(1<<PB5)|(1<<PB7)|(1<<0);
		PORTB |=(1<<PB4);
		SPSR = 0;
		SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPIE);
		SREG = (1<<7);
		/*
		//SET SPI PIN DIRECTIONS
		DDRB|=(1<<4);   //OUTPUT CONTROL THE SS OF THE SLAVE.
		DDRB|=(1<<5);   //MOSI
		DDRB&=~(1<<6);  //MISO
		DDRB|=(1<<7);   //CLK
		PORTB |=(1<<PB4);
		
		//CLOCK POLARITY/PHASE
		SPCR&=~(1<<3);	//(1<<CPOL)
		SPCR&=~(1<<2);	//(1<<CPHA)
		
		//BIT RATE (F/4)
		SPCR&=~(1<<1);	//(1<<SPR1)
		SPCR&=~(1<<0);	//(1<<SPR0)
		SPSR|=(1<<0);	//(1<<SPI2X)
		
		//DATA ORDER (WHEN 1-->LSB)/(WHEN 0-->MSB)
		SPCR|=(1<<5);	//(1<<DORD)
		
		//CHOOSE THE MODE (MASTER/SLAVE)   (1<<MSTR)
		SPCR|=(1<<4);
		
		//ENABLE SPI (1<<SPE)
		SPCR|=(1<<6);
		*/
	}
	else
	{
		DDRB |= (1<<PB6);
		DDRB &=~ ((1<<PB4)|(1<<PB5)|(1<<PB7));
		SPSR = 0;
		SPCR = (1<<SPE)|(1<<SPR0)|(1<<SPIE);
		SREG = (1<<7);
		/*
		//CHOOSE THE MODE (MASTER/SLAVE)   (1<<MSTR)
		SPCR&=~(1<<4);
		
		//SET SPI PIN DIRECTIONS
		DDRB&=~(1<<4);   //INPUT SS
		DDRB&=~(1<<5);   //MOSI
		DDRB|=(1<<6);    //MISO
		DDRB&=~(1<<7);   //CLK
		
		//CLOCK POLARITY/PHASE
		SPCR&=~(1<<3);	//(1<<CPOL)
		SPCR&=~(1<<2);	//(1<<CPHA)
		
		//BIT RATE (F/4)
		SPCR&=~(1<<1);	//(1<<SPR1)
		SPCR&=~(1<<0);	//(1<<SPR0)
		SPSR&=~(1<<0);	//(1<<SPI2X)
		
		//DATA ORDER (WHEN 1-->LSB)/(WHEN 0-->MSB)
		SPCR|=(1<<5);	//(1<<DORD)
		
		//ENABLE SPI (1<<SPE)
		SPCR|=(1<<6);*/
	}
}
//*********************************************************************************************************************************
void SPI_vdSend(unsigned char data )
{
	spi_status = SENDING;
	if(mode == MASTER)
	{
		//TELL THE RECIVER I WILL TRANSMIT.
		PORTB&=~(1<<4);
		
		// Start transmission
		SPDR = data;
	}
	else
	{
		// Start transmission
		SPDR = data;
	}
}
//**********************************************************************************************************************************
unsigned char SPI_u8Recev(void)
{
	rx_complete = 0;
	spi_status = RECIEVING;
	// Wait for transmission complete
	while(!rx_complete)
	;
	return SPDR;
}
//**********************************************************************************************************************************
unsigned char SPI_u8Get_Status()
{
	return spi_status;
}
//**********************************************************************************************************************************
ISR(SPI_STC_vect)
{
	if(spi_status == RECIEVING)
	{
		rx_complete = 1;
	}
	else if (spi_status == SENDING)
	{
		if(mode == MASTER)
		{
			//TELL THE RECIVER I FINISHED THE TRANSMISSION.
			PORTB|=(1<<4);
		}
	}
	spi_status = READY;
}