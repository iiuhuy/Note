/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG_H__
#define __CONFIG_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/***************换算******************/
#define ANGLE_TO_RADIAN 0.01745329f //*0.01745 = /57.3	角度转弧度
/***********************************************/

#define ANO_DT_USE_NRF24l01
/***********************************************/


#define OFFSET_AV_NUM 50

#define G_1G 4096
#define SP_EST_DRAG 1.0f
#define BARO_WIND_COMP 0.10f

//#define GYR_FIL_B_HZ  80.0f
//#define GYR_FIL_G_HZ  80.0f
//#define ACC_FIL_B_HZ  80.0f
//#define ACC_FIL_G_HZ  80.0f
/***********************************************/

#define MOTOR_ESC_TYPE 1  //2：无刷电机带刹车的电调，1：无刷电机不带刹车的电调，0：有刷电机
#define MOTORSNUM 4

#define REF_VOLTAGE 2800//2800  ///MV
#define BAT_LOW_VOTAGE 3250    //mV
#define FLOAW_MAX_HEIGHT  450
#define FLOW_ROLL_CONDITION 8 //   0-12

#define APP_ROLL_CH CH_PIT //app翻滚

#define MAX_ANGLE     25.0f
#define MAX_ANGLE_ROL 25.0f //角度
#define MAX_ANGLE_PIT 25.0f //角度

#define MAX_SPEED_ROL 200  //角度每秒
#define MAX_SPEED_PIT 200  //角度每秒
#define MAX_SPEED_YAW 360  //角度每秒

#define MAX_ROLLING_SPEED 1600  //角度每秒

#define MAX_X_SPEED 1000 //厘米每秒 cm/s
#define MAX_Y_SPEED 1000 //厘米每秒 cm/s

#define MAX_Z_SPEED_UP 350 //厘米每秒 cm/s
#define MAX_Z_SPEED_DW 300 //厘米每秒 cm/s

#define MAX_EXP_XY_ACC   500 //厘米每平方秒 cm/ss

#define CTRL_1_INTE_LIM 250 //角速度环积分限幅 ：输出

#define FINAL_P 			0.3f  //电机输出量比例
#define ANGULAR_VELOCITY_PID_INTE_D_LIM 300/FINAL_P  
#define X_PROPORTION_X_Y 1.0f //proportion
#define ROLL_ANGLE_KP 10.0f   //翻滚角度kp

#define MAX_THR_SET    85  //最大油门百分比 %
#define THR_INTE_LIM_SET   70  //油门积分百分比 % 

#define MAX_THR       MAX_THR_SET/FINAL_P   
#define THR_INTE_LIM   THR_INTE_LIM_SET/FINAL_P  

#define THR_START      40  //油门起调量百分比 %

#define LAND_ACC              500  //着陆加速度检测
#define LAND_ACC_DELTA        300  //着陆加速度变化量检测


#define BARO_FIX -0                          //气压速度积分修正起调值/CM厘米
//#define AUTO_TAKE_OFF_HEIGHT 50  //自动起飞高度
//#define HEIGHT_FIX           0               //气压高度固定补偿/CM厘米



#endif


