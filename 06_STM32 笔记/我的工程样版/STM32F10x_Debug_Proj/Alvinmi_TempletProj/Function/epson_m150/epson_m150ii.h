#ifndef __EPSON_M150II_H__
#define __EPSON_M150II_H__
#include "sys.h"

/******************* PRINTER M-150II IO ************/
#define PTA_PORT						GPIOC
#define PTA_PIN							GPIO_Pin_3
#define PTA_OFF()    					GPIO_ResetBits(PTA_PORT, PTA_PIN)
#define PTA_ON()    					GPIO_SetBits(PTA_PORT, PTA_PIN)

#define PTB_PORT						GPIOC
#define PTB_PIN							GPIO_Pin_2
#define PTB_OFF()     					GPIO_ResetBits(PTB_PORT, PTB_PIN)
#define PTB_ON()    					GPIO_SetBits(PTB_PORT, PTB_PIN)

#define PTC_PORT						GPIOC
#define PTC_PIN							GPIO_Pin_1
#define PTC_OFF()     					GPIO_ResetBits(PTC_PORT, PTC_PIN)
#define PTC_ON()    					GPIO_SetBits(PTC_PORT, PTC_PIN)

#define PTD_PORT						GPIOC
#define PTD_PIN							GPIO_Pin_0
#define PTD_OFF()     					GPIO_ResetBits(PTD_PORT, PTD_PIN)
#define PTD_ON()    					GPIO_SetBits(PTD_PORT, PTD_PIN)

#define MOTER_STA                       PCin(4)		// 位带操作, 判断电机IO 的状态
#define MOTER_PORT						GPIOC
#define MOTER_PIN						GPIO_Pin_4
#define MOTER_OFF()     				GPIO_ResetBits(MOTER_PORT, MOTER_PIN)
#define MOTER_ON()    					GPIO_SetBits(MOTER_PORT, MOTER_PIN)

#define PT_TIMER_PORT					GPIOB
#define PT_TIMER_PIN					GPIO_Pin_9
#define PT_GET_TIMER()     				GPIO_ReadInputDataBit(PT_TIMER_PORT, PT_TIMER_PIN)

#define PT_RESET_DETCT_PORT				GPIOB
#define PT_RESET_DETCT_PIN				GPIO_Pin_8
#define PT_GET_RESET()     				GPIO_ReadInputDataBit(PT_RESET_DETCT_PORT, PT_RESET_DETCT_PIN)

extern u8 print_real[7][12]; 	// 打印的点阵数组
extern uint8_t byPrinter_head_ITFlag ;	// 中断处理标志位

void Printer_IO_Config(void);		// GPIO_Init
void Printer_line(void);			// Printer_line_dot
void Printer_Timer_Init(void);		// printer parameter init
void print_matrix_invert(void);		// matrix invert function
void Printer_Stop(void);			// 停止打印机
void Printer_Font_Extract(char *String,char len);	// 打印字符串接口函数
void Epson_Printer_Init(void);		// Epson_Init

typedef struct
{
	u8 t_h;			/*1:timer=1,0:timer=0*/
	u8 r_h;			/*1:reset_dector=1,0:reset_dector=0*/

	u8 t_index;
	u8 r_index;

	u8 t_num;		// Timing_num
	u8 t_num_back;	// last Timing_num

	u8 line_num;	// line_num
	u8 line_num_back;

	u8 p_on;		
	u8 run_paper;
}PRINTER_CTR_TYPE;

#endif

