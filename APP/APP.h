/*
 * APP.h
 *
 * Created: 9/2/2018 3:06:23 PM
 *  Author: Shady
 */ 


#ifndef APP_H_
#define APP_H_

#define LOCK 1
#define UNLOCK 2
#define LOCK_S 3
#define CH_PASS 4
#define WRONGPASS 11
#define GETPASS 12

#define ADDRESS_EEPROM 0x50

void APP_vdDefaultPASSinit();
void APP_vdDONE();
void APP_vdCall();



#endif /* APP_H_ */