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
	ROL = 0,	// roll  ºá¹ö½Ç
	PIT = 1,	// pitch ¸©Ñö½Ç
	YAW = 2,	// yaw 	 Æ«º½½Ç
	VEC_RPY,
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


