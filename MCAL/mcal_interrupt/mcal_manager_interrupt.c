#include "mcal_manager_interrupt.h"
static uint8 volatile flag_rb4=0,flag_rb5=0,flag_rb6=0,flag_rb7=0;

#if INTERRUPT_PRIORITY_FEATURE==ENABLE
void __interrupt(low_priority) InterruptManagerLow()
{ 
    #if INTERRUPT_TIMER0_FEATURE==ENABLE
    if ((INTCONbits.TMR0IE==INTERRUPT_ENABLE)&&(INTCONbits.TMR0IF==INTERRUPT_OCUUR))
    {
        TIM0_ISR();
    }
    else{}
    #endif    
    #if INTERRUPT_TIMER1_FEATURE==ENABLE
    if ((PIE1bits.TMR1IE==INTERRUPT_ENABLE)&&(PIR1bits.TMR1IF==INTERRUPT_OCUUR))
    {
        TIM1_ISR();
    }
    else{}
    #endif
    #if INTERRUPT_TIMER2_FEATURE==ENABLE
    if ((PIE1bits.TMR2IE==INTERRUPT_ENABLE)&&(PIR1bits.TMR2IF==INTERRUPT_OCUUR))
    {
        TIM2_ISR();
    }
    else{}
    #endif  
    #if INTERRUPT_TIMER3_FEATURE==ENABLE
    if ((PIE2bits.TMR3IE==INTERRUPT_ENABLE)&&(PIR2bits.TMR3IF==INTERRUPT_OCUUR))
    {
        TIM3_ISR();
    }
    else{}
    #endif 

    #if INTERRUPT_CCP1_FEATURE==ENABLE
    if ((PIE1bits.CCP1IE==INTERRUPT_ENABLE)&&(PIR1bits.CCP1IF==INTERRUPT_OCUUR))
    {
        CCP1_ISR();
    }
    else{}
    #endif    
    #if INTERRUPT_CCP2_FEATURE==ENABLE
    if ((PIE2bits.CCP2IE==INTERRUPT_ENABLE)&&(PIR2bits.CCP2IF==INTERRUPT_OCUUR))
    {
        CCP2_ISR();
    }
    else{}
    #endif    
}

void __interrupt(high_priority) InterruptManagerHigh()
{
    #if INTERRUPT_ADC_FEATURE==ENABLE
    if ((PIE1bits.ADIE==INTERRUPT_ENABLE)&&(PIR1bits.ADIF==INTERRUPT_OCUUR))
    {
        ADC_ISR();
    }
    else{}
    #endif    
}
    
#else
void __interrupt() InterruptManager()
{
//    if ((INTCONbits.INT0IE==INTERRUPT_ENABLE)&&(INTCONbits.INT0IF==INTERRUPT_OCUUR))
//        {INT0_ISR();}
//    else{}
//    
//    if ((INTCON3bits.INT1E==INTERRUPT_ENABLE)&&(INTCON3bits.INT1IF==INTERRUPT_OCUUR))
//        {INT1_ISR();}
//    else{}
//    
//    if ((INTCON3bits.INT2IE==INTERRUPT_ENABLE)&&(INTCON3bits.INT2IF==INTERRUPT_OCUUR))
//        {INT2_ISR();}
//    else{}
//
//    if ((INTCONbits.RBIE==INTERRUPT_ENABLE)&&(INTCONbits.RBIF==INTERRUPT_OCUUR)&&(PORTBbits.RB4==HIGH)&&(flag_rb4==0))
//    {
//        flag_rb4=1;
//        INTRB4_HIGH_ISR();
//    }
//    else{}
//    
//    if ((INTCONbits.RBIE==INTERRUPT_ENABLE)&&(INTCONbits.RBIF==INTERRUPT_OCUUR)&&(PORTBbits.RB4==LOW)&&(flag_rb4==1))
//    {
//        flag_rb4=0;
//        INTRB4_LOW_ISR();
//    }
//    else{}
//    
//    if ((INTCONbits.RBIE==INTERRUPT_ENABLE)&&(INTCONbits.RBIF==INTERRUPT_OCUUR)&&(PORTBbits.RB5==HIGH)&&(flag_rb5==0))
//    {
//        flag_rb5=1;
//        INTRB5_HIGH_ISR();
//    }
//    else{}
//    
//    if ((INTCONbits.RBIE==INTERRUPT_ENABLE)&&(INTCONbits.RBIF==INTERRUPT_OCUUR)&&(PORTBbits.RB5==LOW)&&(flag_rb5==1))
//    {
//        flag_rb5=0;
//        INTRB5_LOW_ISR();
//    }
//    else{}
//    
//    if ((INTCONbits.RBIE==INTERRUPT_ENABLE)&&(INTCONbits.RBIF==INTERRUPT_OCUUR)&&(PORTBbits.RB6==HIGH)&&(flag_rb6==0))
//    {
//        flag_rb6=1;
//        INTRB6_HIGH_ISR();
//    }
//    else{}
//    
//    if ((INTCONbits.RBIE==INTERRUPT_ENABLE)&&(INTCONbits.RBIF==INTERRUPT_OCUUR)&&(PORTBbits.RB6==LOW)&&(flag_rb6==1))
//    {
//        flag_rb6=0;
//        INTRB6_LOW_ISR();
//    }
//    else{}
//    
//    if ((INTCONbits.RBIE==INTERRUPT_ENABLE)&&(INTCONbits.RBIF==INTERRUPT_OCUUR)&&(PORTBbits.RB7==HIGH)&&(flag_rb7==0))
//    {
//        flag_rb7=1;
//        INTRB7_HIGH_ISR();
//    }
//    else{}
//    
//    if ((INTCONbits.RBIE==INTERRUPT_ENABLE)&&(INTCONbits.RBIF==INTERRUPT_OCUUR)&&(PORTBbits.RB7==LOW)&&(flag_rb7==1))
//    {
//        flag_rb7=0;
//        INTRB7_LOW_ISR();
//    }
//    else{} 

    #if INTERRUPT_ADC_FEATURE==ENABLE
    if ((PIE1bits.ADIE==INTERRUPT_ENABLE)&&(PIR1bits.ADIF==INTERRUPT_OCUUR))
    {
        ADC_ISR();
    }
    else{}
    #endif 
    
    #if INTERRUPT_TIMER0_FEATURE==ENABLE
    if ((INTCONbits.TMR0IE==INTERRUPT_ENABLE)&&(INTCONbits.TMR0IF==INTERRUPT_OCUUR))
    {
        TIM0_ISR();
    }
    else{}
    #endif 
    #if INTERRUPT_TIMER1_FEATURE==ENABLE
    if ((PIE1bits.TMR1IE==INTERRUPT_ENABLE)&&(PIR1bits.TMR1IF==INTERRUPT_OCUUR))
    {
        TIM1_ISR();
    }
    else{}
    #endif    
}
#endif
