
#ifndef SPI_H_
#define SPI_H_

#define MASTER 1
#define SLAVE 0

void SPI_vdInit(unsigned char);
void SPI_vdSend(unsigned char);
unsigned char SPI_u8Recev(void);


#endif /* SPI_H_ */