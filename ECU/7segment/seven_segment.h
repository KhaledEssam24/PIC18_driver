/* 
 * File:   7segment.h
 * Author: El-Rehab
 *
 * Created on July 18, 2022, 8:30 PM
 */


/*Section : includes */
#include "../../MCAL/gpio/gpio.h"
/*Section macros declarations */



/*Section macros function declarations*/



/*Section Data type declaration */
typedef enum
{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE,        
}segment_status_t;

typedef struct
{
    pin_config_t pins[4];
    segment_status_t status ;  
}seven_segment_t;

 
/*Section function declaration */
Std_ReturnType seven_segment_initialize(const seven_segment_t* pins);
Std_ReturnType seven_segment_write_num(const seven_segment_t* pins ,uint8 num);
