/* 
 * File:   mcal_external_interrupt.h
 * Author: El-Rehab
 *
 * Created on August 21, 2022, 10:40 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/*********************includes*********************/
#include "mcal_config_interrupt.h"
/*************Section macros declarations**********/
#define HIGH_PRIORITY 1
#define LOW_PRIORITY  0

#define FALLING_EDGE 0
#define RISING_EDGE  1
/*************Section macros function declarations*/
#if INTERRUPT_FEATURE==ENABLE
#if INTERRUPT_EXTINT_FEATURE==ENABLE


#if INTERRUPT_EXTINT_FEATURE==ENABLE
#define EXT_INT0_ENABLE()       (INTCONbits.INT0IE=1)
#define EXT_INT0_DISABLE()      (INTCONbits.INT0IE=0)
#define EXT_INT0_CLEARFLAG()    (INTCONbits.INT0IF=0)
#define EXT_INT0_RISING_EDGE()  (INTCON2bits.INTEDG0=1)
#define EXT_INT0_FALLING_EDGE() (INTCON2bits.INTEDG0=0)

#define EXT_INT1_ENABLE()       (INTCON3bits.INT1E=1)
#define EXT_INT1_DISABLE()      (INTCON3bits.INT1E=0)
#define EXT_INT1_CLEARFLAG()    (INTCON3bits.INT1IF=0)
#define EXT_INT1_RISING_EDGE()  (INTCON2bits.INTEDG1=1)
#define EXT_INT1_FALLING_EDGE() (INTCON2bits.INTEDG1=0)
#if INTERRUPT_PRIORITY_FEATURE==ENABLE
#define EXT_INT1_HPRIORITY() (INTCON3bits.INT1IP=1)
#define EXT_INT1_LPRIORITY() (INTCON3bits.INT1IP=0)
#endif

#define EXT_INT2_ENABLE()       (INTCON3bits.INT2IE=1)
#define EXT_INT2_DISABLE()      (INTCON3bits.INT2IE=0)
#define EXT_INT2_CLEARFLAG()    (INTCON3bits.INT2IF=0)
#define EXT_INT2_RISING_EDGE()  (INTCON2bits.INTEDG2=1)
#define EXT_INT2_FALLING_EDGE() (INTCON2bits.INTEDG2=0)
#if INTERRUPT_PRIORITY_FEATURE==ENABLE
#define EXT_INT2_HPRIORITY() (INTCON3bits.INT2IP=1)
#define EXT_INT2_LPRIORITY() (INTCON3bits.INT2IP=0)
#endif

#define EXT_INT_ONCHANGE_ENABLE()       (INTCONbits.RBIE=1)
#define EXT_INT_ONCHANGE_DISABLE()      (INTCONbits.RBIE=0)
#define EXT_INT_ONCHANGE_CLEARFLAG()    (INTCONbits.RBIF=0)
#if INTERRUPT_PRIORITY_FEATURE==ENABLE
#define EXT_INT_ONCHANGE_HPRIORITY() (INTCON2bits.RBIP=1)
#define EXT_INT_ONCHANGE_LPRIORITY() (INTCON2bits.RBIP=0)
#endif

#endif

/*************Section Data type declaration********/
typedef enum 
{
    EXT_INT0,
    EXT_INT1,
    EXT_INT2
}interrupt_source_t;

typedef struct
{
    void (* EXT_interruptHandler) (void);
    uint8 src     :   2;
    uint8 edge    :   1;
    uint8 priority:   1;
    uint8 reserved:   4;
    pin_config_t    pin;  
}Interrupt_INTx_t;

typedef struct
{
    void (* EXT_interruptHandler_HIGH) (void);
    void (* EXT_interruptHandler_LOW) (void);
    uint8  priority;
    pin_config_t    pin;  
}Interrupt_RBx_t;


/*************Section function declaration*********/
Std_ReturnType Interrupt_INTx_Init   (const Interrupt_INTx_t* int_obj);
Std_ReturnType Interrupt_INTx_DeInit (const Interrupt_INTx_t* int_obj);
Std_ReturnType Interrupt_RBx_Init    (const Interrupt_RBx_t* int_obj);
Std_ReturnType Interrupt_RBx_DeInit  (const Interrupt_RBx_t* int_obj);

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void INTRB4_HIGH_ISR(void);
void INTRB4_LOW_ISR(void);
void INTRB5_HIGH_ISR(void);
void INTRB5_LOW_ISR(void);
void INTRB6_HIGH_ISR(void);
void INTRB6_LOW_ISR(void);
void INTRB7_HIGH_ISR(void);
void INTRB7_LOW_ISR(void);
#endif
#endif
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

