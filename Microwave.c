/*
 * File:   Microwave.c
 * Author: Momen Ali
 *
 * Created on February 25, 2020, 6:30 PM
 */

#include <xc.h>

#include "DO.h"
#include "Port.h"

void main(void) {
    
    /* test DO module */
    // lamp initialization
    DO_Init(DO_LAMP,&LAMP_PORT,&LAMP_DIR,LAMP_PIN,DO_OFF);
    //heater initialization
    DO_Init(DO_HEATER,&HEATER_PORT,&HEATER_DIR,HEATER_PIN,DO_OFF);
    //motor initialization
    DO_Init(DO_MOTOR,&MOTOR_PORT,&MOTOR_DIR,MOTOR_PIN,DO_OFF);
    
    DO_SetState(DO_MOTOR,DO_ON);
    while(1)
    {
        
    }
    return;
}
