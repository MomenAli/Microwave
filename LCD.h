
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

#include <xc.h> // include processor files - each processor file is guarded.  

typedef enum 
{
    LCD_Clear           = 0b00000001,          // replace all characters with ASCII 'space'
    LCD_Home            = 0b00000010,          // return cursor to first position on first line
    LCD_EntryMode       = 0b00000110,          // shift cursor from left to right on read/write
    LCD_DisplayOff      = 0b00001000,          // turn display off
    LCD_DisplayOn       = 0b00001100,          // display on, cursor off, don't blink character
    LCD_FunctionReset   = 0b00110000,          // reset the LCD
    LCD_FunctionSet8bit = 0b00111000,          // 8-bit data, 2-line display, 5 x 7 font
    LCD_SetCursor       = 0b10000000,          // set cursor position
}LCD_Instruction_t;


void LCD_Init(void);
void LCD_Write_Char(uint8 ch);
void LCD_Write_String(uint8 * str);
void LCD_Write_Instruction(LCD_Instruction_t inst);
void LCD_Write_Byte(uint8 byte);

#endif	/* LCD_H */

