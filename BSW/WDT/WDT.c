
/*******************************************************************************
 * Title                 :   WDT Initialization
 * Filename              :   WDT.c
 * Author                :   Mohamed Osama
 * Origin Date           :   10/5/2022
 * Version               :   1.0.0
 * Compiler              :   //ti-cgt-arm_20.2.5.LTS
 * Target                :   TM4C123GH6PM
 * Notes                 :   None
 *******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
 *
 *    Date    Software Version    Initials   Description
 *  XX/XX/XX    XXXXXXXXXXX         JWB      Module Created.
 *
 *******************************************************************************/

/*****************************************************************
 * Includes
 *******************************************************************************/

/* standard libraries */
#include <stdint.h>
#include <stdbool.h>


/* tivaWare libraries  */
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/watchdog.h"


/* local includes */
#include "WDT.h"

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
WDT_stateinfo_t *state;
/******************************************************************************
 * Function Definitions
 *******************************************************************************/
/******************************************************************************/



/*
 * Function : WD_init
 * \Description: function to initialize the watch dog peripheral according to the number of the watch dog timer
 *
 *
 *
 * \input  : watch dog number.
 *
 * \return : NONE.
 *
 *  function usage example: WD_init(uint32_t WD_NUM);
 *
 */

void WD_init(uint32_t WD_NUM){


    state->prev=WDT_status_uninitialized;
    //
    // Enable the Watchdog  peripheral
    //
    SysCtlPeripheralEnable(wdt_cfg[WD_NUM].WDT_peri);
    //
    // Wait for the Watchdog  module to be ready.
    //
    while(!SysCtlPeripheralReady(wdt_cfg[WD_NUM].WDT_peri))
            {


            }

    state->curr=WDT_status_Ok;
}


/*
 * Function :WDT_init
 * \Description: function to initialize the timer of the watch dog.
 *
 *
 *
 * \input  : watch dog number.
 *
 * \return : NONE.
 *
 *  function usage example: WDT_init(uint32_t WDT_NUM);
 *
 */

void WDT_init(uint32_t WD_NUM){

    if(state->curr==WDT_status_Ok){
    //
    // Enable the reset.
    //
    WatchdogResetEnable(wdt_cfg[WD_NUM].WDT_base);
    //
    // Enable the watchdog timer.
    //
    WatchdogEnable(wdt_cfg[WD_NUM].WDT_base);
    //
    // Wait for the reset to occur.
    //
    }

    else{
        state->curr=WDT_status_Failed;

    }


}

/*
 * Function :WDT_check_status
 * \Description: function to check the status of the watch dog timer.
 *
 *
 *
 * \input  : watch dog number.
 *
 * \return : NONE.
 *
 *  function usage example: WDT_check_status(uint32_t WDT_NUM);
 *
 */

WDT_status_t WDT_check_status(uint32_t WD_NUM){

    if(state->curr==WDT_status_Ok){
        //
        // Check to see if the registers are locked, and if so, unlock them.
        //
        if(WatchdogLockState(wdt_cfg[WD_NUM].WDT_base) == true)
        {
            WatchdogUnlock(wdt_cfg[WD_NUM].WDT_base);
        }
        //
        // Initialize the watch dog timer.
        //
        WatchdogReloadSet(wdt_cfg[WD_NUM].WDT_base, 0xFEEFEE);

        state->curr=WDT_status_Activated;
    }

    else{

        state->curr=WDT_status_Failed;
    }

    return (WDT_status_t)state->curr;

}


