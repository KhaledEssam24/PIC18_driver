#include "Timer0.h"

#if INTERRUPT_TIMER0_FEATURE==ENABLE
static void (*Timer0_INT_HANDLER)(void)=NULL;
#endif

#if TIMER0_RESOLUTION == 8
static uint8 timer0_preload = 0;
#else
static uint16 timer0_preload = 0;
#endif

/**
 * 
 * @param 
 * @return 
 */
Std_ReturnType Timer0_Init(const timer0_cfg_t* timer0)
{
    Std_ReturnType ret = E_OK;
    if(timer0)
    {
        /*disable timer0*/
        T0CONbits.TMR0ON=TIMER0_DISABLE;
        
        /*timer0 resolution*/
        #if TIMER0_RESOLUTION == 8
        T0CONbits.T08BIT=1;
        #else
        T0CONbits.T08BIT=0;
        #endif

        /*timer0 mode*/
        T0CONbits.T0CS=timer0->timer0_mode;
        
        /*timer0 edge select*/
        T0CONbits.T0SE=timer0->timer0_edge_cfg;
        
        /*prescaler enable*/
        T0CONbits.PSA=timer0->timer0_prescaler_enable;
        /*prescaler config*/
         T0CONbits.T0PS=timer0->timer0_prescaler_cfg;
       
        #if INTERRUPT_TIMER0_FEATURE==ENABLE
        /*clear flag*/
        TIMER0_INT_CLEARFLAG();
        /*global interrupt enable*/
        #if INTERRUPT_PRIORITY_FEATURE==ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        INTERRUPT_HPRIORITY_ENABLE();
        INTERRUPT_LPRIORITY_ENABLE();
        switch(timer0->timer0_priority)
        {
            case(HIGH_PRIORITY):TIMER0_INT_HPRIORITY();break;
            case(LOW_PRIORITY) :TIMER0_INT_LPRIORITY();break;
            default :           TIMER0_INT_HPRIORITY();break;
        }        
        #else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERIAL_INTERRUPT_ENABLE();
        #endif      
        /*enable timer0 interrupt feature*/
        TIMER0_INT_ENABLE();
        Timer0_INT_HANDLER=timer0->TIMER0_InterruptHandler;
        #endif

        /*preload timer 0*/
        #if TIMER0_RESOLUTION == 8
        TMR0L=timer0->timer0_preload;
        timer0_preload=timer0->timer0_preload;
        #else
        TMR0H=(timer0->timer0_preload)>>8;
        TMR0L=(uint8)(timer0->timer0_preload);
        timer0_preload=timer0->timer0_preload;
        #endif 

        /*enable timer0*/
        T0CONbits.TMR0ON=TIMER0_ENABLE;
    }
    else
    {
        ret = E_NOT_OK;
    }
}

/**
 * 
 * @param 
 * @return 
 */
Std_ReturnType Timer0_DeInit(const timer0_cfg_t* timer0)
{
    Std_ReturnType ret = E_OK;
    if(timer0)
    {
        /*disable timer0*/
        T0CONbits.TMR0ON=TIMER0_DISABLE;
        /*disable timer0 interrupt feature*/
        TIMER0_INT_DISABLE();
    }
    else
    {
        ret = E_NOT_OK;
    }
}

#if TIMER0_RESOLUTION == 8
Std_ReturnType Timer0_Write_Value (uint8 value)
{
    Std_ReturnType ret = E_OK;
    TMR0L=value;
    return ret;
}    
    
/**
 * 
 * @param timer0
 * @param value
 * @return 
 */    
Std_ReturnType Timer0_Read_Value  ( uint8* value)
{
    Std_ReturnType ret = E_OK;
    if(value)
    {
        *value=TMR0L;
    }
    else
    {
        ret=E_NOT_OK;
    }
    return ret;
} 

#else
/**
 * 
 * @param timer0
 * @param value
 * @return 
 */
Std_ReturnType Timer0_Write_Value (uint16 value)
{
    Std_ReturnType ret = E_OK;
    TMR0H=value>>8;
    TMR0L=(uint8)(value);
    return ret;
}

/**
 * 
 * @param timer0
 * @param value
 * @return 
 */
Std_ReturnType Timer0_Read_Value  (uint16* value)
{
    Std_ReturnType ret = E_OK;
    if(value)
    {
        uint8 value_low=0,value_high=0;
        value_low=TMR0L;
        value_high=TMR0H;
        *value=value_low+value_high*256;
    }
    else
    {
        ret=E_NOT_OK;
    }
    return ret;
}
#endif

#if INTERRUPT_TIMER0_FEATURE==ENABLE
void TIM0_ISR()
{
    TIMER0_INT_CLEARFLAG();
    /*preload timer 0*/
    #if TIMER0_RESOLUTION == 8
    TMR0L=timer0_preload;
    #else
    TMR0H=timer0_preload>>8;
    TMR0L=(uint8)(timer0_preload);
    #endif     
    if(Timer0_INT_HANDLER) Timer0_INT_HANDLER(); 
}
#endif