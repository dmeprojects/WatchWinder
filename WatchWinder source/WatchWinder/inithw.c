/*
 * inithw.c
 *
 * Created: 2/25/2017 10:59:08 AM
 *  Author: Petervg
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "inithw.h"
//#include "LCD/my_lcd.h"
//#include "ADC.h"
//#include "UART.h"
//#include "I2C.h"
#include "global.h"
//#include "ADXL345.h"

void setup(void)
{
	// Internal peripherals
	// --------------------
	InitTimer0();		// Init timer0 for 1mS interrupts
	InitTimer1();		// Init timer1 for PWM output 
	InitTimer2();		// Init Timer2 for 61Hz PWM (should be 50Hz, but hey... :-) )
	InitGPIO();			// Set PORTD.2 as input and PORTB.5 as output
	InitInt0();			// Enable falling egde interrupts
	
	// External peripherals
	// --------------------
	
	/*Enable Interrupts*/
	sei();
}

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
			sei();
		break;
		
		case 8000000:
			TCCR0A	=	(1<<WGM01);								// Configure timer in CTC mode
			TCCR0B  =	(0<<CS00) | (1<<CS01) | (0<<CS02);		// Set timer clock source to clock/8
			OCR0A	=	125;									// Compare register A to 125
			TIMSK0	=	(1<<OCIE0A);							// Enable compare match A interrupt
			sei();
		break;
	}
}

void InitTimer1()	//Configuration as PWM driver for power led
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

void InitTimer2() //Configuration as PWM driver for ambient LED
{
	// Use timer2 to generate 50Hz PWM at OC2B (fast PWm, 8-bit, TOP = 0xFF (+/-61Hz))
	TCCR2A	=	(1<<WGM20) | (1<<WGM21) | (1<<COM2B1);	// Configure timer in PWM mode, non inverting
	TCCR2B  =	(1<<CS20) | (1<<CS21) | (1<<CS22);		// Set timer clock source to clock/1024 (15625Khz)
	OCR2B	=	0;										// 0% duty cycle
	DDRD	=	DDRD | (1<<3);						// Make sure PORTD.3 is set as output for the servo
}


void InitInt0()
{
	//EICRA	=	(0<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);	// The falling edge of INT0 generates an interrupt request
	EICRA	=	(0<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);	// The rising edge of INT0 generates an interrupt request
	EIMSK	=	(0<<INT1) | (1<<INT0);								// External Interrupt Request 0 Enable
	EIFR	=	(1<<INTF1) | (1<<INTF0);							// Clear interrupt flag to avoid false triggers
	sei();															// Set global interrupt enable bit
}

void InitGPIO(void)
{
	//Set outputs on port C
	DDRC	=	DDRC | ((1<<MotorEnable) | (1<<MotorDirection) | (1<<MotorStep) | (1<<MotorMode1) | (1<<MotorMode2) | (1<<MotorMode2) );		
	//Set input on port D
	DDRD	=	DDRD &~(1<<PowerButton);						
	//Set outputs on port B
	DDRB	=	DDRB | (1<<AmbientLED) | (1<<PowerLED);
}