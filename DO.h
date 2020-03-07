
/* 
 * File:        DO.h 
 * Author:      Momen Ali   
 * Comments:    Driver for Digital Outputs 
 * Revision history: 24/2/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DO_H
#define	DO_H
#include "Main.h"


typedef enum{
    /*modify this enum depend on your connection (cathode or anode)*/
    DO_OFF = 0,
    DO_ON  = 1
}LEDState_t;

typedef enum
{
    DO_LAMP,
    DO_HEATER,
    DO_MOTOR
}DO_t;

uint8 DO_Init(DO_t DO ,volatile uint8* port ,volatile uint8* dir,uint8 pinN ,LEDState_t state);
uint8 DO_GetState(DO_t DO);
void DO_SetState(DO_t DO,LEDState_t state);
void DO_update(void);

#endif	/* DO_H */

