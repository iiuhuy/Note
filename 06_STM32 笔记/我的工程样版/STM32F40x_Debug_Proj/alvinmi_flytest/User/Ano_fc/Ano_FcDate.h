#ifndef __ANO_FCDATA_H__
#define __ANO_FCDATA_H__
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
#define TRUE 1
#define FALSE 0 
enum pwminmode_e
{
	PWM = 0,
	PPM ,
	SBUS,
};


enum
{
	X = 0,
	Y = 1,
	Z = 2,
	VEC_XYZ,
};

enum
{
	ROL = 0,	// roll  横滚角
	PIT = 1,	// pitch 俯仰角
	YAW = 2,	// yaw 	 偏航角
	VEC_RPY,	// 向量化 ? 
				// RPY -> roll、pitch、yaw		// rpy 角也叫 X-Y-Z fixed angles.
				// 另一种姿态描述方式, 绕自身坐标轴旋转。 称为 Z-Y-X 欧拉角. 
				// 两种描述方式不同, 但是最终结果都是一样的。四元数转欧拉角有 12 种旋转次序.
};

enum
{
	KP = 0,
	KI = 1,
	KD = 2,
	PID,
};

typedef struct
{
	u8 first_f;
	float acc_offset[VEC_XYZ];
	float gyro_offset[VEC_XYZ];
	
	float surface_vec[VEC_XYZ];
	
	float mag_offset[VEC_XYZ];
	float mag_gain[VEC_XYZ];

} _save_st ;
extern _save_st save;









void Para_Data_Init(void);

#endif


