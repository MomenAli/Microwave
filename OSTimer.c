/*
 * File:   OSTimer.c
 * Author: Momen Ali
 *
 * Created on February 25, 2020, 6:28 PM
 */


#include <xc.h>
#include"OSTimer.h"
#include "Main.h"
#include "LCD.h"
#include "DO.h"


/********************* private ***********************/
static uint16 tempCounter = 0;



void TMR_Init(void)
{
    // initialize the timer
    // set up the timer pre scaler
    TMR_PRESCALER_ACTIVE;
    TMR_PRESCALER_2;
    //enable the clock
    TMR0_ENABLE_CLOCK;
    //16 BIT TIMER
    TMR016BIT;
    // stop timer
    TMR0_STOP;
    
}



void __interrupt() TMR0_ISR(void) 
{
    static uint8 index = 0; // test
    
    static uint16 counter = 0;
    
    
    tempCounter+=OS_TICK;
    //tasks 
    
    
    //test code
    if(tempCounter >= 1000){
        tempCounter = 0;
        // update lcd as test
        LCD_SetSymbol(LCD_DOOR,index,counter);
        counter++;
        if(counter == 16)
        {counter=-1;index = 1; }
        
    }
    
    //end of test code
    
    LCD_Update();
    // reset the overflow flag
    TMR0_CLEAR_FLAG;
    // load the timer register with the tick
    TMR_LOAD_REGISTER(TMR0_TICK_NUM);
   
}
void TMR_Start(void)
{
    // clear the clock flag to start
    TMR0_CLEAR_FLAG;
    // load the timer register with the tick
    TMR_LOAD_REGISTER(TMR0_TICK_NUM);
    // enable the ISR
    TMR0_ENABLE_INTERRUPT;
    GLOBAL_INTERRUPT_ENABLE;
    // set the start bit
    TMR0_START;
    
}
void TMR_Stop(void)
{
    // stop timer 0
    TMR0_STOP;
}
uint8 TMR_CheckOverflow(void)
{
    // return the overflow flag
    return TMR0_GET_FLAG;
}


