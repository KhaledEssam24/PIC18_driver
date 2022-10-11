/* 
 * File:   mcal_config_interrupt.h
 * Author: El-Rehab
 *
 * Created on August 21, 2022, 11:10 AM
 */

#ifndef MCAL_CONFIG_INTERRUPT_H
#define	MCAL_CONFIG_INTERRUPT_H

/*********************includes*********************/
#include "../mcal_std_types.h"
#include "../proc/pic18f4620.h"
#include "mcal_interrupt_gen.h"
#include "../gpio/gpio.h"
/*************Section macros declarations**********/
#define INTERRUPT_ENABLE  1
#define INTERRUPT_DISABLE 0
#define INTERRUPT_OCUUR     1
#define INTERRUPT_NOT_OCUUR 0
/*************Section macros function declarations*/

#if INTERRUPT_PRIORITY_FEATURE==ENABLE
#define INTERRUPT_PRIORITY_ENABLE()     (RCONbits.IPEN=1)
#define INTERRUPT_PRIORITY_DISABLE()    (RCONbits.IPEN=0)
#define INTERRUPT_HPRIORITY_ENABLE()  (INTCONbits.GIEH=1)
#define INTERRUPT_HPRIORITY_DISABLE() (INTCONbits.GIEH=0)
#define INTERRUPT_LPRIORITY_ENABLE()  (INTCONbits.GIEL=1)
#define INTERRUPT_LPRIORITY_DISABLE() (INTCONbits.GIEL=0)      
#else
#define GLOBAL_INTERRUPT_ENABLE()    (INTCONbits.GIE=1)
#define GLOBAL_INTERRUPT_DISABLE()   (INTCONbits.GIE=0)
#define PERIPHERIAL_INTERRUPT_ENABLE()          (INTCONbits.PEIE=1)
#define PERIPHERIAL_INTERRUPT_DISABLE()         (INTCONbits.PEIE=0)
#endif
/*************Section Data type declaration********/
/*************Section function declaration*********/


#endif	/* MCAL_CONFIG_INTERRUPT_H */

