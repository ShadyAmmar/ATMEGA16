
#include "DIO.h"


int BTN_u8Getstate(void)
{
	int status;
	status=DIO_u8ReadPin('D',0);
	if(status==1)
		return 1;
	else
		return 0;
}