

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

//LCD pins
//EN
#define LCD_EN_PORT GPIO_PORTE_DATA
#define LCD_EN_DIR  GPIO_PORTE_DIR
#define LCD_EN_PIN  PIN_1
//RS
#define LCD_RS_PORT GPIO_PORTE_DATA
#define LCD_RS_DIR  GPIO_PORTE_DIR
#define LCD_RS_PIN  PIN_2
//LCD data pins

/* if 4 bit mode remove the below comment 
 * else comment define LCD_MODE_4_BIT
 */ 
#define LCD_MODE_4_BIT
#define LCD_DATA_PORT GPIO_PORTD_DATA
#define LCD_DATA_DIR  GPIO_PORTD_DIR
#ifdef LCD_MODE_4_BIT
#define LCD_NIBBLE_NUM    (1)
#endif



#endif	/* PORT_H */

