/*
 * File:   LCD.c
 * Author: Momen Ali
 *
 * Created on February 25, 2020, 10:35 AM
 */


#include <xc.h>
#include <stdlib.h>
#include "GPIO.h"
#include "Port.h"
#include "LCD.h"




/*******************************************************************
 * Name :       LCD_Init
 * Purpose :    initialize the lcd pins and make the initial sequence to initialize LCD  
 * Entry :      void  
 * Exit :       void
 * Notes:       support both 8 bit mode and 4 bit mode
 */
void LCD_Init(void)
{
    // 4 bit mode 
    // please put this init in the beginning of the main
    //initialize the lcd pins
    //EN
    GPIO_Init_Pin(&LCD_EN_DIR,LCD_EN_PIN,GPIO_OUT);
    //RS
    GPIO_Init_Pin(&LCD_RS_DIR,LCD_RS_PIN,GPIO_OUT);
    //DATA
#ifdef LCD_MODE_4_BIT
    GPIO_Init_Nibble(LCD_DATA_DIR,LCD_NIBBLE_NUM,GPIO_OUT);
#else
    GPIO_Init_Port(&LCD_DATA_DIR,GPIO_OUT);
#endif
    //START INIT SEQUENCE
#ifdef LCD_MODE_4_BIT
    // delay for 15 ms
    __delay_ms(15);
    
    
#else 
    /* LCD_MODE_8_BIT */
    // power up delay 15 ms
    __delay_ms(35);
    //reset the lcd microcontroller 
    LCD_Write_Instruction(LCD_FunctionReset);   //first step of reset sequence
    __delay_ms(10);                             // delay at least 4.1 ms
    
    LCD_Write_Instruction(LCD_FunctionReset);   //second step of reset sequence
    __delay_us(150);                             // delay at least 100 us
    
    LCD_Write_Instruction(LCD_FunctionReset);   //third step of reset sequence
    
    // set up 8bit , lines and font using function set
    LCD_Write_Instruction(LCD_FunctionSet8bit);
    __delay_us(50);
    
    // Display On/Off Control instruction
    LCD_Write_Instruction(LCD_DisplayOff);       // turn display OFF
    __delay_us(50);                              

// Clear Display instruction
    LCD_Write_Instruction(LCD_Clear);            // clear display RAM
    __delay_ms(2);                                   // 1.64 mS delay 

// ; Entry Mode Set instruction
    LCD_Write_Instruction(LCD_EntryMode);        // set desired shift characteristics
    __delay_ms(50);                               

// END OF INITIALIZATION

// Display On/Off Control instruction
    LCD_Write_Instruction(LCD_DisplayOn);        // turn the display ON
    __delay_ms(50);                              
#endif
}

/*******************************************************************
 * Name :       LCD_Write_Char
 * Purpose :    send a character to the lcd data register   
 * Entry :      byte of data represent location in char map (CGROM)  
 * Exit :       void
 * Notes:       
 */
void LCD_Write_Char(uint8 ch)
{
    // set up data write
    GPIO_Write_Pin(LCD_RS_PORT,LCD_RS_PIN,1);
    // SET EN LOW
    GPIO_Write_Pin(LCD_EN_PORT,LCD_EN_PIN,0);
    //write the instruction 
    LCD_Write_Byte(ch);
}
/*******************************************************************
 * Name :       LCD_Write_String
 * Purpose :    send a string of char to lcd 
 * Entry :      array of char  
 * Exit :       void
 * Notes:       display the array as string
 */
void LCD_Write_String(uint8  str[])
{
//    if(sizeof(*str) == 0)return;
//    static uint8 counter = 0;
//    LCD_Write_Char()
}
/*******************************************************************
 * Name :       LCD_Write_Instruction
 * Purpose :    send byte to the instruction register   
 * Entry :      byte  
 * Exit :       void
 * Notes:       support both 8 bit mode and 4 bit mode
 */

void LCD_Write_Instruction(LCD_Instruction_t inst)
{
    // set up instruction write
    GPIO_Write_Pin(LCD_RS_PORT,LCD_RS_PIN,0);
    // SET EN LOW
    GPIO_Write_Pin(LCD_EN_PORT,LCD_EN_PIN,0);
    //write the instruction 
    LCD_Write_Byte(inst);
}
/*******************************************************************
 * Name :       LCD_Write_Byte
 * Purpose :    send byte in general to LCD, destination unknown   
 * Entry :      byte  
 * Exit :       void
 * Notes:       support both 8 bit mode and 4 bit mode
 */

void LCD_Write_Byte(uint8 byte)
{
#ifdef LCD_MODE_4_BIT
    
#else
    // write the data on lcd data terminals
    GPIO_Write_Port(LCD_DATA_PORT,byte);
    // input data sequence
    // set EN pin high
    GPIO_Write_Pin(LCD_EN_PORT,LCD_EN_PIN,1);
    // enable pulse delay (data set up time))
    __delay_us(100);
    // set EN pin low
    GPIO_Write_Pin(LCD_EN_PORT,LCD_EN_PIN,0);
    // delay for data hold time
    __delay_us(1);
#endif
}


