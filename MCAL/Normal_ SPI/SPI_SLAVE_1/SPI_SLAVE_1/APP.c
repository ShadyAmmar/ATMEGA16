#include "SPI.h"
#include "LCD.h"
#include "LED.h"
#define F_CPU 8000000ul
#include "util/delay.h"

void APP_vdMyApp(void)
{  
	unsigned char x;
	x=SPI_u8Recev();
	if (x == 49)
	{
		LED_vdTurnOn('C',0);
	}
	else if (x == 48)
	{
		LED_vdTurnOff('C',0);
	}
}

