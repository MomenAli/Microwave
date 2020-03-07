

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
/* 
 * (0)   pins from 0 to 3
 * (1)   pins from 4 to 7
 * etc..
 */
#define LCD_NIBBLE_NUM    (1)
#endif


// keypad 

// define the Input pins
// row 1
#define KEYPAD_ROW1_PORT (GPIO_PORTD_DATA) 
#define KEYPAD_ROW1_DIR  (GPIO_PORTD_DIR) 
#define KEYPAD_ROW1_PIN  (PIN_3) 
// row 2
#define KEYPAD_ROW2_PORT (GPIO_PORTD_DATA) 
#define KEYPAD_ROW2_DIR  (GPIO_PORTD_DIR) 
#define KEYPAD_ROW2_PIN  (PIN_2) 
// row 3
#define KEYPAD_ROW3_PORT (GPIO_PORTD_DATA) 
#define KEYPAD_ROW3_DIR  (GPIO_PORTD_DIR) 
#define KEYPAD_ROW3_PIN  (PIN_1) 

// row 4
#define KEYPAD_ROW4_PORT (GPIO_PORTD_DATA) 
#define KEYPAD_ROW4_DIR  (GPIO_PORTD_DIR) 
#define KEYPAD_ROW4_PIN  (PIN_0) 
// define the Output pins
// column 1
#define KEYPAD_COLUMN1_PORT (GPIO_PORTB_DATA) 
#define KEYPAD_COLUMN1_DIR  (GPIO_PORTB_DIR) 
#define KEYPAD_COLUMN1_PIN  (PIN_0) 
// column 2
#define KEYPAD_COLUMN2_PORT (GPIO_PORTB_DATA) 
#define KEYPAD_COLUMN2_DIR  (GPIO_PORTB_DIR) 
#define KEYPAD_COLUMN2_PIN  (PIN_1) 
// column 3
#define KEYPAD_COLUMN3_PORT (GPIO_PORTB_DATA) 
#define KEYPAD_COLUMN3_DIR  (GPIO_PORTB_DIR) 
#define KEYPAD_COLUMN3_PIN  (PIN_2) 


#endif	/* PORT_H */

