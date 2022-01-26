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
volatile unsigned int g_MotorTimer;
volatile unsigned int g_MotorPulseTimer;


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
			
			break;
			
			case STATE_IDLE:
			/*System idle state
			motor disabled
			ambient light off
			power led breathing			
			*/
				ControlPowerLED(OFF);
				ControlMotorEnable(ON);
				g_Delay++;
				gStateMachine++;
			break;
			
			case STATE_ROTATE:
				g_Delay++;
				/*Increment motor pulses*/
				g_MotorPulseTimer++;
				
				if (g_MotorTimer == 3)
				{
					PINC = (1<< MotorStep);	
				}
				
				if (g_MotorTimer > 4)
				{
					PINC = (1<< MotorStep);
					g_MotorTimer = 0;
				}
			break;
			
			case STATE_DIMMING:
			
			break;

			case STATE_SPEEDADJUST:
			
			break;
			
			default:
			/*Should never enter this state*/
			/*Add fault handling*/
			break;			
		}
		
		if (g_Timer0 == 100)
		{
			//ControlPowerLED(ON);
			TogglePowerLED();
			g_Timer0 = 0;
		}
		
		if (g_Timer0 > 200)
		{
			ControlPowerLED(OFF);
			g_Timer0 = 0;
		}
	}
}