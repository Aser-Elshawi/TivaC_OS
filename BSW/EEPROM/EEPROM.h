/*******************************************************************************
 * Title                 :   ****MODULE_TITLE*****
 * Module                :   EEPROM
 * Filename              :   EEPROM.h
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
 *  April 11, 2022         1.0.0          Eslam       Module Created.
 *
 *******************************************************************************/

#ifndef EEPROM_EEPROM_H_
#define EEPROM_EEPROM_H_

/******************************************************************************
 * Preprocessor Macros (Definitions and static Configurations)
 *******************************************************************************/
#define EEPROM_SIZE 512 /* can be using EEPROM  EEPROMSizeGet(void)/32*/
/******************************************************************************
 * Macros (Functions)
 *******************************************************************************/

/******************************************************************************
 * User-defined Types
 *
 *******************************************************************************/
/*
 * Description: Write Here the Description of your defined type
 * */
typedef enum EEPROM_status_e{
    EEPROM_status_initError,
    EEPROM_status_readError,
    EEPROM_status_writeError,
    EEPROM_status_success
}EEPROM_status_t;

typedef union EEPROM_failureStatus_u{
    struct{
        bool busyWriting : 1;           /* 'EEPROM_RC_WRBUSY'  This return code bit indicates that an attempt was made to read from the EEPROM while a write operation was in progress */
        bool writePermissionDenied : 1; /* 'EEPROM_RC_NOPERM'  This return code bit indicates that an attempt was made to write a value but the destination permissions disallow write operations */
        bool copying : 1;               /* 'EEPROM_RC_WKCOPY'  indicates the EEPROM is copying to or from the internal copy buffer to make room for a newly written value  */
        bool erasing : 1;               /* 'EEPROM_RC_WKERASE' indicates that the EEPROM is currently erasing the internal copy buffer */
        bool working : 1;               /* 'EEPROM_RC_WORKING' indicates that the EEPROM is currently working  <no write operations is allowed until this bit is cleared> */
    };
    uint8_t failureCode;
}EEPROM_failureStatus_t;

typedef enum EEPROM_data_e{



    /************************************* encoder data ************************************************************/
    EEPROM_data_EncoderPanAngle,
    EEPROM_data_EncoderTiltAngle,
    EEPROM_data_EncoderPanSign,
    EEPROM_data_EncoderTiltSign,
    /*
     * add additional encoder data here
     */
    EEPROM_data_EncoderNum,

    /************************************ thermal data *************************************************************/
    EEPROM_data_thermalNUC_Mode,
    EEPROM_data_thermalNUC_Time,
    EEPROM_data_thermalNUC_Temperature,
    EEPROM_data_thermalImage_Flip,
    EEPROM_data_thermalDigital_Zoom,
    EEPROM_data_thermalPseudo_Color,
    EEPROM_data_thermalDDE_Mode,
    EEPROM_data_thermalDDE_Level,
    EEPROM_data_thermalImage_Filter,
    EEPROM_data_thermalAGC_Mode,
    EEPROM_data_thermalAGC_Contrast,
    EEPROM_data_thermalAGC_Brightness,
    EEPROM_data_thermalZoom_Position,
    EEPROM_data_thermalFocus_Position,
    EEPROM_data_thermalCamera_Temperature,
    /*
     * add additional thermal data here
     */
    EEPROM_data_thermalnum,

    /********************************** motor data **********************/
    /*
     * add additional motor data here
     */
    EEPROM_data_motorNum,

    /************************************* day data *************************************************************/
    EEPROM_data_dayZoom,
    /*
     * add additional day data here
     */
    EEPROM_data_dayNum,

    /**************************************************************************************************************/

    EEPROM_data_num  /* must be less than  EEPROM_SIZE else an assertion will occur*/
}EEPROM_data_t;


/******************************************************************************
 * Extern for Public Global Variables
 *******************************************************************************/
extern EEPROM_failureStatus_t EEPROM_failureStatus;
/******************************************************************************
 * Function Prototypes
 *******************************************************************************/
EEPROM_status_t EEPROM_init(void);
EEPROM_status_t EEPROM_read(EEPROM_data_t var,uint32_t *ret_data);
EEPROM_status_t EEPROM_write(EEPROM_data_t var,uint32_t data);
void EEPROM_cyclic10min(void);
void EEPROM_getModulesData(EEPROM_data_t eepromData, uint32_t *ret_data);
inline uint32_t eeprom_address(EEPROM_data_t data);
EEPROM_status_t EEPROM_reset(void);

#endif /* EEPROM_EEPROM_H_ */

/*** End of File **************************************************************/
