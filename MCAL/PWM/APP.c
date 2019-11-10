#include "TIMER.h"
#define F_CPU 1000000ul
#include <util/delay.h>
#include "FAN.h"
#include "BTN.h"

void APP_vdMyApp(void)
{  
	unsigned char state;
	BTN_vdRead();
	state=BTN_u8Getstate();
	if (state)
	{
		FAN_vdTurnOn();
	}
	else if (!state)
	{
		FAN_vdTurnOff();
	}
}

