#include "DIO.h"
#define pressed 1
#define realsed 0 
#define error 3

unsigned char btnstate;


void BTN_vdRead(void)
{
	btnstate  =  DIO_u8ReadPin('D',0);
}



int BTN_u8Getstate(void )
{
	switch( btnstate )
	{
		case 1 :
			return pressed;
		break;
		case 0 : 
			return realsed;
		break;
		case 3 :
			return error;
		break;
	}
	return pressed;
}