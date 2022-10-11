/* 
 * File:   adc.h
 * Author: El-Rehab
 *
 * Created on September 6, 2022, 12:35 AM
 */

#ifndef ADC_H
#define	ADC_H

/*********************includes*********************/
#include "adc_config.h"
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../mcal_interrupt/mcal_internal_interrupt.h"
#include "../gpio/gpio.h"
#include "adc_config.h"

/*************Section macros declarations**********/
#define ADC_AN0_ANALOG_FUNCTIONALITY 0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY 0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY 0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY 0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY 0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY 0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY 0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY 0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY 0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY 0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY 0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY 0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY 0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY 0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY 0x0F


#define ADCINPROGRESS 1
#define ADCINIDLE 1
/*************Section macros function declarations*/
#define ADC_ENABLE()  (ADCON0bits.ADON=1)
#define ADC_DISABLE() (ADCON0bits.ADON=0)

#define ADC_CONVERSION_STATUS() (ADCON0bits.GO_nDONE)
#define ADC_START_CONVERSION()  (ADCON0bits.GO_nDONE=1)

#define ADC_SELECT_CHANNEL(channel)  (ADCON0bits.CHS=channel)

#define ADC_INTERNAL_REF_CFG() (ADCON1bits.VCFG=0)
#define ADC_EXTERNAL_REF_CFG() (ADCON1bits.VCFG=3)

/*if AN7 is selected then from AN0 to AN7 will be Analog pins*/
#define ADC_ANALOG_FUNCTIONALITY (ANx) (ADCON1bits.PCFG=ANx) 

#define ADC_RIGHT_JUSTIFIED_CFG() (ADCON2bits.ADFM = 1) 
#define ADC_LEFT_JUSTIFIED_CFG()  (ADCON2bits.ADFM = 0) 

#define ADC_CONFIG_CLOCK_FOSC(ADC_CLOCK_FOSC) (ADCON2bits.ADCS=ADC_CLOCK_FOSC)
#define ADC_CONFIG_TAD(ADC_TAD)               (ADCON2bits.ACQT=ADC_TAD)




/*************Section Data type declaration********/
typedef enum
{
    ADC_CHANNEL0,
    ADC_CHANNEL1,
    ADC_CHANNEL2,
    ADC_CHANNEL3,
    ADC_CHANNEL4,
    ADC_CHANNEL5,
    ADC_CHANNEL6,
    ADC_CHANNEL7,
    ADC_CHANNEL8,
    ADC_CHANNEL9,
    ADC_CHANNEL10,
    ADC_CHANNEL11,
    ADC_CHANNEL12,            
}adc_channel_select_t;

typedef enum 
{
    ADC_0_TAD,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,
}ADC_TAD_t;

typedef enum 
{
    ADC_CLOCK_FOSC_DIV_2,
    ADC_CLOCK_FOSC_DIV_8,
    ADC_CLOCK_FOSC_DIV_32,
    ADC_CLOCK_FOSC_DIV_RC,
    ADC_CLOCK_FOSC_DIV_4,
    ADC_CLOCK_FOSC_DIV_16,
    ADC_CLOCK_FOSC_DIV_64,             
}ADC_CLOCK_FOSC_t;

typedef struct
{
    #if INTERRUPT_ADC_FEATURE==ENABLE
    void (* ADC_InterruptHandler)(void);
    #if INTERRUPT_PRIORITY_FEATURE==ENABLE
    priority_cfg_t adc_priority;
    #endif
    #endif
    ADC_CLOCK_FOSC_t ADC_CLOCK_FOSC;
    ADC_TAD_t       ADC_TAD;
    adc_channel_select_t adc_channel;
}adc_config_t;

/*************Section function declaration*********/
Std_ReturnType ADC_Init(const adc_config_t* adc);
Std_ReturnType ADC_DeInit(const adc_config_t* adc);
Std_ReturnType ADC_SelectChannel (adc_channel_select_t channel );
Std_ReturnType ADC_StartConversion ();
Std_ReturnType ADC_ConversionStatus (uint8* status);
Std_ReturnType ADC_GetResult (uint16* res);
Std_ReturnType ADC_GetConversionBlocking (uint16* res ,adc_channel_select_t channel);

#if INTERRUPT_ADC_FEATURE==ENABLE
Std_ReturnType ADC_GetConversionInterrupt (adc_channel_select_t channel);
void ADC_ISR();
#endif

#endif	/* ADC_H */

