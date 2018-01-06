#ifndef __ANO_FCDATA_H__
#define __ANO_FCDATA_H__
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
#define TRUE 1
#define FALSE 0 

enum
{
	X = 0,
	Y = 1,
	Z = 2,
	VEC_XYZ,
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









void Para_Data_Init(void);

#endif


