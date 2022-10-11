/* 
 * File:   dc_motor.h
 * Author: El-Rehab
 *
 * Created on July 15, 2022, 10:16 PM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

/*Section includes */
#include "../../MCAL/gpio/gpio.h"
/*Section macros declarations */
#define MOTOR_PIN_1 0
#define MOTOR_PIN_2 1
/*Section macros function declarations*/

/*Section Data type declaration */
typedef struct 
{
    pin_config_t pins[2];
    
}motor_pins_t;

/*Section function declaration */
Std_ReturnType dc_motor_initialize    (const motor_pins_t* pins);
Std_ReturnType dc_motor_move_forward  (const motor_pins_t* pins);
Std_ReturnType dc_motor_move_backward (const motor_pins_t* pins);
Std_ReturnType dc_motor_stop          (const motor_pins_t* pins);



#endif	/* DC_MOTOR_H */

