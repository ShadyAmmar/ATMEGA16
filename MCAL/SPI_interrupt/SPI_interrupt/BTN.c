/*
 * BTN.c
 *
 * Created: 8/12/2018 2:04:22 PM
 *  Author: Shady
 */ 

#include "BTN.h"
#include "DIO.h"
#include <avr/io.h>

static unsigned char BTNstatus[] = {0,0,0,0,0,0,0,0};	

unsigned char BTN_u8getStatus(unsigned char port,unsigned char pin){
	switch( BTNstatus[pin] )
	{
		case 1 :
		return pressed;
		break;
		case 0 :
		return released;
		break;
		case 3 :
		return err;
		break;
	}
	return pressed;
}

/*this function treats the bouncing by ignoring the bouncing phase and start
count when the signal becomes stable
i used to count the duration of stable signal
j used to trace if the high signal remains for long time which indicates error
finally this function changes the BTNstatus[pin] ==> (pressed , released , error)*/
/*We can delete j counter & use condition (i%3==0) to check stability*/
void BTN_vdRead(unsigned char port,unsigned char pin){
	static unsigned char temp1[] = {0,0,0,0,0,0,0,0};
	static int i[] = {0,0,0,0,0,0,0,0};
	//static int j[] = {0,0,0,0,0,0,0,0};
	unsigned char temp2 = DIO_u8ReadPin(port,pin);
	
	if(temp1[pin] == temp2){		/*if signal is stable continues counting*/
		i[pin]++;
		//j[pin]++;
	}else{
		temp1[pin] =temp2;			/*if signal changed reset the count*/
		i[pin]=1;
		//j[pin]=1;
	}
		
	if(i[pin] % 3 == 0){		/*if signal is stable until count is 3, catch the BTNstatus and reset the i counter*/
		BTNstatus[pin] = temp2;
		//i[pin]=0;
	}
		
	if(i[pin] == 400 && BTNstatus[pin]==pressed){	 /*if signal is sticked to high ==> error*/
		BTNstatus[pin] = err;
		//j[pin]=0;
		i[pin] = 0;
	}
}

