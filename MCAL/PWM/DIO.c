#include <avr/io.h>

void DIO_vdInit(void)
{
	DDRD=0;
	DDRA =0xFF;
}



int DIO_u8ReadPin(unsigned char portregID ,unsigned char pinNO )
{	
	unsigned int temp=0;
	switch(portregID)
	{
		case 'A' : 
			temp=(PINA &(1<<pinNO));
			return temp;	             
		break ;

        case 'B' :
			 temp=(PINB &(1<<pinNO));
			 return temp;	             
	    break ;
			   
		case 'C' : 
			temp=(PINC &(1<<pinNO));
			return temp;	             
	    break;
		
        case 'D' : 
			temp=(PIND &(1<<pinNO));
			return temp;	             
	    break ;
	}
	return temp;
}



void DIO_vdWritePin(unsigned char portregID, unsigned char pinNO ,unsigned char value_1)
{
	switch(portregID)
	{
		case 'A' : 
			if(value_1)
				 PORTA|=(1<<pinNO);
			else
				 PORTA&=~(1<<pinNO);
			break ;
		case 'B' :  
			if(value_1)
				 PORTB|=(1<<pinNO);
			else
			    PORTB&=~(1<<pinNO);
			break ;
		case 'C' :  
			if(value_1)
				PORTC|=(1<<pinNO);
			else
	     		PORTC&=~(1<<pinNO);
			break ;
		case 'D' :  
			if(value_1)
			    PORTD|=(1<<pinNO);
			else
			  PORTD&=~(1<<pinNO);
			break ;
	}
}