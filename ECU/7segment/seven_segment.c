#include "seven_segment.h"

Std_ReturnType seven_segment_initialize(const seven_segment_t* pins)
{
    Std_ReturnType ret = E_OK;
    if (pins)
    {
        gpio_pin_initialize(&(pins->pins[0]));
        gpio_pin_initialize(&(pins->pins[1]));
        gpio_pin_initialize(&(pins->pins[2]));
        gpio_pin_initialize(&(pins->pins[3]));     
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret ;
}
Std_ReturnType seven_segment_write_num(const seven_segment_t* pins ,uint8 num)
{
    Std_ReturnType ret = E_OK;
    if (pins && num <10)
    {
        gpio_pin_write_logic(&(pins->pins[0]) , (num>>0) & (0x01) );
        gpio_pin_write_logic(&(pins->pins[1]) , (num>>1) & (0x01) );
        gpio_pin_write_logic(&(pins->pins[2]) , (num>>2) & (0x01) );
        gpio_pin_write_logic(&(pins->pins[3]) , (num>>3) & (0x01) );
    } 
    else
    {
        ret = E_NOT_OK;
    }
    return ret ;
}