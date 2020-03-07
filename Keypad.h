
/* 
 * File:        KeyPad.h
 * Author:      Momen Ali
 * Comments:    Driver for KeyPad handel the switches push
 * Revision history: 24/2/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef KPad_H
#define	KPad_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "Main.h"

/* The Number of the buttons in the keypad
 * this application used 12 buttons 
 */
#define KEYPAD_BUTTON_NUMBER  (12)

/* implementation details
 * number of input pins
 * number of output pins  
 * 
 * if you want to edit the number of switches in the keypad
 * 1 - edit the below numbers depend on your implementation 
 * 2 - edit  the keypad section in the port.h 
 * 2 - edit the keypad_Init() function to define the edited values
 */
#define KEYPAD_OUTPUT_PINS_NUMBER (3)
#define KEYPAD_INPUT_PINS_NUMBER  (4)

/* implementation details
 * SW voltage level 
 */
#define SW_PRESSED_LEVEL        (0)
#define SW_RELEASED_LEVEL       (1)


/* define new type to keypad
 * please edit this if your button names are different
 * the index of this enum is related to sampling data 
 *                 -----------------------
 *  in pin        | one   | two   | three |
 *                 -----------------------
 *  in pin        | four  | five  | six   |
 *                 -----------------------
 *  in pin        | seven | eight | nine  |
 *                 -----------------------
 *  in pin        | hash  | zero  | star  |
 *                 -----------------------
 *  
 *                   out     out      out
 *                   pin     pin      pin
 */

typedef enum
{
    KP_ONE,
    KP_TWO,
    KP_THREE,
    KP_FOUR,
    KP_FIVE,
    KP_SIX,
    KP_SEVEN,
    KP_EIGHT,
    KP_NINE,
    KP_HASH,
    KP_ZERO,
    KP_STAR        
}KP_t;


/*
 * Switch states
 */
typedef enum
{
    SW_RELEASED,
    SW_PRE_PRESSED,
    SW_PRESSED,
    SW_PRE_RELEASED
}SW_State_t;


/*----------------------- public function prototypes -----------------------------*/
void keypad_Init(void);
uint8 keypad_getState(KP_t item);
void keypad_Update(void);

#endif	/* KPad_H */

