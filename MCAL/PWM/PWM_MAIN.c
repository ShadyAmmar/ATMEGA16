#include <avr/io.h>
#include "TIMER.h"
#include "APP.h"


int main(void)
{
	TIMER_vdInit(FAST_PWM);
    while(1)
    {
        APP_vdMyApp();
    }
}