/*
 * spi.c
 *
 * Created: 9/3/2018 12:19:11 PM
 * Author : Shady
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include "Sch.h"
#include "DIO.h"
#include "LCD.h"
#include "SPI.h"
#include <stdio.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	Sch_vdInit();

    while (1) 
    {
		Sch_vdEngine();
    }
	
}

