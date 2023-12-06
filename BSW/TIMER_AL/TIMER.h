/*
 * TIMER.h
 *
 *  Created on: Jan 2, 2022
 *      Author: asere
 */

#ifndef BSW_TIMER_AL_TIMER_H_
#define BSW_TIMER_TIMER_H_

typedef struct time_S{
    uint32_t start;
    uint32_t current;
    uint32_t max;
    uint32_t min;
    uint32_t avg;
}time_t;

enum timer_e{
    TASK_5ms,
    TASK1_CALLTIME,
    TASK2,
    TIMER_MAX
};


void TIMER_init(void);
void TIMER_startMeasurement(enum timer_e timer);
void TIMER_stopMeasurement(enum timer_e timer);
#endif /* BSW_TIMER_AL_TIMER_H_ */
