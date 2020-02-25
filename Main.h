
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


// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


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





#endif	/* MAIN_H */

