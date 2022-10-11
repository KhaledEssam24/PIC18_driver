/* 
 * File:   led.h
 * Author: El-Rehab
 *
 * Created on July 10, 2022, 12:28 AM
 */

#ifndef LED_H
#define	LED_H

/*Section : includes */
#include "../../MCAL/gpio/gpio.h"


/*Section macros declarations */



/*Section macros function declarations*/



/*Section Data type declaration */
typedef enum
{
    LED_OFF,
    LED_ON,
}led_status_t;

typedef struct
{
    uint8 port       : 3;
    uint8 pin        : 3;
    uint8 led_status : 1;
    uint8 reserved   : 1;
}led_t;

 
/*Section function declaration */
Std_ReturnType led_initialize (const led_t * led);
Std_ReturnType led_turn_on (const led_t * led);
Std_ReturnType led_turn_off (const led_t * led);
Std_ReturnType led_turn_toggle (const led_t * led);

#endif	/* LED_H */

