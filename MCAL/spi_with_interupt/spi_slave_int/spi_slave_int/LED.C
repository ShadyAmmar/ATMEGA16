
#include "DIO.h"

//*************************************************************************
void LED_vdTurnOn(unsigned char port_ID , unsigned char pin_no)
{
	 DIO_vdWritePin(port_ID,pin_no, 1);
}

//*************************************************************************
void LED_vdTurnOff(unsigned char port_ID , unsigned char pin_no)
{
	DIO_vdWritePin(port_ID,pin_no, 0);
}

//*************************************************************************
void LED_vdTurn(unsigned char port_ID , unsigned char pin_no ,int value)
{
	DIO_vdWritePin(port_ID, pin_no, value);
}
