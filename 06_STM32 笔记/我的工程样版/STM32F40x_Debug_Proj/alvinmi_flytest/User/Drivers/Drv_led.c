#include "Drv_led.h"



/***************************************************************************
* 原型 Prototype: void LED_1ms_DRV(void)
* 功能 Function:  1 ms LED 驱动, 在 1ms 定时器中断里调用
* 参数 Parameter: none
* 返回值 Returned value: none
****************************************************************************/
float LED_Brightness[4] = {0,20,0,0}; 	//TO 20 //XBRG

void LED_1ms_DRV(void)	//0~20
{
	static u16 led_cnt[4];
	
	u8 i;
	
	for(i=0;i<4;i++)
	{
		if(led_cnt[i] < LED_Brightness[i])
		{
			switch(i)
			{
				
			}
		}
		else
		{
		
		}
	}
	
}






