/* 
 * File:   mcal_internal_interrupt.h
 * Author: El-Rehab
 *
 * Created on August 21, 2022, 10:39 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H
/*********************includes*********************/
#include "mcal_interrupt_gen.h"
#include "mcal_config_interrupt.h"
/*************Section macros function declarations*/
#if INTERRUPT_ADC_FEATURE==ENABLE
#define ADC_INT_ENABLE()       (PIE1bits.ADIE=1)
#define ADC_INT_DISABLE()      (PIE1bits.ADIE=0)
#define ADC_INT_CLEARFLAG()    (PIR1bits.ADIF=0)
#if INTERRUPT_PRIORITY_FEATURE==ENABLE
#define ADC_INT_HPRIORITY() (IPR1bits.ADIP=1)
#define ADC_INT_LPRIORITY() (IPR1bits.ADIP=0)
#endif
#endif

#if INTERRUPT_TIMER0_FEATURE==ENABLE
#define TIMER0_INT_ENABLE()       (INTCONbits.TMR0IE=1)
#define TIMER0_INT_DISABLE()      (INTCONbits.TMR0IE=0)
#define TIMER0_INT_CLEARFLAG()    (INTCONbits.TMR0IF=0)
#if INTERRUPT_PRIORITY_FEATURE==ENABLE
#define TIMER0_INT_HPRIORITY()    (INTCON2bits.TMR0IP=1)
#define TIMER0_INT_LPRIORITY()    (INTCON2bits.TMR0IP=0)
#endif
#endif

#if INTERRUPT_TIMER1_FEATURE==ENABLE
#define TIMER1_INT_ENABLE()       (PIE1bits.TMR1IE=1)
#define TIMER1_INT_DISABLE()      (PIE1bits.TMR1IE=0)
#define TIMER1_INT_CLEARFLAG()    (PIR1bits.TMR1IF=0)
#if INTERRUPT_PRIORITY_FEATURE==ENABLE
#define TIMER1_INT_HPRIORITY()    (IPR1bits.TMR1IP=1)
#define TIMER1_INT_LPRIORITY()    (IPR1bits.TMR1IP=0)
#endif
#endif

#if INTERRUPT_TIMER2_FEATURE==ENABLE
#define TIMER2_INT_ENABLE()       (PIE1bits.TMR2IE=1)
#define TIMER2_INT_DISABLE()      (PIE1bits.TMR2IE=0)
#define TIMER2_INT_CLEARFLAG()    (PIR1bits.TMR2IF=0)
#if INTERRUPT_PRIORITY_FEATURE==ENABLE
#define TIMER2_INT_HPRIORITY()    (IPR1bits.TMR2IP=1)
#define TIMER2_INT_LPRIORITY()    (IPR1bits.TMR2IP=0)
#endif
#endif

#if INTERRUPT_TIMER3_FEATURE==ENABLE
#define TIMER3_INT_ENABLE()       (PIE2bits.TMR3IE=1)
#define TIMER3_INT_DISABLE()      (PIE2bits.TMR3IE=0)
#define TIMER3_INT_CLEARFLAG()    (PIR2bits.TMR3IF=0)
#if INTERRUPT_PRIORITY_FEATURE==ENABLE
#define TIMER3_INT_HPRIORITY()    (IPR2bits.TMR3IP=1)
#define TIMER3_INT_LPRIORITY()    (IPR2bits.TMR3IP=0)
#endif
#endif

#if INTERRUPT_CCP1_FEATURE==ENABLE
#define CCP1_INT_ENABLE()       (PIE1bits.CCP1IE=1)
#define CCP1_INT_DISABLE()      (PIE1bits.CCP1IE=0)
#define CCP1_INT_CLEARFLAG()    (PIR1bits.CCP1IF=0)
#if INTERRUPT_PRIORITY_FEATURE==ENABLE
#define CCP1_INT_HPRIORITY()    (IPR1bits.CCP1IP=1)
#define CCP1_INT_LPRIORITY()    (IPR1bits.CCP1IP=0)
#endif
#endif

#if INTERRUPT_CCP2_FEATURE==ENABLE
#define CCP2_INT_ENABLE()       (PIE2bits.CCP2IE=1)
#define CCP2_INT_DISABLE()      (PIE2bits.CCP2IE=0)
#define CCP2_INT_CLEARFLAG()    (PIR2bits.CCP2IF=0)
#if INTERRUPT_PRIORITY_FEATURE==ENABLE
#define CCP2_INT_HPRIORITY()    (IPR2bits.CCP2IP=1)
#define CCP2_INT_LPRIORITY()    (IPR2bits.CCP2IP=0)
#endif
#endif
/*************Section macros declarations**********/
#define HIGH_PRIORITY 1
#define LOW_PRIORITY  0

/*************Section Data type declaration********/

/*************Section function declaration*********/



#endif	/* MCAL_INTERNAL_INTERRUPT_H */