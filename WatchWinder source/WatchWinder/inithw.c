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
#include "Timers.h"

void setup(void)
{
	// Internal peripherals
	// --------------------
	InitTimer0();		// Init timer0 for 1mS interrupts
	//InitTimer1();		// Init timer1 for PWM output 
	InitTimer2();		// Init Timer2 for motor pule step
	InitGPIO();			// Set PORTD.2 as input and PORTB.5 as output
	InitInt0();			// Enable falling egde interrupts
	
	/*Set step mode*/
	PORTC &= ~(1 << MotorMode0) | ~(1 << MotorMode1)| ~(1 << MotorMode2);	//Full step
	//PORTC = PORTC & (1 << MotorMode0) | ~(1 << MotorMode1)| ~(1 << MotorMode2);	//1/2 step
	//PORTC = PORTC & ~(1 << MotorMode0) | (1 << MotorMode1)| ~(1 << MotorMode2);	//1/4 step
	
	PORTC |= (1 << MotorMode2);	//1/16th stepp
	PORTC |= (1 << MotorMode2) | (1 << MotorMode0);	//1/16th stepp
	
	
	// External peripherals
	// --------------------
	
	/*Enable Interrupts*/
	sei();
}




void InitInt0()
{
	//EICRA	=	(0<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);	// The falling edge of INT0 generates an interrupt request
	EICRA	=	(0<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);	// The rising edge of INT0 generates an interrupt request
	EIMSK	=	(0<<INT1) | (1<<INT0);								// External Interrupt Request 0 Enable
	EIFR	=	(1<<INTF1) | (1<<INTF0);							// Clear interrupt flag to avoid false triggers
	//sei();															// Set global interrupt enable bit
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