
/* 
 * File:        LCD.h
 * Author:      Momen Ali
 * Comments:    Driver for LCD
 * Revision history:    25/2/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_H
#define	LCD_H

#include <xc.h>
#include "Port.h" // include processor files - each processor file is guarded.  

#define LCD_LINES (2)
#define LCD_CHAR  (40)



typedef enum
{
    LCD_MOTOR1,
    LCD_MOTOR2,
    LCD_MOTOR3,
    LCD_MOTOR4,
    LCD_LAMP,
    LCD_HEATER,
    LCD_DOOR
    /* LCD_MOTOR1 = 0*8,
    LCD_MOTOR2 = 1*8,
    LCD_MOTOR3 = 2*8,
    LCD_MOTOR4 = 3*8,
    LCD_LAMP = 4*8,
    LCD_HEATER = 5*8 */
}LCD_CUSTOM_CHAR;

typedef enum 
{
#ifdef LCD_MODE_4_BIT
    LCD_Clear           = 0b00000001,          // replace all characters with ASCII 'space'
    LCD_Home            = 0b00000010,          // return cursor to first position on first line
    LCD_EntryMode       = 0b00000110,          // shift cursor from left to right on read/write
    LCD_DisplayOff      = 0b00001000,          // turn display off
    LCD_DisplayOn       = 0b00001100,          // display on, cursor off, don't blink character
    LCD_FunctionReset   = 0b00110000,          // reset the LCD
    LCD_FunctionSet4bit = 0b00101000,          // 4-bit data, 2-line display, 5 x 7 font
    LCD_SetCursor       = 0b10000000           // set cursor position
#else
    LCD_Clear           = 0b00000001,          // replace all characters with ASCII 'space'
    LCD_Home            = 0b00000010,          // return cursor to first position on first line
    LCD_EntryMode       = 0b00000110,          // shift cursor from left to right on read/write
    LCD_DisplayOff      = 0b00001000,          // turn display off
    LCD_DisplayOn       = 0b00001100,          // display on, cursor off, don't blink character
    LCD_FunctionReset   = 0b00110000,          // reset the LCD
    LCD_FunctionSet8bit = 0b00111000,          // 8-bit data, 2-line display, 5 x 7 font
    LCD_SetCursor       = 0b10000000,          // set cursor position
#endif
}LCD_Instruction_t;


void LCD_Init(void);
void LCD_SetSymbol(uint8 sym,uint8 row,uint8 column);
void LCD_SetString(uint8 sym[],uint8 row,uint8 column,uint8 number);
void LCD_Update(void);

#endif	/* LCD_H */

