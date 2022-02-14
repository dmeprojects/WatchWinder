/*
 * Timers.c
 *
 * Created: 13/02/2022 16:35:48
 *  Author: nick_
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "global.h"


void InitTimer0()
{
	
	// Use timer0 to generate an interrupt every mS at 16Mhz
	switch (F_CPU)
	{
		case 16000000:
			TCCR0A	=	(1<<WGM01);								// Configure timer in CTC mode
			TCCR0B  =	(1<<CS00) | (1<<CS01) | (0<<CS02);		// Set timer clock source to clock/64
			OCR0A	=	250;									// Compare register A to 250
			//OCR0A	=	32;									// Compare register A to 32
			TIMSK0	=	(1<<OCIE0A);							// Enable compare match A interrupt
			//sei();
		break;
		
		case 8000000:
			TCCR0A	=	(1<<WGM01);								// Configure timer in CTC mode
			TCCR0B  =	(1<<CS00) | (1<<CS01) | (0<<CS02);		// Set timer clock source to clock/8
			OCR0A	=	125;									// Compare register A to 125
			TIMSK0	=	(1<<OCIE0A);							// Enable compare match A interrupt
			//sei();
		break;
	}
}

void InitTimer1()	//Configuration as PWM driver for power led & ambient LED
{	
	switch (F_CPU)
	{
		case 16000000:
			TCCR1A = ( (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10));	//Fast PWM mode 5, clear OC1X on compare match, set at bottom
			TCCR1B = ((1<<CS12) | (0<<CS11) | (1<<CS10) |(1<<WGM12)); //Prescaler on 1024: 156.25Khz, mode 5
			TIFR1 = (1<<OCF1A);		//Clear flag before set interrupt
			TIMSK1 = (1<<OCIE1A);	//Enable compare match interrupt
			OCR1A = 127;	//Set value in center
			OCR1B = 127;	//Set value in center
		break;
		
		case 8000000:
			TCCR1B = ((0<<CS10)| (1<<CS11) | (1<<WGM12));	//CTC mode prescaler 8x (1µs)
			OCR1A = 0;
			TIFR1 = (1<<OCF1A);		//Clear flag before set interrupt
			TIMSK1 = (1<<OCIE1A);	//Enable compare match interrupt
		break;
	}

}

void InitTimer2() //Configuration as step driver for stepper motor
{	
	/*
	TCCR2A in CTC mode, toggle O2CA on compare match
	*/
	TCCR2A	=	(0<<COM2A1) | (1<<COM2A0) | (0<<COM2B1) | (0<<COM2B0) | (0<<WGM20) | (1<<WGM21) | (0<<COM2B1);	
	TCCR2B  =	(1<<CS20) | (0<<CS21) | (0<<CS22);		// Set timer clock source to clock/64 (8Mhz/64 = 125Khz)
	OCR2A	=	125;	//1ms interrupt
	OCR2B	=	0;		
	TCNT2	=	0;		
	DDRB	=	DDRB | (1<<MotorStep);						// Make sure PORTB.3 is set as output for the servo
	TIFR2	=	(1<<OCF2A);		//Clear interrupt flag
	TIMSK2	=	(1<<OCIE2A);	//Enable interrupt
}

void StartTimer2 (unsigned char Prescaler)
{
	TCCR2B  =	(1<<CS20) | (0<<CS21) | (0<<CS22);		// Set timer clock source to clock/64 (8Mhz/64 = 125Khz)	
}
 
 void StopTimer2(void)
 {
	 TCCR2B = 0;	 
 }
 
