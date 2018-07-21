#include "i2c_soft.h"

void I2C_Delay(void)
{
   /*u8 i=0; 
   while(i) 
   { 
     i--; 
   } 
		*/ 	
}

/******************************************************************************
* 函数原型:	void I2c_Soft_Init(void)	模拟 IIC 初始化
* 功    能: IIC_Soft Init
* 参    数:	null
* 返 回 值: null
*******************************************************************************/ 
void I2c_Soft_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_I2C, ENABLE);
	GPIO_InitStructure.GPIO_Pin   = I2C_Pin_SCL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIO_I2C, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin   = I2C_Pin_SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIO_I2C, &GPIO_InitStructure);
}

/******************************************************************************
* 函数原型:	int I2c_Soft_Start(void)
* 功    能: iic Start	IIC 起始信号
* 参    数:	null
* 返 回 值: int
*******************************************************************************/ 
int I2c_Soft_Start(void)
{
	SDA_H;
	SCL_H;
	I2C_Delay();
	if(!SDA_Read) return 0;		// SDA 线为低电平则总线忙, 退出. -> SDA = 0, return.
	SDA_L;
	I2C_Delay();
	if(!SDA_Read) return 0;		// SDA 线为高电平则总线错误, 退出. -> SDA = 1, ERROR
	SDA_L;
	I2C_Delay();
	return 1;
}

/******************************************************************************
* 函数原型:	void I2c_Soft_Stop(void)
* 功    能: iic Stop	IIC 停止信号
* 参    数:	null
* 返 回 值: null
*******************************************************************************/ 
void I2c_Soft_Stop(void)
{
	SCL_L;
	I2C_Delay();
	SDA_L;
	I2C_Delay();
	SCL_H;
	I2C_Delay();
	SDA_H;
	I2C_Delay();
}

/******************************************************************************
* 函数原型:	void I2c_Soft_Ack(void)
* 功    能: iic ACK		IIC 应答信号
* 参    数:	null
* 返 回 值: null
*******************************************************************************/ 
void I2c_Soft_Ack(void)
{
	SCL_L;
	I2C_Delay();
	SDA_L;
	I2C_Delay();
	SCL_H;
	I2C_Delay();
	SCL_L;
	I2C_Delay();
}

/******************************************************************************
* 函数原型:	void I2c_Soft_NoAck(void)
* 功    能: iic NoACK		IIC 无应答信号
* 参    数:	null
* 返 回 值: null
*******************************************************************************/ 
void I2c_Soft_NoAck(void)
{
	SCL_L;
	I2C_Delay();
	SDA_H;
	I2C_Delay();
	SCL_H;
	I2C_Delay();
	SCL_L;
	I2C_Delay();
}

/******************************************************************************
* 函数原型:	int I2c_Soft_WaitAck(void)
* 功    能: iic WaitACK		return 1 -- ACK; return 0 NoAck.
* 参    数:	null
* 返 回 值: int 
*******************************************************************************/ 
int I2c_Soft_WaitAck(void)
{
	u8 ErrorTime = 0;
	SCL_L;
	I2C_Delay();
	SDA_H;
	I2C_Delay();
	SCL_H;
	I2C_Delay();
	if(SDA_Read)
	{
		ErrorTime ++;
		if(ErrorTime > 200)
		{
			I2c_Soft_Stop();
			return 1;
		}
	}
	SCL_L;
	I2C_Delay();
	return 0;
}

/******************************************************************************
* 函数原型:	void I2c_Soft_SendByte(u8 SendByte)
* 功    能: iic SendByte		数据从高位到地位 
* 参    数:	u8 SendByte
* 返 回 值: null
*******************************************************************************/ 
void I2c_Soft_SendByte(u8 SendByte)
{
	u8 i = 8;
	while(i--)
	{
		SCL_L;
		I2C_Delay();
		if(SendByte&0x80)
		{
			SDA_H;
		}else
		{
			SDA_L;
			SendByte <<=1;
			I2C_Delay();
			SCL_H;
			I2C_Delay();
		}
	}
	SCL_L;
}

/******************************************************************************
* 函数原型:	u8 I2c_Soft_ReadByte(u8 ask)
* 功    能: iic ReadByte		数据从高位到地位 
			读 1 个字节, ack = 1时, 发送 Ack, ack = 0时, 发送 NoAck
* 参    数:	u8 ask
* 返 回 值: 返回这个字节
*******************************************************************************/ 
u8 I2c_Soft_ReadByte(u8 ask)
{
	u8 i = 8;
	u8 ReceiveByte = 0;
	
	SDA_H;
	while(i--)
	{
		ReceiveByte <<= 1;
		SCL_L;
		I2C_Delay();
		SCL_H;
		I2C_Delay();
		if(SDA_Read)
		{
			ReceiveByte |= 0x01; 
		}
	}
	SCL_L;
	
	if(ask)
		I2c_Soft_Ack();
	else
		I2c_Soft_NoAck();
	
	return ReceiveByte;
}

/******************************************************************************
* 函数原型:	u8 IIC_Write_1Byte(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
* 功    能: IIC Write 1Byte Date.		IIC 写一个字节数据
* 参    数:	u8 SlaveAddress
			u8 REG_Address
			u8 REG_data
* 返 回 值: 0 | 1
*******************************************************************************/ 
u8 IIC_Write_1Byte(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
{
	I2c_Soft_Start();
	I2c_Soft_SendByte(SlaveAddress<<1);
	if(I2c_Soft_WaitAck())
	{
		I2c_Soft_Stop();
		return 1;
	}
	I2c_Soft_SendByte(REG_Address);		
	I2c_Soft_WaitAck();
	I2c_Soft_SendByte(REG_data);
	I2c_Soft_WaitAck();
	I2c_Soft_Stop();
	return 0;
}

/******************************************************************************
* 函数原型:	u8 IIC_Read_1Byte(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
* 功    能: IIC Read 1Byte Date.		IIC 读一个字节数据
* 参    数:	u8 SlaveAddress
			u8 REG_Address
			u8 REG_data
* 返 回 值: 0 | 1
*******************************************************************************/ 
u8 IIC_Read_1Byte(u8 SlaveAddress,u8 REG_Address,u8 *REG_data)
{
	I2c_Soft_Start();
	I2c_Soft_SendByte(SlaveAddress<<1); 
	if(I2c_Soft_WaitAck())	
	{
		I2c_Soft_Stop();
		return 1;
	}
	I2c_Soft_SendByte(REG_Address<<1);
	I2c_Soft_WaitAck();
	I2c_Soft_Start();
	I2c_Soft_SendByte(SlaveAddress<<1 | 0x01);
	I2c_Soft_WaitAck();
	*REG_data = I2c_Soft_ReadByte(0);
	I2c_Soft_Stop();
	return 0;
}

/******************************************************************************
* 函数原型:	u8 IIC_Write_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf)
* 功    能: IIC Write nByte Date.		IIC 写 n 个字节数据
* 参    数:	u8 SlaveAddress
			u8 REG_Address
			u8 len
			u8 *buf
* 返 回 值: 0 | 1
*******************************************************************************/ 
u8 IIC_Write_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf)
{
	I2c_Soft_Start();
	I2c_Soft_SendByte(SlaveAddress<<1); 
	if(I2c_Soft_WaitAck())
	{
		I2c_Soft_Stop();
		return 1;
	}
	I2c_Soft_SendByte(REG_Address); 
	I2c_Soft_WaitAck();
	while(len--) 
	{
		I2c_Soft_SendByte(*buf++); 
		I2c_Soft_WaitAck();
	}
	I2c_Soft_Stop();
	return 0;
}

/******************************************************************************
* 函数原型:	u8 IIC_Read_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf)
* 功    能: IIC Read nByte Date.		IIC 读 n 个字节数据
* 参    数:	u8 SlaveAddress
			u8 REG_Address
			u8 len
			u8 *buf
* 返 回 值: 0 | 1
*******************************************************************************/ 
u8 mpu_test;

u8 IIC_Read_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf)
{
	mpu_test = I2c_Soft_Start();
	I2c_Soft_SendByte(SlaveAddress<<1); 
	if(I2c_Soft_WaitAck())
	{
		I2c_Soft_Stop();
		return 1;
	}
	I2c_Soft_SendByte(REG_Address); 
	I2c_Soft_WaitAck();
	
	I2c_Soft_Start();
	I2c_Soft_SendByte(SlaveAddress<<1 | 0x01); 
	I2c_Soft_WaitAck();
	while(len) 
	{
		if(len == 1)
		{
			*buf = I2c_Soft_ReadByte(0);
		}
		else
		{
			*buf = I2c_Soft_ReadByte(1);
		}
		buf++;
		len--;
	}
	I2c_Soft_Stop();
	return 0;
}


