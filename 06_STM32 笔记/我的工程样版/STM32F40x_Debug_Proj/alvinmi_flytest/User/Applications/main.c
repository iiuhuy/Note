#include "BSP_Init.h"

/*--->>> 如果出现 "Undefined symbol assert_failed" 这个错误,则需要在 stm32f4xx.h 中,
74 行左右把 #define USE_STDPERIPH_DRIVER 给定义上, 而且主函数一定要加下面这个函数.*/
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
		// 系统出错, 就会进入到这里
  }
}
#endif

int main(void)
{
	All_Init();
}






