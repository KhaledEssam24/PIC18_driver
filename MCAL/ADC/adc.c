#include "adc.h"

#if INTERRUPT_ADC_FEATURE==ENABLE
static void (*Global_ADC_INT_HANDLER)(void)=NULL;
#endif
static void ADC_Config_Analog_Pin (adc_channel_select_t channel);

/**
 * 
 * @param adc
 * @return 
 */
Std_ReturnType ADC_Init(const adc_config_t* adc)
{
    Std_ReturnType ret = E_OK;
    if(adc)
    {
        /*disable ADC*/
        ADC_DISABLE();
        /*config acqusisition time*/
        ADC_CONFIG_TAD(adc->ADC_TAD);
        /*config clock prescalar*/
        ADC_CONFIG_CLOCK_FOSC(adc->ADC_CLOCK_FOSC);
        /*config default channel*/
        ADC_SELECT_CHANNEL(adc->adc_channel);
        ADC_Config_Analog_Pin(adc->adc_channel);
        /*config adc result format*/
        #if ADC_RESULT_FORMAT==ADC_LEFT_JUSTIFIED
        ADC_LEFT_JUSTIFIED_CFG();
        #else
        ADC_RIGHT_JUSTIFIED_CFG();
        #endif
        /*config voltage reference*/
        #if VOLTAGE_REF==ADC_EXTERNAL_REF 
        ADC_EXTERNAL_REF_CFG();
        #else
        ADC_INTERNAL_REF_CFG();
        #endif
        /*config interrupt handler*/
        #if INTERRUPT_ADC_FEATURE==ENABLE
        ADC_INT_CLEARFLAG();
        #if INTERRUPT_PRIORITY_FEATURE==ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        INTERRUPT_HPRIORITY_ENABLE();
        INTERRUPT_LPRIORITY_ENABLE();
        switch(adc->adc_priority)
        {
            case(HIGH_PRIORITY):ADC_INT_HPRIORITY();break;
            case(LOW_PRIORITY) :ADC_INT_LPRIORITY();break;
            default :           ADC_INT_HPRIORITY();break;
        }
        #else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERIAL_INTERRUPT_ENABLE();
        #endif        
        ADC_INT_ENABLE();
        if(adc->ADC_InterruptHandler) Global_ADC_INT_HANDLER=adc->ADC_InterruptHandler;
        else ret=E_NOT_OK;
        #endif    
        /*enable ADC*/
        ADC_ENABLE();
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}

/**
 * 
 * @param adc
 * @return 
 */
Std_ReturnType ADC_DeInit(const adc_config_t* adc)
{
    Std_ReturnType ret = E_OK;
    if(adc)
    {
        /*disable ADC*/
        ADC_DISABLE();
        /*config interrupt handler*/
        #if INTERRUPT_ADC_FEATURE==ENABLE
        ADC_INT_DISABLE();
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
 * @param adc
 * @param channel
 * @return 
 */
Std_ReturnType ADC_SelectChannel (adc_channel_select_t channel )
{
    Std_ReturnType ret = E_OK;
    ADC_SELECT_CHANNEL(channel);
    ADC_Config_Analog_Pin(channel);
    return ret;
}

/**
 * 
 * @param adc
 * @return 
 */
Std_ReturnType ADC_StartConversion ()
{
    Std_ReturnType ret = E_OK;
    ADC_START_CONVERSION();   
    return ret;
}

/**
 * this API is for getting the status of the conversion if status True then conversion is complete
 * @param adc
 * @param status
 * @return 
 */
Std_ReturnType ADC_ConversionStatus (uint8* status)
{
    Std_ReturnType ret = E_OK;
    if(status)
    {
        *status= !(uint8) ADC_CONVERSION_STATUS();
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}

/**
 *  this API is for getting result of ADC
 * @param res
 * @return 
 */
Std_ReturnType ADC_GetResult (uint16* res)
{
    Std_ReturnType ret = E_OK;
    if(res)
    {
        #if INTERRUPT_ADC_FEATURE==ENABLE
        #else
        while(ADC_CONVERSION_STATUS() == ADCINPROGRESS){};
        #endif
        #if ADC_RESULT_FORMAT==ADC_LEFT_JUSTIFIED
        *res = (uint16)((ADRESL+(ADRESH<<8))>>6);break;
        #else
        *res = ADRESL+(ADRESH<<8);
        #endif     
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}

/**
 * this API is for selecting channel ,start conversion and get result in one call
 * @param adc
 * @param res
 * @return 
 */
Std_ReturnType ADC_GetConversionBlocking (uint16* res ,adc_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;
    if(res)
    {
        /*select channel*/
        ret &= ADC_SelectChannel(channel);
        /*start conversion*/
        ret &= ADC_StartConversion();
        /*get the result*/
        ret &= ADC_GetResult(res);
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}

#if INTERRUPT_ADC_FEATURE==ENABLE
/**
 * 
 * @param channel
 */
Std_ReturnType ADC_GetConversionInterrupt (adc_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;

    /*select channel*/
    ret &= ADC_SelectChannel(channel);
    /*start conversion*/
    ret &= ADC_StartConversion(); 
    return ret;
}
#endif

/**
 * 
 * @param channel
 */
static void ADC_Config_Analog_Pin (adc_channel_select_t channel)
{
    switch(channel)
    {
        case ADC_CHANNEL0: SET_BIT(TRISA,_TRISA_RA0_POSITION) ;break;
        case ADC_CHANNEL1: SET_BIT(TRISA,_TRISA_RA1_POSITION) ;break;
        case ADC_CHANNEL2: SET_BIT(TRISA,_TRISA_RA2_POSITION) ;break;
        case ADC_CHANNEL3: SET_BIT(TRISA,_TRISA_RA3_POSITION) ;break;
        case ADC_CHANNEL4: SET_BIT(TRISA,_TRISA_RA5_POSITION) ;break;        
        case ADC_CHANNEL5: SET_BIT(TRISE,_TRISE_RE0_POSITION) ;break;
        case ADC_CHANNEL6: SET_BIT(TRISE,_TRISE_RE1_POSITION) ;break;
        case ADC_CHANNEL7: SET_BIT(TRISE,_TRISE_RE2_POSITION) ;break;        
        case ADC_CHANNEL8: SET_BIT(TRISB,_TRISB_RB2_POSITION) ;break;
        case ADC_CHANNEL9: SET_BIT(TRISB,_TRISB_RB3_POSITION) ;break;
        case ADC_CHANNEL10:SET_BIT(TRISB,_TRISB_RB1_POSITION) ;break;
        case ADC_CHANNEL11:SET_BIT(TRISB,_TRISB_RB4_POSITION) ;break;
        case ADC_CHANNEL12:SET_BIT(TRISB,_TRISB_RB0_POSITION) ;break;     
    }
}

#if INTERRUPT_ADC_FEATURE==ENABLE
void ADC_ISR()
{
    ADC_INT_CLEARFLAG();
    if(Global_ADC_INT_HANDLER) Global_ADC_INT_HANDLER(); 
}
#endif