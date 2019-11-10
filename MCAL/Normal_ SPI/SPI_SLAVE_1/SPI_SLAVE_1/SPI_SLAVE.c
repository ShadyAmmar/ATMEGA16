#define F_CPU 8000000ul
#include "util/delay.h"
#include <avr/io.h>
#include "DIO.h"
#include "SPI.h"
#include "APP.h"
#include "LCD.h"
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