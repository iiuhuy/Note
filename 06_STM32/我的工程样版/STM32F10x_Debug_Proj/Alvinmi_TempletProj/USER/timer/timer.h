#ifndef _TIMER_H_
#define _TIMER_H_
#include "stm32f10x.h"

/******************************************************************************
*							全局变量声明							
*******************************************************************************/ 
extern uint32_t Timer3_Count;
extern uint16_t Timer3_Frequency;
extern uint32_t Timer4_Count;
extern uint16_t Timer4_Frequency;

extern uint16_t Count_10ms,Count_20ms,Count_40ms,Count_250ms,Count_1s;	// Timer4 IT Count variable

/******************************************************************************
							全局函数声明
*******************************************************************************/ 
void Timer3_Init(uint16_t Handler_Frequency);	// Timer3 Init
void Timer4_Init(uint16_t Handler_Frequency);	// Timer4 Init





#endif


