/*
 * DIO.h
 *
 * Created: 8/12/2018 1:26:21 PM
 *  Author: Shady
 */ 


#ifndef DIO_H_
#define DIO_H_

void DIO_vdInit();
unsigned char DIO_u8ReadPin(unsigned char port,unsigned char pin);
unsigned char DIO_u8ReadPort(unsigned char port);
void DIO_vdWritePin(unsigned char data,unsigned char port,unsigned char pin);
void DIO_vdWritePort(unsigned char data,unsigned char port);

#endif /* DIO_H_ */