/*
 * GPIO.h
 *
 * Created: 3/8/2017 8:26:23 PM
 *  Author: DMeynen
 */ 


#ifndef GPIO_H_
#define GPIO_H_

// prototypes
// -----------
void ControlPowerLED (unsigned char LedState);
void ControlAmbientLED (unsigned char LedState);
void ToggleAmbientLED (void);
void TogglePowerLED (void);
unsigned char StatusPowerButton (void);
void ControlMotorStep (unsigned char StepSTate);
void ControlMotorEnable (unsigned char MotorState);
void ToggleMotorStep (void);
void ControlMotorDirection (unsigned char Direction);
void ToggleMotorDirection (void);



#endif /* GPIO_H_ */