/*
 * File:   KPad.c
 * Author: Momen Ali
 *
 * Created on February 24, 2020, 8:21 PM
 */


#include <xc.h>
#include "Keypad.h"
#include "IOPinInterface.h"
#include "Port.h"
#include "GPIO.h"
#include "Keypad.h"
#include "LCD.h"

#define KEYPAD_UPDATE_TICK (10)

/*
 * State Structure to hold data 
 * the state of every switch in the keypad
 * 2 samples of the last situation of the switch
 *   _________________________________________________________________
 *  | state   | last sample (n-1) | present sample (n) |  next state  |
 *  |_________|___________________|____________________|______________|
 *  | pre rel |         1         |        1           |   release    |
 *  |_________|___________________|____________________|______________|
 *  | release |         0         |        0           |   pre pre    |
 *  |_________|___________________|____________________|______________|
 *  | pre pre |         0         |        0           |   pressed    |
 *  |_________|___________________|____________________|______________|
 *  | pressed |         1         |        1           |   pre rel    |
 *  |_________|___________________|____________________|______________|
 * 
 *  the above table assumes that 
 *  pressed level  = 0
 *  released level = 1
 */

typedef struct 
{
    uint8 samples[2];
    uint8 state;
}KEYPAD_BTN_DATA_t;


/*
 * this structure keypad  
 * KP_O_Pins : holds ana array of output pins of the keypad 
 * KP_I_Pins : holds ana array of input pins of the keypad 
 */
typedef struct
{
    IOPinStruct_t KP_O_Pins[KEYPAD_OUTPUT_PINS_NUMBER];
    IOPinStruct_t KP_I_Pins[KEYPAD_INPUT_PINS_NUMBER];
}Keypad_Struct_t;


/*---------------------   private variables  ----------------------*/

/*
 * Create array of structures to hold data
 * Note:
 * the index of this array the integer represented by KP_t enum
 */
static KEYPAD_BTN_DATA_t KP_Btn_Data [KEYPAD_BUTTON_NUMBER];

/* structure contains the I/O pins needed*/
static Keypad_Struct_t keypad;

/**/
static uint8 current_column = 0;

/* */
static uint8 tick_counter = 0;




/*-------------------  public functions implementation ----------------------*/

void keypad_Init(void)
{
    
    KEYPAD_PULLUP_RESISOR_ENABLE;
    
    // define the Input pins
    // row 1
    keypad.KP_I_Pins[0].portRegPtr = &KEYPAD_ROW1_PORT;
    keypad.KP_I_Pins[0].dirRegPtr  = &KEYPAD_ROW1_DIR;
    keypad.KP_I_Pins[0].pin        = KEYPAD_ROW1_PIN;
    GPIO_Init_Pin(keypad.KP_I_Pins[0].dirRegPtr,keypad.KP_I_Pins[0].pin,GPIO_IN);
    // row 2
    keypad.KP_I_Pins[1].portRegPtr = &KEYPAD_ROW2_PORT;
    keypad.KP_I_Pins[1].dirRegPtr  = &KEYPAD_ROW2_DIR;
    keypad.KP_I_Pins[1].pin        = KEYPAD_ROW2_PIN;
    GPIO_Init_Pin(keypad.KP_I_Pins[1].dirRegPtr,keypad.KP_I_Pins[1].pin,GPIO_IN);
    // row 3
    keypad.KP_I_Pins[2].portRegPtr = &KEYPAD_ROW3_PORT;
    keypad.KP_I_Pins[2].dirRegPtr  = &KEYPAD_ROW3_DIR;
    keypad.KP_I_Pins[2].pin        = KEYPAD_ROW3_PIN;
    GPIO_Init_Pin(keypad.KP_I_Pins[2].dirRegPtr,keypad.KP_I_Pins[2].pin,GPIO_IN);
    // row 4
    keypad.KP_I_Pins[3].portRegPtr = &KEYPAD_ROW4_PORT;
    keypad.KP_I_Pins[3].dirRegPtr  = &KEYPAD_ROW4_DIR;
    keypad.KP_I_Pins[3].pin        = KEYPAD_ROW4_PIN;
    GPIO_Init_Pin(keypad.KP_I_Pins[3].dirRegPtr,keypad.KP_I_Pins[3].pin,GPIO_IN);
    // define the Output pins
    // column 1
    keypad.KP_O_Pins[0].portRegPtr = &KEYPAD_COLUMN1_PORT;
    keypad.KP_O_Pins[0].dirRegPtr  = &KEYPAD_COLUMN1_DIR;
    keypad.KP_O_Pins[0].pin        = KEYPAD_COLUMN1_PIN;
    GPIO_Init_Pin(keypad.KP_O_Pins[0].dirRegPtr,keypad.KP_O_Pins[0].pin,GPIO_OUT);
    // column 2
    keypad.KP_O_Pins[1].portRegPtr = &KEYPAD_COLUMN2_PORT;
    keypad.KP_O_Pins[1].dirRegPtr  = &KEYPAD_COLUMN2_DIR;
    keypad.KP_O_Pins[1].pin        = KEYPAD_COLUMN2_PIN;
    GPIO_Init_Pin(keypad.KP_O_Pins[1].dirRegPtr,keypad.KP_O_Pins[1].pin,GPIO_OUT);
    // column 3
    keypad.KP_O_Pins[2].portRegPtr = &KEYPAD_COLUMN3_PORT;
    keypad.KP_O_Pins[2].dirRegPtr  = &KEYPAD_COLUMN3_DIR;
    keypad.KP_O_Pins[2].pin        = KEYPAD_COLUMN3_PIN;
    GPIO_Init_Pin(keypad.KP_O_Pins[2].dirRegPtr,keypad.KP_O_Pins[2].pin,GPIO_OUT);
    
    // reset
    GPIO_Write_Pin(*keypad.KP_O_Pins[0].portRegPtr,keypad.KP_O_Pins[0].pin,SW_RELEASED_LEVEL);
    GPIO_Write_Pin(*keypad.KP_O_Pins[1].portRegPtr,keypad.KP_O_Pins[1].pin,SW_RELEASED_LEVEL);
    GPIO_Write_Pin(*keypad.KP_O_Pins[2].portRegPtr,keypad.KP_O_Pins[2].pin,SW_RELEASED_LEVEL);
    
    // active the first column
    GPIO_Write_Pin(*keypad.KP_O_Pins[current_column].portRegPtr,keypad.KP_O_Pins[current_column].pin,SW_PRESSED_LEVEL);
    
}
uint8 keypad_getState(KP_t item)
{
    return KP_Btn_Data[item].state;
}
void keypad_Update(void)
{
    int i;
    tick_counter += OS_TICK;
    if(tick_counter != KEYPAD_UPDATE_TICK){
        // active the next column
        GPIO_Write_Pin(*keypad.KP_O_Pins[current_column].portRegPtr,keypad.KP_O_Pins[current_column].pin,SW_PRESSED_LEVEL);
        return;
    }
    tick_counter = 0;
    
    
    //sampling 
    
    for(i =0; i<KEYPAD_INPUT_PINS_NUMBER;i++)
    {
        // row number i with current column 
        // transition for old sample
        KP_Btn_Data[current_column + 3*i].samples[0] = KP_Btn_Data[current_column+ 3*i].samples[1];
        // get new sample 
        KP_Btn_Data[current_column+ 3*i].samples[1] = GPIO_Read_Pin(*keypad.KP_I_Pins[i].portRegPtr,keypad.KP_I_Pins[i].pin);
    }

    
    // update the state
    
    for(i =0; i<KEYPAD_INPUT_PINS_NUMBER;i++)
    {
        switch(KP_Btn_Data[current_column + 3*i].state)
        {

            case SW_PRE_RELEASED:
                if(KP_Btn_Data[current_column + 3*i].samples[0] == SW_RELEASED_LEVEL && KP_Btn_Data[current_column + 3*i].samples[1] == SW_RELEASED_LEVEL)
                    KP_Btn_Data[current_column + 3*i].state = SW_RELEASED;
                break;
            case SW_RELEASED:
                if(KP_Btn_Data[current_column + 3*i].samples[0] == SW_PRESSED_LEVEL && KP_Btn_Data[current_column + 3*i].samples[1] == SW_PRESSED_LEVEL)
                    KP_Btn_Data[current_column + 3*i].state = SW_PRE_PRESSED;
                break;
            case SW_PRE_PRESSED:
                if(KP_Btn_Data[current_column + 3*i].samples[0] == SW_PRESSED_LEVEL && KP_Btn_Data[current_column + 3*i].samples[1] == SW_PRESSED_LEVEL)
                    KP_Btn_Data[current_column + 3*i].state = SW_PRESSED;
                break;
            case SW_PRESSED:
                if(KP_Btn_Data[current_column + 3*i].samples[0] == SW_RELEASED_LEVEL && KP_Btn_Data[current_column + 3*i].samples[1] == SW_RELEASED_LEVEL)
                    KP_Btn_Data[current_column + 3*i].state = SW_PRE_RELEASED;
                break;
            default:
                break;
        }
        if(KP_Btn_Data[current_column + 3*i].state == SW_PRE_PRESSED)LCD_SetSymbol('0'+current_column + 3*i+1 , 0 , current_column + 3*i);
    }
    //switch to the next column
    
    // reset last output pin
    GPIO_Write_Pin(*keypad.KP_O_Pins[current_column].portRegPtr,keypad.KP_O_Pins[current_column].pin,SW_RELEASED_LEVEL);
    //keypad.KP_O_Pins[current_column].
    // increment current_column
    current_column++;
    if(current_column == KEYPAD_OUTPUT_PINS_NUMBER)current_column = 0;
    
    
    
}



