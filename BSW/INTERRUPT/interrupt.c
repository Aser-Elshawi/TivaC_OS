
/*******************************************************************************
 * Title                 :   INTERRUPT Initialization
 * Filename              :   interrupt.c
 * Author                :   Mohamed Osama
 * Origin Date           :   16/5/2022
 * Version               :   1.0.0
 * Compiler              :   //ti-cgt-arm_20.2.5.LTS
 * Target                :   TM4C123GH6PM
 * Notes                 :   None
 *******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
 *
 *    Date    Software Version    Initials   Description
 *  XX/XX/XX    XXXXXXXXXXX                 Module Created.
 *
 *******************************************************************************/
// there are 15 system exceptions supported by cortex M processors and 240 interrupts

// EXCEPTION NUMBER ONE IS RESET

// only 9 implemented system exceptions

// exception number 16 is interrupt 1 (IRQ1)
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


/* local includes */
#include "interrupt.h"

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

/******************************************************************************
 * Function Definitions
 *******************************************************************************/
/******************************************************************************/

/*
 * disable interrupts
 *
 * enabling internal pull up resistor according to gpio
 *
 *enable external interrupt pin INt1
 *
 *
 *configure port c pins output
 *
 *difference between exception and interrupts is: exception is happened by cpu only through interrupt but interrupt can be external one
 *
 *
 *non_maskable interrupts have the highest priority after reset like clock security system
 *
 *
 *addresses in arm cortex m4 is 32 bit
 *
 *vector table is considered to be an array and we can make it relocation
 *
 *
 *jump address of any interrupt start with 1 bit to make cpu know that or indicate it's thumb state execution
 *
 *
 *vector table in startup file, address zero have the stack pointer
 *
 *
 *cmsis is considered to be header files
 *
 *
 *
 *set_pending to make interrupt wait it's trigger when cpu make it in active state
 *
 *
 *get pending  to know any interrupt if it's in pending state or not
 *
 *active bit register to know if there is any active exception or not
 *
 *hard fault and reset and non_maskable interrupts theses interrupts
 *
 *
 *priority level register
 *
 *
 *0 to 240 , 0 is the high priority
 *
 *
 *sub priority are used when there is two preempt priority and have same priority happened at the same time then  processor will choose
 *
 *the one that have sub_priority less
 *
 *
 *
 *interrupt priority registers, every register can change the priority of four interrupts
 *
 *
 *
 *in case of exception we use irqn but in case of interrupt we use interrupt priority register
 *
 *
 *functions of encode and decode priority in nvic
 *
 *
 *encode priority function gives you the value that will be in the priority register
 *
 *decode priority function i use to know the ppreempt_priority and psub_priority
 *
 *
 *
 *software trigger interrupt register privillage and unprivillage?
 *
 *
 *system control block contains some registers that commonly used in the interrupts.
 *
 *
 *vector table offset register when we want to make reallocation
 *
 *
 *register to specify group priority: application interrupt and reset control register (AIRCR) that have vector key must be changed
 *
 *and i can make system reset to the microcontroller
 *
 *
 *register that for exception priority(system handler priority registers)
 *
 *
 *another register to make control for exception and read fault state -> system handler control and state register (SCB->SHCSR)
 *
 *
 *primask: mask and unmasking for interrupts
 *
 *
 *
 *FAULTMASK: mask and unmask for interrupts and fault exception, it's cleared automatically upon exiting the exception handler
 *
 *
 *BASEPRI: to configure the low priority to make mask in the
 *
 *
 *work flow:
 *
 *
 *set up the priority group setting
 *
 *set up the priority level of the interrupt
 *
 *enable the interrupt at the NVIC and at the peripheral
 *
 *configure interrupts at MCU peripheral
 *
 *interrupt shall be triggered by peripheral or from the software
 *
 *
 *primask prevent all interrupts except the reset, hard fault and non_maskable interrupts
 *
 *
 *
 *
 *
 *
 * */


/*
 * Function : WD_init
 * \Description: function to initialize the watch dog peripheral according to the number of the watch dog timer
 *
 *
 * \input  : watch dog number.
 *
 * \return : NONE.
 *
 *  function usage example: WD_init(uint32_t WD_NUM);
 *
 */



