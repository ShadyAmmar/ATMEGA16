#define F_CPU 8000000ul
#include "util/delay.h"
#include <avr/io.h>
#include "SPI.h"
#include "APP.h"
#include "DIO.h"
#include "LED.h"

int main(void)
{
	DIO_vdInit();
	SPI_vdInit(MASTER);
	_delay_ms(1000);
	//APP_vdMyApp();
	while(1)
	{
		_delay_ms(500);
		APP_vdMyApp();
	}
}