#include "Ano_Pid.h"


float PID_calculate(float T,		// 周期
					float in_ff,	// 前馈值
					float expect,	// 期望值(设定值)
					float feedback,	// 反馈值
					_PID_arg_st *pid_arg,	// PID 参数结构体
					_PID_arg_st *pid_val,	// PID 数据结构体
					float inte_d_lim,		// 积分误差限幅
					float inre_lim			// integration limit, 积分限幅
					)
{
	float differential, hz;
//	hz = safe_div(1.0f, dT_s, 0);
	
//	pid
}


