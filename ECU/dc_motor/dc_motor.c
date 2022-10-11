#include "dc_motor.h"

/**
 * 
 * @param pins
 * @return 
 */
Std_ReturnType dc_motor_initialize(const motor_pins_t* pins)
{    
    Std_ReturnType ret = E_OK;
    if (pins)
    {
        gpio_pin_initialize(&(pins->pins[MOTOR_PIN_1]));
        gpio_pin_initialize(&(pins->pins[MOTOR_PIN_2]));
    }
    else
    {
        Std_ReturnType ret = E_NOT_OK;
    } 
    return ret ;   
}

/**
 * 
 * @param pin
 * @return 
 */
Std_ReturnType dc_motor_move_forward(const motor_pins_t* pins)
{    
    Std_ReturnType ret = E_OK;
    if (pins)
    {
        gpio_pin_write_logic(&(pins->pins[MOTOR_PIN_1]),HIGH);
        gpio_pin_write_logic(&(pins->pins[MOTOR_PIN_2]),LOW);
    }
    else
    {
        Std_ReturnType ret = E_NOT_OK;
    }    
    return ret ;
} 

/**
 * 
 * @param pin
 * @return 
 */
Std_ReturnType dc_motor_move_backward (const motor_pins_t* pins)
{    
    Std_ReturnType ret = E_OK;
    if (pins)
    {
        gpio_pin_write_logic(&(pins->pins[MOTOR_PIN_1]),LOW);
        gpio_pin_write_logic(&(pins->pins[MOTOR_PIN_2]),HIGH);
    }
    else
    {
        Std_ReturnType ret = E_NOT_OK;
    }    
    return ret ;
}

/**
 * 
 * @param pins
 * @return 
 */
Std_ReturnType dc_motor_stop      (const motor_pins_t* pins)
{    
    Std_ReturnType ret = E_OK;
    if (pins)
    {
        gpio_pin_write_logic(&(pins->pins[MOTOR_PIN_1]),HIGH);
        gpio_pin_write_logic(&(pins->pins[MOTOR_PIN_2]),HIGH);
    }
    else
    {
        Std_ReturnType ret = E_NOT_OK;
    }    
    return ret ;
}        
