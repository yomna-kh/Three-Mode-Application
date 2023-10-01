/*
 * timer.h
 *
 *  Created on: 18 Dec 2022
 *      Author: world
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "std_types.h"
#include "tm4c123gh6pm.h"

typedef enum
{
	TIMER_0 , TIMER_1 , TIMER_2 , TIMER_3 , TIMER_4,TIMER_5
} Timer;

typedef enum
{
	ONESHOT_UP = 0X11,ONESHOT_DOWN = 0X01,PERIODIC_UP = 0X12,PERIODIC_DOWN = 0X02,
	CAPTURE_UP = 0X13,CAPTURE_DOWN = 0X03
}Timer_Mode;

typedef enum
{
	DOWN,UP
}Timer_count;

typedef struct {
 uint16 load_value;
 uint8 prescaler;
 Timer_Mode mode;
 Timer timer ;
} Timer_ConfigType;

void Timer_init(const Timer_ConfigType * Config_Ptr);
void Timer_setCallBack(uint8 TIMER_NUMBER,void(*a_ptr)(void));
void Timer_ChangeValue(uint8 TIMER_NUMBER, uint16 Reload_value);
void Timer_ENAB(uint8 TIMER_NUMBER);
void Timer_DENAB(uint8 TIMER_NUMBER);

#endif
