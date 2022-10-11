/* 
 * File:   mcal_manager_interrupt.h
 * Author: El-Rehab
 *
 * Created on August 21, 2022, 10:40 AM
 */

#ifndef MCAL_MANAGER_INTERRUPT_H
#define	MCAL_MANAGER_INTERRUPT_H
/*********************includes*********************/
#include "mcal_config_interrupt.h"
/*************Section macros declarations**********/
/*************Section macros function declarations*/
/*************Section Data type declaration********/
/*************Section function declaration*********/
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
#if INTERRUPT_ADC_FEATURE==ENABLE
void ADC_ISR();
#endif
#if INTERRUPT_TIMER0_FEATURE==ENABLE
void TIM0_ISR();
#endif
#if INTERRUPT_TIMER1_FEATURE==ENABLE
void TIM1_ISR();
#endif
#if INTERRUPT_TIMER2_FEATURE==ENABLE
void TIM2_ISR();
#endif
#if INTERRUPT_TIMER3_FEATURE==ENABLE
void TIM3_ISR();
#endif
#if INTERRUPT_CCP1_FEATURE==ENABLE
void CCP1_ISR();
#endif
#if INTERRUPT_CCP2_FEATURE==ENABLE
void CCP2_ISR();
#endif
#endif	/* MCAL_MANAGER_INTERRUPT_H */

