
/*
 * TIMER.c
 *
 *  Created on: Jan 2, 2022
 *      Author: asere
 */
#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include <BSW/TIMER_AL/TIMER.h>

time_t TIMER_runtime[TIMER_MAX];
time_t TIMER_calltime[TIMER_MAX];
void TIMER_init(void){
    int task;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC_UP);
    //stall the timer on debugging
    TimerControlStall (TIMER0_BASE, TIMER_A, true);
    for(task = 0; task < TIMER_MAX; ++task ){
           TIMER_runtime[task].min = UINT32_MAX;
           TIMER_calltime[task].min = UINT32_MAX;
       }
    TimerEnable(TIMER0_BASE, TIMER_A);

}

void TIMER_startMeasurement(enum timer_e timer){
    uint32_t timeNow = TimerValueGet(TIMER0_BASE,
                                     TIMER_A);
    TIMER_runtime[timer].start = timeNow/80;
    timeNow /= 80000;
    // measure the time between two starts
    if(TIMER_calltime[timer].start < timeNow)
        TIMER_calltime[timer].current = timeNow-TIMER_calltime[timer].start;
    else
        TIMER_calltime[timer].current = ((UINT32_MAX/80000) - TIMER_calltime[timer].start) + timeNow;
    if(TIMER_calltime[timer].current < TIMER_calltime[timer].min)
        TIMER_calltime[timer].min = TIMER_calltime[timer].current;
    if(TIMER_calltime[timer].current > TIMER_calltime[timer].max)
        TIMER_calltime[timer].max = TIMER_calltime[timer].current;
    TIMER_calltime[timer].start = timeNow;

}
void TIMER_stopMeasurement(enum timer_e timer){
    uint32_t timeNow = TimerValueGet(TIMER0_BASE,
                                     TIMER_A);
    timeNow /= 80;
    if(TIMER_runtime[timer].start < timeNow)
        TIMER_runtime[timer].current = timeNow - TIMER_runtime[timer].start;
    else
        TIMER_runtime[timer].current = ((UINT32_MAX/80) - TIMER_runtime[timer].start) + timeNow;
    if(TIMER_runtime[timer].current < TIMER_runtime[timer].min)
        TIMER_runtime[timer].min = TIMER_runtime[timer].current;
    if(TIMER_runtime[timer].current > TIMER_runtime[timer].max)
        TIMER_runtime[timer].max = TIMER_runtime[timer].current;
}
