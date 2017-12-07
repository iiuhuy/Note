#include "BSP_Init.h"
#include "Drv_timer.h"


u8 All_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);		// 中断优先级组别设置

	SysTick_Configuration();	// SysTick Init
	
	return 0;
}





