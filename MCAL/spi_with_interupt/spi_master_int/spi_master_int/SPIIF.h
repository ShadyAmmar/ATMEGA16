/*
 * SPIIF.h
 *
 * Created: 9/17/2018 1:01:32 PM
 *  Author: islam
 */ 


#ifndef SPIIF_H_
#define SPIIF_H_

#define T_OK 1
#define T_NOK 0
unsigned char SPIIF_u8Send(unsigned char data);
void SPIIF_u8Rec(unsigned char* Rec_data,unsigned char* status);


#endif /* SPIIF_H_ */