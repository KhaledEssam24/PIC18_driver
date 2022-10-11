/* 
 * File:   std_types.h
 * Author: El-Rehab
 *
 * Created on July 10, 2022, 12:06 AM
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H

/*Section : includes */
#include "std_libraries.h"
#include "compilier.h"
#include "device_config.h"

/*Section Data type declaration */
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned long      uint32;
typedef signed char        sint8;
typedef signed short       sint16;
typedef signed long        sint32;

typedef uint8 Std_ReturnType; 

/*Section macros declarations */
#define STD_ON     0x01
#define STD_OFF    0x00

#define STD_ACTIVE 0x01
#define STD_IDLE   0x00

#define STD_HIGH   0x01
#define STD_LOW    0x00

#define E_OK       (Std_ReturnType)0x01
#define E_NOT_OK   (Std_ReturnType)0x00

/*Section macros function declarations*/
 
/*Section function declaration */


#endif	/* STD_TYPES_H */

