/*
 * TASKS.c
 *
 *  Created on: Dec 16, 2021
 *      Author: asere
 */

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_gpio.h"
#include "OS/OS.h"
#include "SERVICES/STD_TYPES/STD_TYPES.h"
#include "SERVICES/DEBUG_PORT/DEBUG_PORT.h"
#include "BSW/UART/UART.h"
#include "BSW/GPIO/GPIO.h"
#include "BSW/TIMER/TIMER.h"
#include "BSW/TIMER_AL/TIMER.h"
#include "BSW/EEPROM/EEPROM.h"
#include "HAL/MOTOR_DRIVER/MOTOR_DRIVER.h"
#include "HAL/JETSON_DRIVER/JETSON_DRIVER.h"
#include "HAL/Thermal_Camera/TH_CAM.h"
#include "HAL/HOME_SENSOR/HOME_SENSOR.h"
#include "APP/PTZ_APP.h"
#include "HAL/DAY_LENS/DAY_LENS.h"
#include "HAL/DAY_LENS/DAY_LENS_FCBEX1020.h"
#include "HAL/ROTARY_ENCODER/ROTARY_ENCODER.h"
#include "HAL/AXIS_VIDEO_ENCODER/AXIS.h"
#include "HAL/PELCO_D_DRIVER/PELCO_D.h"
#include "HAL/DAY_LENS_YAMANO/YAMANO.h"
#include "TASKS/TASKS.h"




void TASKS_Init(){

    OS_Init();
    EEPROM_init();
    PTZ_init();
}

void TASKS_20ms()
{
    AXIS_cyclic20ms();
#ifdef YAMANO_DAY_LENS
    YAMANO_cyclic20ms();
#endif
}

void TASKS_5ms()
{

    PTZ_periods10ms();
    MOTOR_SM_cyclic10ms();
    JETSON_cyclic10ms();

#ifndef YAMANO_DAY_LENS
    DAY_SM_cyclic10ms();
#endif

}

void TASKS_1Sec()
{

}



void TASKS_1ms()
{
    // BSW handling
    UARTS_cyclic5ms(); // this function must not take any parameter
    // Service layer
    MOTOR_cyclic5ms();

#ifndef YAMANO_DAY_LENS
    DAY_LENS_cyclic10ms();
#endif

    TH_CAM_UART_5ms_cyclic();
    TH_CAM_State_Machine_5ms_cyclic();
    // Application
    HOME_SENSOR_cyclic_1ms();
}

void TASKS_100uS(){
    ENCODER_cyclicMs();
    MOTOR_checkLimit_cyclic100us();

}
void TASKS_3min(){
    //EEPROM_cyclic10min();
}
