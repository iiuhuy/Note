#include <stdio.h>
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "rtc.h" 		    

_calendar_obj calendar; // 时钟结构体 通过调用这个结构体就能拿到时钟的数据. 

/******************************************************************************
* 函数原型:	static void RTC_NVIC_Config(void)	
* 功    能: STM32_RTC 中断配置
* 参    数:	null
* 返 回 值: null
*******************************************************************************/ 
static void RTC_NVIC_Config(void)
{	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;		//RTC全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//先占优先级1位,从优先级3位
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	//先占优先级0位,从优先级4位
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//使能该通道中断
	NVIC_Init(&NVIC_InitStructure);		//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

/******************************************************************************
* 函数原型:	u8 RTC_Init(void)
* 功    能: STM32_RTC 初始化, 同时检测时钟是否工作正常
*			BKP->DR1 用于保存是否第一次配置的设置
* 参    数:	null
* 返 回 值: 0: 初始化失败    1: ok
*******************************************************************************/ 
u8 RTC_Init(void)
{
	//检查是不是第一次配置时钟
	u8 temp=0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	// 使能 PWR 和 BKP 外设时钟  -- ①
	PWR_BackupAccessCmd(ENABLE);	// 使能后备寄存器访问  	-- ②
	if (BKP_ReadBackupRegister(BKP_DR1) != 0x5050)		//从指定的后备寄存器中读出数据:读出了与写入的指定数据不相乎
	{	 			
		BKP_DeInit();	// 复位备份区域 	-- ③-1
		RCC_LSEConfig(RCC_LSE_ON);	// 设置外部低速晶振(LSE),使用外设低速晶振	-- ③-2
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET&&temp<250)	//检查指定的RCC标志位设置与否,等待低速晶振就绪
			{
			temp++;
			delay_ms(10);
			}
		if(temp>=250)return 1;//初始化时钟失败,晶振有问题	    
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		// 设置 RTC 时钟(RTCCLK),选择 LSE 作为 RTC 时钟		-- ④-1  
		RCC_RTCCLKCmd(ENABLE);	// 使能RTC时钟		-- ④-2
		RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成
		RTC_WaitForSynchro();		//等待RTC寄存器同步  
		RTC_ITConfig(RTC_IT_SEC, ENABLE);		// 使能RTC秒中断	-- ⑤-4
		RTC_WaitForLastTask();	 // 等待最近一次对RTC寄存器的写操作完成
		RTC_EnterConfigMode();   // 允许配置		-- ⑤-1	
		RTC_SetPrescaler(32767); // 设置RTC预分频的值 -- ⑤-2
		RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成
		RTC_Set(2017,1,14,17,42,55);  //设置时间	
//		RTC_SetCounter(0x00000000);   // 清除 RTC 计数器的值	-- ⑤-3
//		RTC_WaitForLastTask();		  // 等待最近一次对 RTC 寄存器的写操作
		RTC_ExitConfigMode();    // 退出配置模式		-- ⑤-5
		BKP_WriteBackupRegister(BKP_DR1, 0X5050);	//向指定的后备寄存器中写入用户程序数据
	}
	else	//系统继续计时
	{
		RTC_WaitForSynchro();	//等待最近一次对RTC寄存器的写操作完成
		RTC_ITConfig(RTC_IT_SEC, ENABLE);	//使能RTC秒中断
		RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成
	}
	RTC_NVIC_Config();//RCT中断分组设置		    				     
	RTC_Get();//更新时间	
	return 1; //ok
}		 				    
 
//extern u16 tcnt; 
/******************************************************************************
* 函数原型: void RTC_IRQHandler(void)
* 功    能: 每秒触发一次, 一般中断函数, 放到 "stm32f10x_it.c"
* 参    数:	null
* 返 回 值: null
*******************************************************************************/
void RTC_IRQHandler(void)
{		 
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET) //秒钟中断
	{							
		RTC_Get();//更新时间   
 	}
	if(RTC_GetITStatus(RTC_IT_ALR)!= RESET) //闹钟中断
	{
		RTC_ClearITPendingBit(RTC_IT_ALR);		//清闹钟中断	  	
		RTC_Get();				//更新时间   
  	printf("Alarm Time:%d-%d-%d %d:%d:%d\n",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);//输出闹铃时间	
  	} 				  								 
	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);		//清闹钟中断
	RTC_WaitForLastTask();	  	  	// 等待最近一次对 RTC 寄存器写操作完成 						 	   	 
}


/******************************************************************************
* 函数原型: u8 Is_Leap_Year(u16 year)
* 功    能: 判断是否是闰年函数
* 参    数:	year
* 返 回 值: 1: 是闰年;   0: 不是闰年
* -----------------------------------------------------------------------------
* | Moth |1  2  3  4  5  6  7  8  9  10 11 12
* |	闰年 |31 29 31 30 31 30 31 31 30 31 30 31
* |非闰年|31 28 31 30 31 30 31 31 30 31 30 31
*******************************************************************************/
u8 Is_Leap_Year(u16 year)
{			  
	if(year%4==0) //必须能被4整除
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;//如果以00结尾,还要能被400整除 	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}

/******************************************************************************
* 函数原型: u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
* 功    能: 把输入的时钟转换为秒钟
*			以1970年1月1日为基准, 1970~2099 年为合法年份
* 参    数:	u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec
* 返 回 值: 0: 成功;  1: 失败
*******************************************************************************/
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表	  
//平年的月份日期表
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	//把所有年份的秒钟相加
	{
		if(Is_Leap_Year(t))seccount+=31622400;//闰年的秒钟数
		else seccount+=31536000;			  //平年的秒钟数
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //把前面月份的秒钟数相加
	{
		seccount+=(u32)mon_table[t]*86400;//月份秒钟数相加
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//闰年2月份增加一天的秒钟数	   
	}
	seccount+=(u32)(sday-1)*86400;//把前面日期的秒钟数相加 
	seccount+=(u32)hour*3600;//小时秒钟数
    seccount+=(u32)min*60;	 //分钟秒钟数
	seccount+=sec;//最后的秒钟加上去

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//使能PWR和BKP外设时钟  
	PWR_BackupAccessCmd(ENABLE);	//使能RTC和后备寄存器访问 
	RTC_SetCounter(seccount);	//设置RTC计数器的值

	RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成  	
	return 0;	    
}

/******************************************************************************
* 函数原型: u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
* 功    能: 初始化闹钟.
*			以1970年1月1日为基准, 1970~2099 年为合法年份
* 参    数:	u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec: 闹钟的年月日时分秒
* 返 回 值: 0: 成功;  1: 失败
*******************************************************************************/
u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	//把所有年份的秒钟相加
	{
		if(Is_Leap_Year(t))seccount+=31622400;//闰年的秒钟数
		else seccount+=31536000;			  //平年的秒钟数
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //把前面月份的秒钟数相加
	{
		seccount+=(u32)mon_table[t]*86400;//月份秒钟数相加
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//闰年2月份增加一天的秒钟数	   
	}
	seccount+=(u32)(sday-1)*86400;//把前面日期的秒钟数相加 
	seccount+=(u32)hour*3600;//小时秒钟数
    seccount+=(u32)min*60;	 //分钟秒钟数
	seccount+=sec;//最后的秒钟加上去 			    
	//设置时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//使能PWR和BKP外设时钟   
	PWR_BackupAccessCmd(ENABLE);	//使能后备寄存器访问  
	//上面三步是必须的!
	
	RTC_SetAlarm(seccount);
 
	RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成  	
	
	return 0;	    
}

/******************************************************************************
* 函数原型: u8 RTC_Get(void)
* 功    能: 得到当前的时间
* 参    数:	null
* 返 回 值: 0: 成功;  1: 失败
*******************************************************************************/
u8 RTC_Get(void)
{
	static u16 daycnt=0;
	u32 timecount=0; 
	u32 temp=0;
	u16 temp1=0;	  
    timecount=RTC_GetCounter();	 
 	temp=timecount/86400;   //得到天数(秒钟数对应的)
	if(daycnt!=temp)//超过一天了
	{	  
		daycnt=temp;
		temp1=1970;	//从1970年开始
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//是闰年
			{
				if(temp>=366)temp-=366;//闰年的秒钟数
				else {temp1++;break;}  
			}
			else temp-=365;	  //平年 
			temp1++;  
		}   
		calendar.w_year=temp1;//得到年份
		temp1=0;
		while(temp>=28)//超过了一个月
		{
			if(Is_Leap_Year(calendar.w_year)&&temp1==1)//当年是不是闰年/2月份
			{
				if(temp>=29)temp-=29;//闰年的秒钟数
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];//平年
				else break;
			}
			temp1++;  
		}
		calendar.w_month=temp1+1;	//得到月份
		calendar.w_date=temp+1;  	//得到日期 
	}
	temp=timecount%86400;     		//得到秒钟数   	   
	calendar.hour=temp/3600;     	//小时
	calendar.min=(temp%3600)/60; 	//分钟	
	calendar.sec=(temp%3600)%60; 	//秒钟
	calendar.week=RTC_Get_Week(calendar.w_year,calendar.w_month,calendar.w_date);//获取星期   
	return 0;
}

/******************************************************************************
* 函数原型: u8 RTC_Get_Week(u16 year,u8 month,u8 day)
* 功    能: 获得现在是星期几。 输入公历日期得到星期(只允许1901-2099年)
* 参    数:	公历年月日
* 返 回 值: 星期号
*******************************************************************************/
u8 RTC_Get_Week(u16 year,u8 month,u8 day)
{	
	u16 temp2;
	u8 yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 
	// 如果为21世纪,年份数加100  
	if (yearH>19)yearL+=100;
	// 所过闰年数只算1900年之后的  
	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
}			  




