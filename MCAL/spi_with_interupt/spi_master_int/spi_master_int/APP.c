#include "BTN.h"
#include "LED.h"
#include "SPIIF.h"
#define pressed 1
#define released 0

void APP_vdMyApp(void)
{  
	unsigned char value=0;
	unsigned char sending_check;
	static unsigned char prev_state_1 = released;
	unsigned char curr_state_1 = BTN_u8Getstate();
	if(prev_state_1==released && curr_state_1==pressed)
	{
		value=49;
		sending_check = SPIIF_u8Send(value);
		while(sending_check == T_NOK)
		{
			sending_check = SPIIF_u8Send(value);
		}
	}
	else if(prev_state_1==pressed && curr_state_1==released)
	{
		value=48;
		SPIIF_u8Send(value);
	}
	prev_state_1=curr_state_1;
	
	
}

