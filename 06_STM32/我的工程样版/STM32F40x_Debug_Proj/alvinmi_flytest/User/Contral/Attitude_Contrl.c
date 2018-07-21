#include "Attitude_Contrl.h"
#include "Ano_FcDate.h"
#include "Ano_Parameter.h"
#include "Ano_Pid.h"

// 角速度控制环参数
_PID_arg_st  arg_1[VEC_RPY];

// 角度环控制参数
_PID_arg_st  arg_2[VEC_RPY];



/*
姿态角速率部分控制参数

arg_1_kp:  调整角速度相应速度, 不震荡的前提下, 尽量越高越好.

震荡时, 可以降低 arg_1_kp, 增大 arg_1_kd .

若增大 arg_1_kd 已经不能抑制震荡, 需要将 kp 和 kd 同时减小. 
*/
#define CTRL_1_KI_START 0.f


/*角速度环PID参数初始化*/
void Att_1level_PID_Init(void)
{
	arg_1[ROL].kp = Ano_Parame.set.pid_att_1level[ROL][KP];
	arg_1[ROL].ki = Ano_Parame.set.pid_att_1level[ROL][KI];
	arg_1[ROL].kd_ex = 0.005f;
	arg_1[ROL].kd_fb = Ano_Parame.set.pid_att_1level[ROL][KD];
	arg_1[ROL].k_ff = 0.0f;
	
	arg_1[PIT].kp = Ano_Parame.set.pid_att_1level[PIT][KP];
	arg_1[PIT].ki = Ano_Parame.set.pid_att_1level[PIT][KI];
	arg_1[PIT].kd_ex = 0.005f;
	arg_1[PIT].kd_fb = Ano_Parame.set.pid_att_1level[PIT][KD];
	arg_1[PIT].k_ff  = 0.0f;

	arg_1[YAW].kp = Ano_Parame.set.pid_att_1level[YAW][KP];
	arg_1[YAW].ki = Ano_Parame.set.pid_att_1level[YAW][KI];
	arg_1[YAW].kd_ex = 0.005f;
	arg_1[YAW].kd_fb = Ano_Parame.set.pid_att_1level[YAW][KD];
	arg_1[YAW].k_ff  = 0.0f;

#if (MOTOR_ESC_TYPE == 2)	// 无刷电机带刹车的电调反馈.
	#define DIFF_GAIN 0.3f
//	arg_1[ROL].kd_ex = arg_1[ROL].kd_ex *DIFF_GAIN;
//	arg_1[PIT].kd_ex = arg_1[PIT].kd_ex *DIFF_GAIN;
	arg_1[ROL].kd_fb = arg_1[ROL].kd_fb *DIFF_GAIN;
	arg_1[PIT].kd_fb = arg_1[PIT].kd_fb *DIFF_GAIN;
	
#elif (MOTOR_ESC_TYPE == 1)	// 无刷电机不带刹车的电调.
	#define DIFF_GAIN 1.0f
//	arg_1[ROL].kd_ex = arg_1[ROL].kd_ex *DIFF_GAIN;
//	arg_1[PIT].kd_ex = arg_1[PIT].kd_ex *DIFF_GAIN;
	arg_1[ROL].kd_fb = arg_1[ROL].kd_fb *DIFF_GAIN;
	arg_1[PIT].kd_fb = arg_1[PIT].kd_fb *DIFF_GAIN;
	
#endif
	
}


void Att_2level_PID_Init(void)
{
	arg_2[ROL].kp = Ano_Parame.set.pid_att_2level[ROL][KP];
	
}


