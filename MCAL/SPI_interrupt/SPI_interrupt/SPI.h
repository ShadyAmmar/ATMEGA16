/*
 * SPI.h
 *
 * Created: 9/3/2018 12:23:20 PM
 *  Author: Shady
 */ 


#ifndef SPI_H_
#define SPI_H_

#define MASTER 0
#define SLAVE 1

#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7

/*SPI Control Register – SPCR*/
//SPIE - SPE	- DORD		- MSTR		- CPOL		- CPHA		- SPR1 - SPR0
//				1 LSB first			0 rising 1st	0 sample@LE
//				0 MSB first			1 falling 1st   1 sample@TE

/*SPI Status Register – SPSR*/
//SPIF - WCOL – – – – – SPI2X

/*SPI Data Register – SPDR*/

void SPI_vdInit(unsigned char MODE, void (*f)(unsigned char) );
void SPI_vdSendByte(unsigned char data);
void SPI_vdSend2Bytes(int data);
unsigned char SPI_u8Receive();
void SPI_vdSSenable();

#endif /* SPI_H_ */