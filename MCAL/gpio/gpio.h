/* 
 * File:   gpio.h
 * Author: El-Rehab
 *
 * Created on July 9, 2022, 11:54 PM
 */

#ifndef GPIO_H
#define	GPIO_H

/*Section : includes */
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"

/*Section macros declarations */
#define BIT_MASK   0x01

/*Section macros function declarations*/
#define HWREG8 (_X)  (*((volatile uint8 *)(_X)))  /*hardware register 8 bits*/

#define SET_BIT(REG,BIT_POSITION)      (REG |= (BIT_MASK<<BIT_POSITION))
#define CLEAR_BIT(REG,BIT_POSITION)    (REG &= ~(BIT_MASK<<BIT_POSITION))
#define TOGGLE_BIT(REG,BIT_POSITION)   (REG ^= (BIT_MASK<<BIT_POSITION))

#define READ_BIT(REG,BIT_POSITION)     ((REG>>BIT_POSITION)&BIT_MASK)

/*Section Data type declaration */
typedef enum 
{
    PORTA_INDEX,
    PORTB_INDEX,            
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}port_index_t;

typedef enum 
{
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
}pin_index_t;

typedef enum 
{
    LOW,
    HIGH
}pin_logic_t;
 
typedef enum 
{
    INPUT,
    OUTPUT
}pin_direction_t;

typedef struct 
{
    uint8  port  :3;
    uint8  pin   :3;
    uint8  logic :1;
    uint8  dir   :1;
}pin_config_t;

/*Section function declaration */
Std_ReturnType gpio_pin_initialize(const pin_config_t * pin_config);
Std_ReturnType gpio_pin_get_direction(const pin_config_t * pin_config , pin_direction_t* dir);
Std_ReturnType gpio_pin_write_logic(const pin_config_t * pin_config ,pin_logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t * pin_config ,pin_logic_t* logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * pin_config);

Std_ReturnType gpio_port_direction_initialize(const port_index_t port ,uint8 dir);
Std_ReturnType gpio_port_get_direction(const port_index_t port , uint8* dir);
Std_ReturnType gpio_port_write_logic(const port_index_t port ,uint8 logic);
Std_ReturnType gpio_port_read_logic(const port_index_t port  ,uint8* logic);
Std_ReturnType gpio_port_toggle_logic(const port_index_t port );

#endif	/* GPIO_H */

