/*
 * BTN.h
 *
 * Created: 8/12/2018 2:04:49 PM
 *  Author: Shady
 */ 


#ifndef BTN_H_
#define BTN_H_

#define pressed 1
#define released 0
#define err 3
unsigned char BTN_u8getStatus(unsigned char port,unsigned char pin);
void BTN_vdRead(unsigned char port,unsigned char pin);


#endif /* BTN_H_ */