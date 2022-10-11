#include "ccp.h"

#if INTERRUPT_CCP1_FEATURE==ENABLE
static void (*CCP1_INT_HANDLER)(void) = NULL ;
#endif
#if INTERRUPT_CCP2_FEATURE==ENABLE
static void (*CCP2_INT_HANDLER)(void) = NULL ;
#endif

/**
 * 
 * @param ccp1
 * @return 
 */
Std_ReturnType CCP1_Init   (const ccp1_cfg_t* ccp1)
{
    Std_ReturnType ret = E_OK; 
    if(ccp1)
    {
        /*disable ccp1 module*/
        CCP1CONbits.CCP1M= CCP1_DISABLED ;
        /* select the mode of ccp1 module */
        #if CCP1_CFG_MODE_SELECTED==CCP1_CFG_PWM_MODE
        #else
        CCP1CONbits.CCP1M= ccp1->mode ;
        #endif
        #if CCP1_CFG_MODE_SELECTED==CCP1_CFG_CAPTURE_MODE
        SET_BIT(TRISC,_TRISC_RC2_POSITION);      /*input config*/
        #else
        CLEAR_BIT(TRISC,_TRISC_RC2_POSITION);    /*output config*/
        #endif

        #if CCP1_CFG_MODE_SELECTED==CCP1_CFG_CAPTURE_MODE
        T3CONbits.T3CCP1 = ccp1->ccp_timer_select & 0x01 ;
        T3CONbits.T3CCP2 = ccp1->ccp_timer_select & 0x02;
        #endif

        #if CCP1_CFG_MODE_SELECTED==CCP1_CFG_PWM_MODE
        /* pwm frequency initialize */
        switch(ccp1->timer2_prescaler_cfg)
        {
            case TIMER2_PRESCALER_DIV1:PR2= (uint8)((_XTAL_FREQ_/4)/(ccp1->frequency * ccp1->timer2_postscaler_cfg)    -1);break;
            case TIMER2_PRESCALER_DIV4:PR2= (uint8)((_XTAL_FREQ_/4)/(ccp1->frequency * ccp1->timer2_postscaler_cfg *4) -1);break;
            case TIMER2_PRESCALER_DIV16:PR2=(uint8)((_XTAL_FREQ_/4)/(ccp1->frequency * ccp1->timer2_postscaler_cfg *16)-1);break;
            default: PR2= (uint8)((_XTAL_FREQ_/4.0)/(ccp1->frequency * ccp1->timer2_postscaler_cfg *ccp1->timer2_prescaler_cfg) -1);break;
        }
              
        #endif        
        
        #if INTERRUPT_CCP1_FEATURE==ENABLE
        /*clear flag*/
        CCP1_INT_CLEARFLAG();
        /*global interrupt enable*/
        #if INTERRUPT_PRIORITY_FEATURE==ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        INTERRUPT_HPRIORITY_ENABLE();
        INTERRUPT_LPRIORITY_ENABLE();
        switch(ccp1->ccp1_priority)
        {
            case(HIGH_PRIORITY):CCP1_INT_HPRIORITY();break;
            case(LOW_PRIORITY) :CCP1_INT_LPRIORITY();break;
            default :           CCP1_INT_HPRIORITY();break;
        }        
        #else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERIAL_INTERRUPT_ENABLE();
        #endif      
        /*enable CCP1 interrupt feature*/
        CCP1_INT_ENABLE();
        CCP1_INT_HANDLER=ccp1->CCP1_InterruptHandler;
        #endif
    
    }
    else
    {
        ret = E_NOT_OK;  
    }
    return ret;
}

/**
 * 
 * @param ccp2
 * @return 
 */
Std_ReturnType CCP2_Init   (const ccp2_cfg_t* ccp2)
{
    Std_ReturnType ret = E_OK; 
    if(ccp2)
    {
        /*disable ccp2 module*/
        CCP2CONbits.CCP2M= CCP2_DISABLED ;
        /* select the mode of ccp1 module */
        #if CCP2_CFG_MODE_SELECTED==CCP2_CFG_PWM_MODE
        #else
        CCP2CONbits.CCP2M= ccp2->mode ;
        #endif
        #if CCP2_CFG_MODE_SELECTED==CCP2_CFG_CAPTURE_MODE
        SET_BIT(TRISC,_TRISC_RC1_POSITION);      /*input config*/
        #else
        CLEAR_BIT(TRISC,_TRISC_RC1_POSITION);    /*output config*/
        #endif

        #if CCP2_CFG_MODE_SELECTED==CCP2_CFG_PWM_MODE
        /* pwm frequency initialize */
        switch(ccp2->timer2_prescaler_cfg)
        {
            case TIMER2_PRESCALER_DIV1:PR2= (uint8)((_XTAL_FREQ/4)/(ccp2->frequency * ccp2->timer2_postscaler_cfg) -1);break;
            case TIMER2_PRESCALER_DIV4:PR2= (uint8)((_XTAL_FREQ/4)/(ccp2->frequency * ccp2->timer2_postscaler_cfg *4) -1);break;
            case TIMER2_PRESCALER_DIV16:PR2= (uint8)((_XTAL_FREQ/4)/(ccp2->frequency * ccp2->timer2_postscaler_cfg *16) -1);break;
            default: PR2= (uint8)((_XTAL_FREQ/4)/(ccp2->frequency * ccp2->timer2_postscaler_cfg *ccp2->timer2_prescaler_cfg) -1);break;
        }
              
        #endif

        #if CCP1_CFG_MODE_SELECTED==CCP1_CFG_CAPTURE_MODE
        T3CONbits.T3CCP1 = ccp2->ccp_timer_select & 0x01 ;
        T3CONbits.T3CCP2 = ccp2->ccp_timer_select & 0x02;
        #endif

        #if INTERRUPT_CCP2_FEATURE==ENABLE
        /*clear flag*/
        CCP2_INT_CLEARFLAG();
        /*global interrupt enable*/
        #if INTERRUPT_PRIORITY_FEATURE==ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        INTERRUPT_HPRIORITY_ENABLE();
        INTERRUPT_LPRIORITY_ENABLE();
        switch(ccp2->ccp2_priority)
        {
            case(HIGH_PRIORITY):CCP2_INT_HPRIORITY();break;
            case(LOW_PRIORITY) :CCP2_INT_LPRIORITY();break;
            default :           CCP2_INT_HPRIORITY();break;
        }        
        #else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERIAL_INTERRUPT_ENABLE();
        #endif      
        /*enable CCP2 interrupt feature*/
        CCP2_INT_ENABLE();
        CCP2_INT_HANDLER=ccp2->CCP2_InterruptHandler;
        #endif

    }
    else
    {
        ret = E_NOT_OK;  
    }
    return ret;
}

/**
 * 
 * @param ccp1
 * @return 
 */
Std_ReturnType CCP1_DeInit (const ccp1_cfg_t* ccp1)
{
    Std_ReturnType ret = E_OK; 
    if(ccp1)
    {
        /*disable ccp1 module*/
        CCP1CONbits.CCP1M= CCP1_DISABLED ;
        #if INTERRUPT_CCP1_FEATURE==ENABLE
        CCP1_INT_DISABLE();
        #endif
    }
    else
    {
        ret = E_NOT_OK;  
    }
    return ret;
}

/**
 * 
 * @param ccp2
 * @return 
 */
Std_ReturnType CCP2_DeInit (const ccp2_cfg_t* ccp2)
{
    Std_ReturnType ret = E_OK; 
    if(ccp2)
    {
        /*disable ccp2 module*/
        CCP2CONbits.CCP2M= CCP2_DISABLED ;
        #if INTERRUPT_CCP2_FEATURE==ENABLE
        CCP2_INT_DISABLE();
        #endif
    }
    else
    {
        ret = E_NOT_OK;  
    }
    return ret;
}

#if   CCP1_CFG_MODE_SELECTED==CCP1_CFG_CAPTURE_MODE
/**
 * 
 * @param status
 * @return 
 */
Std_ReturnType CCP1_CaptureDataIsReady (uint8* status)
{
    Std_ReturnType ret = E_OK; 
    if(status)
    {
        *status=PIR1bits.CCP1IF;
        if (PIR1bits.CCP1IF == CCP1_IS_DONE) PIR1bits.CCP1IF=0; /*clear flag*/
    }
    else
    {
        ret = E_NOT_OK;  
    }
    return ret;
}

/**
 * 
 * @param value
 * @return 
 */
Std_ReturnType CCP1_CaptureReadValue (uint16* value)
{
    Std_ReturnType ret = E_OK; 
    if(value)
    {
        *value= CCPR1L+(CCPR1H<<8);
    }
    else
    {
        ret = E_NOT_OK;  
    }
    return ret;
}


#elif CCP1_CFG_MODE_SELECTED==CCP1_CFG_COMPARE_MODE 

/**
 * 
 * @param status
 * @return 
 */
Std_ReturnType CCP1_CompareIsComplete (uint8* status)
{
    Std_ReturnType ret = E_OK; 
    if(status)
    {
        *status=PIR1bits.CCP1IF;
        if (PIR1bits.CCP1IF == CCP1_IS_DONE) PIR1bits.CCP1IF=0; /*clear flag*/        
    }
    else
    {
        ret = E_NOT_OK;  
    }
    return ret;
}

/**
 * 
 * @param value
 * @return 
 */
Std_ReturnType CCP1_CompareValue (uint16 value)
{
    Std_ReturnType ret = E_OK; 
    CCPR1L=(uint8)value;
    CCPR1H=(uint8)(value>>8);    
    return ret;
}
    
#else
/**
 * 
 * @param duty
 * @return 
 */
Std_ReturnType CCP1_PWM_Duty(uint8 duty)
{
    Std_ReturnType ret = E_OK;  
    duty=100-duty;
    uint16 l_duty=(uint16) ( (PR2+1) * duty * 4 / 100) ;
    CCP1CONbits.DC1B =(uint8) (l_duty & 0x03) ;
    CCPR1L=(uint8) (l_duty >> 2) ;
    return ret;
}

/**
 * 
 * @return 
 */
Std_ReturnType CCP1_PWM_Start()
{
    Std_ReturnType ret = E_OK;   
    CCP1CONbits.CCP1M= CCP1_PWM_MODE ;
    return ret;
}

Std_ReturnType CCP1_PWM_Stop()
{
    Std_ReturnType ret = E_OK;
    CCP1CONbits.CCP1M= CCP1_DISABLED ;
    return ret;
}
#endif

#if   CCP2_CFG_MODE_SELECTED==CCP2_CFG_CAPTURE_MODE
/**
 * 
 * @param status
 * @return 
 */
Std_ReturnType CCP2_CaptureDataIsReady (uint8* status)
{
    Std_ReturnType ret = E_OK; 
    if(status)
    {
        *status=PIR2bits.CCP2IF;
        if (PIR2bits.CCP2IF == CCP2_IS_DONE) PIR2bits.CCP2IF=0; /*clear flag*/
    }
    else
    {
        ret = E_NOT_OK;  
    }
    return ret;
}

/**
 * 
 * @param value
 * @return 
 */
Std_ReturnType CCP2_CaptureReadValue (uint16* value)
{
    Std_ReturnType ret = E_OK; 
    if(value)
    {
        *value= CCPR2L+(CCPR2H<<8);
    }
    else
    {
        ret = E_NOT_OK;  
    }
    return ret;
}


#elif CCP2_CFG_MODE_SELECTED==CCP2_CFG_COMPARE_MODE 

/**
 * 
 * @param status
 * @return 
 */
Std_ReturnType CCP2_CompareIsComplete (uint8* status)
{
    Std_ReturnType ret = E_OK; 
    if(status)
    {
        *status=PIR2bits.CCP2IF;
        if (PIR2bits.CCP2IF == CCP2_IS_DONE) PIR2bits.CCP2IF=0; /*clear flag*/        
    }
    else
    {
        ret = E_NOT_OK;  
    }
    return ret;
}

/**
 * 
 * @param value
 * @return 
 */
Std_ReturnType CCP2_CompareValue (uint16 value)
{
    Std_ReturnType ret = E_OK; 
    CCPR2L=(uint8)value;
    CCPR2H=(uint8)(value>>8);    
    return ret;
}
    
#else
/**
 * 
 * @param duty
 * @return 
 */
Std_ReturnType CCP2_PWM_Duty(uint8 duty)
{
    Std_ReturnType ret = E_OK;  
    //duty=100-duty;
    uint16 l_duty=(uint16) ( (PR2+1) * duty * 4 / 100) ;
    CCP2CONbits.DC2B =(uint8) (l_duty & 0x03) ;
    CCPR2L=(uint8) (l_duty >> 2) ;
    return ret;
}

/**
 * 
 * @return 
 */
Std_ReturnType CCP2_PWM_Start()
{
    Std_ReturnType ret = E_OK;   
    CCP2CONbits.CCP2M= CCP2_PWM_MODE ;
    return ret;
}


Std_ReturnType CCP2_PWM_Stop()
{
    Std_ReturnType ret = E_OK;
    CCP2CONbits.CCP2M= CCP2_DISABLED ;
    return ret;
}
#endif



#if INTERRUPT_CCP1_FEATURE==ENABLE
void CCP1_ISR()
{
    CCP1_INT_CLEARFLAG();
    if(CCP1_INT_HANDLER) CCP1_INT_HANDLER(); 
}
#endif

#if INTERRUPT_CCP2_FEATURE==ENABLE
void CCP2_ISR()
{
    CCP2_INT_CLEARFLAG();
    if(CCP2_INT_HANDLER) CCP2_INT_HANDLER(); 
}
#endif