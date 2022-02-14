/*
 * global.h
 *
 * Created: 2/25/2017 11:01:47 AM
 *  Author: Dmeynen
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

//CPU Frequentie
//-----------------
#define F_CPU	8000000
//#define F_CPU	16000000

// instellingen
// ------------
#define DELAY			10				// ms delay for switch bounce (char)
#define BOOTDELAY		500			    // ms delay for booting up
#define UARTDELAY		1000			// Ms of delay before time and temperature is sent to the PC

#define DEFAULTBLINKSPEED 75			//ms delay of the default blinkspeed (default 150)
/*
External components
-------------------
*/
//LED outputs on Port B
#define AmbientLED	0	
#define PowerLED	1
#define MotorStep	3	//Connected to OC2A

//Button input on port D	
#define PowerButton	4	

//Motor controller signals on port C
#define MotorEnable		0
#define MotorDirection	1
//#define MotorStep		2
#define MotorMode0		3
#define MotorMode1		4
#define MotorMode2		5


// State defines of statemachine
// -----------------------------------
#define STATE_BOOT			1
#define STATE_IDLE			2
#define STATE_ROTATE		3
#define STATE_DIMMING		4
#define STATE_SPEEDADJUST	5


// general defines
// ----------------
#define ON				1
#define OFF				0
#define	TRUE			1
#define FALSE			0
#define OK				1
#define ERROR			0
#define FORWARD			1
#define BACKWARD		0

#endif /* GLOBAL_H_ */