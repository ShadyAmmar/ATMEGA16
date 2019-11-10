#include "BTN.h"
#include "LED.h"
#include "SPI.h"
#define pressed 1
#define released 0

void APP_vdMyApp(void)
{  
	unsigned char status = 0;
	unsigned char value=0;
	//unsigned char x=0;
	//SPI_vdSend(0x09);
	
	
	status=BTN_u8Getstate();
	if(status == pressed)
	{
		value=49;
		SPI_vdSend(value);
	}
	else if(status == released)
	{
		value=48;//'0'
		SPI_vdSend(value);
	}
	
}

