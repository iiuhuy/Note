#include "stm32f10x.h"
#include "timer.h"

/**************************************************************
* TIMx(TIM6 & TIM7)  为基本定时器 
* TIMx(TIM1 & TIM8)  为高级控制定时器 
* TIMx(TIM2,TIM3,TIM4,TIM5) 为通用定时器 
***************************************************************/
// STM32 的定时器除了 Timer6 & Timer7 其他都可以用来做 PWM 输出
// 同样的 STM32 除了 Timer6 & Timer7 其他都可以用来做输入捕获

// Timer3
uint32_t Timer3_Count = 0;	// 记录 Timer3 中断次数
uint16_t Timer3_Frequency;	// Timer3 中断频率

// Timer4
uint32_t Timer4_Count = 0;	// 记录 Timer3 中断次数
uint16_t Timer4_Frequency;	// Timer3 中断频率

//============================== Timer Fuction ================================//
/******************************************************************************
* 函数原型:	void Timer3_Init(uint16_t Handler_Frequency)
* 功    能: Init Timer3
* 参    数:	Handler_Frequency is Timer3 中断频率(IT_Frequency)
*******************************************************************************/ 
void Timer3_Init(uint16_t Handler_Frequency)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	Timer3_Frequency = Handler_Frequency;	// Timer3 频率
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Period = 1000*1000/Handler_Frequency ;	// 装载值
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;		// 分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	// 不分割时钟
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 向上计数
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);	// 清楚中断标志
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);	// 使能 Timer3
}

/******************************************************************************
* 函数原型:	void Timer3_pwm_init(u16 autoload, u16 prescale)
* 功    能: Timer3 Pwm Init
* 参    数:	autoload -->> 自动装载值 & prescale -->> 预分频参数
* 描	述: Example: Timer3_pwm_init(899,0) -> 不分频,PWM频率=72000000/900=80Khz
			把 Timer3_channel2 重映射到 PB5 产生 PWM
*******************************************************************************/ 
void Timer3_pwm_init(u16 autoload, u16 prescale)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;		 // Timer 输出比较设置

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	// 使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  // 使能GPIO外设和AFIO复用功能模块时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); // Timer3部分重映射  TIM3_CH2->PB5    
 
   // 设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_5; 		// TIM_CH2
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;  // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 
   // 初始化TIM3
	TIM_TimeBaseStructure.TIM_Period		= autoload; // 设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler		= prescale; // 设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	// 设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;  // TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); // 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	// 初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM2; // 选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity	= TIM_OCPolarity_High; // 输出极性:TIM输出比较极性高
	
	// TIM 通道设置
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
	TIM_Cmd(TIM3, ENABLE);  // 使能TIM3
	
	/* 修改 TIM3_CCR2 来控制占空比 */
	//TIM_SetCompare2(TIM3,0);	 	// 占空比根据实际情况来修改
}


/******************************************************************************
* 函数原型:	void Timer4_Init(uint16_t Handler_Frequency)
* 功    能: Init Timer4
* 参    数:	Handler_Frequency is Timer4 中断频率(IT_Frequency)
*******************************************************************************/ 
void Timer4_Init(uint16_t Handler_Frequency)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	Timer4_Frequency = Handler_Frequency;	// Timer4 频率
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructure.TIM_Period = 1000*1000/Handler_Frequency ;	// 装载值
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;		// 分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	// 不分割时钟
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 向上计数
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);	// 清楚中断标志
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM4,ENABLE);	// 使能 Timer4
}

/******************************************************************************
* 函数原型:	void Timer5_InputCapture_Init(u16 autoload, u16 prescale)
* 功    能: Timer5_Channel1 (PA0)  输入捕获, 捕获 PA0 上高电平脉冲
* 参    数:	autoload -> 自动装载值 & prescale -> 预分频参数
			Example: Timer5_InputCapture_Init(0xFFFF,72-1) // 以 1MHz 的频率计数
					 即 1us 计数一次,  重新装载值为最大值. 
*******************************************************************************/ 
void Timer5_InputCapture_Init(u16 autoload, u16 prescale)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
   	NVIC_InitTypeDef	NVIC_InitStructure;
	TIM_ICInitTypeDef	TIM5_ICInitStructure;	// Timer5_InputCapture_InitStructure

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	// 使能TIM5时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// 使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  	// PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   // PA0 输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);	
	// PA0 下拉
	// 初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period 		= autoload; 	// 设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler 	= prescale; 	// 预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;  // TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); // 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	// 初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; // CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	// 上升沿捕获
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; // 映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 // 配置输入分频,不分频 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;	// IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	// 中断分组初始化	/* 可以考虑集中到 NVIC_Init() */
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);// 允许更新中断 ,允许CC1IE捕获中断	
   	TIM_Cmd(TIM5,ENABLE ); 	// 使能定时器5
}

// 这里的两个全局变量只是为了进行测试这个实验.
u8  TIM5CH1_CAPTURE_STA=0;	// 输入捕获状态	 	    				
u16	TIM5CH1_CAPTURE_VAL;	// 输入捕获值
/******************************************************************************
* 函数原型:	void TIM5_IRQHandler(void)
* 功    能: TIM5_IRQHandler 捕获中断
* 参    数:	None
*******************************************************************************/ 
void TIM5_IRQHandler(void)
{ 

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}

