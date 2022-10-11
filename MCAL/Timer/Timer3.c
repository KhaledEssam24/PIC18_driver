#include "Timer3.h"

#if INTERRUPT_TIMER3_FEATURE==ENABLE
void (*Timer3_INT_HANDLER) (void) =NULL;
#endif

static uint16 timer3_preload = 0;

/**
 * 
 * @param timer3
 * @return 
 */
Std_ReturnType Timer3_Init        (const timer3_cfg_t* timer3)
{
    Std_ReturnType ret =E_OK;
    if(timer3)
    {
        /* disable timer3 */
        T3CONbits.TMR3ON=TIMER3_DISABLE;
        /* timer3 mode */
        T3CONbits.TMR3CS=timer3->timer3_mode;
        /* synchronization external clock input cfg */
        T3CONbits.T3SYNC=timer3->timer3_sync;
        /* prescaler config */
        T3CONbits.T3CKPS=timer3->timer3_prescaler_cfg;
        /* 16bit RW cfg */
        T3CONbits.RD16=1;

        #if INTERRUPT_TIMER3_FEATURE==ENABLE
        /*clear flag*/
        TIMER3_INT_CLEARFLAG();
        /*global interrupt enable*/
        #if INTERRUPT_PRIORITY_FEATURE==ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        INTERRUPT_HPRIORITY_ENABLE();
        INTERRUPT_LPRIORITY_ENABLE();
        switch(timer3->timer3_priority)
        {
            case(HIGH_PRIORITY):TIMER3_INT_HPRIORITY();break;
            case(LOW_PRIORITY) :TIMER3_INT_LPRIORITY();break;
            default :           TIMER3_INT_HPRIORITY();break;
        }        
        #else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERIAL_INTERRUPT_ENABLE();
        #endif      
        /*enable timer1 interrupt feature*/
        TIMER3_INT_ENABLE();
        Timer3_INT_HANDLER=timer3->TIMER3_InterruptHandler;
        #endif

        /*preload timer3 */
        TMR3H=timer3->timer3_preload>>8;
        TMR3L=(uint8)timer3->timer3_preload;
        timer3_preload=timer3->timer3_preload;
        /*enable timer3*/
        T3CONbits.TMR3ON=TIMER3_ENABLE;
    }
    else
    {
        ret = E_NOT_OK;
    }       
    return ret;
}

/**
 * 
 * @param timer3
 * @return 
 */
Std_ReturnType Timer3_DeInit      (const timer3_cfg_t* timer3)
{
    Std_ReturnType ret =E_OK;
    /* disable timer3 */
    T1CONbits.TMR1ON=TIMER3_DISABLE;
    #if INTERRUPT_TIMER3_FEATURE==ENABLE        
    TIMER3_INT_ENABLE();
    #endif        
    return ret;
}

/**
 * 
 * @param timer3
 * @param value
 * @return 
 */
Std_ReturnType Timer3_Write_Value (uint16 value)
{
    Std_ReturnType ret = E_OK;
    TMR3H=value>>8;
    TMR3L=(uint8)value;
    return ret;
}

/**
 * 
 * @param timer3
 * @param value
 * @return 
 */
Std_ReturnType Timer3_Read_Value  (uint16* value)
{
    Std_ReturnType ret = E_OK;
    if(value)
    {
        uint8 value_high = 0 ,value_low = 0 ; 
        value_low=TMR3L;
        value_high=TMR3H;
        *value=(uint16)(value_low+value_high*256);
    }
    else
    {
        ret=E_NOT_OK;
    }
    return ret;
}

#if INTERRUPT_TIMER3_FEATURE==ENABLE         
void TIM3_ISR()
{
    TIMER3_INT_CLEARFLAG();
    /*preload timer3 */
    TMR3H=timer3_preload>>8;
    TMR3L=(uint8)timer3_preload;
    if(Timer3_INT_HANDLER) Timer3_INT_HANDLER();
}
#endif 