/*
 * CFile1.c
 *
 * Created: 8/28/2018 7:02:49 PM
 *  Author: Shady
 */ 

#include "KEYPAD.h"
#include "DIO.h"
#include "config.h"
#include "LCD.h"

static unsigned char arr[4][4]={{'7','8','9','a'}
						,{'4','5','6','b'}
						,{'1','2','3','c'}
						,{'*','0','#','d'}};
static unsigned char status = 0;

//return the current value of the pressed button but we want to eliminate the bouncing
//so we use it inside KEYPAD_vdRead which used to count the time of signal to fix the bouncing							
static unsigned char KEYPAD_u8Get(){
	unsigned char x = 0;
	unsigned char y = 0;
	unsigned char i = 0;
	unsigned char temp;
	for(i=0;i<4;i++){
		temp = 1<<i;
		DIO_vdWritePort(temp,KEYPADport);
		switch(DIO_u8ReadPort(KEYPADport) & 0xF0){
			case 0x10:
			y=i;
			x=0;
			return arr[x][y];
			break;
			
			case 0x20:
			y=i;
			x=1;
			return arr[x][y];
			break;
			
			case 0x40:
			y=i;
			x=2;
			return arr[x][y];
			break;
			
			case 0x80:
			y=i;
			x=3;
			return arr[x][y];
			break;
		}
	}
	return 0;
}

/*this function treats the bouncing by ignoring the bouncing phase and start
count when the signal becomes stable
i used to count the duration of stable signal
j used to trace if the high signal remains for long time which indicates error
finally this function changes the BTNstatus[pin] ==> (pressed , released , error)*/
/*We can delete j counter & use condition (i%3==0) to check stability*/
void KEYPAD_vdRead(){
	static unsigned char temp1 = 0;
	static int i = 0;
	unsigned char temp2 = KEYPAD_u8Get();
	
	if(temp1 == temp2){		/*if signal is stable continues counting*/
		i++;
		}else{
		temp1 =temp2;			/*if signal changed reset the count*/
		i=1;
	}
	
	if(i % 3 == 0){		/*if signal is stable until count is 3, catch the BTNstatus and reset the i counter*/
		status = temp2;
	}
	
	if(i == 400 && status != KPreleased){	 /*if signal is sticked to high ==> error*/
		status = KPerr;
		i= 0;
	}
}

unsigned char KEYPAD_u8Read(){
	switch( status )
	{
		case 0 :
		return KPreleased;
		break;
		
		case 3 :
		return KPerr;
		break;
		
		default:
		return status;
		break;
	}
	return KPreleased;
}