#include "stm32f4xx.h"
#include "include.h"
#include "Ano_Parameter.h"
#include "Drv_w25qxx.h"

#include "Flight_Ctrl.h"

union Parameter Ano_Parame;

// PID Rest
void PID_Rest(void)
{
//---	姿态控制角速度环 PID 参数
	Ano_Parame.set.pid_att_1level[ROL][KP]	= 3.5f;  	// 姿态控制角速度环 PID 参数
	Ano_Parame.set.pid_att_1level[ROL][KI]	= 0; 		// 姿态控制角速度环 PID 参数
	Ano_Parame.set.pid_att_1level[ROL][KD]	= 0.1f; 	// 姿态控制角速度环 PID 参数
	
	Ano_Parame.set.pid_att_1level[PIT][KP]	= 3.5f;		// 姿态控制角速度环 PID 参数
	Ano_Parame.set.pid_att_1level[PIT][KI]	= 0;		// 姿态控制角速度环 PID 参数
	Ano_Parame.set.pid_att_1level[PIT][KD]	= 0.1f;		// 姿态控制角速度环 PID 参数
	
	Ano_Parame.set.pid_att_1level[YAW][KP]	= 4.0f; 	// 姿态控制角速度环 PID 参数
	Ano_Parame.set.pid_att_1level[YAW][KI]	= 0.f; 		// 姿态控制角速度环 PID 参数
	Ano_Parame.set.pid_att_1level[YAW][KD]	= 0.0f; 	// 姿态控制角速度环 PID 参数
	
//---   姿态控制角度环 PID 参数
	Ano_Parame.set.pid_att_2level[ROL][KP]	= 5.0f;		// 姿态控制角度环 PID 参数
	Ano_Parame.set.pid_att_2level[ROL][KI]	= 3.0f;		// 姿态控制角度环 PID 参数
	Ano_Parame.set.pid_att_2level[ROL][KD]	= 0.0f;		// 姿态控制角度环 PID 参数
	
	Ano_Parame.set.pid_att_2level[PIT][KP]	= 5.0f;		// 姿态控制角度环 PID 参数
	Ano_Parame.set.pid_att_2level[PIT][KI]	= 3.0f;		// 姿态控制角度环 PID 参数
	Ano_Parame.set.pid_att_2level[PIT][KD]	= 0.0f;		// 姿态控制角度环 PID 参数
	
	Ano_Parame.set.pid_att_2level[YAW][KP]	= 5.0f;		// 姿态控制角度环 PID 参数
	Ano_Parame.set.pid_att_2level[YAW][KI]	= 1.0f;		// 姿态控制角度环 PID 参数
	Ano_Parame.set.pid_att_2level[YAW][KD]	= 0.8f;		// 姿态控制角度环 PID 参数
		
//---	高度控制高度速度环 PID 参数
	Ano_Parame.set.pid_alt_1level[KP]		= 2.0f;		// 高度控制高度速度环 PID 参数
	Ano_Parame.set.pid_alt_1level[KI]		= 2.0f;		// 高度控制高度速度环 PID 参数
	Ano_Parame.set.pid_alt_1level[KD]		= 0.02f;	// 高度控制高度速度环 PID 参数
	
//---	高度控制高度环	PID 参数
	Ano_Parame.set.pid_alt_2level[KP]		= 1.0f;		// 高度控制高度环 PID 参数
	Ano_Parame.set.pid_alt_2level[KI]		= 0;		// 高度控制高度环 PID 参数
	Ano_Parame.set.pid_alt_2level[KD]		= 0;		// 高度控制高度环 PID 参数
	
//---	位置控制位置速度环 PID 参数						
	Ano_Parame.set.pid_loc_1level[KP]		= 0;		// 位置控制位置速度环 PID 参数
	Ano_Parame.set.pid_loc_1level[KI]		= 0;		// 位置控制位置速度环 PID 参数
	Ano_Parame.set.pid_loc_1level[KD]		= 0;		// 位置控制位置速度环 PID 参数
	
//---	位置控制位置环 PID 参数
	Ano_Parame.set.pid_loc_2level[KP]		= 0;		// 位置控制位置环 PID 参数
	Ano_Parame.set.pid_loc_2level[KI]		= 0;		// 位置控制位置环 PID 参数
	Ano_Parame.set.pid_loc_2level[KD]		= 0;		// 位置控制位置环 PID 参数
	
//	ANO_DT_SendString("PID reset!",sizeof("PID reset!"));
}

static void Ano_Parame_Write(void)
{
	All_PID_Init();			// 储存 PID 参数后, 重新初始化 PID
	
	
}

void Ano_Parame_Read(void)
{
	// 读取第一扇区内的参数
	Flash_SectorsRead(0x000000,&Ano_Parame.byte[0], 1);		// 长度是 4096KB
	
	// 如果内容没有被初始化, 则进行参数初始化工作.
	if(Ano_Parame.set.frist_init != SOFT_VER)
	{
		Parame_Reset();				// 参数初始化
		PID_Rest();					// PID_Rest
		Ano_Parame_Write();			// Write_Parame
	}
	// 
//	Parame_Copy_Para2fc();
}

static void Parame_Copy_Para2fc(void)
{
	for(u8 i=0; i<3; i++)
	{
		save.acc_offset [i]	 =	Ano_Parame.set.acc_offset[i];
		save.gyro_offset[i]	 =	Ano_Parame.set.gyro_offset[i];
		save.mag_offset [i]	 =	Ano_Parame.set.mag_offset[i];  
		save.mag_gain   [i]	 =	Ano_Parame.set.mag_gain[i];    

		// icm 20602
//		Center_Pos_Set();		// 重心位置设置?	
	}
}
	
void Parame_Reset(void)
{
	// 参数初始化 Parameter.Parameter_s = Ano_Parame.set
	Ano_Parame.set.pwmInMode =  PWM;		// 	PWM 为枚举	Parameter.Parameter_s.pwmInMode
	Ano_Parame.set.warn_power_voltage = 3.55 * 3;
	Ano_Parame.set.return_home_power_voltage = 3.7f * 3;
	Ano_Parame.set.lowest_power_voltage = 3.5f * 3;
	
	Ano_Parame.set.auto_take_off_height = 0;    // cm   
	
	for(u8 i = 0;i<3;i++)	// 为什么是  3？
	{
		Ano_Parame.set.acc_offset [i] = 0;		// 加速度计零偏
		Ano_Parame.set.gyro_offset[i] = 0;		// 陀螺仪零偏
		Ano_Parame.set.mag_offset [i] = 0;  	// 磁力计零偏
		Ano_Parame.set.mag_gain   [i] = 1; 		// 磁力计校正比例
		
		Ano_Parame.set.center_pos_cm[i] = 0;	// 重心相对传感器位置偏移量
	}
	
	// 将参数 copy 到飞控
	Parame_Copy_Para2fc();
	
//	ANO_DT_SendString("parameter reset!",sizeof("parameter reset!"));
}


