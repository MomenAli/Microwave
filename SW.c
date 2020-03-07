/*
 * File:   SW.c
 * Author: Momen Ali
 *
 * Created on February 24, 2020, 8:05 PM
 */


#include <xc.h>
#include "SW.h"
#include "IOPinInterface.h"
#include "GPIO.h"
#include "LCD.h"


/* SW voltage level */
#define SW_PRESSED_LEVEL        (0)
#define SW_RELEASED_LEVEL       (1)

/*
 * update the state depend on the previous state the state transition table
 */
void SW_UpdateState(SW_t sw);

/*
 * State Struct to hold data 
 * the state of the switch
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
 */

typedef struct 
{
    uint8 samples[2];
    uint8 state;
}SW_DATA_t;

/*--------------------------  private variables --------------------------*/

/*
 * Create array of structures to hold data
 */
 static SW_DATA_t SW_DATA[SW_NUM];
 
/*
 * Create array of I/O pin holds the sw parameters
 */ 
 IOPinStruct_t SW [SW_NUM];


 
 
/*------------------------ public functions implementation -----------------*/ 
 
 
 
void SW_Init(SW_t sw,volatile uint8 * dir,volatile uint8 * port , uint8 pin)
{
     
    SWITCH_PULLUP_RESISOR_ENABLE;
    
    // save the parameter to the switch
    SW[sw].dirRegPtr = dir;
    SW[sw].portRegPtr = port;
    SW[sw].pin = pin;
    
    // initialize the switch
    GPIO_Init_Pin(SW[sw].dirRegPtr,SW[sw].pin,GPIO_IN);
    SW_DATA[sw].state = SW_RELEASED;
    SW_DATA[sw].samples[0] = SW_RELEASED_LEVEL;
    SW_DATA[sw].samples[1] = SW_RELEASED_LEVEL;
    
}
uint8 SW_GetState(SW_t sw)
{
    uint8 ret =0;
    
    // return the state of the passed switch
    ret = SW_DATA[sw].state;
    
    return ret;
}
void SW_Update(void)
{
    int i =0;
    /*
     * create static variable to hold time
     */
    static uint8 SW_Time_Counter = 0; 
    SW_Time_Counter += OS_TICK;
    //check if it's my tick 
    if(SW_Time_Counter != SW_UPDATE_TICK)
    {
        return;
    }
    SW_Time_Counter = 0;
    
    for(i =0;i<SW_NUM;i++)
    {
        // update samples of plus switch
        SW_DATA[i].samples[0] = SW_DATA[i].samples[1];
        SW_DATA[i].samples[1] = GPIO_Read_Pin(*SW[i].portRegPtr,SW[i].pin);
        // update state of plus switch
        SW_UpdateState(i);
    }
  
}

void SW_UpdateState(SW_t sw)
{
    /*
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
     */
    
    // update the state of the passed switch
    // this switch represent the state machine of the switch
    switch(SW_DATA[sw].state)
    {
        
        case SW_PRE_RELEASED:
            if(SW_DATA[sw].samples[0] == SW_RELEASED_LEVEL && SW_DATA[sw].samples[1] == SW_RELEASED_LEVEL)
                SW_DATA[sw].state = SW_RELEASED;
            break;
        case SW_RELEASED:
            if(SW_DATA[sw].samples[0] == SW_PRESSED_LEVEL && SW_DATA[sw].samples[1] == SW_PRESSED_LEVEL)
                SW_DATA[sw].state = SW_PRE_PRESSED;
            break;
        case SW_PRE_PRESSED:
            if(SW_DATA[sw].samples[0] == SW_PRESSED_LEVEL && SW_DATA[sw].samples[1] == SW_PRESSED_LEVEL)
                SW_DATA[sw].state = SW_PRESSED;
            break;
        case SW_PRESSED:
            if(SW_DATA[sw].samples[0] == SW_RELEASED_LEVEL && SW_DATA[sw].samples[1] == SW_RELEASED_LEVEL)
                SW_DATA[sw].state = SW_PRE_RELEASED;
            break;
        default:
            
            break;
    }
}