/*
 * uart.c
 *
 * Created: 9/1/2018 2:59:36 PM
 * Author : Shady
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include "UART.h"

int main(void)
{
    /* Replace with your application code */
	UART_vdInit(9600);
    while (1) 
    {
		unsigned char data = UART_u8ReceiveByte();
		UART_vdSendByte(data);
    }
}

