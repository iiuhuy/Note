#include "spi.h"

/******************************************************************************
* 1.配置相关引脚的复用功能, 使能 SPI2 CLOCK
* 2.初始化 SPI2, 设置 SPI2 工作模式
* 3.使能 SPI2
* 4.SPI 数据传输
* 5.查看 SPI 传输状态
******************************************************************************/

/******************************************************************************
* 函数原型: void SPI2_Config_Init(void)
* 功    能: SPI2 初始化
* 参    数: null
* 返 回 值: null
*******************************************************************************/ 
void SPI2_Config_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure; 
	GPIO_InitTypeDef  GPIO_InitStructure; 
		
	// 打开对应的时钟源
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); 
	
	/* Config SPI_NRF_SPI: 'SCK','MISO','MOSI' Pin */ 
	GPIO_InitStructure.GPIO_Pin = SPI_Pin_SCK| SPI_Pin_MISO| SPI_Pin_MOSI; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用功能
	GPIO_Init(SPI_PORT, &GPIO_InitStructure);
	/* SPI_NRF_SPI: CSN Pin */
	GPIO_InitStructure.GPIO_Pin = SPI_Pin_CSN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(SPI_PORT, &GPIO_InitStructure);	

	GPIO_SetBits(SPI_PORT, SPI_Pin_CSN);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // 双线全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 	// 主模式
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 	// 数据大小 8 位 
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 		// 时钟极性, 空闲时为低 (0)
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; // 第一个边沿有效, 上升沿为采样时刻 
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; 	// NSS 信号由软件产生
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;  // 4 分频, 9MHz 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 	// 高位在前
	SPI_InitStructure.SPI_CRCPolynomial = 7; 
	SPI_Init(SPI2, &SPI_InitStructure); 

	/* Enable SPI2 */ 
	SPI_Cmd(SPI2, ENABLE);
}

/******************************************************************************
* 函数原型: u8 SPI_RW(u8 data);
* 功    能: SPI 读写函数
* 参    数: 写入的 一个字节数据
* 返 回 值: SPI 接收到的一个字节数据
*******************************************************************************/ 
u8 SPI_RW(u8 data)
{
	/* 当 SPI 发送缓冲器非空等待| */
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET); 	// 参考 st 官方文档
	/* 通过 SPI2 发送一字节数据 */
	SPI_I2S_SendData(SPI2, data);
	/* 当 SPI 接收缓冲器为空时等待 */
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET); 	// 参考 st 官方文档
	/* Return the byte read from the SPI bus */ 
	return SPI_I2S_ReceiveData(SPI2); 
}

void SPI_CSN_H(void)
{
	GPIO_SetBits(SPI_PORT, SPI_Pin_CSN);
}

void SPI_CSN_L(void)
{
	GPIO_ResetBits(SPI_PORT, SPI_Pin_CSN);
}

//=============================================================================//
// 写一个字节
u8 SPI_Write_Byte(u8 reg, u8 Value)
{
	u8 state;
	SPI_CSN_L();	// 这类可以直接宏定义(类似IIC里) -->> eg: #define	CSN_L GPIO_XXX ->BSRR = SPI_Pin_CSN
	state = SPI_RW(reg);
	SPI_RW(Value);
	SPI_CSN_H();
	return state;
}

// 读一个字节
u8 SPI_Read_Byte(u8 reg)
{
	u8 value;
	SPI_CSN_L();
	SPI_RW(reg);			// 返回的是一个无效数据
	value = SPI_RW(0);		// 写入无效数据
	SPI_CSN_H();
	return value;
}

// 写多个字节
u8 SPI_Write_nByte(u8 reg, u8 *pbuf, u8 len)
{
	u8 state;
	SPI_CSN_L();
	state = SPI_RW(reg);
	while(len)
	{
		SPI_RW(*pbuf);			// 写一串数据, 将首地址传进去
		pbuf++;
		len--;
	}
	SPI_CSN_H();
	return state;
}

// 读多个字节
u8 SPI_Read_nByte(u8 reg, u8 *pbuf, u8 len)
{
	u8 state;
	SPI_CSN_L();
	state = SPI_RW(reg);
	while(len)
	{
		*pbuf = SPI_RW(0);		// 同上写入无效数据
		pbuf ++;
		len--;
	}
	SPI_CSN_H();
	return state;
}



