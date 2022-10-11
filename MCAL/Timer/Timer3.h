/* 
 * File:   Timer3.h
 * Author: El-Rehab
 *
 * Created on September 18, 2022, 4:06 PM
 */

#ifndef TIMER3_H
#define	TIMER3_H

/*Section : includes */
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/mcal_interrupt/mcal_internal_interrupt.h"
/*Section macros declarations */
#define TIMER3_ENABLE  1
#define TIMER3_DISABLE 0

#define TIMER3_COUNTER_MODE 1
#define TIMER3_TIMER_MODE   0

#define TIMER3_SYNC_EXTERNAL_CLOCK  0
#define TIMER3_ASYNC_EXTERNAL_CLOCK 1
/*Section macros function declarations*/

/*Section Data type declaration */
typedef enum 
{
    TIMER3_PRESCALER_DIV1,
    TIMER3_PRESCALER_DIV2,
    TIMER3_PRESCALER_DIV4,            
    TIMER3_PRESCALER_DIV8,                         
};

typedef struct 
{
    uint8 timer3_prescaler_cfg    : 2;
    uint8 timer3_mode             : 1;
    uint8 timer3_sync             : 1;
    #if INTERRUPT_TIMER3_FEATURE==ENABLE
    #if INTERRUPT_PRIORITY_FEATURE==ENABLE
    uint8 timer3_priority         : 1;
    uint8 reserved                : 3;
    #endif
    #else
    uint8 reserved                : 4;
    #endif 

    uint16 timer3_preload;
    
    #if INTERRUPT_TIMER3_FEATURE==ENABLE
    void (* TIMER3_InterruptHandler)(void);
    #endif 
    
}timer3_cfg_t;

/*Section function declaration */
Std_ReturnType Timer3_Init        (const timer3_cfg_t* timer3);
Std_ReturnType Timer3_DeInit      (const timer3_cfg_t* timer3);
Std_ReturnType Timer3_Write_Value (uint16 value);
Std_ReturnType Timer3_Read_Value  (uint16* value);

#endif	/* TIMER3_H */

