#include "Flight_Ctrl.h"
#include "Attitude_Contrl.h"

/* PID 参数初始化 */ 
void All_PID_Init(void)
{
	/*姿态控制，角速度 PID 初始化*/
	Att_1level_PID_Init();
	
	/*姿态控制，角度 PID 初始化*/
	Att_2level_PID_Init();
	
	/*高度控制，高度速度 PID 初始化*/

	
	/*高度控制，高度 PID 初始化*/

	
	/*位置控制，位置速度 PID 初始化*/

}



