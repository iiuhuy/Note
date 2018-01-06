#include "include.h"
#include "Ano_Parameter.h"
#include "Drv_w25qxx.h"

union Parameter Ano_Parame;


void Ano_Parame_Read(void)
{
	// 读取第一扇区内的参数
	Flash_SectorsRead(0x000000,&Ano_Parame.byte[0], 1);
	
	// 如果内容没有被初始化, 则进行参数初始化工作.
	if(Ano_Parame.set.frist_init != SOFT_VER)
	{
		Parame_Reset();
//		PID_Rest();
//		Ano_Parame_Write();
	}
	// 
//	Parame_Copy_Para2fc();
}

static void Parame_Copy_Para2fc(void)
{
	for(u8 i=0; i < 3; i++)
	{
//		save.acc_offset[i]		=	Ano_Parame.set.acc_offset[i];
//		save.gyro_offset[i]		=	Ano_Parame.set.gyro_offset[i];
//		save.mag_offset[i]		=	Ano_Parame.set.mag_offset[i];  
//		save.mag_gain[i]		=	Ano_Parame.set.mag_gain[i];  
		
	}
}
	
void Parame_Reset(void)
{
	// 参数初始化
//	Ano_Parame.set.pwmInMode =  PWM;		// 	PWM 为枚举
	Ano_Parame.set.warn_power_voltage = 3.55 * 3;
	Ano_Parame.set.return_home_power_voltage = 3.7f * 3;
	Ano_Parame.set.lowest_power_voltage = 3.5f * 3;
	
	Ano_Parame.set.auto_take_off_height = 0;    // cm   
	
	for(u8 i = 0;i<3;i++)	// 为什么是 8次?
	{
//		Ano_Parame.set.acc_offset[i] = 0;		// 加速度计零偏
//		Ano_Parame.set.gyro_offset[i] = 0;		// 陀螺仪零偏
//		Ano_Parame.set.mag_offset[i] = 0;  		// 磁力计零偏
//		Ano_Parame.set.mag_gain[i] = 1; 		// 磁力计校正比例
//		
//		Ano_Parame.set.center_pos_cm[i] = 0;	// 重心相对传感器位置偏移量
	}
	
	// 将参数 copy 到飞控
	Parame_Copy_Para2fc();
	
//	ANO_DT_SendString("parameter reset!",sizeof("parameter reset!"));
}


