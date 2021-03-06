

/* 
 * File:        GPIO.h
 * Author:      Momen Ali
 * Comments:    this header made for deal with i/o 
 * Revision history:  24/2/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef GPIO_H
#define	GPIO_H

#include "Main.h"


/* GPIO port operations */
#define GPIO_Set_Dir_Port(DIRECTION_REG , DIRECTION)    ((DIRECTION_REG)=(DIRECTION)?(~0):(0))
#define GPIO_Write_Port(DATA_REG , DATA)                ((DATA_REG)=(DATA))
#define GPIO_Read_Port(DATA_REG)                        (DATA_REG)


/* GPIO pin operations */
#define GPIO_Set_Dir_Pin(DIRECTION_REG ,PIN, DIRECTION)     ((DIRECTION_REG)=(DIRECTION_REG & ~(1<<PIN))|(DIRECTION<<PIN))
#define GPIO_Write_Pin(DATA_REG ,PIN, DATA)                 ((DATA_REG)=(DATA_REG & ~(1<<PIN))|(DATA<<PIN))
#define GPIO_Toggle_Pin(DATA_REG ,PIN)                      ((DATA_REG)=(DATA_REG ^(1<<PIN)))
#define GPIO_Read_Pin(DATA_REG ,PIN)                        ((DATA_REG >> PIN)& 1)

/*GPIO nibble operation*/
/* N = 0 first nibble , N = 1 second nibble*/
#define GPIO_Write_Nibble(DATA_REG , DATA , N)                ((DATA_REG)=((DATA_REG)&~(0xF<<(N*4))));\
                                                              ((DATA_REG)=((DATA_REG)|((DATA<<(N*4))&(0xF<<(N*4)))))
#define GPIO_Set_Dir_Nibble(DIRECTION_REG , N, DIRECTION)     ((DIRECTION_REG)= ((DIRECTION_REG)& ~(0xF<<(N*4))));\
                                                              ((DIRECTION_REG)=((DIRECTION_REG)|(((DIRECTION)?(~0):(0))&(0xF<<(N*4)))))
                                                                                

uint8 GPIO_Init_Port(volatile uint8 * DirRegAddress/*direction register address*/,uint8 dir/* DIRECTION*/);
uint8 GPIO_Init_Pin(volatile uint8 * DirRegAddress/*direction register address*/,uint8 pin_number,uint8 dir/* I/O*/);
uint8 GPIO_Init_Nibble(volatile uint8 * DirRegAddress/*direction register address*/,uint8 nibble_num,uint8 dir/* I/O*/);


#endif	/* GPIO */

