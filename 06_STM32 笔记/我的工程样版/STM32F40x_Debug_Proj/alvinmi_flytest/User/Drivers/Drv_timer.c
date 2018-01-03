#include "Drv_timer.h"
#include "Drv_led.h"

void TIM2_CONF(void)		// AHB1 84M
{
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	
	// 使能时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// TIM_DeInit
	TIM_DeInit(TIMER2);
	
	// 自动重装载寄存器周期的值(计数值)
	TIM_TimeBaseStructure.TIM_Period = 1000;
	
	// 累计 TIM_Period 个频率后产生一个更新或者中断, 时钟分频系数为 72
	TIM_TimeBaseStructure.TIM_Prescaler = 84 - 1;
	
	// 对外部时钟进行采样的时钟分频, 这里没有用到
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	// 计数模式 -> 向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	// 初始化定时器2
	TIM_TimeBaseInit(TIMER2, &TIM_TimeBaseStructure);
	
	// 清中断, 避免一启用中断后立即产生中断.  
 	TIM_ClearFlag(TIMER2, TIM_FLAG_Update);
	
	// 允许定时器更新中断(中断源)。 Update -> 更新中断;  TIM_FLAG_Trigger -> 触发中断
	TIM_ITConfig(TIMER2, TIM_IT_Update, ENABLE);
	
	// 使能定时器
	TIM_Cmd(TIMER2, ENABLE);

	// 先屏蔽等待使用
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);
}

void TIM2_NVIC(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init ( &NVIC_InitStructure );
}

void Timer2_Init(void)
{
	TIM2_CONF();
	TIM2_NVIC();
	// 重新开时钟, 开始计时
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
}

//-----------------------------------------------------------------------------------//

void SysTick_Configuration(void)
{
	RCC_ClocksTypeDef rcc_clocks;
	uint32_t	cnts;
	
	RCC_GetClocksFreq(&rcc_clocks);	// 将芯片内各个模块的时钟保存在参数 rcc_clocks 中, 包含了结构体中的四个参数
	
	cnts = (uint32_t) rcc_clocks.HCLK_Frequency / TICK_PER_SECOND;		// HCLK_Frequency/1000 = 1000 
	cnts = cnts / 8;	// cnts/8 = 1000 
	
	SysTick_Config(cnts);
	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	// SysTick 时钟源为 AHB / 8 
}

volatile uint32_t sysTickUpTime = 0;

/***************************************************************************
* 原型 Prototype: uint32_t GetSysTimer_us(void)
* 功能 Function: get systime
* 参数 Parameter: none
* 返回值 Returned value: value
****************************************************************************/
uint32_t GetSysTime_us(void)
{
	register	uint32_t	ms;
	u32	value;
	ms = sysTickUpTime;
	value = ms * TICK_US + (SysTick->LOAD - SysTick->VAL) * TICK_US / SysTick->LOAD;
	return value;
}

/***************************************************************************
* 原型 Prototype: void Delay_us (uint32_t us)
* 功能 Function: Delay_us
* 参数 Parameter: us
* 返回值 Returned value: none
****************************************************************************/
void Delay_us (uint32_t us)
{
    uint32_t now = GetSysTime_us();
    while ( GetSysTime_us() - now < us );
}

/***************************************************************************
* 原型 Prototype: void Delay_us (uint32_t us)
* 功能 Function: Delay_us
* 参数 Parameter: ms
* 返回值 Returned value: none
****************************************************************************/
void Delay_ms(uint32_t ms)
{
	while ( ms-- )
        Delay_us ( 1000 );
}


u32 systime_ms;
void sys_time(void)
{
	systime_ms++;
}

u32 SysTick_GetTick(void)
{
	return systime_ms;
}

u32 Get_Delta_T(_get_dT_st *data)
{
    data->old = data->now;		 // 上一次的时间
    data->now = GetSysTime_us(); // 本次的时间
    data->dT = ( ( data->now - data->old ) );// 时间的间隔(周期)
	
	if(data->init_flag == 0)
	{
		data->init_flag = 1; // 第一次调用时输出 0 作为初始化, 以后正常输出。 
		return 0;
	}
	else
	{
		return data->dT;
	}
}

void SysTick_Handler(void)
{
	sysTickUpTime++;
	sys_time();
	LED_1ms_DRV();	// LED 1ms 驱动
}

//------------------------------------- end of file --------------------------------//
