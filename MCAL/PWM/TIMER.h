/*
 * PWM.h
 *
 * Created: 19/09/2015 12:55:02 م
 *  Author: eslam
 */ 


#ifndef PWM_H_
#define PWM_H_

#define NORMAL 1
#define CTC 2
#define FAST_PWM 3
#define PHASE_CORRECT_PWM 4

void TIMER_vdSetDutyCycle(unsigned char);
void TIMER_vdInit(unsigned char);


#endif /* PWM_H_ */