
/* 
 * File:        Main.h
 * Author:      Momen Ali
 * Comments:    this file contain all the hardware configuration
 * Revision history:  24/2/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAIN_H
#define	MAIN_H

#include <xc.h> // include processor files - each processor file is guarded.  
#define _XTAL_FREQ 8000000

#define OS_TICK (5)



/************************************HW*************************************
 *                               description                               *
 * this header included all the configuration of micro controller directly *
 * if you change the micro controller please change these configuration    *
 * pic18f4550                                                              *
 ***************************************************************************/


/* GPIO Port Data Registers redefinition */
#define GPIO_PORTA_DATA      (PORTA)
#define GPIO_PORTB_DATA      (PORTB)
#define GPIO_PORTC_DATA      (PORTC)
#define GPIO_PORTD_DATA      (PORTD)
#define GPIO_PORTE_DATA      (PORTE)

/* GPIO Port Direction Registers redefinition */
#define GPIO_PORTA_DIR       (TRISA)
#define GPIO_PORTB_DIR       (TRISB)
#define GPIO_PORTC_DIR       (TRISC)
#define GPIO_PORTD_DIR       (TRISD)
#define GPIO_PORTE_DIR       (TRISE)


/* number of pins in ports */

#define PORTA_PINS              (8)
#define PORTB_PINS              (8)
#define PORTC_PINS              (8)
#define PORTD_PINS              (8)
#define PORTE_PINS              (4)

/* GPIO direction setting */
#define GPIO_OUT                (0)
#define GPIO_IN                 (1)

// redefine pins value
#define PIN_0 (0)
#define PIN_1 (1)
#define PIN_2 (2)
#define PIN_3 (3)
#define PIN_4 (4)
#define PIN_5 (5)
#define PIN_6 (6)
#define PIN_7 (7)


/* define some standard types does not depend on the machine */
typedef unsigned char uint8;
typedef unsigned int  uint16;


/*
 * Redefine register and configuration bits of TIMER 0
 * if you use another timer please edit this section 
 */
/*
 * PSA: Timer0 Prescaler Assignment bit
 * 1 = TImer0 prescaler is NOT assigned. Timer0 clock input bypasses prescaler.
 * 0 = Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
 */
#define TMR_PRESCALER_ACTIVE   (PSA = 0)

/*
 * 
 *  define the pre scaler as below table 
 *    _____________________
 *  | TMR0 RATE | PS2:PS0 |
 *  |___________|_________|
 *  |     2     |   000   |
 *  |___________|_________|
 *  |     4     |   001   |
 *  |___________|_________|
 *  |     .     |    .    |
 *  |___________|_________|
 *  |     .     |    .    |
 *  |___________|_________|
 *  |    128    |   110   |
 *  |___________|_________|
 *  |    256    |   111   |
 *  |___________|_________|
 *  
 */
/* 
 * we will use pre scaler 256
 * edit this if you need to change pre scaler 
 */
#define TMR_PRESCALER_256 T0PS2 = 1;\
                          T0PS1 = 1;\
                          T0PS0 = 1


#define TMR_PRESCALER_2   T0PS2 = 0;\
                          T0PS1 = 0;\
                          T0PS0 = 0

/*
 * timer 0 register
 */
#define TMR0_REG    (TMR0)
/*this flag will be 1 if overflow happened to the timer*/
#define TMR0_I_FLAG (TMR0IF)


/*enable interrupts flag*/
#define TMR0_ENABLE_INTERRUPT	(TMR0IE = 1)
/*enable global interrupt flag*/
#define GLOBAL_INTERRUPT_ENABLE	(GIE = 1)


/* CLOCK CONTROL BIT
 * TOCS = 0  enable internal instruction cycle clock(CLKO)
 * T0CS = 1  enable external clock from TOCKI pin
 */
#define TMR0_ENABLE_CLOCK		(T0CS = 0)



/* TMR0ON: Timer0 On/Off Control bit
 * 1 = Enables Timer0
 * 0 = Stops Timer0
 */
#define TMR0_STOP		(TMR0ON = 0)
#define TMR0_START		(TMR0ON = 1)
/* 
 * we don't have any input in RA4
 * be sure you don't use this pin if you need to stop the timer0
 */

/* T08BIT: Timer0 8-Bit/16-Bit Control bit
 * 1 = Timer0 is configured as an 8-bit timer/counter
 * 0 = Timer0 is configured as a 16-bit timer/counter 
 */
#define TMR016BIT        (T08BIT = 1)



// keypad pull up resistor enable
/* RDPU: PORTD Pull-up Enable bit
 * 1 = PORTD pull-ups are enabled by individual port latch values
 * 0 = All PORTD pull-ups are disabled*/

#define KEYPAD_PULLUP_RESISOR_ENABLE (RDPU = 1)

// switches pull up resistor enable
/* RBPU: PORTB Pull-up Enable bit
 * 1 = All PORTB pull-ups are disabled
 * 0 = PORTB pull-ups are enabled by individual port latch values */
#define SWITCH_PULLUP_RESISOR_ENABLE (RBPU = 1)


#endif	/* MAIN_H */

