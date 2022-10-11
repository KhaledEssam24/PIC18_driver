#include "gpio.h"

volatile uint8 *tris_arr[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8 *lat_arr[]  = {&LATA,&LATB,&LATC,&LATD,&LATE};
volatile uint8 *port_arr[] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

/**
 * 
 * @param pin_config
 * @return 
 */
Std_ReturnType gpio_pin_initialize(const pin_config_t *pin_config)
{
    Std_ReturnType ret=E_OK;
    if ( (pin_config) && (pin_config->pin <= PIN7) && (pin_config->port <= PORTE_INDEX) )
    {
        switch (pin_config->dir)
        {
            case OUTPUT :
                CLEAR_BIT (*tris_arr[pin_config->port],pin_config->pin);
                gpio_pin_write_logic (pin_config ,pin_config->logic);
                break;
            case INPUT :
                SET_BIT (*tris_arr[pin_config->port],pin_config->pin); 
                break;
            default :  
                ret=E_NOT_OK;   
        }
    }
    else
    {
         ret=E_NOT_OK;
    }
    return ret;
}

/**
 * 
 * @param pin_config
 * @param dir
 * @return 
 */
Std_ReturnType gpio_pin_get_direction(const pin_config_t * pin_config , pin_direction_t* dir)
{
    Std_ReturnType ret=E_OK;
    if ( (pin_config) && (dir) && (pin_config->pin <= PIN7) && (pin_config->port <= PORTE_INDEX) )
    {
        *dir=READ_BIT(*tris_arr[pin_config->port],pin_config->pin);
    }
    else
    {
        ret=E_NOT_OK;
    }
    return ret;    
}

/**
 * 
 * @param pin_config
 * @param logic
 * @return 
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t * pin_config ,pin_logic_t logic)
{
    Std_ReturnType ret=E_OK;
    if ( (pin_config) && (pin_config->pin <= PIN7) && (pin_config->port <= PORTE_INDEX) )
    {
        switch (logic)
        {
            case HIGH :
                SET_BIT( *lat_arr[pin_config->port] , pin_config->pin);
                break;
            case LOW :
                CLEAR_BIT( *lat_arr[pin_config->port] , pin_config->pin);
                break;
            default : 
                ret=E_NOT_OK;                
        }         
    }
    else
    {
         ret=E_NOT_OK;
    }
    return ret;    
}

/**
 * 
 * @param pin_config
 * @param logic
 * @return 
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t * pin_config ,pin_logic_t* logic)
{
    Std_ReturnType ret = E_OK;
    if ( (pin_config) && (logic) && (pin_config->pin <= PIN7) && (pin_config->port <= PORTE_INDEX) )
    {
       *logic = READ_BIT(*port_arr[pin_config->port] , pin_config->pin);
    }
    else
    {
        ret=E_NOT_OK;
    }
    return ret;    
}

/**
 * 
 * @param pin_config
 * @return 
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * pin_config)
{
    Std_ReturnType ret=E_OK;
    if ( (pin_config) && (pin_config->pin <= PIN7) && (pin_config->port <= PORTE_INDEX) )
    {
        TOGGLE_BIT(*lat_arr[pin_config->port] , pin_config->pin);
    }
    else
    {
        ret=E_NOT_OK;
    }
    return ret;    
}

/**
 * 
 * @param port
 * @param dir
 * @return 
 */
Std_ReturnType gpio_port_direction_initialize(const port_index_t port ,uint8 dir )
{
    Std_ReturnType ret = E_OK;
    if ( (port <= PORTE_INDEX) ) 
    {
        *tris_arr[port]= dir ;
        *lat_arr[port] = 0x00 ;
    }
    else
    {
        ret = E_NOT_OK;
    }
            
    return ret;
}

/**
 * 
 * @param port
 * @param dir
 * @return 
 */
Std_ReturnType gpio_port_get_direction(const port_index_t port , uint8* dir)
{
    Std_ReturnType ret = E_OK;
    if ( (port <= PORTE_INDEX) && dir) 
    {
        *dir = *tris_arr[port];
    }
    else
    {
        ret = E_NOT_OK;
    }
            
    return ret;    
}

/**
 * 
 * @param port
 * @param logic
 * @return 
 */
Std_ReturnType gpio_port_write_logic(const port_index_t port ,uint8 logic)
{
    Std_ReturnType ret = E_OK;
    if ( (port <= PORTE_INDEX) ) 
    {
        *lat_arr[port]= logic ;
    }
    else
    {
        ret = E_NOT_OK;
    }
            
    return ret;
}

/**
 * 
 * @param port
 * @param logic
 * @return 
 */
Std_ReturnType gpio_port_read_logic(const port_index_t port  ,uint8* logic)
{
    Std_ReturnType ret = E_OK;
    if ( (port <= PORTE_INDEX) && logic ) 
    {
        *logic = *port_arr[port];
    }
    else
    {
        ret = E_NOT_OK;
    }
            
    return ret;
}

/**
 * 
 * @param port
 * @return 
 */
Std_ReturnType gpio_port_toggle_logic(const port_index_t port )
{
    Std_ReturnType ret = E_OK;
    if ( (port <= PORTE_INDEX) ) 
    {
        *lat_arr[port] ^= 0xFF ;
    }
    else
    {
        ret = E_NOT_OK;
    }
            
    return ret;
}        
