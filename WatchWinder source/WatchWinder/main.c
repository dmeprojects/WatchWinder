/*
 * main.c
 *
 * Created: 11/22/2021 8:09:46 PM
 *  Author: nick_
 */ 

#include <xc.h>

#include <avr/io.h>
#include <stdlib.h>
#include "main.h"
#include "global.h"
#include "GPIO.h"
#include "inithw.h"

unsigned char gStateMachine = STATE_BOOT;	//State machine variable

volatile unsigned int g_Delay;
volatile unsigned char g_INT0;
volatile unsigned char g_ButtonPressed;
volatile unsigned int g_Timer0;
volatile unsigned int g_UartTimer;
volatile unsigned int g_BlinkTimer;


unsigned char g_State;
unsigned char g_LedState;
unsigned char g_PowerLEDState;
unsigned char g_AmbientLEDState;
volatile unsigned char g_RFState;

int main(void)
{
	g_ButtonPressed = 0;
	g_Timer0 = 0;
	g_LedState = 0;
	
	gStateMachine = STATE_IDLE;
	
	setup();
		
    while(1)
    {
        switch (gStateMachine)
		{
			case STATE_BOOT:
				g_Delay++;				
			break;
			
			case STATE_IDLE:
				ControlPowerLED(OFF);
				g_Delay++;
				gStateMachine++;
			break;
			
			case STATE_ROTATE:
				g_Delay++;
			break;
			
			case STATE_DIMMING:
			
			break;
				g_Delay++;
			case STATE_SPEEDADJUST:
			
			break;
			
			default:
			/*Should never enter this state*/
			/*Add fault handling*/
			break;			
		}
		
		if (g_Timer0 == 5)
		{
			ControlPowerLED(ON);
		}
		
		if (g_Timer0 > 10)
		{
			ControlPowerLED(OFF);
			g_Timer0 = 0;
		}
	}
}