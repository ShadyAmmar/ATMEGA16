/*
 * ADC.h
 *
 * Created: 9/16/2018 11:20:00 PM
 *  Author: Shady
 */ 


#ifndef ADC_H_
#define ADC_H_

//1/By default, the successive approximation circuitry requires an input clock frequency
//  between 50 kHz and 200 kHz to get maximum resolution.If a lower resolution than 10
//  bits is needed, the input clock frequency to the ADC can be higher than 200 kHz to get a higher sample rate.
//  Alternatively, setting the ADHSM bit in SFIOR allows an increased ADC clock frequency at the 
//  expense of higher power consumption.
//2/The ADC module contains a prescaler, which generates an acceptable ADC clock frequency from 
//  any CPU frequency above 100 kHz(because min. prescalar is 0.5 which get ADCfreq>50Hz). 
//3/The prescaler starts counting from the moment the ADC is switched on by
//  setting the ADEN bit in ADCSRA. The prescaler keeps running for as long as the ADEN
//  bit is set, and is continuously reset when ADEN is low.
//4/A normal conversion takes 13 ADC clock cycles. The first conversion after the ADC is
//  switched on (ADEN in ADCSRA is set) takes 25 ADC clock cycles in order to initialize the analog circuitry.
// Timing for Singe-conversion Mode:
//	1 ADCclk for MUX and REFS update
//then
//  1st conversion -> 13.5 ADCclk for Sample&hold + 11.5 conversion = 25 ADCclk
//then
//	next conversi. -> 1.5  ADCclk for Sample&hold + 11.5 conversion = 13 ADCclk
// Timing for Auto-triggered Conversion Mode: ... page 203 & 204
// Timing for Free-running Conversion Mode: ...  page 203 & 204

//Single-ended Conversion:
// ADC = Vin * 1024 / Vref     //NOTE: when Vin = Vref ==> ADC = 1024 (max 10 bit) so Vref is the max detected voltage
//Differential channels:
// ADC = (Vpos - Vneg)*Gain*512 / Vref		//NOTE: Vneg = -Vpos ==> 2*V so 1024 ==> 512

/*ADC Multiplexer Selection Register – ADMUX*/ 
//REFS1 - REFS0 - ADLAR - MUX4 - MUX3 - MUX2 - MUX1 - MUX0
//REFS1:0 ==> 0 0 -> AREF, Internal Vref turned off
//		  ==> 0 1 -> AVCC with external capacitor at AREF pin
//		  ==> 1 0 -> Reserved
//		  ==> 1 1 -> Internal 2.56V Voltage Reference with external capacitor at AREF pin
//ADLAR: ADC Left Adjust Result ==> 1->left  (normally it's 0)
//MUX4:0: Analog Channel and Gain Selection Bits ==> ADC0 -> 00000	PORTA 0
//													 ADC1 -> 00001	PORTA 1
//													 ...			
//													 ADC7 -> 00111

/*ADC Control and Status Register A – ADCSRA */
//ADEN - ADSC - ADATE - ADIF - ADIE - ADPS2 - ADPS1 - ADPS0
//ADEN: ADC Enable ==> 1
//ADSC: ADC Start Conversion ==> 1 -> in Single Conv. -> starts each conversion
//								   -> in Free running -> starts the 1st conversion
//							 ==> after conversion it returns to 0 automatcally
//ADATE: ADC Auto Trigger Enable :  conversion on a positive edge of the selected trigger signal. The trigger source is
//									selected by setting the ADC Trigger Select bits, ADTS in SFIOR.
//ADIF: ADC Interrupt Flag: cleared automatically after ISR or by writing 1 to it
//ADIE: ADC Interrupt Enable
//ADPS2:0: ADC Prescaler Select Bits: 0 0 0 ==> XTAL freq/2
//									  0 0 1 ==>			 /2
//									  0 1 0 ==>			 /4
//									   ...

/*ADC Data Register – ADCL and ADCH*/ 
//ADC9:0 : ADC Conversion Result

/*Special FunctionIO Register – SFIOR*/
//ADTS2 - ADTS1 - ADTS0 - ADHSM - ACME - PUD - PSR2 - PSR10
//ADTS2:0: ADC Auto Trigger Source ==> 0 0 0 -> free running mode
//									   0 0 1 -> analog comprator
//									   0 1 0 -> external interrupt request 0
//										...
//ADHSM: ADC High Speed Mode : Writing this bit to one enables the ADC High Speed mode. This mode enables higher
//		 conversion rate at the expense of higher power consumption.
/*------------------------------------------------------------------------------*/

void ADC_vdInit();
int ADC_intRead(unsigned char pin);

#endif /* ADC_H_ */