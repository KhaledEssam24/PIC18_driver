#include "mcal_external_interrupt.h"
#if INTERRUPT_FEATURE==ENABLE
#if INTERRUPT_EXTINT_FEATURE==ENABLE

static void (*Global_INT0_HANDLER)(void)=NULL;
static void (*Global_INT1_HANDLER)(void)=NULL;
static void (*Global_INT2_HANDLER)(void)=NULL;

static void (*Global_INTRB4_HANDLER_HIGH)(void)=NULL;
static void (*Global_INTRB4_HANDLER_LOW)(void)=NULL;
static void (*Global_INTRB5_HANDLER_HIGH)(void)=NULL;
static void (*Global_INTRB5_HANDLER_LOW)(void)=NULL;
static void (*Global_INTRB6_HANDLER_HIGH)(void)=NULL;
static void (*Global_INTRB6_HANDLER_LOW)(void)=NULL;
static void (*Global_INTRB7_HANDLER_HIGH)(void)=NULL;
static void (*Global_INTRB7_HANDLER_LOW)(void)=NULL;

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init   (const Interrupt_INTx_t* int_obj)
{
    Std_ReturnType ret =E_OK;
    if (int_obj)
    {
        //pin initialization
        ret=gpio_pin_initialize(&(int_obj->pin));
        switch(int_obj->src)
        {
            case EXT_INT0 :
                //disable
                EXT_INT0_DISABLE();
                //clear flag
                EXT_INT0_CLEARFLAG();
                // edge selection
                switch(int_obj->edge)
                {
                    case FALLING_EDGE: EXT_INT0_FALLING_EDGE();ret =E_OK; break;
                    case RISING_EDGE : EXT_INT0_RISING_EDGE(); ret =E_OK; break;
                    default : ret =E_NOT_OK; break;
                }
                //call back 
                if (int_obj->EXT_interruptHandler)
                {
                    Global_INT0_HANDLER=int_obj->EXT_interruptHandler;
                }
                else
                {
                    ret =E_NOT_OK;
                }
                //enable
                EXT_INT0_ENABLE();
                #if INTERRUPT_PRIORITY_FEATURE==ENABLE
                INTERRUPT_PRIORITY_ENABLE();
                INTERRUPT_HPRIORITY_ENABLE();
                INTERRUPT_LPRIORITY_ENABLE();
                EXT_INT1_HPRIORITY();
                #else
                GLOBAL_INTERRUPT_ENABLE();
                PERIPHERIAL_INTERRUPT_ENABLE();
                #endif
                ret =E_OK;
                break;
                
                
                case EXT_INT1 :
                //disable
                EXT_INT1_DISABLE();
                // edge selection
                switch(int_obj->edge)
                {
                    case FALLING_EDGE: EXT_INT1_FALLING_EDGE();ret =E_OK; break;
                    case RISING_EDGE : EXT_INT1_RISING_EDGE(); ret =E_OK; break;
                    default : ret =E_NOT_OK; break;
                }
                //priority selection
                #if INTERRUPT_PRIORITY_FEATURE==ENABLE
                switch(int_obj->priority)
                {
                    case HIGH_PRIORITY: EXT_INT1_HPRIORITY();INTERRUPT_HPRIORITY_ENABLE();ret =E_OK; break;
                    case LOW_PRIORITY : EXT_INT1_LPRIORITY();INTERRUPT_LPRIORITY_ENABLE();ret =E_OK; break;
                    default : ret =E_NOT_OK; break;
                }
                #endif
                //call back 
                if (int_obj->EXT_interruptHandler)
                {
                    Global_INT1_HANDLER = int_obj->EXT_interruptHandler;
                }
                else
                {
                    ret =E_NOT_OK;
                }
                //enable
                EXT_INT1_ENABLE();
                #if INTERRUPT_PRIORITY_FEATURE==ENABLE
                INTERRUPT_PRIORITY_ENABLE();         
                #else
                GLOBAL_INTERRUPT_ENABLE();
                PERIPHERIAL_INTERRUPT_ENABLE();
                #endif
                ret =E_OK;
                break;
                
                
                case EXT_INT2 :
                //disable
                EXT_INT2_DISABLE();
                // edge selection
                switch(int_obj->edge)
                {
                    case FALLING_EDGE: EXT_INT2_FALLING_EDGE();ret =E_OK; break;
                    case RISING_EDGE : EXT_INT2_RISING_EDGE() ; ret =E_OK; break;
                    default : ret =E_NOT_OK; break;
                }
                //enable
                #if INTERRUPT_PRIORITY_FEATURE==ENABLE
                INTERRUPT_PRIORITY_ENABLE();              
                #else
                GLOBAL_INTERRUPT_ENABLE();
                PERIPHERIAL_INTERRUPT_ENABLE();
                #endif
                //priority selection
                #if INTERRUPT_PRIORITY_FEATURE==ENABLE
                switch(int_obj->priority)
                {
                    case HIGH_PRIORITY: INTERRUPT_HPRIORITY_ENABLE();EXT_INT2_HPRIORITY();ret =E_OK; break;
                    case LOW_PRIORITY : INTERRUPT_LPRIORITY_ENABLE();EXT_INT2_LPRIORITY();ret =E_OK;break;
                    default : ret =E_NOT_OK; break;
                }
                #endif
                EXT_INT2_ENABLE();
                //call back 
                if (int_obj->EXT_interruptHandler)
                {
                    Global_INT2_HANDLER=int_obj->EXT_interruptHandler;
                }
                else
                {
                    ret =E_NOT_OK;
                }
                
                ret =E_OK;
                break;  
        }
    }
    else
    {
        Std_ReturnType ret =E_NOT_OK;
    }
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit (const Interrupt_INTx_t* int_obj)
{
    Std_ReturnType ret =E_OK;
    if (int_obj)
    {
        switch(int_obj->src)
        {
            case EXT_INT0 :
                //disable
                EXT_INT0_DISABLE(); ret =E_OK; break;
            case EXT_INT1 :
                EXT_INT1_DISABLE(); ret =E_OK; break;
            case EXT_INT2 :    
                EXT_INT2_DISABLE(); ret =E_OK; break;
            default : ret =E_NOT_OK; break;       
        }
    }
    else
    {
        Std_ReturnType ret =E_NOT_OK;
    }
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init    (const Interrupt_RBx_t* int_obj)
{
    Std_ReturnType ret =E_OK;
    if (int_obj)
    {
        //pin initialization
        ret=gpio_pin_initialize(&(int_obj->pin));
        //disable
        EXT_INT_ONCHANGE_DISABLE();
        //clear flag
        EXT_INT_ONCHANGE_CLEARFLAG();
        //callback
        if (int_obj->EXT_interruptHandler_HIGH&&int_obj->EXT_interruptHandler_LOW)
        {
            switch((int_obj->pin).pin)
            {
                case PIN4:Global_INTRB4_HANDLER_HIGH =int_obj->EXT_interruptHandler_HIGH;
                          Global_INTRB4_HANDLER_LOW = int_obj->EXT_interruptHandler_LOW ;break;
                case PIN5:Global_INTRB5_HANDLER_HIGH =int_obj->EXT_interruptHandler_HIGH;
                          Global_INTRB5_HANDLER_LOW = int_obj->EXT_interruptHandler_LOW ;break;
                case PIN6:Global_INTRB6_HANDLER_HIGH =int_obj->EXT_interruptHandler_HIGH;
                          Global_INTRB6_HANDLER_LOW = int_obj->EXT_interruptHandler_LOW ;break;
                case PIN7:Global_INTRB7_HANDLER_HIGH =int_obj->EXT_interruptHandler_HIGH;
                          Global_INTRB7_HANDLER_LOW = int_obj->EXT_interruptHandler_LOW ;break;                          
                default: ret =E_NOT_OK;break;
            }   
        }
        else
        {
            ret =E_NOT_OK;
        }
        //enable
        #if INTERRUPT_PRIORITY_FEATURE==ENABLE
        INTERRUPT_PRIORITY_ENABLE();              
        #else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERIAL_INTERRUPT_ENABLE();
        #endif
        //priority selection
        #if INTERRUPT_PRIORITY_FEATURE==ENABLE
        switch(int_obj->priority)
        {
            case HIGH_PRIORITY: INTERRUPT_HPRIORITY_ENABLE();EXT_INT_ONCHANGE_HPRIORITY();ret =E_OK; break;
            case LOW_PRIORITY : INTERRUPT_LPRIORITY_ENABLE();EXT_INT_ONCHANGE_LPRIORITY();ret =E_OK;break;
            default : ret =E_NOT_OK; break;
        }
        #endif
        EXT_INT_ONCHANGE_ENABLE();   
    }
    else
    {
        Std_ReturnType ret =E_NOT_OK;
    }
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit  (const Interrupt_RBx_t* int_obj)
{
    Std_ReturnType ret =E_OK;
    if (int_obj)
    {
        
    }
    else
    {
        Std_ReturnType ret =E_NOT_OK;
    }
}


void INT0_ISR()
{
    if(Global_INT0_HANDLER)
    {
        Global_INT0_HANDLER();
        EXT_INT0_CLEARFLAG();
    }
}

void INT1_ISR()
{
    if(Global_INT1_HANDLER)
    {
        Global_INT1_HANDLER();
        EXT_INT1_CLEARFLAG();
    }
}

void INT2_ISR()
{
    if(Global_INT2_HANDLER)
    {
        Global_INT2_HANDLER();
        EXT_INT2_CLEARFLAG();
    }     
}

void INTRB4_HIGH_ISR()
{
    if(Global_INTRB4_HANDLER_HIGH)
    {
        Global_INTRB4_HANDLER_HIGH();
        EXT_INT_ONCHANGE_CLEARFLAG();
    }
}
void INTRB4_LOW_ISR()
{
    if(Global_INTRB4_HANDLER_LOW)
    {
        Global_INTRB4_HANDLER_LOW();
        EXT_INT_ONCHANGE_CLEARFLAG();
    }
}
void INTRB5_HIGH_ISR()
{
    if(Global_INTRB5_HANDLER_HIGH)
    {
        Global_INTRB5_HANDLER_HIGH();
        EXT_INT_ONCHANGE_CLEARFLAG();
    }
}
void INTRB5_LOW_ISR()
{
    if(Global_INTRB5_HANDLER_LOW)
    {
        Global_INTRB5_HANDLER_LOW();
        EXT_INT_ONCHANGE_CLEARFLAG();
    }
}
void INTRB6_HIGH_ISR()
{
    if(Global_INTRB6_HANDLER_HIGH)
    {
        Global_INTRB6_HANDLER_HIGH();
        EXT_INT_ONCHANGE_CLEARFLAG();
    }
}
void INTRB6_LOW_ISR()
{
    if(Global_INTRB6_HANDLER_LOW)
    {
        Global_INTRB6_HANDLER_LOW();
        EXT_INT_ONCHANGE_CLEARFLAG();
    }
}
void INTRB7_HIGH_ISR()
{
    if(Global_INTRB7_HANDLER_HIGH)
    {
        Global_INTRB7_HANDLER_HIGH();
        EXT_INT_ONCHANGE_CLEARFLAG();
    }
}
void INTRB7_LOW_ISR()
{
    if(Global_INTRB7_HANDLER_LOW)
    {
        Global_INTRB7_HANDLER_LOW();
        EXT_INT_ONCHANGE_CLEARFLAG();
    }
}


#endif
#endif