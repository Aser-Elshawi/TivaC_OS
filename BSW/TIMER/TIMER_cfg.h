/*******************************************************************************
 * Title                 :   Timer Module Configuration File
 * Module                :   TIMER_cfg
 * Filename              :   TIMER_cfg.h
 * Author                :   Mohamed Taha
 * Origin Date           :   Apr 17, 2022
 * Version               :   1.0.0
 * Compiler              :   Texas Instruments v20.2.6 LTS
 * Target                :   TM4C123GH6PM
 * Notes                 :   None
 *******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
 *
 *    Date         Software Version    Initials     Description
 *  Apr 17, 2022        1.0.0             MT       Module Created.
 *
 *******************************************************************************/

#ifndef BSW_TIMER_TIMER_CFG_H_
#define BSW_TIMER_TIMER_CFG_H_

/******************************************************************************
 * Preprocessor Macros (Definitions and static Configurations)
 *******************************************************************************/
#define TIMER_MODULES_USED_NUM 6U
/******************************************************************************
* Macros (Functions)
*******************************************************************************/

/******************************************************************************
 * User-defined Types
 *******************************************************************************/
/*
 * Description: Post build settings for the timer
 * */
TIMER_Settings_t Settings[TIMER_MODULES_USED_NUM] =
{
 {.TIMER_Module_Number = TIMER_Module_TIMER0 , .TIMER_Module_Config = TIMER_Config_Full_Width_Periodic_Down , .TIMER_Int_Enable = TIMER_Int_Enable_ON , .TIMER_Int_Flags = TIMER_Int_Flags_Timeout},
 {.TIMER_Module_Number = TIMER_Module_TIMER1 , .TIMER_Module_Config = TIMER_Config_Full_Width_One_Shot_Down , .TIMER_Int_Enable = TIMER_Int_Enable_ON , .TIMER_Int_Flags = TIMER_Int_Flags_Timeout},
 {.TIMER_Module_Number = TIMER_Module_TIMER2 , .TIMER_Module_Config = TIMER_Config_Full_Width_One_Shot_Down , .TIMER_Int_Enable = TIMER_Int_Enable_OFF , .TIMER_Int_Flags = TIMER_Int_Flags_NULL},
 {.TIMER_Module_Number = TIMER_Module_TIMER3 , .TIMER_Module_Config = TIMER_Config_Full_Width_One_Shot_Down , .TIMER_Int_Enable = TIMER_Int_Enable_OFF , .TIMER_Int_Flags = TIMER_Int_Flags_NULL},
 {.TIMER_Module_Number = TIMER_Module_TIMER4 , .TIMER_Module_Config = TIMER_Config_Full_Width_One_Shot_Down , .TIMER_Int_Enable = TIMER_Int_Enable_OFF , .TIMER_Int_Flags = TIMER_Int_Flags_NULL},
 {.TIMER_Module_Number = TIMER_Module_TIMER5 , .TIMER_Module_Config = TIMER_Config_Full_Width_One_Shot_Down , .TIMER_Int_Enable = TIMER_Int_Enable_OFF , .TIMER_Int_Flags = TIMER_Int_Flags_NULL}

};
/******************************************************************************
* Extern for Public Global Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#endif /* BSW_TIMER_TIMER_CFG_H_ */

/*** End of File **************************************************************/
