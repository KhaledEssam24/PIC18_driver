/* 
 * File:   button.h
 * Author: El-Rehab
 *
 * Created on July 13, 2022, 2:44 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

/*Section : includes */
#include "../../MCAL/gpio/gpio.h"
/*Section Data type declaration */
typedef enum 
{
    ACTIVE_HIGH,
    ACTIVE_LOW
}btn_cfg_t;

typedef enum 
{
    BUTTON_PRESSED,
    BUTTON_REALEASED
}btn_status;

typedef struct
{
    uint8 port   : 3;
    uint8 pin    : 3;
    uint8 cfg    : 1;
}btn_t;

Std_ReturnType ecu_btn_initialize(const btn_t *btn);
Std_ReturnType ecu_btn_status(const btn_t *btn ,btn_status* status);

#endif	/* BUTTON_H */

