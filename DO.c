/*
 * File:   DO.c
 * Author: Momen Ali
 *
 * Created on February 24, 2020, 8:12 PM
 */


#include <xc.h>
#include "DO.h"
#include "Port.h"
#include "GPIO.h"

#define DO_NUM (3)
/*
 * array of structure of the DOs
 * please add any new DO to this array
 * and add the name of it in DO_t in the same index
 */

static DOStruct_t  DOArray[DO_NUM];


uint8 DO_Init(DO_t DO ,volatile uint8* port ,volatile uint8* dir,uint8 pinN ,LEDState_t state)
{
    DOArray[DO].portRegPtr = port;
    DOArray[DO].dirRegPtr = dir;
    DOArray[DO].pin = pinN;
    
    GPIO_Init_Pin(dir,pinN,GPIO_OUT);
    GPIO_Write_Pin(*port,pinN,state);
}
uint8 DO_GetState(DO_t DO)
{
    return GPIO_Read_Pin(*(DOArray[DO].portRegPtr),DOArray[DO].pin);
}
void DO_SetState(DO_t DO,LEDState_t state)
{
    GPIO_Write_Pin(*(DOArray[DO].portRegPtr),DOArray[DO].pin,state);
}
void DO_update(void)
{
    //do nothing here in this design
}