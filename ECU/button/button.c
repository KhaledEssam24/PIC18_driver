#include "button.h"

/**
 * 
 * @param btn
 * @return 
 */
Std_ReturnType ecu_btn_initialize(const btn_t *btn)
{
    Std_ReturnType ret = E_OK;
    if (btn)
    {
        pin_config_t pin = 
        {
            .port = btn->port,
            .pin  = btn->pin,
            .dir  = INPUT,
            .logic= LOW
        };
        ret = gpio_pin_initialize(&pin);
    }
    else
    {
        ret = E_NOT_OK ;
    }
    return ret ;
}

/**
 * 
 * @param btn
 * @param status
 * @return 
 */
Std_ReturnType ecu_btn_status(const btn_t *btn ,btn_status* status)
{
    Std_ReturnType ret = E_OK;
    if (btn && status)
    {
        pin_config_t pin = 
        {
            .port = btn->port,
            .pin  = btn->pin,
            .dir  = INPUT,
            .logic= LOW
        };
        pin_logic_t logic ;
        ret = gpio_pin_read_logic(&pin , &logic);
        switch (btn->cfg)
        {
            case ACTIVE_HIGH :
                if (logic == HIGH)
                {
                    *status = BUTTON_PRESSED ;
                }
                else if (logic == LOW)
                {
                    *status = BUTTON_REALEASED ;
                }
                break;
            case ACTIVE_LOW :
                if (logic == HIGH)
                {
                    *status = BUTTON_REALEASED ;
                }
                else if (logic == LOW)
                {
                    *status = BUTTON_PRESSED ;
                } 
                break;
            default :
               ret = E_NOT_OK ; 
        }        
        
    }
    else
    {
        ret = E_NOT_OK ;
    }
    return ret ;
}        
