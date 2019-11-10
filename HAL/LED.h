/*
 * LED.h
 *
 * Created: 8/12/2018 2:05:08 PM
 *  Author: Shady
 */ 


#ifndef LED_H_
#define LED_H_


void LEDon(unsigned char port,unsigned char pin);
void LEDoff(unsigned char port,unsigned char pin);
void LEDtoggle(unsigned char port,unsigned char pin);
void LEDrefresh(unsigned char port,unsigned char pin);


#endif /* LED_H_ */