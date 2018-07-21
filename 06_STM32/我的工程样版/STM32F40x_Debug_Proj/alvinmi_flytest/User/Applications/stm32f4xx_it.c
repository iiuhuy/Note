#include "include.h"
#include "Ano_FlightDataCal.h"

void NMI_Handler(void)
{
}

void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void EXTI9_5_IRQHandler(void)  
{  
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)  
    {  
      EXTI_ClearITPendingBit(EXTI_Line7);  
			
			//Fc_Sensor_Get();
    }  
}


void TIM3_IRQHandler(void)
{
	_TIM3_IRQHandler();

}

void TIM4_IRQHandler(void)
{
	_TIM4_IRQHandler();

}

void USART2_IRQHandler(void)
{
	Usart2_IRQ();
}

void UART4_IRQHandler(void)
{
	Uart4_IRQ();
}

void UART5_IRQHandler(void)
{
	Uart5_IRQ();
}
