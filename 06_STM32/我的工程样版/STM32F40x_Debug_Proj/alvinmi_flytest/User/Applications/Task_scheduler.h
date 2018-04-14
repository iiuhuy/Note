#ifndef		__TASK_SCHEDULER__
#define 	__TASK_SCHEDULER__
#include "stm32f4xx.h"

typedef	struct
{
void (*task_func)(void);
uint16_t	rate_hz;			// 频率
uint16_t	interval_ticks;		// 滴答间隔(滴答时基为 1ms)
uint32_t	last_run;			// 上次运行(记录上次运行的时间)
}sched_task_t;

void Scheduler_Setup(void);
void Scheduler_Run(void);


#endif

