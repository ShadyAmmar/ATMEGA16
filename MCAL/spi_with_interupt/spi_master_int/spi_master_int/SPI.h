﻿
#ifndef SPI_H_
#define SPI_H_

#define MASTER 1
#define SLAVE 0

#define READY 2
#define SENDING 1
#define RECIEVING 0


void SPI_vdInit(unsigned char);
void SPI_vdSend(unsigned char);
unsigned char SPI_u8Recev(void);
unsigned char SPI_u8Get_Status(void);


#endif /* SPI_H_ */