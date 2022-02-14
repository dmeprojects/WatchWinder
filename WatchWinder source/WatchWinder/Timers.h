/*
 * Timers.h
 *
 * Created: 13/02/2022 16:36:13
 *  Author: nick_
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

void InitTimer0(void);
void StartTimer0(unsigned char Prescaler);
void StopTimer0(void);

void InitTimer1(void);
void StartTimer1(unsigned char Prescaler);
void StopTimer1(void);

void InitTimer2(void);
void StartTimer2 (unsigned char Prescaler);
void StopTimer2(void);


#endif /* TIMERS_H_ */