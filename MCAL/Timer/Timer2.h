/* 
 * File:   Timer2.h
 * Author: El-Rehab
 *
 * Created on September 18, 2022, 4:06 PM
 */

#ifndef TIMER2_H
#define	TIMER2_H

/*Section : includes */
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/mcal_interrupt/mcal_internal_interrupt.h"
/*Section macros declarations */
#define TIMER2_ENABLE  1
#define TIMER2_DISABLE 0
/*Section macros function declarations*/

/*Section Data type declaration */
typedef enum 
{
    TIMER2_PRESCALER_DIV1 =1,
    TIMER2_PRESCALER_DIV4,
    TIMER2_PRESCALER_DIV16,            
              
}timer2_prescaler_div_t;

typedef enum 
{
    TIMER2_POSTSCALER_DIV1 = 1,
    TIMER2_POSTSCALER_DIV2,
    TIMER2_POSTSCALER_DIV3,
    TIMER2_POSTSCALER_DIV4,
    TIMER2_POSTSCALER_DIV5,
    TIMER2_POSTSCALER_DIV6,
    TIMER2_POSTSCALER_DIV7,
    TIMER2_POSTSCALER_DIV8,
    TIMER2_POSTSCALER_DIV9,            
    TIMER2_POSTSCALER_DIV10,
    TIMER2_POSTSCALER_DIV11,
    TIMER2_POSTSCALER_DIV12,    
    TIMER2_POSTSCALER_DIV13,
    TIMER2_POSTSCALER_DIV14,
    TIMER2_POSTSCALER_DIV15,
    TIMER2_POSTSCALER_DIV16,            
}timer2_postscaler_div_t;

typedef struct 
{
    uint8 timer2_postscaler_cfg   : 4;
    uint8 timer2_prescaler_cfg    : 2;
    
    #if INTERRUPT_TIMER2_FEATURE==ENABLE
    #if INTERRUPT_PRIORITY_FEATURE==ENABLE
    uint8 timer2_priority         : 1;
    uint8 reserved                : 1;
    #endif
    #else
    uint8 reserved                : 2;
    #endif     

    uint8 timer2_preload;
    
    #if INTERRUPT_TIMER2_FEATURE==ENABLE
    void (* TIMER2_InterruptHandler)(void);
    #endif  

}timer2_cfg_t;

/*Section function declaration */
Std_ReturnType Timer2_Init  (const timer2_cfg_t* timer2);
Std_ReturnType Timer2_DeInit(const timer2_cfg_t* timer2);
Std_ReturnType Timer2_Write_Value (uint8 value);
Std_ReturnType Timer2_Read_Value  (uint8* value);

#endif	/* TIMER2_H */

