/*
 * spi_slave_int.c
 *
 * Created: 9/7/2018 10:37:47 AM
 * Author : islam
 */ 

#define F_CPU 8000000ul
#include "util/delay.h"
#include <avr/io.h>
#include "DIO.h"
#include "SPI.h"
#include "APP.h"
#include "LED.h"

int main(void)
{
	DIO_vdInit();
	SPI_vdInit(SLAVE);
	while(1)
	{
		APP_vdMyApp();
	}
}

