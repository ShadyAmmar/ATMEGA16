/*
 * UART.h
 *
 * Created: 9/1/2018 3:02:25 PM
 *  Author: Shady
 */ 


#ifndef UART_H_
#define UART_H_

#define F_CPU 8000000UL
void UART_vdInit(unsigned int baud);
void UART_vdSendByte(unsigned char data);
void UART_vdSendu8asASCI(unsigned char data);
unsigned char UART_u8ReceiveByte();


#endif /* UART_H_ */