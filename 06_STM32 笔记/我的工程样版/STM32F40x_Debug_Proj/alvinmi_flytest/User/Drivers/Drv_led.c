#include "Drv_led.h"

u8 LED_state;
static u8 LED_state_old;

void Drv_LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);	

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;		// 输出模式
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		// 上下拉枚举---这里是上拉
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		// 推挽/开漏输出枚举---这里是推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// 输出速度
	GPIO_InitStructure.GPIO_Pin   = ANO_Pin_LED2| ANO_Pin_LED3| ANO_Pin_LED4;
	GPIO_Init(ANO_GPIO_LED, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = ANO_Pin_LED1;
	GPIO_Init(ANO_GPIO_LED, &GPIO_InitStructure);
		
	GPIO_ResetBits(ANO_GPIO_LED, ANO_Pin_LED1);		
	GPIO_SetBits(ANO_GPIO_LED, ANO_Pin_LED2);		
	GPIO_ResetBits(ANO_GPIO_LED, ANO_Pin_LED3);		
	GPIO_ResetBits(ANO_GPIO_LED, ANO_Pin_LED4);
}

/***************************************************************************
* 原型 Prototype: void LED_1ms_DRV(void)
* 功能 Function:  1 ms LED 驱动, 在 1ms 定时器中断里调用
* 参数 Parameter: none
* 返回值 Returned value: none
****************************************************************************/
u16 led_accuracy = 20;	// 该时间应与 LED_Duty() 调用周期相同.

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
				case 0:	
					LED1_ON;
				break;
				case 1:	
					LED2_ON;
				break;
				case 2:	
					LED3_ON;
				break;
				case 3:	
					LED4_ON;
				break;
			}
		}
		else
		{
			switch(i)
			{
				case 0:	
					LED1_OFF;
				break;
				case 1:	
					LED2_OFF;
				break;
				case 2:	
					LED3_OFF;
				break;
				case 3:	
					LED4_OFF;
				break;
			}
		}
		if(++led_cnt[i]>=led_accuracy)
		{
			led_cnt[i] = 0;
		}
	}
}






