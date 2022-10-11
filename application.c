#include "application.h"
#include "MCAL/Timer/Timer1.h"
#include "MCAL/CCP/ccp.h"
#include "MCAL/Timer/Timer3.h"

volatile uint8 flag=0;

timer1_cfg_t timer1=
{
    .TIMER1_InterruptHandler=TIM1_Handler,
    .timer1_osc_enable=TIMER1_OSCILLATOR_DISABLE,
    .timer1_priority=LOW_PRIORITY,
    .timer1_mode=TIMER1_TIMER_MODE,
    .timer1_preload=0,
    .timer1_prescaler_cfg=TIMER1_PRESCALER_DIV1,    
};

ccp1_cfg_t ccp1=
{
    .CCP1_InterruptHandler=CCP1_Handler,
    .ccp1_priority=LOW_PRIORITY,
    .ccp_timer_select=CCP1_TIMER1_CCP2_TIMER1,
    .mode=CCP1_COMPARE_MODE_TOGGLE_ON_MATCH,
};



void main() 
{
    
    Timer1_Init(&timer1);
    CCP1_CompareValue(12500);
    CCP1_Init(&ccp1);
    while(1)
    {
        
    }
}

void CCP1_Handler()
{
    if (flag==0)
    {
        CCP1_CompareValue(12500);
        Timer1_Write_Value(0);
        flag=1;
    }
    else if (flag==1)
    {
        CCP1_CompareValue(37500);
        Timer1_Write_Value(0);
        flag=0;
    }
    
}
void TIM1_Handler()
{

}

