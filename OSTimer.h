

/* 
 * File:        OSTimer.h  
 * Author:      Momen Ali
 * Comments:    module for OS tick ( time driven design)
 * Revision history: 25/2/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "Main.h"

/*TIMER INTERUPT FLAG OPERATIONS*/
#define TMR0_GET_FLAG			(TMR0_I_FLAG)
#define TMR0_CLEAR_FLAG			(TMR0_I_FLAG = 0)

/* 
 * Time calculation
 * timer0 is 16bit => max count is 65,536
 * CLKO input in the timer0 is (FOSC/4)
 * XTEL_FREQ = 8000000     => CLKO = 2000000 
 * we are using pre scaler so CLK =  ( CLKO / PRE SCALER )
 * PRE SCALER = 2  => CLK = 1000000
 * TICK TIME = 1 / CLK   => TICK TIME = 1 us
 * OVERFLOW TIME = TICK TIME * 65,536  => 1 us * 65,536 = 65,536 ms
 * TICK TIME = 1 us
 * we need tick every 5 ms 
 * 5 ms / 1 us = 5000
 * TMR0 = 65,536 - (TICKS)
 */
#define TMR0_TICK_NUM (5000)
#define TMR_LOAD_REGISTER(TICKS)		(TMR0_REG = 65,536 - (TICKS))


void TMR_Init(void);
void TMR_Start(void);
void TMR_Stop(void);
uint8 TMR_CheckOverflow(void);
void TMR0_ISR(void);

#endif	/* XC_HEADER_TEMPLATE_H */

