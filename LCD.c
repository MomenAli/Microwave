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

#define LCD_UPDATE_TICK  (5)

// max number of char update per invoke
#define MAX_UPDATE (5)



/*******************************  private data ********************************/
// buffer to hold the data which displayed on the lcd
static uint8 LCD_Data_Buffer [LCD_LINES][LCD_CHAR];
// hold 1 in the updated places which didn't handled yet
static uint16  update_flag[LCD_LINES][(LCD_CHAR/sizeof(uint16))+1];
// hold the line number which has the turn to check if it needs to update
static uint8 line_counter = 0;
// counter to the ticks
static int tick_counter = 0;
// lines address
// please edit this if your hardware configuration 
static uint8 lines_offset_adresses [LCD_LINES] = {
                                            0x00     /* offset address for line 0*/,
                                            0x40     /* offset address for line 1*/
                                            };

// 

/**************************** private functions **********************************/

static void LCD_Write_Symbol(uint8 sym);
static void LCD_Write_Instruction(LCD_Instruction_t inst);
static void LCD_Data_Out(uint8 byte);
static void LCD_SetDDRAM(uint8 ADDRESS);
static void LCD_Init_Custom_Sym();
static void LCD_SetCGRAM(uint8 ADDRESS);

/*******************************************************************************/





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
    GPIO_Init_Nibble(&LCD_DATA_DIR,LCD_NIBBLE_NUM,GPIO_OUT);
#else
    GPIO_Init_Port(&LCD_DATA_DIR,GPIO_OUT);
#endif
    //START INIT SEQUENCE
#ifdef LCD_MODE_4_BIT
    // power up 15 ms
    __delay_ms(15);
    // prepare the RS and EN for initialization
    // set up instruction write
    GPIO_Write_Pin(LCD_RS_PORT,LCD_RS_PIN,0);
    // SET EN LOW
    GPIO_Write_Pin(LCD_EN_PORT,LCD_EN_PIN,0);
    
    //reset the lcd microcontroller 
    LCD_Data_Out(LCD_FunctionReset);            // first step of reset sequence
    __delay_ms(5);                             // delay for 4.1 ms
    
    LCD_Data_Out(LCD_FunctionReset);            // second step of reset sequence
    __delay_us(150);                            // delay for 4.1 ms
    
    LCD_Data_Out(LCD_FunctionReset);            // third step of reset sequence
    
    //set up 4 bit mode
    LCD_Data_Out(LCD_FunctionSet4bit);          
    __delay_us(50);
    
    // set up mode lines font
    LCD_Write_Instruction(LCD_FunctionSet4bit);
    __delay_us(50);
    
    // Display off
    LCD_Write_Instruction(LCD_DisplayOff);
    __delay_us(50);
    
    //clear display 
    LCD_Write_Instruction(LCD_Clear);
    __delay_ms(2);
    
    //set up displayed address increment auto, shift off
    LCD_Write_Instruction(LCD_EntryMode);
    __delay_us(50);
    
    // End Initialization
    
    // Display on
    LCD_Write_Instruction(LCD_DisplayOn);
    __delay_us(50);
    
    LCD_Init_Custom_Sym();
    
#else 
    /* LCD_MODE_8_BIT */
    // power up delay 15 ms
    __delay_ms(15);
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
    
    LCD_Init_Custom_Sym();
#endif
}

/*******************************************************************
 * Name :       LCD_Write_Symbol
 * Purpose :    send a character to the lcd data register   
 * Entry :      byte of data represent location in char map (CGROM)  
 * Exit :       void
 * Notes:       support both 8 bit and 4 bit mode
 */
static void LCD_Write_Symbol(uint8 sym)
{
    // set up data write
    GPIO_Write_Pin(LCD_RS_PORT,LCD_RS_PIN,1);
    // SET EN LOW
    GPIO_Write_Pin(LCD_EN_PORT,LCD_EN_PIN,0);
#ifdef LCD_MODE_4_BIT
    //write the data
    // most significant nibble
    LCD_Data_Out((sym>>4));
    // least significant nibble
    LCD_Data_Out(sym);
#else
    //write the data 
    LCD_Data_Out(sym);
#endif
}
/*******************************************************************
 * Name :       LCD_Write_String
 * Purpose :    send a string of char to lcd 
 * Entry :      array of char  
 * Exit :       void
 * Notes:       display the array as string
 */
//void LCD_Write_String(uint8  str[])
//{
////    if(sizeof(*str) == 0)return;
////    static uint8 counter = 0;
////    LCD_Write_Symbol()
//}
/*******************************************************************
 * Name :       LCD_Write_Instruction
 * Purpose :    send byte to the instruction register   
 * Entry :      byte  
 * Exit :       void
 * Notes:       support both 8 bit mode and 4 bit mode
 */

static void LCD_Write_Instruction(LCD_Instruction_t inst)
{
    // set up instruction write
    GPIO_Write_Pin(LCD_RS_PORT,LCD_RS_PIN,0);
    // SET EN LOW
    GPIO_Write_Pin(LCD_EN_PORT,LCD_EN_PIN,0);
#ifdef LCD_MODE_4_BIT
    LCD_Data_Out((inst>>4));
    LCD_Data_Out(inst);
#else
    //write the instruction 
    LCD_Data_Out(inst);
#endif
}
/*******************************************************************
 * Name :       LCD_Data_Out
 * Purpose :    send byte in general to LCD, destination unknown   
 * Entry :      byte  
 * Exit :       void
 * Notes:       support both 8 bit mode and 4 bit mode
 */

static void LCD_Data_Out(uint8 byte)
{
#ifdef LCD_MODE_4_BIT
       // write least significant nibble of data on lcd data terminals
       GPIO_Write_Nibble(LCD_DATA_PORT,byte,LCD_NIBBLE_NUM);
       // input data sequence
       // set EN pin high
       GPIO_Write_Pin(LCD_EN_PORT,LCD_EN_PIN,1);
       // enable pulse delay (data set up time))
       __delay_us(100);
       // set EN pin low
       GPIO_Write_Pin(LCD_EN_PORT,LCD_EN_PIN,0);
       // delay for data hold time
       __delay_us(1);
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
/*******************************************************************
 * Name :       LCD_SetSymbol
 * Purpose :    update symbol on the buffer of the lcd and rise the flag of update   
 * Entry :      symbol, row and column of the symbol  
 * Exit :       void
 * Notes:       if the row and column is out of index this process will be ignored
 */
void LCD_SetSymbol(uint8 sym,uint8 row,uint8 column)
{
    if(row >= LCD_LINES && column >= LCD_CHAR)return;
    LCD_Data_Buffer[row][column] = sym;
    update_flag[row][column/16] |= (0x0001<<(column%16));
}
/*******************************************************************
 * Name :       LCD_SetString
 * Purpose :    set    
 * Entry :      byte  
 * Exit :       void
 * Notes:       support both 8 bit mode and 4 bit mode
 */

void LCD_SetString(uint8 sym[],uint8 row,uint8 column,uint8 number)
{
    int i;
    //uint8 sym2[5] = {'H','e','l','l','o'} ;
    if(row >= LCD_LINES && column >= LCD_CHAR)return;
    
    for(i=0;i<number;i++)
    {
        LCD_Data_Buffer[row][column+i] = sym[i];
        update_flag[row][(column+i)/16] |= (0x0001<<((column+i)%16));
    }
    
}
/*******************************************************************
 * Name :       LCD_SetDDRAM
 * Purpose :    set the address of the DDRAM     
 * Entry :      byte  
 * Exit :       void
 * Notes:       
 */
static void LCD_SetDDRAM(uint8 ADDRESS)
{
    ADDRESS &= 0x7f;
    ADDRESS |= 0x80;
    LCD_Write_Instruction(ADDRESS);
}

/*******************************************************************
 * Name :       LCD_Update
 * Purpose :    task made to update the lcd values   
 * Entry :      void  
 * Exit :       void
 * Notes:       
 */
void LCD_Update(void)
{   
    uint8 j,i,updated = 0;
    tick_counter += OS_TICK;
    if(tick_counter != LCD_UPDATE_TICK)return;
    //reset the tick counter 
    tick_counter = 0;
    //iteration for column flags buffer
    for(j = 0;j<((LCD_CHAR/16)+1);j++)
    {
        if(update_flag[line_counter][j]!=0)
        {
            // if true we have something to update
            for(i=0;i<16;i++)
            {
                // check for update flag
                if((update_flag[line_counter][j])&(0x0001<<i))
                {
                    // symbol need to update
                    uint8 address = lines_offset_adresses[line_counter] + ((j*16)+i);
                    // update the cursor position
                    LCD_SetDDRAM(address);
                    // update the LCD data
                    LCD_Write_Symbol(LCD_Data_Buffer[line_counter][((j*16)+i)]);
                    // reset the update flag
                    update_flag[line_counter][j] &= ~(1<<i);
                    // updated symbols counter
                    updated++;
                    if(updated == MAX_UPDATE || update_flag[line_counter][j]==0 )break;
                }
            }
        }
    }
    line_counter++;
    if(line_counter == LCD_LINES)line_counter = 0;
    
}

static void LCD_Init_Custom_Sym()
{
    // create first motor custom char
    int i;
    uint8 data[8] = {   0x00,
                        0x00,
                        0x00,
                        0x00,
                        0x00,
                        0xF8,
                        0xF8,
                        0x00};
    LCD_SetCGRAM(LCD_MOTOR1*8);
    for(i =0;i<8;i++){
        LCD_Write_Symbol(data[i]);
    }
    // create second motor custom char
    data[0] = 0x00;
    data[1] = 0xF8;
    data[2] = 0xF8;
    data[3] = 0x00;
    data[4] = 0x00;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x00;
    LCD_SetCGRAM(LCD_MOTOR2*8);
    for(i =0;i<8;i++){
        LCD_Write_Symbol(data[i]);
    }
    // create third motor custom char
    data[0] = 0x00;
    data[1] = 0x03;
    data[2] = 0x03;
    data[3] = 0x00;
    data[4] = 0x00;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x00;
    LCD_SetCGRAM(LCD_MOTOR3*8);
    for(i =0;i<8;i++){
        LCD_Write_Symbol(data[i]);
    }
    
    // create fourth motor custom char
    data[0] = 0x00;
    data[1] = 0x00;
    data[2] = 0x00;
    data[3] = 0x00;
    data[4] = 0x00;
    data[5] = 0x03;
    data[6] = 0x03;
    data[7] = 0x00;
    LCD_SetCGRAM(LCD_MOTOR4*8);
    for(i =0;i<8;i++){
        LCD_Write_Symbol(data[i]);
    }
    
    // create lamp1 custom char
    data[0] = 0xFF;
    data[1] = 0x11;
    data[2] = 0x15;
    data[3] = 0x15;
    data[4] = 0x15;
    data[5] = 0xFF;
    data[6] = 0xFF;
    data[7] = 0x04;
    LCD_SetCGRAM(LCD_LAMP*8);
    for(i =0;i<8;i++){
        LCD_Write_Symbol(data[i]);
    }
    
    
    
    // create heater custom char
    
    data[0] = 0xE9;
    data[1] = 0xF2;
    data[2] = 0xE9;
    data[3] = 0xF2;
    data[4] = 0x00;
    data[5] = 0xFF;
    data[6] = 0xFF;
    data[7] = 0x0E;
    LCD_SetCGRAM(LCD_HEATER*8);
    for(i =0;i<8;i++){
        LCD_Write_Symbol(data[i]);
    }  
    
      // create door custom char
    
    data[0] = 0xFF;
    data[1] = 0x11;
    data[2] = 0x11;
    data[3] = 0x11;
    data[4] = 0x19;
    data[5] = 0x11;
    data[6] = 0x11;
    data[7] = 0xFF;
    LCD_SetCGRAM(LCD_DOOR*8);
    for(i =0;i<8;i++){
        LCD_Write_Symbol(data[i]);
    }  
}
static void LCD_SetCGRAM(uint8 ADDRESS)
{
    ADDRESS &= 0x3f;
    ADDRESS |= 0x40;
    LCD_Write_Instruction(ADDRESS);
}