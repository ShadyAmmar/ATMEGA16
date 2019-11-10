/*
 * KEYPAD.h
 *
 * Created: 8/28/2018 7:03:28 PM
 *  Author: Shady
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KPreleased 0
#define KPerr 3			//because the keypad wont return 3

void KEYPAD_vdRead();
unsigned char KEYPAD_u8Read();


#endif /* KEYPAD_H_ */