/* 
 * File:   application.h
 * Author: El-Rehab
 *
 * Created on July 10, 2022, 12:32 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/*Section : includes */
#include "MCAL/device_config.h"
#include "builtins.h"
//#include "MCAL/Timer/Timer0.h"


/*Section macros declarations */



/*Section macros function declarations*/



/*Section Data type declaration */


 
/*Section function declaration */
void ADC_INT();
void TIM0_Handler();
void TIM1_Handler();
void TIM2_Handler();
void TIM3_Handler();
void CCP1_Handler();
void CCP2_Handler();
#endif	/* APPLICATION_H */

