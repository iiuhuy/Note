#include "Task_scheduler.h"
#include "Drv_timer.h"

u32 test_dT_1000hz[3],test_rT[6];	// 应该是测试线程函数里面任务的执行时间



void Loop_1000Hz(void)	// 1ms 执行一次
{
	test_dT_1000hz[0] = test_dT_1000hz[1];
	test_rT[3] = test_dT_1000hz[1] = GetSysTime_us ();
	test_dT_1000hz[2] = (u32)(test_dT_1000hz[1] - test_dT_1000hz[0]);
//-------------------------------------------------------------------------------------------------------//
	/* 传感器数据读取 */
//	Fc_Sensor_Get();
	
	/* 惯性传感器数据准备 */
//	Sensor_Data_Prepare(1);
	
	/* 姿态结算更新 */
//	IMU_Update_Task(1);
	
	/* 获取 WC_Z 加速度 */
//	WCZ_Acc_Get_Task();
	
	/* 飞行状态任务 */
//	Flight_State_Task(1,CH_N);
	
	/* 姿态角速度环控制 */
//	Att_1level_Ctrl(1e-3f);
	
	/* 电机输出控制 */
//	Motor_Ctrl_Task(1);
	
	/* 数传数据交换(匿名数传) */
//	ANO_DT_Date_Exchange();
//-----------------------------------------------------------------------------------------------------//
	test_rT[4]= GetSysTime_us ();
	test_rT[5] = (u32)(test_rT[4] - test_rT[3]);
}

void Loop_500Hz(void)	// 2ms 执行一次
{

}

void Loop_200Hz(void)	// 5ms 执行一次
{

}

void Loop_100Hz(void)	// 10ms 执行一次
{
	test_rT[0]= GetSysTime_us ();	
//-----------------------------------------------------------------------------------------------------//
	/* 遥控数据处理 */
//	RC_duty_task(10);
	
	/* 飞行模式设置任务 */
//	Flight_Mode_Set(10);
	
	/* 获取姿态角 (ROLL PITCH YAW) */
//	calculate_RPY();
	
	/* 姿态角度换控制 */
//	Att_2level_Ctrl(10e-3f,CH_N);
	
	/* 位置速度环控制 (暂无) */
//	Loc_1level_Ctrl(10,CH_N);
	
	/* 高度数据融合任务 */
//	WCZ_Fus_Task(10);

	/* 高度速度环控制 */
//	Alt_1level_Ctrl(10e-3f);

	/* 高度环控制 */
//	Alt_2level_Ctrl(10e-3f);
	
	/* 灯光控制 */
//	LED_Task(10);
	
//----------------------------------------------------------------------------------------------------//
	test_rT[4] = GetSysTime_us ();			// 
	test_rT[5] = (u32)(test_rT[4] - test_rT[3]) ;	// 
}


void Loop_50Hz(void)	// 20ms 执行一次
{
	/* 罗盘数据处理任务 */
//	Mag_Update_Task(20);
}

void Loop_20Hz(void)	// 50ms 执行一次
{
	/* TOF 激光任务 */
//	Drv_Vl53_RunTask();
	/* 电压相关任务 */
//	Power_UpdateTask(50);
}

void Loop_2Hz(void)		// 500ms 执行一次
{
	/* 延时储存任务 */
//	Ano_Parame_Write_task(500);
}

// 系统任务配置, 创建不同的执行频率的线程 (结构体数组)
static sched_task_t  sched_tasks[] = 
{
	{Loop_1000Hz,1000,  0, 0},		// 1ms
	{Loop_500Hz , 500,  0, 0},		// 2ms
	{Loop_200Hz , 200,  0, 0},		// 5ms
	{Loop_100Hz , 100,  0, 0},		// 10ms
	{Loop_50Hz  ,  50,  0, 0},		// 20ms
	{Loop_20Hz  ,  20,  0, 0},		// 50ms
	{Loop_2Hz   ,   2,  0, 0},		// 500ms
};

// 根据数组长度, 判断线程数量
#define	TASK_NUM	(sizeof(sched_tasks)/sizeof(sched_task_t))

void Scheduler_Setup(void)
{
	uint8_t	index = 0;
	// 初始化任务表
	for(index=0; index < TASK_NUM; index++)
	{
		// 计算每个任务的延时周期数
		sched_tasks[index].interval_ticks = TICK_PER_SECOND/sched_tasks[index].rate_hz;
		
		// 最短周期为 1, 也就是 1ms	(不能大于定时时基)
		if(sched_tasks[index].interval_ticks < 1)
		{
			sched_tasks[index].interval_ticks = 1;
		}
	}
}

// 这个函数放到 main() 函数的主循环 while(1) 中, 不停的判断是否有线程应该执行.
void Scheduler_Run(void)
{
	uint8_t		index = 0;
	
	// 循环判断所以线程, 是否应该执行
	for(index=0; index < TASK_NUM; index++)
	{
		// 获取系统当前的时间, 单位 ms
		uint32_t tnow = SysTick_GetTick();	
		
		// 进行判断, 如果当前时间减去上一次执行的时间, 大于等于该线程的执行周期, 则执行线程
		if(tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
		{	
			// 更新线程的时间, 用于下一次判断
			sched_tasks[index].last_run = tnow;
			
			// 执行线程函数, 使用函数指针指定对应的线程函数
			sched_tasks[index].task_func();
		}
	}	
}


