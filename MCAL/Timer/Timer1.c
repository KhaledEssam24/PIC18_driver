#include "Timer1.h"

#if INTERRUPT_TIMER1_FEATURE==ENABLE
void (*Timer1_INT_HANDLER) (void) =NULL;
#endif

static uint16 timer1_preload = 0;

/**
 * 
 * @param timer1
 * @return 
 */
Std_ReturnType Timer1_Init        (const timer1_cfg_t* timer1)
{
    Std_ReturnType ret =E_OK;
    if(timer1)
    {
        /* disable timer1 */
        T1CONbits.TMR1ON=TIMER1_DISABLE;
        /* timer1 mode */
        T1CONbits.TMR1CS=timer1->timer1_mode;
        /* synchronization external clock input cfg */
        T1CONbits.T1SYNC=timer1->timer1_sync;
        /* timer1 osc enable cfg */
        T1CONbits.SOSCEN=timer1->timer1_osc_enable;
        /* prescaler config */
        T1CONbits.T1CKPS=timer1->timer1_prescaler_cfg;
        /* 16bit RW cfg */
        T1CONbits.RD16=1;

        #if INTERRUPT_TIMER1_FEATURE==ENABLE
        /*clear flag*/
        TIMER1_INT_CLEARFLAG();
        /*global interrupt enable*/
        #if INTERRUPT_PRIORITY_FEATURE==ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        INTERRUPT_HPRIORITY_ENABLE();
        INTERRUPT_LPRIORITY_ENABLE();
        switch(timer1->timer1_priority)
        {
            case(HIGH_PRIORITY):TIMER1_INT_HPRIORITY();break;
            case(LOW_PRIORITY) :TIMER1_INT_LPRIORITY();break;
            default :           TIMER1_INT_HPRIORITY();break;
        }        
        #else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERIAL_INTERRUPT_ENABLE();
        #endif      
        /*enable timer1 interrupt feature*/
        TIMER1_INT_ENABLE();
        Timer1_INT_HANDLER=timer1->TIMER1_InterruptHandler;
        #endif

        /*preload timer 1 */
        TMR1H=timer1->timer1_preload>>8;
        TMR1L=(uint8)timer1->timer1_preload;
        timer1_preload=timer1->timer1_preload;
        /*enable timer1*/
        T1CONbits.TMR1ON=TIMER1_ENABLE;
    }
    else
    {
        ret = E_NOT_OK;
    }       
    return ret;
}

/**
 * 
 * @param timer1
 * @return 
 */
Std_ReturnType Timer1_DeInit      (const timer1_cfg_t* timer1)
{
    Std_ReturnType ret =E_OK;
    /* disable timer1 */
    T1CONbits.TMR1ON=TIMER1_DISABLE;
    #if INTERRUPT_TIMER1_FEATURE==ENABLE        
    TIMER1_INT_ENABLE();
    #endif        
    return ret;
}

/**
 * 
 * @param timer1
 * @param value
 * @return 
 */
Std_ReturnType Timer1_Write_Value (uint16 value)
{
    Std_ReturnType ret = E_OK;
    TMR1H=value>>8;
    TMR1L=(uint8)value;
    return ret;
}

/**
 * 
 * @param timer1
 * @param value
 * @return 
 */
Std_ReturnType Timer1_Read_Value  (uint16* value)
{
    Std_ReturnType ret = E_OK;
    if(value)
    {
        uint8 value_high = 0 ,value_low = 0 ; 
        value_low=TMR1L;
        value_high=TMR1H;
        *value=(uint16)(value_low+value_high*256);
    }
    else
    {
        ret=E_NOT_OK;
    }
    return ret;
}

#if INTERRUPT_TIMER1_FEATURE==ENABLE         
void TIM1_ISR()
{
    TIMER1_INT_CLEARFLAG();
    /*preload timer 1 */
    TMR1H=timer1_preload>>8;
    TMR1L=(uint8)timer1_preload;
    if(Timer1_INT_HANDLER) Timer1_INT_HANDLER();
}
#endif 