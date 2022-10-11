/* 
 * File:   EEPROM.h
 * Author: El-Rehab
 *
 * Created on August 29, 2022, 11:21 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

/*Section : includes */
#include "../mcal_std_types.h"
/*Section macros declarations */


/*Section macros function declarations*/
#define DATA_EEPROM_FLASH_MEMORY_SELECT() (EECON1bits.CFGS=0)
#define DATA_CONFIG_SELECT()              (EECON1bits.CFGS=1)

#define DATA_EEPROM_MEMORY_SELECT()       (EECON1bits.EEPGD=0)
#define DATA_FLASH_MEMORY_SELECT()        (EECON1bits.EEPGD=1)

#define  ALLOWS_WRITE_CYCLES_TO_FLASH_EEPROM_MEMORY()    (EECON1bits.WREN=1)
#define  INHIBITS_WRITE_CYCLES_TO_FLASH_EEPROM_MEMORY()  (EECON1bits.WREN=0)

#define INITIATE_EEPROM_ERASE_WRITE()  (EECON1bits.WR=1)
#define INITIATE_EEPROM_ERASE_READ()  (EECON1bits.RD=1)
/*Section Data type declaration */


 
/*Section function declaration */
Std_ReturnType EEPROM_Write_Byte (uint16 ADD,uint8 data);
Std_ReturnType EEPROM_Read_Byte (uint16 ADD,uint8* data);

#endif	/* EEPROM_H */

