

/* 
 * File:        SW.h
 * Author:      Momen Ali   
 * Comments:    Switch state detection
 * Revision history: 24/2/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SW_H
#define	SW_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include "Main.h"
/*
 * number of switches in this application is 3  plus, minus and set
 * please edit this number if you change the application
 */
#define SW_NUM (2)

/*
 * we will take samples every this amount of time
 * please edit this number depend on the debouncing time of your switch data sheet
 */
#define SW_UPDATE_TICK (20)


/*
 * Switch type
 * we have three buttons in this application
 * please edit this enum if you change the application.
 */
typedef enum
{
    SW_DOOR,
    SW_WEIGHT_SENSOR
}SW_t;

/*
 * Switch states
 * if release
 */
#ifndef SW_State_define
#define SW_State_define
typedef enum
{
    SW_RELEASED,
    SW_PRE_PRESSED,
    SW_PRESSED,
    SW_PRE_RELEASED
}SW_State_t;
#endif

/*
 * Initialize the buttons 
 * Initialize the samples
 */
void SW_Init(SW_t ,volatile uint8 * dir,volatile uint8 * port , uint8 pin);
/*
 * get the current state of button
 */
uint8 SW_GetState(SW_t sw);
/*
 * update the samples of the situation of button
 * update the state of the button
 */
void SW_Update(void);


#endif	/* SW_H */

