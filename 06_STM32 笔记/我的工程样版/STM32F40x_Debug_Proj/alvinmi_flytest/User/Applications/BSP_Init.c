#include "BSP_Init.h"
#include "Drv_timer.h"
#include "Drv_led.h"
#include "Drv_w25qxx.h"




u8 All_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);		// 中断优先级组别设置

	SysTick_Configuration();	// SysTick Init
	
	Drv_LED_Init();				// LED 功能初始化, 即 Init LED GPIO.
	
	Flash_Init();               // 板载 Flash 芯片驱动初始化.

	Para_Data_Init();           // 参数数据初始化

	
	return 0;
}





