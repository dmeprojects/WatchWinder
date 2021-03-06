/*
 * Interrupts.c
 *
 * Created: 3/8/2017 8:24:06 PM
 *  Author: Petervg
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "global.h"

extern volatile unsigned int g_Delay;
extern volatile unsigned char g_INT0;
extern volatile unsigned char g_ButtonPressed;
extern volatile unsigned int g_Timer0;
extern volatile unsigned int g_UartTimer;
extern volatile unsigned int g_BlinkTimer;

extern volatile unsigned int g_MotorTimer;
extern volatile unsigned int g_MotorPulseTimer;
extern volatile unsigned char g_MotorDirection;
extern volatile int g_MotorSteps;


volatile unsigned char g_SyncStatus = 0;
volatile unsigned char g_OnTimeSec = 0;
volatile unsigned char g_OnTimeMin = 0;
volatile unsigned char g_OnTimeHr = 0;
volatile unsigned char g_ZeroCounter = 0;

volatile unsigned char g_DataSync = 0;

volatile unsigned int g_OnTimems = 0;
volatile unsigned int MotorTimer = 0;


// Interrupt triggers every 1mS
// ----------------------------
ISR (TIMER0_COMPA_vect)
{
	// Delay used for debouce of switch on INT0
	// ----------------------------------------
	if (g_INT0)
	{
		// Check if the delay has passed AND button is actually pressed down
		if ( (++g_Delay > DELAY) & ((PIND & (1<<2)) == 0))
		{
			g_ButtonPressed = 1;
			g_Delay = 0;
			g_INT0 = 0;
		}
	}
	
	// General purpose timer value
	// ---------------------------
	g_Timer0++;
	
	g_MotorPulseTimer++;
	g_MotorTimer++;
	
	
	//Timer for blinking LED's
	//------------------------
	g_BlinkTimer++;
	
	// ADC timer
	// ---------
	MotorTimer++;	
	
	// Time counter (HH:MM:SS)
	// -----------------------
	if (++g_OnTimems == 1000)
	{
		g_OnTimems = 0;
		//g_DisplayDirty = 1;
		if (++g_OnTimeSec == 60)
		{		
			g_OnTimeSec = 0;
			if (++g_OnTimeMin == 60)
			{
				g_OnTimeMin = 0;
				if (++g_OnTimeHr == 25)
				{
					g_OnTimeHr = 0;
				}
			}
		}
	}
}

// Interrupt triggers on button pressed (PORTD.2, Arduino port 2)
// --------------------------------------------------------------
ISR (INT0_vect)
{
	g_INT0 = 1;
	g_Delay = 0;
}

/*
Interrupt triggers 
*/
ISR (TIMER2_COMPA_vect)
{	
	//Check OCR2A value
	//Switch between high and low value depending on OCR2A content
	//Increment or decrement motor steps
	if (OCR2A == HIGHTIME)
	{
		OCR2A = LOWTIME;
	}
	else
	{
		OCR2A = HIGHTIME;
	}
	
	if (g_MotorDirection == FORWARD)
	{	
		g_MotorSteps++;
	}
	else
	{		
		g_MotorSteps--;
	}	
}







