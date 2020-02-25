

/* 
 * File:        Port.h
 * Author:      Momen Ali
 * Comments:    this file contain all the schematic configuration 
 * Revision history:  24/2/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PORT_H
#define	PORT_H

#include "Main.h"

//Lamp output pin 
#define  LAMP_PORT GPIO_PORTB_DATA
#define  LAMP_DIR  GPIO_PORTB_DIR
#define  LAMP_PIN  PIN_0


//Heater output pin 
#define  HEATER_PORT GPIO_PORTB_DATA
#define  HEATER_DIR  GPIO_PORTB_DIR
#define  HEATER_PIN  PIN_1


//Motor output pin 
#define  MOTOR_PORT GPIO_PORTC_DATA
#define  MOTOR_DIR  GPIO_PORTC_DIR
#define  MOTOR_PIN  PIN_2



#endif	/* PORT_H */

