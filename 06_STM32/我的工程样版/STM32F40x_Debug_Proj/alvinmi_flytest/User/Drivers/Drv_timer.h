#ifndef _TIMER_H_
#define _TIMER_H_
#include "stm32f4xx.h"

#define TIMER2 		TIM2

#define TICK_PER_SECOND	1000
#define TICK_US	(1000000/TICK_PER_SECOND)
extern volatile uint32_t sysTickUpTime;

typedef struct
{
	u8 init_flag;
	u32 old;
	u32 now;
	u32 dT;
}_get_dT_st;

void Timer2_Init(void);	// Timer2 Init
void TIM2_CONF(void);	// Timer2 Config
void TIM2_NVIC(void);	// Timer2 NVIC 
void SysTick_Configuration(void);	// SysTick Init
uint32_t GetSysTime_us(void);		// 
void Delay_us (uint32_t us);		// delay us
void Delay_ms (uint32_t ms);		// delay ms
void sys_time(void);
u32 SysTick_GetTick(void);			 
u32 Get_Delta_T(_get_dT_st *data);


#endif

