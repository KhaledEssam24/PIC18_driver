/* 
 * File:   Timer0.h
 * Author: El-Rehab
 *
 * Created on September 16, 2022, 2:55 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

/*Section : includes */
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/mcal_interrupt/mcal_internal_interrupt.h"
#include "Timer0_cfg.h"
/*Section macros declarations */
#define TIMER0_ENABLE  1
#define TIMER0_DISABLE 0

#define TIMER0_PRESCALER_ENABLE   0
#define TIMER0_PRESCALER_DISABLE  1

#define TIMER0_RISING_EDGE  0
#define TIMER0_FALLING_EDGE 1

#define TIMER0_TIMER_MODE    0 
#define TIMER0_COUNTER_MODE  1

/*Section macros function declarations*/

/*Section Data type declaration */
typedef enum 
{
    TIMER0_PRESCALER_DIV2,
    TIMER0_PRESCALER_DIV4,
    TIMER0_PRESCALER_DIV8,            
    TIMER0_PRESCALER_DIV16,            
    TIMER0_PRESCALER_DIV32,
    TIMER0_PRESCALER_DIV64,
    TIMER0_PRESCALER_DIV128,            
    TIMER0_PRESCALER_DIV256,              
}timer0_prescaler_div_t;

typedef struct 
{
    uint8 timer0_prescaler_cfg    : 3;
    uint8 timer0_prescaler_enable : 1;
    uint8 timer0_edge_cfg         : 1;
    uint8 timer0_mode             : 1;
    
    #if INTERRUPT_TIMER0_FEATURE==ENABLE
    #if INTERRUPT_PRIORITY_FEATURE==ENABLE
    uint8 timer0_priority         : 1;
    uint8 reserved                : 1;
    #endif
    #else
    uint8 reserved                : 2;
    #endif     

    #if TIMER0_RESOLUTION == 8
    uint8 timer0_preload;
    #else
    uint16 timer0_preload;
    #endif    

    #if INTERRUPT_TIMER0_FEATURE==ENABLE
    void (* TIMER0_InterruptHandler)(void);
    #endif  

}timer0_cfg_t;

/*Section function declaration */
#if TIMER0_RESOLUTION == 8
Std_ReturnType Timer0_Init(const timer0_cfg_t*);
Std_ReturnType Timer0_DeInit(const timer0_cfg_t*);
Std_ReturnType Timer0_Write_Value (uint8 value);
Std_ReturnType Timer0_Read_Value  (uint8* value);
#else
Std_ReturnType Timer0_Init(const timer0_cfg_t* timer0);
Std_ReturnType Timer0_DeInit(const timer0_cfg_t* timer0);
Std_ReturnType Timer0_Write_Value (uint16 value);
Std_ReturnType Timer0_Read_Value  (uint16* value);
#endif


#endif	/* TIMER0_H */

