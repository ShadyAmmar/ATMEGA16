/*
 * spi_slave.c
 *
 * Created: 9/3/2018 1:44:22 PM
 * Author : Shady
 */ 
#define  F_CPU 8000000UL
#include <avr/io.h>
#include "Sch.h"

int main(void)
{
    /* Replace with your application code */
	Sch_vdInit();
    while (1) 
    {
		Sch_vdEngine();
		
    }
}

