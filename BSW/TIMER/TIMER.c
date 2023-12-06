/*******************************************************************************
 * Title                 :   Timer Module Source File
 * Module                :   TIMER
 * Filename              :   TIMER.c
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

/******************************************************************************
 * Include Standard C Header files
 *******************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
/******************************************************************************
 * Include Compiler Libraries Header files
 *******************************************************************************/
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
/******************************************************************************
 * Include any service file that will be used
 *******************************************************************************/
#include "SERVICES/MACROS/MACROS.h"
/******************************************************************************
 * Include Module.h file
 *******************************************************************************/
#include "TIMER.h"
/******************************************************************************
 * Include Module_cfg.h file
 *******************************************************************************/
#include "TIMER_cfg.h"
/******************************************************************************
 * Include Module_Private.h file
 *******************************************************************************/
#define TIMER_PRIVATE_ENABLE /* Private header file guard */
#include "TIMER_private.h"
#undef  TIMER_PRIVATE_ENABLE /* Private header file guard */

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

/*************************************/
/* Private (Static) Global Variables */
/*************************************/
/* Global variables to hold the address of the call back function in the application */
static void (*callBackPtrTimer0)(void) = MACROS_NULL_PTR;
static void (*callBackPtrTimer1)(void) = MACROS_NULL_PTR;
static void (*callBackPtrTimer2)(void) = MACROS_NULL_PTR;
static void (*callBackPtrTimer3)(void) = MACROS_NULL_PTR;
static void (*callBackPtrTimer4)(void) = MACROS_NULL_PTR;
static void (*callBackPtrTimer5)(void) = MACROS_NULL_PTR;

/* Array of Pointers to Pointer to function that will hold the Handler sent by the user */
void (**callBackPtr[6])(void) ={&callBackPtrTimer0 , &callBackPtrTimer1 , &callBackPtrTimer2 , &callBackPtrTimer3 , &callBackPtrTimer4 , &callBackPtrTimer5};

/* Array to pointer to function to hold the Timer ISR */
void (*timer_isr_ptr[6])(void) = {TIMER_0_ISR , TIMER_1_ISR , TIMER_2_ISR , TIMER_3_ISR , TIMER_4_ISR , TIMER_5_ISR};
/******************************************************************************
 * Function Definitions
 *******************************************************************************/

/*****************************/
/* Public (Shared) Functions */
/*****************************/

/******************************************************************************
 * Function name : TIMER_Init
 * Parameters (in):
 *                  1- Timer Module to be selected
 *                  2- Handler function if Interrupt is enabled , if not send a null pointer
 * Parameters (in/out): None
 * Parameters (out): None
 * Return value: None
 * Function description : Function Initializes the Timer Module
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  Apr 17, 2022        1.0.0             MT       Module Created.
 *
 * Notes : None
 *******************************************************************************/
void TIMER_Init(TIMER_Module_t Module , TIMER_ISR_Handler_t Handler)
{
    /* Enable the Timer Module peripheral */
    SysCtlPeripheralEnable(timer_get_module_sysctl[Module]);

    /* Wait for the Timer Module peripheral to be ready */
    while(!SysCtlPeripheralReady(timer_get_module_sysctl[Module]));

    /* Configure the Timer Module */
    TimerConfigure(timer_get_module_base_address[Module], timer_get_configurations[Settings[Module].TIMER_Module_Config]);

    /* Check if the Interrupt is enabled */
    if(Settings[Module].TIMER_Int_Enable == TIMER_Int_Enable_ON)
    {
        /* Register the Interrupt handler for the module */
        TimerIntRegister(timer_get_module_base_address[Module], TIMER_A, timer_isr_ptr[Module]);

        /* Enable Interrupt */
        if(Settings[Module].TIMER_Int_Flags != TIMER_Int_Flags_NULL)
        {
            IntEnable(timer_get_timer_int[Module]);
        }

        /* Enable the Module Interrupt source */
        TimerIntEnable(timer_get_module_base_address[Module], timer_get_interrupt_sources[Settings[Module].TIMER_Int_Flags]);

        /* Assign the handler */
        *callBackPtr[Module] = Handler;
    }

    /* Enable timer to stop while debugging */
    TimerControlStall(timer_get_module_base_address[Module], TIMER_BOTH, true);
}

/******************************************************************************
 * Function name : TIMER_Start
 * Parameters (in):
 *                  1- Timer Module to be selected
 *                  2- Match time in Milli-Second
 * Parameters (in/out): None
 * Parameters (out): None
 * Return value: None
 * Function description : This function start the timer module with selected Match time
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  Apr 26, 2022        1.0.0             MT       Module Created.
 *
 * Notes : None
 *******************************************************************************/
void TIMER_Start(TIMER_Module_t Module , TIMER_Load_t Time)
{
    /* Variable to hold the ticks */
    uint32_t number_of_matching_ticks = 0;

    /* Get the number of ticks needed */
    number_of_matching_ticks = (((float)Time/1000) * SysCtlClockGet());

    /* Load timer with value */
    TimerLoadSet(timer_get_module_base_address[Module], TIMER_A, number_of_matching_ticks);

    /* Enable the timer */
    TimerEnable(timer_get_module_base_address[Module], TIMER_A);
}

/******************************************************************************
 * Function name : TIMER_Stop
 * Parameters (in): Timer Module to be selected
 * Parameters (in/out): None
 * Parameters (out): None
 * Return value: None
 * Function description : This function stop the timer module
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  Apr 26, 2022        1.0.0             MT       Module Created.
 *
 * Notes : None
 *******************************************************************************/
void TIMER_Stop(TIMER_Module_t Module)
{
    /* Disable the timer */
    TimerDisable(timer_get_module_base_address[Module], TIMER_A);
}

/******************************************************************************
 * Function name : TIMER_Delay
 * Parameters (in):
 *                  1- Timer Module to be selected
 *                  2- Delay time in Milli-Second
 * Parameters (in/out): None
 * Parameters (out): None
 * Return value: None
 * Function description : Function that can be as a Delay using one shot timer
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  Apr 27, 2022        1.0.0             MT       Module Created.
 *
 * Notes : This function is a blocking function
 *******************************************************************************/
void TIMER_Delay(TIMER_Module_t Module , TIMER_Load_t Delay_time)
{
    /* Variable to hold the interrupt Status */
    uint32_t IntStatus = 0;

    /* Variable to hold the ticks */
    uint32_t number_of_matching_ticks = 0;

    /* Get the number of ticks needed */
    number_of_matching_ticks = (((float)Delay_time/1000) * SysCtlClockGet());

    /* Load timer with value */
    TimerLoadSet(timer_get_module_base_address[Module], TIMER_A, number_of_matching_ticks);

    /* Enable the timer */
    TimerEnable(timer_get_module_base_address[Module], TIMER_A);

    /* Get the Interrupt status for the module */
    IntStatus = TimerIntStatus(timer_get_module_base_address[Module], false);

    /* Loop on the Interrupt status till the timer timeout flag is set */
    while(!(IntStatus & timer_get_interrupt_sources[Module]))
    {
        /* Update the interrupt status */
        IntStatus = TimerIntStatus(timer_get_module_base_address[Module], false);
    }

    /* Clear the Interrupt source */
    TimerIntClear(timer_get_module_base_address[Module], IntStatus);
}

/******************************************************************************
 * Function name : TIMER_GetCurrentTime
 * Parameters (in): Timer Module to be selected
 * Parameters (in/out): Returned current time
 * Parameters (out): None
 * Return value: None
 * Function description : Function to get the current time in Milli second
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  Apr 27, 2022        1.0.0             MT       Module Created.
 *
 * Notes : None
 *******************************************************************************/
void TIMER_GetCurrentTime(TIMER_Module_t Module , TIMER_Load_t *ret_Time)
{
    /* Variable to hold the current tick */
    uint32_t cur_tick = 0;

    /* Get the current register value */
    cur_tick = TimerValueGet(timer_get_module_base_address[Module], TIMER_A);

    /* Get current time from number of ticks */
    cur_tick = (float)cur_tick/((float)SysCtlClockGet()/1000);

    /* Return the current time */
    *ret_Time = (cur_tick);
}
/******************************/
/* Private (Static) Functions */
/******************************/

/******************************************************************************
 * Function name : timer_handle_ISR
 * Parameters (in): Timer Module
 * Parameters (in/out): None
 * Parameters (out): None
 * Return value: None
 * Function description : This function calls the callback function for the specified Timer
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  Apr 27, 2022        1.0.0             MT       Module Created.
 *
 * Notes : None
 *******************************************************************************/
static void timer_handle_ISR(TIMER_Module_t Module)
{
    /* Variable to hold the interrupt Status */
    uint32_t IntStatus = 0;

    /* Get the Interrupt source */
    IntStatus = TimerIntStatus(timer_get_module_base_address[Module], true);

    /* Clear the Interrupt source */
    TimerIntClear(timer_get_module_base_address[Module], IntStatus);  // Clear the timer interrupt

    /* Check first if the call back function is present */
    if(*callBackPtr[Module] != MACROS_NULL_PTR)
    {
        /* Call the Call Back function in the application */
        (*callBackPtr[Module])();
    }
}

/*----------------------- Interrupt Service Routines -----------------------*/
void TIMER_0_ISR(void)
{
    /* Call the timer handler function that will call the timer callback function */
    timer_handle_ISR(TIMER_Module_TIMER0);
}

void TIMER_1_ISR(void)
{
    /* Call the timer handler function that will call the timer callback function */
    timer_handle_ISR(TIMER_Module_TIMER1);
}

void TIMER_2_ISR(void)
{
    /* Call the timer handler function that will call the timer callback function */
    timer_handle_ISR(TIMER_Module_TIMER2);
}

void TIMER_3_ISR(void)
{
    /* Call the timer handler function that will call the timer callback function */
    timer_handle_ISR(TIMER_Module_TIMER3);
}

void TIMER_4_ISR(void)
{
    /* Call the timer handler function that will call the timer callback function */
    timer_handle_ISR(TIMER_Module_TIMER4);
}

void TIMER_5_ISR(void)
{
    /* Call the timer handler function that will call the timer callback function */
    timer_handle_ISR(TIMER_Module_TIMER5);
}

/*************** END OF FUNCTIONS ***************************************************************************/
