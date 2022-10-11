/* 
 * File:   Timer1.h
 * Author: El-Rehab
 *
 * Created on September 17, 2022, 6:22 PM
 */

#ifndef TIMER1_H
#define	TIMER1_H
/*Section : includes */
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/mcal_interrupt/mcal_internal_interrupt.h"
/*Section macros declarations */
#define TIMER1_ENABLE  1
#define TIMER1_DISABLE 0

#define TIMER1_COUNTER_MODE 1
#define TIMER1_TIMER_MODE   0

#define TIMER1_SYNC_EXTERNAL_CLOCK  0
#define TIMER1_ASYNC_EXTERNAL_CLOCK 1

#define TIMER1_OSCILLATOR_ENABLE  1
#define TIMER1_OSCILLATOR_DISABLE 0

/*Section macros function declarations*/

/*Section Data type declaration */
typedef enum 
{
    TIMER1_PRESCALER_DIV1,
    TIMER1_PRESCALER_DIV2,
    TIMER1_PRESCALER_DIV4,            
    TIMER1_PRESCALER_DIV8,                         
};

typedef struct 
{
    uint8 timer1_prescaler_cfg    : 2;
    uint8 timer1_mode             : 1;
    uint8 timer1_osc_enable       : 1;
    uint8 timer1_sync             : 1;
    #if INTERRUPT_TIMER1_FEATURE==ENABLE
    #if INTERRUPT_PRIORITY_FEATURE==ENABLE
    uint8 timer1_priority         : 1;
    uint8 reserved                : 2;
    #endif
    #else
    uint8 reserved                : 3;
    #endif 

    uint16 timer1_preload;
    
    #if INTERRUPT_TIMER1_FEATURE==ENABLE
    void (* TIMER1_InterruptHandler)(void);
    #endif 
    
}timer1_cfg_t;

/*Section function declaration */
Std_ReturnType Timer1_Init        (const timer1_cfg_t* timer1);
Std_ReturnType Timer1_DeInit      (const timer1_cfg_t* timer1);
Std_ReturnType Timer1_Write_Value (uint16 value);
Std_ReturnType Timer1_Read_Value  (uint16* value);



#endif	/* TIMER1_H */

