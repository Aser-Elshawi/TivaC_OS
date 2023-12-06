/*******************************************************************************
 * Title                 :   ****MODULE_TITLE*****
 * Module                :   EEPROM
 * Filename              :   EEPROM.c
 * Author                :   Eslam
 * Origin Date           :   Apr 11, 2022
 * Version               :   1.0.0
 * Compiler              :   Texas Instruments v20.2.6 LTS
 * Target                :   TM4C123GH6PM
 * Notes                 :   None
 *******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
 *
 *    Date         Software Version    Initials     Description
 *  April 11, 2022        1.0.0           Eslam     Module Created.
 *
 *******************************************************************************/

/******************************************************************************
 * Include Standard C Header files
 *******************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
/******************************************************************************
 * Include Compiler Libraries Header files
 *******************************************************************************/
#include <driverlib/eeprom.h>
#include <driverlib/sysctl.h>

/******************************************************************************
 * Include any service file that will be used
 *******************************************************************************/
#include "SERVICES/STD_TYPES/STD_TYPES.h"
#include "HAL/Thermal_Camera/TH_CAM.h"
#include "HAL/ROTARY_ENCODER/ROTARY_ENCODER.h"
/******************************************************************************
 * Include Module.h file
 *******************************************************************************/
#include "EEPROM.h"
/******************************************************************************
 * Include Module_cfg.h file
 *******************************************************************************/

/******************************************************************************
 * Include Module_Private.h file
 *******************************************************************************/
#define EEPROM_PRIVATE_ENABLE /* Private header file guard */

#undef  EEPROM_PRIVATE_ENABLE /* Private header file guard */

/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

/******************************************************************************
 * Module Preprocessor Macros
 *******************************************************************************/

/******************************************************************************
 * Module Typedefs
 *******************************************************************************/

/******************************************************************************
 * Module Variable Definitions
 *******************************************************************************/

/************************************/
/* Public (Shared) Global Variables */
/************************************/
EEPROM_failureStatus_t EEPROM_failureStatus;
/*************************************/
/* Private (Static) Global Variables */
/*************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

/*****************************/
/* Public (Shared) Functions */
/*****************************/
/******************************************************************************
 * Function name : EEPROM_Init
 * Parameters (in): None
 * Parameters (in/out): None
 * Parameters (out): EEPROM_status_t
 * Return value: the status of the eeprom (success or fail)
 * Function description : init the EEPROM to be used
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  April 11, 2022        1.0.0          Eslam       Module Created.
 *
 * Notes : assertion will happen if the number of data to be saved 'EEPROM_data_num' in the EEPROM accessed its size(512)
 *******************************************************************************/

EEPROM_status_t EEPROM_init(void)
{
    assert(EEPROM_SIZE >= EEPROM_data_num);
    uint32_t ui32EEPROMInit;
    EEPROM_status_t error = EEPROM_status_success;

    /* Enable the EEPROM module.*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

    /* Wait for the EEPROM module to be ready.*/
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0));

    /* Wait for the EEPROM Initialization to complete */
    ui32EEPROMInit = EEPROMInit();

    /* Check if the EEPROM Initialization returned an error and inform the application*/
    if(ui32EEPROMInit != EEPROM_INIT_OK){
        error = EEPROM_status_initError;     //check for status 'the status are ORed together' 'the APP layer must check for the status code using EEPROM_status'
    }
    EEPROM_failureStatus.failureCode = (uint8_t)EEPROMStatusGet();
    return error;
}

/******************************************************************************
 * Function name : EEPROM_getModulesData
 * Parameters (in): EEPROM_data_t : the index of the data to be read from the module
 * Parameters (in/out): uint32_t ret_data : the value of the data
 * Parameters (out): None
 * Return value: None
 * Function description : read the data from the driver to be saved in the eeprom
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  April 11, 2022        1.0.0          Eslam       Module Created.
 *
 * Notes : EX: EEPROM_getModulesData(EEPROM_data_motorJogSpeed,data);
 *                     data will be the current value of the motor jogSpeed
 *******************************************************************************/

void EEPROM_getModulesData(EEPROM_data_t eepromData, uint32_t *ret_data){
    if(eepromData < EEPROM_data_EncoderNum){
        //call encoder getter
        ENCODER_GetEEPROM_Data(eepromData, ret_data);
    }else if(eepromData < EEPROM_data_thermalnum){
        //CALL thermal getter
        TH_CAM_GetEEPROM_Data(eepromData, ret_data);
    }else if(eepromData < EEPROM_data_motorNum){
        //call motor getter

    }else if(eepromData < EEPROM_data_dayNum){
        //call day getter
    }
}
/******************************************************************************
 * Function name : EEPROM_cyclic10m
 * Parameters (in): None
 * Parameters (in/out): None
 * Parameters (out): None
 * Return value: None
 * Function description : update PTZ essential data into EEPROM cyclically in 10 MIN cyclic task
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  April 11, 2022        1.0.0          Eslam       Module Created.
 *
 * Notes : None
 *******************************************************************************/

//power down sequence
void EEPROM_cyclic10min(void){
    /*
     * newValues = readValuesFromDevices();
     * oldValues = readFromEEPROM
     * for each value:
     *      if oldValue != newValue:
     *              updateValueInEEPROM()
     *
     * */
    uint16_t ctr;
    uint32_t newData;
    uint32_t oldData;
    for(ctr=0 ; ctr<EEPROM_data_num ; ctr++){
        if(ctr == EEPROM_data_EncoderNum || ctr == EEPROM_data_motorNum || ctr == EEPROM_data_dayNum || ctr == EEPROM_data_thermalnum)
            continue;
        EEPROM_getModulesData((EEPROM_data_t)ctr, &newData);
        EEPROM_read((EEPROM_data_t)ctr, &oldData);
        if(oldData != newData){
            EEPROM_write((EEPROM_data_t)ctr, newData);
        }
    }
}

/******************************************************************************
 * Function name : EEPROM_read
 * Parameters (in): EEPROM_data_t enum that holds the indexes of the data saved on the EEPROM
 * Parameters (in/out): ret_data pointer to data to be read from the EEPROM
 * Parameters (out): EEPROM_status_t
 * Return value: the status of the eeprom (success or fail)
 * Function description : read the data saved in EEPROM location associated with the var address
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  April 11, 2022        1.0.0          Eslam       Module Created.
 *
 * Notes : None
 *******************************************************************************/

EEPROM_status_t EEPROM_read(EEPROM_data_t var,uint32_t *ret_data)
{
    uint32_t address;


    address = eeprom_address(var);
    EEPROMRead(ret_data, address, 4);
    EEPROM_failureStatus.failureCode = (uint8_t)EEPROMStatusGet();

    if(EEPROM_failureStatus.failureCode == (uint8_t)0){
        return EEPROM_status_success;
    }else{
        return EEPROM_status_readError;    //check for status 'the status are ORed together' 'the APP layer must check for the status code using EEPROM_status'
    }
    //read EEPROM status
}

/******************************************************************************
 * Function name : EEPROM_write
 * Parameters (in): 1 - EEPROM_data_t var : enum that holds the indexes of the data saved on the EEPROM
 *                  2 - data : the data to be saved in the EEPROM
 * Parameters (in/out): None
 * Parameters (out): EEPROM_status_t
 * Return value: the status of the eeprom (success or fail)
 * Function description : write the data in EEPROM location associated with the var address
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  April 11, 2022        1.0.0          Eslam       Module Created.
 *
 * Notes : None
 *******************************************************************************/

EEPROM_status_t EEPROM_write(EEPROM_data_t var,uint32_t data)
{
    uint32_t address;
    address = eeprom_address(var);
    EEPROM_failureStatus.failureCode = (uint8_t)EEPROMProgram(&data, address, 4);
    if(EEPROM_failureStatus.failureCode == (uint8_t)0){
        return EEPROM_status_success;
    }else{
        return EEPROM_status_writeError;    //check for status 'the status are ORed together' 'the APP layer must check for the status code using EEPROM_status'
    }
}

/******************************/
/* Private (Static) Functions */
/******************************/
/******************************************************************************
 * Function name : eeprom_address
+ * Parameters (in): EEPROM_data_t data
 * Parameters (in/out): None
 * Parameters (out): None
 * Return value: uint32_t EEPROM address for the given data to save it into or retrieve it from
 * Function description : map the data to EEPROM address location (this function is used for read or write the data from EEPROM)
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  Apr 11, 2022        1.0.0           Eslam       Module Created.
 *
 * Notes : None
 *******************************************************************************/

inline uint32_t eeprom_address(EEPROM_data_t data)
{
    return (uint32_t)(data*4);
}
/*************** END OF FUNCTIONS ***************************************************************************/
