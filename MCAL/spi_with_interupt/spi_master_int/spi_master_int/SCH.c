#include "app.h"
#include "TIM.h"
#include "LED.h"
#include "DIO.h"
#include "SPI.h"

int TimeTick = 0;
int NewTick=0;
unsigned char count=0;

void SCH_vdTick (void)
{
	TimeTick++;
	NewTick=1;
	LED_vdTurnOn('B',6);
}
//*****************************************
void SCH_vdInit(void)
{
	DIO_vdInit();
	SPI_vdInit(MASTER);
	TIM_vdInit(SCH_vdTick);
}
//******************************************
void SCH_vdEngine(void)
{
	if(NewTick == 1)
	{
		switch(TimeTick)
		{
			case 20:
				APP_vdMyApp();
				TimeTick = 0;
			break;
		}
		NewTick = 0;
	}
}