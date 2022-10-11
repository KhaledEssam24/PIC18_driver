#include "led.h"

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_initialize (const led_t* led)
{
    Std_ReturnType ret = E_OK;
    if ((led))
    {
        pin_config_t pin =
        {
            .port = led->port,
            .pin =led->pin,
            .logic = led->led_status,
            .dir = OUTPUT
        };
        gpio_pin_initialize(&pin);
    }
    else
    {
        ret = E_NOT_OK ;
    }
    return ret;
}

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_turn_on (const led_t* led)
{
    Std_ReturnType ret = E_OK;
    if (led)
    {
        pin_config_t pin =
        {
            .port = led->port,
            .pin =led->pin,
            .logic = led->led_status,
            .dir = OUTPUT
        };
        gpio_pin_write_logic(&pin , HIGH);
    }
    else
    {
        ret = E_NOT_OK ;
    }
    return ret;
}

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_turn_off (const led_t* led)
{
    Std_ReturnType ret = E_OK;
    if (led)
    {
        pin_config_t pin =
        {
            .port = led->port,
            .pin =led->pin,
            .logic = led->led_status,
            .dir = OUTPUT
        };
        gpio_pin_write_logic(&pin , LOW);
    }
    else
    {
        ret = E_NOT_OK ;
    }
    return ret;
}

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_turn_toggle (const led_t* led)
{
    Std_ReturnType ret = E_OK;
    if (led)
    {
        pin_config_t pin =
        {
            .port = led->port,
            .pin =led->pin,
            .logic = led->led_status,
            .dir = OUTPUT
        };
        gpio_pin_toggle_logic(&pin);
    }
    else
    {
        ret = E_NOT_OK ;
    }
    return ret;
}        