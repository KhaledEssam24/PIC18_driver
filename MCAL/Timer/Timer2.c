#include "Timer2.h"

#if INTERRUPT_TIMER2_FEATURE==ENABLE
static void (*Timer2_INT_HANDLER)(void)=NULL;
#endif

static uint8 timer2_preload = 0;

/**
 * 
 * @param timer2
 * @return 
 */
Std_ReturnType Timer2_Init  (const timer2_cfg_t* timer2)
{
    Std_ReturnType ret=E_OK;
    if(timer2)
    {
        /* disable timer2 */
        T2CONbits.TMR2ON=TIMER2_DISABLE;
        /* config prescaler and postscaler */
        T2CONbits.TOUTPS=(timer2->timer2_postscaler_cfg)-1;
        T2CONbits.T2CKPS=(timer2->timer2_prescaler_cfg)-1;
        /* config interrupt handler */
        #if INTERRUPT_TIMER2_FEATURE==ENABLE
        /*clear flag*/
        TIMER2_INT_CLEARFLAG();
        /*global interrupt enable*/
        #if INTERRUPT_PRIORITY_FEATURE==ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        INTERRUPT_HPRIORITY_ENABLE();
        INTERRUPT_LPRIORITY_ENABLE();
        switch(timer2->timer2_priority)
        {
            case(HIGH_PRIORITY):TIMER2_INT_HPRIORITY();break;
            case(LOW_PRIORITY) :TIMER2_INT_LPRIORITY();break;
            default :           TIMER2_INT_HPRIORITY();break;
        }        
        #else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERIAL_INTERRUPT_ENABLE();
        #endif
        /*enable timer2 interrupt feature*/
        TIMER2_INT_ENABLE();
        Timer2_INT_HANDLER=timer2->TIMER2_InterruptHandler;
        #endif        
        /* preload value */
        PR2=timer2->timer2_preload;
        timer2_preload=timer2->timer2_preload;
        /* enable timer2 */
        T2CONbits.TMR2ON=TIMER2_ENABLE;
    }
    else
    {
        ret=E_NOT_OK;
    }
    return ret;
}

/**
 * 
 * @param timer2
 * @return 
 */
Std_ReturnType Timer2_DeInit(const timer2_cfg_t* timer2)
{
    Std_ReturnType ret=E_OK;
    if(timer2)
    {
        /* disable timer2 */
        T2CONbits.TMR2ON=TIMER2_DISABLE;
        /*disable timer2 interrupt feature*/
        #if INTERRUPT_TIMER2_FEATURE==ENABLE
        TIMER2_INT_ENABLE();
        #endif        
    }
    else
    {
        ret=E_NOT_OK;
    }
    return ret;
}

/**
 * 
 * @param value
 * @return 
 */
Std_ReturnType Timer2_Write_Value (uint8 value)
{
    Std_ReturnType ret=E_OK;
    TMR2=value;
    return ret;
}

/**
 * 
 * @param value
 * @return 
 */
Std_ReturnType Timer2_Read_Value  (uint8* value)
{
    Std_ReturnType ret=E_OK;
    if(value)
    {
        *value=TMR2;
    }
    else
    {
        ret=E_NOT_OK;
    }
    return ret;
}        

#if INTERRUPT_TIMER2_FEATURE==ENABLE
void TIM2_ISR()
{
    TIMER2_INT_CLEARFLAG();
    /*preload timer2*/
    PR2=timer2_preload;    
    if(Timer2_INT_HANDLER) Timer2_INT_HANDLER(); 
}
#endif