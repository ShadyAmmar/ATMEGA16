#ifndef DIO_H_
#define DIO_H_

void DIO_vdInit(void);
int DIO_u8ReadPin(unsigned char  ,unsigned char  );
void DIO_vdWritePin(unsigned char , unsigned char ,unsigned char );
void DIO_vdWritePort(unsigned char  ,unsigned char );

#endif