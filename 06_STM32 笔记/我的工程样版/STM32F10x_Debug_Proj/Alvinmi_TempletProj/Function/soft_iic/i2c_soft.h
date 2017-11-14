#ifndef _I2C_SOFT_H
#define _I2C_SOFT_H

#include "stm32f10x.h"

/**************** i2c gpio define *****************/
#define GPIO_I2C		GPIOB
#define I2C_Pin_SCL		GPIO_Pin_6
#define I2C_Pin_SDA		GPIO_Pin_7
#define RCC_I2C			RCC_APB2Periph_GPIOB
/**************************************************/

#define	SCL_H		GPIO_I2C->BSRR = I2C_Pin_SCL
#define SCL_L		GPIO_I2C->BRR  = I2C_Pin_SCL
#define SDA_H		GPIO_I2C->BSRR = I2C_Pin_SDA
#define SDA_L		GPIO_I2C->BRR  = I2C_Pin_SDA
#define SCL_Read	GPIO_I2C->IDR  & I2C_Pin_SCL
#define SDA_Read	GPIO_I2C->IDR  & I2C_Pin_SDA

void I2c_Soft_Init(void);
void I2c_Soft_SendByte(u8 SendByte);	// i2c 发送一个字节
u8 I2c_Soft_ReadByte(u8);				// i2c 读取一个字节
u8 IIC_Write_1Byte(u8 SlaveAddress, u8 REG_Address, u8 REG_Date);	// IIC_Write 1Byte
u8 IIC_Read_1Byte(u8 SlaveAddress, u8 REG_Address, u8 *REG_Date);	// IIC_Read	 1Byte
u8 IIC_Write_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf);	// IIC_Write nByte
u8 IIC_Read_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf);	// IIC_Read	nByte


#endif


