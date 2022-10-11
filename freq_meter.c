#include "application.h"
#include "ECU/LED/led.h"
#include "MCAL/Timer/Timer1.h"
volatile uint16 freq=0;

timer0_cfg_t timer0=
{
    .TIMER0_InterruptHandler=TIM0_Handler,
    .timer0_priority = LOW_PRIORITY,
    .timer0_edge_cfg=TIMER0_RISING_EDGE,
    .timer0_mode=TIMER0_COUNTER_MODE,
    .timer0_prescaler_enable=TIMER0_PRESCALER_DISABLE,
    //.timer0_prescaler_cfg=TIMER0_PRESCALER_DIV16,
    .timer0_preload=0   
};


timer1_cfg_t timer1=
{
    .TIMER1_InterruptHandler=TIM1_Handler,
    .timer1_mode=TIMER1_TIMER_MODE,
    .timer1_osc_enable=TIMER1_OSCILLATOR_DISABLE,
    .timer1_preload=3036,
    .timer1_priority=LOW_PRIORITY,
    .timer1_prescaler_cfg=TIMER1_PRESCALER_DIV8,
    .timer1_sync=TIMER1_ASYNC_EXTERNAL_CLOCK,
};


void main() 
{
    Timer0_Init(&timer0);
    Timer1_Init(&timer1);
    //led_initialize(&led1);
    while(1)
    {
        //Timer0_Read_Value(&timer,&counter);
    }  
}

void TIM2_Handler()
{

}
void TIM1_Handler()
{
    Timer0_Read_Value(&freq);
    Timer0_Write_Value(0x00);
}