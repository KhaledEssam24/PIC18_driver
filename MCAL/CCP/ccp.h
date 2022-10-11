/* 
 * File:   ccp.h
 * Author: El-Rehab
 *
 * Created on September 22, 2022, 1:15 PM
 */

#ifndef CCP_H
#define	CCP_H

/*Section : includes */
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/mcal_interrupt/mcal_internal_interrupt.h"
#include "ccp_cfg.h"
#include "../../MCAL/Timer/Timer2.h"
/*Section macros declarations */
#define CCP1_DISABLED                           0x0
#if   CCP1_CFG_MODE_SELECTED==CCP1_CFG_COMPARE_MODE
#define CCP1_COMPARE_MODE_TOGGLE_ON_MATCH       0x2
#define CCP1_COMPARE_MODE_HIGH_ON_MATCH         0x8
#define CCP1_COMPARE_MODE_SW_INTERRUPT_ON_MATCH 0xA
#define CCP1_COMPARE_MODE_GEN_EVENT_ON_MATCH    0xB
#elif CCP1_CFG_MODE_SELECTED==CCP1_CFG_CAPTURE_MODE
#define CCP1_CAPTURE_MODE_1_FALLING_EDGE        0x4
#define CCP1_CAPTURE_MODE_1_RISING_EDGE         0x5
#define CCP1_CAPTURE_MODE_16_FALLING_EDGE       0x7
#define CCP1_CAPTURE_MODE_4_RISING_EDGE         0x6
#else
#define CCP1_PWM_MODE                           0x0F
#endif

#define CCP2_DISABLED                           0x0
#if   CCP2_CFG_MODE_SELECTED==CCP2_CFG_COMPARE_MODE
#define CCP2_COMPARE_MODE_TOGGLE_ON_MATCH       0x2
#define CCP2_COMPARE_MODE_HIGH_ON_MATCH         0x8
#define CCP2_COMPARE_MODE_SW_INTERRUPT_ON_MATCH 0xA
#define CCP2_COMPARE_MODE_GEN_EVENT_ON_MATCH    0xB
#elif CCP2_CFG_MODE_SELECTED==CCP2_CFG_CAPTURE_MODE
#define CCP2_CAPTURE_MODE_1_FALLING_EDGE        0x4
#define CCP2_CAPTURE_MODE_1_RISING_EDGE         0x5
#define CCP2_CAPTURE_MODE_16_FALLING_EDGE       0x7
#define CCP2_CAPTURE_MODE_4_RISING_EDGE         0x6
#else
#define CCP2_PWM_MODE                           0x0F
#endif

#define CCP1_IS_DONE 1
#define CCP2_IS_DONE 1

#define CCP1_TIMER1_CCP2_TIMER1 0x00
#define CCP1_TIMER1_CCP2_TIMER3 0x01
#define CCP1_TIMER3_CCP2_TIMER3 0x02

/*Section macros function declarations*/

/*Section Data type declaration */

typedef struct
{    
    #if INTERRUPT_CCP1_FEATURE==ENABLE
    #if INTERRUPT_PRIORITY_FEATURE==ENABLE
    uint8 ccp1_priority           : 1;
    #endif
    #endif
    
    #if   CCP1_CFG_MODE_SELECTED==CCP1_CFG_CAPTURE_MODE
    uint8 mode             : 4;
    uint8 ccp_timer_select : 2;
    #elif CCP1_CFG_MODE_SELECTED==CCP1_CFG_COMPARE_MODE
    uint8 mode             : 4;
    uint8 ccp_timer_select : 2;
    #else
    uint8 timer2_postscaler_cfg   : 4;
    uint8 timer2_prescaler_cfg    : 2;
    uint32 frequency;
    #endif
    uint8 reserved : 1;

    #if INTERRUPT_CCP1_FEATURE==ENABLE
    void (* CCP1_InterruptHandler)(void);
    #endif       
}ccp1_cfg_t;

typedef struct
{      
    #if INTERRUPT_CCP2_FEATURE==ENABLE
    #if INTERRUPT_PRIORITY_FEATURE==ENABLE
    uint8 ccp2_priority           : 1;
    #endif
    #endif
    
    #if   CCP2_CFG_MODE_SELECTED==CCP2_CFG_CAPTURE_MODE
    uint8 mode             : 4;
    uint8 ccp_timer_select : 2;
    #elif CCP2_CFG_MODE_SELECTED==CCP2_CFG_COMPARE_MODE
    uint8 mode             : 4;
    uint8 ccp_timer_select : 2;
    #else
    uint8 timer2_postscaler_cfg   : 4;
    uint8 timer2_prescaler_cfg    : 2;
    uint32 frequency;  
    #endif

    #if INTERRUPT_CCP2_FEATURE==ENABLE
    void (* CCP2_InterruptHandler)(void);
    #endif       
}ccp2_cfg_t;

typedef union 
{
    struct
    {
        uint8 ccp1_low ;
        uint8 ccp1_high ;
    };
    struct
    {
        uint16 ccp1_16bit ;
    };
}ccp1_reg;

typedef union 
{
    struct
    {
        uint8 ccp2_low ;
        uint8 ccp2_high ;
    };
    struct
    {
        uint16 ccp2_16bit ;
    };
}ccp2_reg;

/*Section function declaration */
Std_ReturnType CCP1_Init   (const ccp1_cfg_t* ccp1);
Std_ReturnType CCP1_DeInit (const ccp1_cfg_t* ccp1);

Std_ReturnType CCP2_Init   (const ccp2_cfg_t* ccp2);
Std_ReturnType CCP2_DeInit (const ccp2_cfg_t* ccp2);

#if   CCP1_CFG_MODE_SELECTED==CCP1_CFG_CAPTURE_MODE
Std_ReturnType CCP1_CaptureDataIsReady (uint8* status);
Std_ReturnType CCP1_CaptureReadValue (uint16* value);
#elif CCP1_CFG_MODE_SELECTED==CCP1_CFG_COMPARE_MODE
Std_ReturnType CCP1_CompareIsComplete (uint8* status);
Std_ReturnType CCP1_CompareValue (uint16 value);
#else
Std_ReturnType CCP1_PWM_Duty(uint8 duty);
Std_ReturnType CCP1_PWM_Start();
Std_ReturnType CCP1_PWM_Stop();
#endif

#if   CCP2_CFG_MODE_SELECTED==CCP2_CFG_CAPTURE_MODE
Std_ReturnType CCP2_CaptureDataIsReady (uint8* status);
Std_ReturnType CCP2_CaptureReadValue (uint16* value);
#elif CCP2_CFG_MODE_SELECTED==CCP2_CFG_COMPARE_MODE
Std_ReturnType CCP2_CompareIsComplete (uint8* status);
Std_ReturnType CCP2_CompareValue (uint16 value);
#else
Std_ReturnType CCP2_PWM_Duty(uint8 duty);
Std_ReturnType CCP2_PWM_Start();
Std_ReturnType CCP2_PWM_Stop();
#endif
#endif	/* CCP_H */

