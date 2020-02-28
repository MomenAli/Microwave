/*
 * File:   GPIO.c
 * Author: Momen Ali
 *
 * Created on February 24, 2020, 8:02 PM
 */

#include "GPIO.h"

uint8 GPIO_Init_Port(volatile uint8 * DirRegAddress/*direction register address*/,uint8 dir/* DIRECTION*/)
{
    uint8 ret =1;
    /*check if the address valid*/
    if(*DirRegAddress != GPIO_PORTA_DIR && *DirRegAddress != GPIO_PORTB_DIR &&
       *DirRegAddress != GPIO_PORTC_DIR && *DirRegAddress != GPIO_PORTD_DIR &&
       *DirRegAddress != GPIO_PORTE_DIR)
    {
       /*invalid input return 0 */
       ret =0;
    }
    else
    {
        GPIO_Set_Dir_Port(*DirRegAddress ,dir);

    }
    return ret;
}


uint8 GPIO_Init_Pin(volatile uint8 *DirRegAddress/*direction register address*/,uint8 pin_number,uint8 dir/* DIRECTION*/)
{
    uint8 ret = 1;
    /*check if the address valid*/
    if(*DirRegAddress != GPIO_PORTA_DIR && *DirRegAddress != GPIO_PORTB_DIR &&
       *DirRegAddress != GPIO_PORTC_DIR &&*DirRegAddress != GPIO_PORTD_DIR &&
       *DirRegAddress != GPIO_PORTE_DIR)
    {
       /*invalid input return 0 */
       ret = 0;
    }
    else
    {      
        GPIO_Set_Dir_Pin(*DirRegAddress,pin_number,dir);
    }
    return ret;
}


uint8 GPIO_Init_Nibble(volatile uint8 * DirRegAddress/*direction register address*/,uint8 nibble_num,uint8 dir/* I/O*/)
{
    uint8 ret = 1;
    /*check if the address valid*/
    if(*DirRegAddress != GPIO_PORTA_DIR && *DirRegAddress != GPIO_PORTB_DIR &&
       *DirRegAddress != GPIO_PORTC_DIR &&*DirRegAddress != GPIO_PORTD_DIR &&
       *DirRegAddress != GPIO_PORTE_DIR)
    {
       /*invalid input return 0 */
       ret = 0;
    }
    else
    {      
        GPIO_Set_Dir_Nibble(*DirRegAddress,nibble_num,dir);
    }
    return ret;
    
}