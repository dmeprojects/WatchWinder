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

unsigned char gStateMachine = STATE_BOOT;

volatile unsigned char g_Delay;
volatile unsigned char g_INT0;
volatile unsigned char g_ButtonPressed;
volatile unsigned char g_RFState;
volatile unsigned int g_Timer0;
volatile unsigned int g_UartTimer;
volatile unsigned int g_BlinkTimer;
volatile unsigned int g_RFTimer;
volatile unsigned char g_RFData[];
volatile unsigned char RFDataCounter;
volatile unsigned char g_RFDataReady;




int main(void)
{
	setup();
	gStateMachine = STATE_IDLE;
    while(1)
    {
        switch (gStateMachine)
		{
			case STATE_BOOT:
			
			break;
			
			case STATE_IDLE:
			
			break;
			
			case STATE_ROTATE:
			
			break;
			
			default:
			/*Should never enter this state*/
			/*Add fault handling*/
			break;
			
			
			
		}
		
    }
}