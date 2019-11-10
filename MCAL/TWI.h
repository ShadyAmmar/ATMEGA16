/*
 * I2C.h
 *
 * Created: 9/16/2018 6:44:51 PM
 *  Author: Shady
 */ 


#ifndef TWI_H_
#define TWI_H_

#define True 1
#define False 0

#define READ 1
#define WRITE 0

#define Start 0x08
#define RStart 0x10
#define SLA_W_ACK_MT 0x18		//Master Transmitter Mode:(SLA+W has been transmitted & ACK has been received)
#define SLA_W_NACK_MT 0x20		//Master Transmitter Mode:(SLA+W has been transmitted & NOT ACK has been received)
#define DataACK_MT 0x28			//Master Transmitter Mode:(Data byte has been transmitted & ACK has been received)
#define DataNACK_MT 0x30		//Master Transmitter Mode:(Data byte has been transmitted & NOT ACK has been received)
#define ArbitrationLost 0x38
#define ArbitrationLost_addressed 0x68 
#define ArbitrationLost_GC 0x78 
#define SLA_R_ACK_MR 0x40		//Master Receiver Mode:(SLA+R has been transmitted & ACK has been received)
#define SLA_R_NACK_MR 0x48		//Master Receiver Mode:(SLA+R has been transmitted & NOT ACK has been received)
#define DataACK_MR 0x50			//Master Receiver Mode:(Data byte has been transmitted & ACK has been returned to slave because I set TWEA=1)
#define DataNACK_MR 0x58		//Master Receiver Mode:(Data byte has been transmitted & NOT ACK has been returned to slave because I set TWEA=0)
#define SLA_R_ACK_SR 0x60		//Slave Receiver Mode:(Own SLA+W has been received; ACK has been returned)
#define GC_ACK_SR 0x70			//Slave Receiver Mode:(General call address has been received; ACK has been returned)
#define DataACK_SR 0x80			//Slave Receiver Mode:(Previously addressed with own SLA+W; data has been received; ACK has been returned)
#define DataACK_GC_SR 0x90		//Slave Receiver Mode:(Previously addressed with general call; data has been received; ACK has been returned)
#define DataNACK_SR 0x88		//Slave Receiver Mode:(Previously addressed with own SLA+W; data has been received; NOT ACK has been returned
													//because during waiting i made the TWEA = 0 in the SLAVE)
#define DataNACK_GC_SR 0x98		//Slave Receiver Mode:(Previously addressed with general call; data has been received; NOT ACK has been returned
													//because during waiting i made the TWEA = 0 in the SLAVE)

#define STO_Rstart_SR 0xA0		//Slave Receiver Mode:(A STOP condition or repeatedSTART condition has been received while still addressed as slave)								
#define DataACK_ST 0xB8			//Slave Transmitter Mode:(Data byte in TWDR has been transmitted; ACK has been received)
#define DataNACK_ST 0xC0			//Slave Transmitter Mode:(Data byte in TWDR has been transmitted; NOT ACK  has been received)
#define DataACK_err_ST 0xC8		//Slave Transmitter Mode:(the master demands additional data bytes by transmitting ACK, even though the slave has
												//transmitted the last byte



/*TWI bit rate register - TWBR*/
//SCL freq = CPU freq / ( 16 + 2 * TWBR * 4^TWPS )
//TWBR = 10;		//Should be 10 or higher

/*TWI control register - TWCR*/
//TWINT - TWEA - TWSTA - TWSTO - TWWC - TWEN – .. - TWIE
//TWINT : When high, the Low SCL stretched - Must be cleared by writting 1 by SW - Clearing this
//			flag starts th operation so all accesses to TWAR , TWSR , TWDR must be completed before clearing
//TWSTA (start condition bit) : writing 1 -> master , and HW checks if the bus is available and generates a START condition
//								if bus is busy, it waits until STOP is detected and generates a new START and then cleared by
//								the HW when the START bit is transmitted
//TWEA (TWI Enable Acknowledge Bit): 1 -> ACK on 
//TWSTO (stop condition bit) : in Master mode -> generate STOP & cleared automatically
//							   in Slave mode -> used to recover from error condition by generating a STOP and the 
//												TWI returns to a well-defined unaddressed slave mode and 
//												releases the SCL and SDA lines to a high impedance state. 
//TWEN (TWI Enable Bit) : When TWEN is written to one, the TWI takes control over the I/O pins connected to the SCL and SDA
//							pins, enabling the slew-rate limiters and spike filters.

/*TWI Status Register – TWSR*/
//TWS7 - TWS6 - TWS5 - TWS4 - TWS3 - .. – TWPS1 - TWPS0
//TWS (TWI Status) : 
//TWPS (TWI Prescaler Bits) 

/*TWI Data Register – TWDR*/
//In Transmit mode, TWDR contains the next byte to be transmitted. In Receive mode, the
//TWDR contains the last byte received.It is writable while the TWI is not in the process of
//shifting a byte. This occurs when the TWI Interrupt Flag (TWINT) is set by hardware.

/*TWI (Slave) Address Register – TWAR*/
//TWA7:1(SLAVE address of the TWI unit) - 
//TWGCE(If set, this bit enables the recognition of a General Call given over the Two-wire Serial Bus.)

//ACK is 1 / notACK is 0	//not Sure check sensor datasheet

//Master transmitter mode
//1)TWEN = 1 / TWSTA = 1 /TWINT = 1(to clear) => TWI generates START when not busy 
//2)TWINT is set by HW , TWSR = 0x08(A START condition has been transmitted)
//3)TWDR = SLA + W , TWINT = 1(to clear)	  =>write addr+W then 1 in TWINT to start transmission
//4)TWINT is set by HW , TWSR = 0x18(SLA+W has been transmitted & ACK has been received)
//						 TWSR = 0x20(SLA+W has been transmitted & NOT ACK has been received) ==> then Send STOP go to 7 or 7'
//																							or continue sending "not good i think")
//						 TWSR = 0x38(Arbitration Lost other master will continue)			 ==> dont do anything
//						 TWSR = 0x68 or 0x78 or 0xB0 (Arbitration lost and addressed as Slave)==> go to corresponding
//																								  state in Slave mode
//5)TWDR = data , TWINT = 1(to clear)	  =>write data then 1 in TWINT to start transmission
//6)TWINT is set by HW , TWSR = 0x28(Data byte has been transmitted & ACK has been received)
//						 TWSR = 0x30(Data byte has been transmitted & NOT ACK has been received)==> then Send STOP go to 7)
//						 TWSR = 0x38(Arbitration Lost other master will continue)			 ==> dont do anything
//7)TWEN = 1 / TWSTO = 1 /TWINT = 1		  => Transmit STOP
//or 7')TWEN = 1 / TWSTA = 1 /TWINT = 1(to clear) ==> repeated start
//	 8')TWINT is set by HW , TWSR = 0x10(Repeated start) ==> go to 3) again or SLA + R (Master receiver mode)


//Master receiver mode
//1)TWEN = 1 / TWSTA = 1 /TWINT = 1(to clear) => TWI generates START when not busy
//2)TWINT is set by HW , TWSR = 0x08(A START condition has been transmitted)
//3)TWDR = SLA + R , TWINT = 1(to clear)	  =>write addr+R then 1 in TWINT to start transmission
//4)TWINT is set by HW , TWSR = 0x40(SLA+R has been transmitted & ACK has been received)
//						 TWSR = 0x48(SLA+R has been transmitted & NOT ACK has been received) ==> then Send STOP go to 7 or 7')
//						 TWSR = 0x38(Arbitration Lost other master will continue)			 ==> dont do anything
//						 TWSR = 0x68 or 0x78 or 0xB0 (Arbitration lost and addressed as Slave)==> go to corresponding
//																								  state in Slave mode
//5)data received in TWDR , if (TWEA==1){will send ACK to slave}else{NOT ACK to slave} <== I should change TWEA based on
//																							data received(less common) or 
//																	if I don't want more data and I will send STOP(more common)
//6)TWINT is set by HW , TWSR = 0x50(Data byte has been transmitted & ACK has been returned to slave because I set TWEA=1)
//						 TWSR = 0x58(Data byte has been transmitted & NOT ACK has been returned to slave because I set TWEA=0)
//																							 ==>go to 7)
//						 TWSR = 0x38(Arbitration Lost other master will continue)			 ==> dont do anything
//7)go to 5) again
//8)TWEN = 1 / TWSTO = 1 /TWINT = 1		  => Transmit STOP
//or 8')TWEN = 1 / TWSTA = 1 /TWINT = 1(to clear) ==> repeated start
//	 9')TWINT is set by HW , TWSR = 0x10(Repeated start) ==> go to 3) again or SLA + W (Master transmitter mode)

//Slave Receiver Mode
//1)TWAR reg must be initialized with the slave addr /
//  TWEN = 1 / TWEA = 1 /TWINT = 1(to clear) => TWEN enables TWI / TWEA enables ACK(While TWEA is zero, the TWI does not respond to its own slave address)
//													/ TWSTA & TWSTO must be zero
//	TWGCE = 1 ==> enables responding to general call (addr 0x00)
//  this makes the slave waiting until addressed (or general call) + 0"write" so Slave Reciev. mode starts
//2)TWINT is set , TWSR = 0x60(Own SLA+W has been received; ACK has been returned)
//				   TWSR = 0x68(Arbitration lost in SLA+R/W as master; own SLA+W has been received; ACK has been returned)
//or 2')TWINT is set , TWSR = 0x70(General call address has been received; ACK has been returned)
//                     TWSR = 0x78(Arbitration lost in SLA+R/W as master; General call address has been received; 
//							ACK has been returned)
//3)No action waiting the completion of transmission
//4)TWINT is set , TWSR = 0x80(Previously addressed with own SLA+W; data has been received; ACK has been returned)
//or 4')TWINT is set , TWSR = 0x90(Previously addressed with general call; data has been received; ACK has been returned)
//5)waiting
//6)TWINT is set , TWSR = 0x80(Previously addressed with own SLA+W; data has been received; ACK has been returned)
//				   TWSR = 0x88(Previously addressed with own SLA+W; data has been received; NOT ACK has been returned 
//								because during waiting i made the TWEA = 0 in the SLAVE)==> go to No action (stop or repeated start 
//																									will be received)
//or 6')TWINT is set , TWSR = 0x90(Previously addressed with general call; data has been received; ACK has been returned)
//				       TWSR = 0x98(Previously addressed with general call; data has been received; NOT ACK has been returned
//								because during waiting i made the TWEA = 0 in the SLAVE)==> go to No action (stop or repeated start
//																									will be received)
//7)TWINT is set , TWSR = 0xA0(A STOP condition or repeatedSTART condition has been received while still addressed as slave)

//Slave Transmitter Mode
//1)TWAR reg must be initialized with the slave addr /
//  TWEN = 1 / TWEA = 1 /TWINT = 1(to clear) => TWEN enables TWI / TWEA enables ACK(While TWEA is zero, the TWI does not respond to its own slave address) 
//													/ TWSTA & TWSTO must be zero
//	TWGCE = 1 ==> enables responding to general call (addr 0x00)
//  this makes the slave waiting until addressed (or general call) + 1"read" so Slave Trans. mode starts
//2)TWINT is set , TWSR = 0xA8(SLA+R has been received and ACK has been returned)
//				   TWSR = 0xB0(Arbitration is lost in SLA+W/R and SLA+R has been received,ACK has been returned)
//3)TWDR = data
//4)TWINT is set , TWSR = 0xB8(Data byte in TWDR has been transmitted; ACK has been received)
//				   TWSR = 0xC0(Data byte in TWDR has been transmitted; NOT ACK has been received
//							or If TWEA is written zero during transfer & Master send Not ACK) ==>go to No action
//				   TWSR = 0xC8(the master demands additional data bytes by transmitting ACK, even though the slave has 
//			              transmitted the last byte (TWEA zero and expecting NACK from the master)
//						  so The TWI is switched to the not addressed Slave mode, and will ignore the master if it 
//						continues the transfer. Thus th master receiver receives all “1” as serial data. )
//						  NOTE: same as the 0xC0 but the master sent ACK instead of NOT ACK


void TWI_vdInit();
void TWI_vdSendStart();
void TWI_vdSendStop();
void TWI_vdWrite(unsigned char);
unsigned char TWI_u8CheckStatus(unsigned char);
unsigned char TWI_u8ReadwithNoAck();
unsigned char TWI_u8ReadwithAck();



#endif /* TWI_H_ */