/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * 作者    ：匿名科创
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
 * 描述    ：LED驱动
**********************************************************************************/
#include "Drv_led.h"
//#include "Ano_Math.h"
#include "Drv_timer.h"
u8 LED_state;
static u8 LED_state_old;

void Drv_LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(ANO_RCC_LED,ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = ANO_Pin_LED2| ANO_Pin_LED3| ANO_Pin_LED4;
	GPIO_Init(ANO_GPIO_LED, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = ANO_Pin_LED1;
	GPIO_Init(ANO_GPIO_LED, &GPIO_InitStructure);
	
	
	GPIO_ResetBits(ANO_GPIO_LED, ANO_Pin_LED1);		
	GPIO_SetBits(ANO_GPIO_LED, ANO_Pin_LED2);		
	GPIO_ResetBits(ANO_GPIO_LED, ANO_Pin_LED3);		
	GPIO_ResetBits(ANO_GPIO_LED, ANO_Pin_LED4);
	
	
}




u16 led_accuracy = 20;//该时间应与LED_Duty()调用周期相同
float LED_Brightness[4] = {0,20,0,0}; //TO 20 //XBRG


//LED的1ms驱动，在1ms定时中断里调用。
void LED_1ms_DRV( ) //0~20
{
	static u16 led_cnt[4];

	u8 i;
	
	for(i=0;i<4;i++)
	{
			
		if( led_cnt[i] < LED_Brightness[i] )
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

u8 led_breath(u8 dT_ms,u8 i,u16 T)// T,led编号,一次半程的时间，单位ms
{
	u8 f = 0;
	static u8 dir[LED_NUM];
	switch(dir[i])
	{
		case 0:
//			LED_Brightness[i] += safe_div(led_accuracy,((float)T/(dT_ms)),0);
			if(LED_Brightness[i]>20)
			{
				dir[i] = 1;
			}
		
		break;
		case 1:
//			LED_Brightness[i] -= safe_div(led_accuracy,((float)T/(dT_ms)),0);
			if(LED_Brightness[i]<0)
			{
				dir[i] = 0;
				f = 1;//流程已完成1次
			}
			
		break;
			
		default:
			dir[i] = 0;
			
		break;
		
	}
	return (f);
}	

static u16 ms_cnt[LED_NUM];
static u16 group_n_cnt[LED_NUM];
//亮-灭 为一组
//调用周期（s），LED编号, 亮度（20级），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;
u8 led_flash(u8 dT_ms,u8 i,u8 lb,u16 group_n,u16 on_ms,u16 off_ms,u16 group_dT_ms)
{
	u8 f = 0;

	
	if(group_n_cnt[i] < group_n)   //组数没到
	{
		if(ms_cnt[i]<on_ms)
		{
			LED_Brightness[i] = lb;
		}
		else if(ms_cnt[i]<(on_ms+off_ms))
		{
			LED_Brightness[i] = 0;
		}
		if(ms_cnt[i]>=(on_ms+off_ms))
		{
			group_n_cnt[i] ++;
			ms_cnt[i] = 0;
		}
	}
	else						//进入组间隔
	{
		if(ms_cnt[i]<group_dT_ms)
		{
			LED_Brightness[i] = 0;
		}
		else
		{
			group_n_cnt[i] = 0;
			ms_cnt[i] = 0;
			f = 1; //流程完成1次
		}
	}
	
	ms_cnt[i] += (dT_ms);        //计时
	return (f); //0，未完成，1完成
}

static u16 led_times;	
void led_cnt_restar() //灯光驱动计数器复位
{
			led_times = 0;
			for(u8 i =0;i<LED_NUM;i++)
			{
				LED_Brightness[i] = 0;
				ms_cnt[i] = 0;
				group_n_cnt[i] = 0;
			}

}



void led_cnt_res_check()
{
		if(LED_state != LED_state_old)
		{
			led_cnt_restar();
			LED_state_old = LED_state;		
		}

}


extern u8 height_ctrl_mode;


//u8 LED_status[2];  //  0:old;  1:now


void LED_Task(u8 dT_ms) //10ms一次
{
	u8 j=0;	
	static s16 k;
	led_cnt_res_check();

	switch(LED_state)
	{
		case 0:
			{
				
			}
		break;
		case 1://没电
			led_flash(dT_ms,R_led,20,1,60,60,0);//调用周期（s）,led编号，亮度（0-20），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;
			
		break;
		case 2://校准gyro
			for(u8 i=0;i<LED_NUM;i++)
			{			
				j = led_flash(dT_ms,i,20,4,50,50,0);
				if(j) //调用周期（s）,led编号，亮度（0-20），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;
				{
					LED_state = 0;
				}
			}
		break;	
		case 3://校准acc
			for(u8 i=0;i<LED_NUM;i++)
			{			
				j = led_flash(dT_ms,i,20,8,50,50,0);
				if(j) //调用周期（s）,led编号，亮度（0-20），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;
				{
					LED_state = 0;
				}
			}			
		break;
		case 4://校准水平面
				k -= led_flash(dT_ms,((k) %4),20,1,240,20,0);
				if(k<=0) k = 20000;			
		break;
		case 5: //校准罗盘step1
					{
						led_breath(dT_ms,G_led,300);

					}			
		break;	
		case 6: //校准罗盘step2
					{
						for(u8 i=0;i<2;i++)
						{
							led_flash(dT_ms,R_led-i,20,1,100,100,000) ;
						}	
					}						
		break;
		case 7: //校准罗盘step3
					{
						led_breath(dT_ms,B_led,300);

					}			
		break;
		case 8: //错误
					{

						led_times += led_flash(dT_ms,R_led,20,1,2500,0,0);
						if(led_times == 1)
						{
							LED_state = 0;
						}

					}						
		break;
		case 9: //对频
			
		break;		
		case 10: //等待
			for(u8 i=0;i<LED_NUM;i++)
			{	
				led_flash(dT_ms,i,20,3,60,60,200);//调用周期（s）,led编号，亮度（0-20），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;
			}			
		break;
		case 11://无信号
//			LED_Brightness[1] = 20;
			led_breath(dT_ms,R_led,500);
//			for(u8 i=0;i<LED_NUM;i++)
//			{		
//				led_breath(dT_ms,i,500);
//			}			
		break;	
		case 12://翻滚
			
		break;
		case 13: //闪1次
					{
						LED_Brightness[0] = 20;
						j = led_flash(dT_ms,1,20,1,400,100,300) ;
						
						if(j)
						{
							LED_state = 0;
						}
					}		
		break;						
		case 14: //闪2次				
					{
						LED_Brightness[0] = 20;
						j = led_flash(dT_ms,1,20,2,200,200,300) ;
						
						if(j)
						{
							LED_state = 0;
						}
					}			
		break;		
		case 15://闪3次
					{
						LED_Brightness[0] = 20;
						j = led_flash(dT_ms,1,20,3,200,200,300) ;
						
						if(j)
						{
							LED_state= 0;
						}
					}		
		break;
		case 16://校准罗盘，未平
					{
						for(u8 i=0;i<2;i++)
						{
							led_flash(dT_ms,R_led+i,20,1,100,100,000) ;
						}
	

					}		
		break;
		case 17://正确、保存数据
					{

						led_times += led_flash(dT_ms,G_led,20,1,2500,0,0);
						if(led_times == 1)
						{
							LED_state = 0;
						}

					}			
		break;
		case 18://禁止解锁
					{

						led_times += led_flash(dT_ms,G_led,20,1,600,400,0);
						if(led_times == 3)
						{
							LED_state = 0;
						}

					}			
		break;
		case 80://惯性传感器异常
					{

						led_flash(dT_ms,R_led,20,2,100,100,800);


					}			
		break;
		case 81://电子罗盘异常
					{

						led_flash(dT_ms,R_led,20,3,100,100,800);


					}			
		break;
		case 82://气压计异常
					{

						led_flash(dT_ms,R_led,20,4,100,100,800);


					}			
		break;
///////////////////////
		case 116:		
		
		break;
		case 117:
			
		break;
		case 118:
			
		break;		
		case 119: 
			
		break;	
		case 120: 
			
		break;	
		case 121://mode1
		{
			for(u8 i=0;i<LED_NUM;i++)
			{			
				led_flash(dT_ms,i,20,1,100,100,600); //调用周期（s）,led编号，亮度（0-20），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;

			}
		}
		break;
		case 122://mode2 
			for(u8 i=0;i<LED_NUM;i++)
			{			
				led_flash(dT_ms,i,20,2,100,100,600); //调用周期（s）,led编号，亮度（0-20），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;

			}
		break;		
		case 123://mode3 
			for(u8 i=0;i<LED_NUM;i++)
			{			
				led_flash(dT_ms,i,20,3,100,100,600); //调用周期（s）,led编号，亮度（0-20），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;

			}		
		break;	
		case 124://mode4 
			for(u8 i=0;i<LED_NUM;i++)
			{			
				led_flash(dT_ms,i,20,4,100,100,600); //调用周期（s）,led编号，亮度（0-20），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;

			}		
		break;	
		case 125: 
		
		break;		
		case 126: 
		
		break;	
		case 127: 
		
		break;	
		case 128: 
		
		break;		
		case 129: 
		
		break;	
		case 130: 
		
		break;
		case 131://mode1
			{			
				led_flash(dT_ms,G_led,20,1,100,100,600); //调用周期（s）,led编号，亮度（0-20），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;

			}		
		break;
		case 132://mode2 
			{			
				led_flash(dT_ms,G_led,20,2,100,100,600); //调用周期（s）,led编号，亮度（0-20），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;

			}		
		break;		
		case 133://mode3 
			{			
				led_flash(dT_ms,G_led,20,3,100,100,600); //调用周期（s）,led编号，亮度（0-20），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;

			}			
		break;	
		case 134://mode4 
			{			
				led_flash(dT_ms,G_led,20,4,100,100,600); //调用周期（s）,led编号，亮度（0-20），组数，亮时间(ms)，灭时间(ms)，组间隔 ,ms>led_accuracy;

			}			
		break;			
		default:break;
	}
			
}



/******************* (C) COPYRIGHT 2016 ANO TECH *****END OF FILE************/

