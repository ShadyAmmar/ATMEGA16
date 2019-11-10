#include "TIMER.h"

void FAN_vdTurnOn(void)
{
	TIMER_vdSetDutyCycle(50);
}

//*****************************************************************
void FAN_vdTurnOff(void)
{
	TIMER_vdSetDutyCycle(0);
}