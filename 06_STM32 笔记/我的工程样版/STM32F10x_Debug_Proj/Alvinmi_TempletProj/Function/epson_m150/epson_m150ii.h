#ifndef __EPSON_M150II_H
#define __EPSON_M150II_H
#include "sys.h"

extern u8 print_real[7][12]; 	// 打印的点阵数组
extern uint8_t byPrinter_head_ITFlag ;	// 中断处理标志位

void Printer_IO_Config(void);
void Printer_line(void);
void Printer_Timer_Init(void);		// printer parameter init
void print_matrix_invert(void);		// matrix invert function
void Printer_Stop(void);			// 停止打印机
void Printer_Font_Extract(char *String);	// 打印字符串接口函数
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

