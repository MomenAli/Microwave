
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "Main.h"

/* 
 * this structure holds the I/O pin parameter
 * portRegPtr : this is pointer to the data register of the DO
 * dirRegPtr : this is pointer to the direction control register of the DO
 * pin : the pin number of the DO
 */
typedef struct {
    volatile uint8 * portRegPtr;
    volatile uint8 * dirRegPtr; 
    uint8 pin;
}IOPinStruct_t;

#endif	/* XC_HEADER_TEMPLATE_H */

