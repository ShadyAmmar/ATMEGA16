/*
 * SPIIF.c
 *
 * Created: 9/17/2018 1:01:17 PM
 *  Author: islam
 */ 
#include "SPI.h"
#include "SPIIF.h"
#include "LED.h"
unsigned char SPI_status;

unsigned char SPIIF_u8Send(unsigned char data)
{
	unsigned char temp = SPI_u8Get_Status();
	if(temp == READY)
	{
		SPI_vdSend(data);
		return T_OK;
	}
	else
	{
		return T_NOK;
	}
}

void SPIIF_u8Rec(unsigned char* Rec_data,unsigned char* status)
{
	unsigned char temp = SPI_u8Get_Status();
	if(temp == READY)
	{
		*Rec_data = SPI_u8Recev();
		*status = T_OK;
	}
	else
	{
		*status = T_NOK;
	}
}