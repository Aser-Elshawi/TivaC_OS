/*******************************************************************************
 * Title                 :   Timer Module Header File
 * Module                :   TIMER
 * Filename              :   TIMER.h
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

#ifndef BSW_TIMER_TIMER_H_
#define BSW_TIMER_TIMER_H_

/******************************************************************************
 * Preprocessor Macros (Definitions and static Configurations)
 *******************************************************************************/

/******************************************************************************
* Macros (Functions)
*******************************************************************************/

/******************************************************************************
 * User-defined Types
 *******************************************************************************/
/*
 * Description: Enum to hold the different Timer Modules
 * */
typedef enum TIMER_Module_e
{
    TIMER_Module_TIMER0,
    TIMER_Module_TIMER1,
    TIMER_Module_TIMER2,
    TIMER_Module_TIMER3,
    TIMER_Module_TIMER4,
    TIMER_Module_TIMER5,
    TIMER_Module_NUM
}TIMER_Module_t;

/*
 * Description: Enum to hold the different Timer Configurations
 * */
typedef enum TIMER_Config_e
{
    /* Full Width */
    TIMER_Config_Full_Width_One_Shot_Down,
    TIMER_Config_Full_Width_Periodic_Down,
    TIMER_Config_NUM
}TIMER_Config_t;

/*
 * Description: Enum to hold the different Timer Interrupt flags
 * */
typedef enum TIMER_Int_Flags_e
{
    /* Timer */
    TIMER_Int_Flags_NULL,
    TIMER_Int_Flags_Timeout,
    TIMER_Int_Flags_Match,
    TIMER_Int_Flags_NUM

}TIMER_Int_Flags_t;

/*
 * Description: Initial Load value in the timer
 * */
typedef uint32_t TIMER_Initial_t;

/*
 * Description: Matching Compare value in the timer
 *              In Milli-Seconds
 * */
typedef uint32_t TIMER_Load_t;

/*
 * Description: Interrupt Enable for the timer module
 * */
typedef enum TIMER_Int_Enable_e
{
    TIMER_Int_Enable_OFF,
    TIMER_Int_Enable_ON
}TIMER_Int_Enable_t;

/*
 * Description: Pointer to the function to be called when the timer interrupt occurs
 * */
typedef void (*TIMER_ISR_Handler_t)(void);

/*
 * Description: Structure to hold the different Timer Module Settings
 * */

typedef struct TIMER_Settings_s
{
    TIMER_Module_t          TIMER_Module_Number;
    TIMER_Config_t          TIMER_Module_Config;
    TIMER_Int_Enable_t      TIMER_Int_Enable;
    TIMER_Int_Flags_t       TIMER_Int_Flags;
}TIMER_Settings_t;


/******************************************************************************
* Extern for Public Global Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void TIMER_Init(TIMER_Module_t Module , TIMER_ISR_Handler_t Handler);
void TIMER_Start(TIMER_Module_t Module , TIMER_Load_t Time);
void TIMER_Stop(TIMER_Module_t Module);
void TIMER_Delay(TIMER_Module_t Module , TIMER_Load_t Delay_time);
void TIMER_GetCurrentTime(TIMER_Module_t Module , TIMER_Load_t *ret_Time);

#endif /* BSW_TIMER_TIMER_H_ */

/*** End of File **************************************************************/
