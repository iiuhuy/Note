#ifndef _USART_H_
#define _USART_H_
#include "stm32f10x.h"

#define USART_REC_LEN  			200  	//定义最大接收字节数 200
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	

/******************************************************************************
							全局函数声明
*******************************************************************************/ 
void Uart1_Init(uint32_t baud);


#endif
