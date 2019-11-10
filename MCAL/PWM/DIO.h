#ifndef DIO_H_
#define DIO_H_

void DIO_vdInit(void);
int DIO_u8ReadPin(unsigned char portregID ,unsigned char pinNO );
void DIO_vdWritePin(unsigned char portregID, unsigned char pinNO,unsigned char value_1);

#endif