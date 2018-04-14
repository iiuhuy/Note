#include "Ano_FcDate.h"
#include "Ano_Parameter.h"

//void data_save(void)
//{
//	para_sta.save_en = !flag.fly_ready;
//	para_sta.save_trig = 1;
//}

_save_st save;		// 声明


void Para_Data_Init(void)
{
	Ano_Parame_Read();	// 参数读取
}

