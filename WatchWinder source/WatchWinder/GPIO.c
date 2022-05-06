/*
 * GPIO.c
 *
 * Created: 3/8/2017 8:26:01 PM
 *  Author: Petervg
 */ 

#include <avr/io.h>
#include "GPIO.h"
//#include "lcd/my_lcd.h"
#include "./global.h"


extern unsigned char g_State;
extern unsigned char g_LedState;
extern unsigned char g_PowerLEDState;
extern unsigned char g_AmbientLEDState;
extern volatile unsigned char g_RFState;


void ControlPowerLED(unsigned char LedState)
{
	if (LedState == ON)
	{		
		PORTB = PORTB | (1<<PowerLED);					// Turn on the led
		g_PowerLEDState = ON;
	}
	else
	{		
		PORTB = PORTB & ~(1<<PowerLED);				// Turn off the led
		g_PowerLEDState = OFF;
	}
}

void ControlAmbientLED(unsigned char LedState)
{
	if (LedState == ON)
	{
		PORTB = PORTB | (1<<AmbientLED);					// Turn on the led
		g_AmbientLEDState = ON;									
	}
	else
	{
		PORTB = PORTB & ~(1<<AmbientLED);				// Turn off the led
		g_AmbientLEDState = OFF;		
	}
}

void ControlMotorEnable (unsigned char MotorState)
{
	if (MotorState == ON)
	{
		PORTC |=  (1<<MotorEnable);
	}
	
	if (MotorState == OFF)
	{
		PORTC &= ~(1<<MotorEnable);
	}
}

void ControlMotorDirection (unsigned char Direction)
{
	if (Direction == FORWARD)
	{
		PORTC |= (1<< MotorDirection);
	}
	else
	{
		PORTC &= ~(1<<MotorDirection);
	}
}

void ToggleMotorDirection (void)
{
	PORTC |= (1<<MotorDirection);
}

void ToggleAmbientLED (void)
{
	PORTB |= (1<<AmbientLED);	
}

void TogglePowerLED (void)
{
	PORTB |= (1<<PowerLED);
}

unsigned char StatusPowerButton (void)
{
	if (PIND & (1 << PowerButton)){return FALSE;}
	else {return TRUE;}	
}


