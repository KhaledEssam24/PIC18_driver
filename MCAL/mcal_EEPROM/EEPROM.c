#include "EEPROM.h"
#include "../proc/pic18f4620.h"
#include "../mcal_interrupt/mcal_config_interrupt.h"

/**
 * 
 * @param ADD
 * @param data
 * @return 
 */
Std_ReturnType EEPROM_Write_Byte (uint16 ADD,uint8 data)
{
    uint8 ret=E_OK;
    /*Get the status of interrupt */
    uint8 gloabal_interrupt_status = INTCONbits.GIE;
    uint8 periph_interrupt_status = INTCONbits.PEIE;
    /*select EEPROM and FLASH section*/
    DATA_EEPROM_FLASH_MEMORY_SELECT();
    /*EEPROM selection*/
    DATA_EEPROM_MEMORY_SELECT();
    /*Address Write*/
    EEADR  =  ADD     & 0xFF;
    EEADRH = (ADD>>8) & 0x03;
    /*Data Write Register*/
    EEDATA=data;
    /*allow write cycles to EEPROM*/
    ALLOWS_WRITE_CYCLES_TO_FLASH_EEPROM_MEMORY();
    /*Disable Interrupt Feature*/
    #if INTERRUPT_PRIORITY_FEATURE==ENABLE
    INTERRUPT_HPRIORITY_DISABLE();
    INTERRUPT_LPRIORITY_DISABLE();
    #else
    GLOBAL_INTERRUPT_DISABLE();
    PERIPHERIAL_INTERRUPT_DISABLE();
    #endif 
    /*Write the required sequence*/
    EECON2=0x55;
    EECON2=0xAA;
    /* Initiates a data EEPROM erase/write cycle*/
    INITIATE_EEPROM_ERASE_WRITE();
    /*waiting*/
    while(EECON1bits.WR);
    /*inhibits write cycles to EEPROM*/
    INHIBITS_WRITE_CYCLES_TO_FLASH_EEPROM_MEMORY();
    /*return the status of interrupt */
    INTCONbits.GIE  = gloabal_interrupt_status ;
    INTCONbits.PEIE = periph_interrupt_status;    
}

Std_ReturnType EEPROM_Read_Byte (uint16 ADD,uint8* data)
{
    Std_ReturnType ret =E_NOT_OK;
    if (data)
    {
        /*select EEPROM and FLASH section*/
        DATA_EEPROM_FLASH_MEMORY_SELECT();
        /*EEPROM selection*/
        DATA_EEPROM_MEMORY_SELECT();
        /*Address Read*/
        EEADR  =  ADD     & 0xFF;
        EEADRH = (ADD>>8) & 0x03;
        /* Initiates a data EEPROM read cycle*/
        INITIATE_EEPROM_ERASE_READ();
        /*waiting*/
        while(EECON1bits.RD);
        /*Data Read Register*/
        *data=EEDATA;
        ret =E_OK;
    }
    else
    {
        ret =E_NOT_OK;
    }
}

