#include "24cxx.h" 
#include "delay.h"

/* 24CXX驱动 代码(适合24C01~24C16,24C32~256未经过测试!有待验证!)*/

/******************************************************************************
* 函数原型:	void AT24CXX_Init(void)
* 功    能: 初始化 AT24cxx
* 参    数:	null
* 返 回 值: null
*******************************************************************************/ 
void AT24CXX_Init(void)
{
	I2c_Soft_Init();
}

/******************************************************************************
* 函数原型:	u8 AT24CXX_Read1Byte(u16 readaddr)
* 功    能: 在AT24CXX指定地址读出一个数据
* 参    数:	readaddr 开始读数的地址
* 返 回 值: temp 读到的数据
*******************************************************************************/ 
u8 AT24CXX_Read1Byte(u16 readaddr)
{				  
	u8 temp=0;		  	    																 
    I2c_Soft_Start();  
	if(EE_TYPE>AT24C16)
	{
		I2c_Soft_SendByte(0XA0);	   //发送写命令
		I2c_Soft_WaitAck();
		I2c_Soft_SendByte(readaddr>>8);//发送高地址
		I2c_Soft_WaitAck();		 
	}else I2c_Soft_SendByte(0XA0+((readaddr/256)<<1));   //发送器件地址0XA0,写数据 	 

	I2c_Soft_WaitAck(); 
    I2c_Soft_SendByte(readaddr%256);   //发送低地址
	I2c_Soft_WaitAck();	    
	I2c_Soft_Start();  	 	   
	I2c_Soft_SendByte(0XA1);           //进入接收模式			   
	I2c_Soft_WaitAck();	 
    temp=I2c_Soft_ReadByte(0);		   
    I2c_Soft_Stop();//产生一个停止条件	    
	return temp;
}

/******************************************************************************
* 函数原型:	void AT24CXX_Write1Byte(u16 writeaddr,u8 data)
* 功    能: 在AT24CXX指定地址写入一个数据
* 参    数:	u16 writeaddr -> 写入数据的目的地址,u8 data -> 要写入的数据
* 返 回 值: null
*******************************************************************************/ 
void AT24CXX_Write1Byte(u16 writeaddr,u8 data)
{				   	  	    																 
    I2c_Soft_Start();  
	if(EE_TYPE>AT24C16)
	{
		I2c_Soft_SendByte(0XA0);	    //发送写命令
		I2c_Soft_WaitAck();
		I2c_Soft_SendByte(writeaddr>>8);//发送高地址
 	}else
	{
		I2c_Soft_SendByte(0XA0+((writeaddr/256)<<1));   //发送器件地址0XA0,写数据 
	}	 
	I2c_Soft_WaitAck();	   
    I2c_Soft_SendByte(writeaddr%256);   //发送低地址
	I2c_Soft_WaitAck(); 	 										  		   
	I2c_Soft_SendByte(data);     //发送字节							   
	I2c_Soft_WaitAck();  		    	   
    I2c_Soft_Stop();//产生一个停止条件 
	delay_ms(10);	 
}

/******************************************************************************
* 函数原型:	void AT24CXX_WriteLenByte(u16 writeaddr,u32 data,u8 len)
* 功    能: 在AT24CXX里面的指定地址开始写入长度为Len的数据
*			用于写入16bit或者32bit的数据.
* 参    数:	u16 writeaddr,	开始写入的地址  
*			u32 data,		数据数组首地址
*			u8 len			要写入数据的长度2,4
* 返 回 值: null
*******************************************************************************/ 
void AT24CXX_WriteLenByte(u16 writeaddr,u32 data,u8 len)
{  	
	u8 t;
	for(t=0;t<len;t++)
	{
		AT24CXX_Write1Byte(writeaddr+t,(data>>(8*t))&0xff);
	}												    
}

/******************************************************************************
* 函数原型:	u32 AT24CXX_ReadLenByte(u16 readaddr,u8 len)
* 功    能: 在AT24CXX里面的指定地址开始读出长度为Len的数据
*			用于写入16bit或者32bit的数据.
* 参    数:	u16 readaddr,	开始读出的地址 
*			u8 len			要读出数据的长度2,4
* 返 回 值: temp	读取的数据
*******************************************************************************/ 
u32 AT24CXX_ReadLenByte(u16 readaddr,u8 len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_Read1Byte(readaddr+len-t-1); 	 				   
	}
	return temp;												    
}

/******************************************************************************
* 函数原型: u8 AT24CXX_Check(void)
* 功    能: 检查AT24CXX是否正常
*			这里用了24XX的最后一个地址(255)来存储标志字.
*			如果用其他24C系列,这个地址要修改
* 参    数:	null
* 返 回 值: 1: 失败; 0: ok
*******************************************************************************/ 
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp=AT24CXX_Read1Byte(255);//避免每次开机都写AT24CXX			   
	if(temp==0X55)return 0;		   
	else//排除第一次初始化的情况
	{
		AT24CXX_Write1Byte(255,0X55);
	    temp=AT24CXX_Read1Byte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

/******************************************************************************
* 函数原型: void AT24CXX_Read(u16 readaddr,u8 *pbuffer,u16 num)
* 功    能: 在AT24CXX里面的指定地址开始读出指定个数的数据
* 参    数:	u16 readaddr,	开始读出的地址 对24c02为0~255
*			u8 *pbuffer,	数据数组首地址
*			u16 num			要读出数据的个数
* 返 回 值: null
*******************************************************************************/ 
void AT24CXX_Read(u16 readaddr,u8 *pbuffer,u16 num)
{
	while(num)
	{
		*pbuffer++=AT24CXX_Read1Byte(readaddr++);	
		num--;
	}
}  

/******************************************************************************
* 函数原型: void AT24CXX_Write(u16 writeaddr,u8 *pbuffer,u16 num)
* 功    能: 在AT24CXX里面的指定地址开始写入指定个数的数据
* 参    数:	u16 writeaddr,	开始写入的地址 对24c02为0~255
*			u8 *pbuffer,	数据数组首地址
*			u16 num			要写入数据的个数
* 返 回 值: null
*******************************************************************************/ 
void AT24CXX_Write(u16 writeaddr,u8 *pbuffer,u16 num)
{
	while(num--)
	{
		AT24CXX_Write1Byte(writeaddr,*pbuffer);
		writeaddr++;
		pbuffer++;
	}
}
 


