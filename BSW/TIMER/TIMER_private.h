/*******************************************************************************
 * Title                 :   Timer Module Private Header File
 * Module                :   TIMER_private
 * Filename              :   TIMER_private.h
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

#ifndef BSW_TIMER_TIMER_PRIVATE_H_
#define BSW_TIMER_TIMER_PRIVATE_H_
#ifdef TIMER_PRIVATE_ENABLE /* Private header file guard */

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
 * Description: Get Timer module base addresses
 * */
const uint32_t timer_get_module_base_address[TIMER_Module_NUM] =
{
     WTIMER0_BASE , // Timer0
     WTIMER1_BASE , // Timer1
     WTIMER2_BASE , // Timer2
     WTIMER3_BASE , // Timer3
     WTIMER4_BASE , // Timer4
     WTIMER5_BASE   // Timer5
};

/*
 * Description: Get Timer module base addresses
 * */
const uint32_t timer_get_module_sysctl[TIMER_Module_NUM] =
{
     SYSCTL_PERIPH_WTIMER0 , // Timer0
     SYSCTL_PERIPH_WTIMER1 , // Timer1
     SYSCTL_PERIPH_WTIMER2 , // Timer2
     SYSCTL_PERIPH_WTIMER3 , // Timer3
     SYSCTL_PERIPH_WTIMER4 , // Timer4
     SYSCTL_PERIPH_WTIMER5   // Timer5
};

/*
 * Description: Get Timer A module Interrupt flags
 * */
const uint32_t timer_get_interrupt_sources[TIMER_Int_Flags_NUM] =
{
     0x00,                // In case no Interrupt source is needed
     TIMER_TIMA_TIMEOUT , // TimerA time out interrupt
     TIMER_TIMA_MATCH     // TimerA match interrupt used in the Input Edge-Time Mode
};

/*
 * Description: Get Single Timer module Configurations
 * */
const uint32_t timer_get_configurations[TIMER_Config_NUM] =
{
     TIMER_CFG_ONE_SHOT         ,   // Full-width one-shot timer
     TIMER_CFG_PERIODIC             // Full-width periodic timer
};

/*
 * Description: Get Timer A Interrupt module Configurations
 * */
const uint32_t timer_get_timer_int[TIMER_Module_NUM] =
{
     INT_WTIMER0A    ,
     INT_WTIMER1A    ,
     INT_WTIMER2A    ,
     INT_WTIMER3A    ,
     INT_WTIMER4A    ,
     INT_WTIMER5A
};

/******************************************************************************
* Extern for Public Global Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void timer_handle_ISR(TIMER_Module_t Module);

void TIMER_0_ISR(void);
void TIMER_1_ISR(void);
void TIMER_2_ISR(void);
void TIMER_3_ISR(void);
void TIMER_4_ISR(void);
void TIMER_5_ISR(void);

#endif /* TIMER_PRIVATE_ENABLE */
#endif /* BSW_TIMER_TIMER_PRIVATE_H_ */

/*** End of File **************************************************************/
