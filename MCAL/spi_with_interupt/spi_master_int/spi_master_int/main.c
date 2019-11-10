/*
 * spi_master_int.c
 *
 * Created: 9/7/2018 8:47:35 AM
 * Author : islam
 */ 

#define F_CPU 8000000ul
#include "util/delay.h"
#include <avr/io.h>
#include "SCH.h"


int main(void)
{
	SCH_vdInit();
	while(1)
	{
		SCH_vdEngine();
	}
}

