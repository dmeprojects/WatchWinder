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
#include "Timers.h"

unsigned char gStateMachine = STATE_BOOT;	//State machine variable

volatile unsigned int g_Delay;
volatile unsigned char g_INT0;
volatile unsigned char g_ButtonPressed;
volatile unsigned int g_Timer0;
volatile unsigned int g_UartTimer;
volatile unsigned int g_BlinkTimer;
volatile unsigned int g_MotorTimer;
volatile unsigned int g_MotorPulseTimer;

volatile int g_MotorSteps;
volatile int g_MotorPosition;
volatile unsigned char g_MotorDirection;


unsigned char g_State;
unsigned char g_LedState;
unsigned char g_PowerLEDState;
unsigned char g_AmbientLEDState;


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
			ControlPowerLED(OFF);
			ControlMotorEnable(OFF);
			ControlAmbientLED(OFF);
			gStateMachine++;			
			
			break;
			
			case STATE_IDLE:
			/*System idle state
			motor disabled
			ambient light off
			power led breathing			
			*/
			
			if (g_ButtonPressed)
			{
				g_ButtonPressed = 0;
				ControlPowerLED(ON);
				ControlMotorEnable(ON);
				g_MotorSteps = 0;
				g_MotorPosition = 500;
				g_MotorDirection = FORWARD;
				gStateMachine++;
				StartTimer2(0);
			}

			break;
			
			case STATE_ROTATE:
			//PINC = (1<< MotorStep);	
				/*Increment motor pulses*/
				if (g_MotorSteps == g_MotorPosition)	//Change direction
				{
					if (g_MotorSteps < 0)
					{
						g_MotorDirection = FORWARD;
						ToggleMotorDirection();
						g_MotorPosition = 500;
					}
					else
					{
						g_MotorDirection = BACKWARD;
						ToggleMotorDirection();
						g_MotorPosition = -500;
					}				

				}
				
				if (g_ButtonPressed)
				{
					g_ButtonPressed = 0;
					ControlPowerLED(OFF);
					ControlMotorEnable(OFF);
					gStateMachine = STATE_IDLE;
					StopTimer2();
				}
				//PINC = (1<< MotorStep);	
				
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
	}
}