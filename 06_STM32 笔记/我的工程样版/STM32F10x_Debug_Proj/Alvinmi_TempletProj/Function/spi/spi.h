#ifndef _SPI_H_
#define _SPI_H_
#include "stm32f10x.h"

/*************** SPI GPIO define ******************/
#define SPI_PORT			GPIOB
#define ANO_GPIO_CE			GPIOA
#define RCC_GPIO_SPI		RCC_APB2Periph_GPIOB
#define SPI_Pin_CSN			GPIO_Pin_12
#define SPI_Pin_SCK			GPIO_Pin_13
#define SPI_Pin_MISO		GPIO_Pin_14
#define SPI_Pin_MOSI		GPIO_Pin_15
/*********************************************/

void SPI2_Config_Init(void);
void SPI_CE_H(void);
void SPI_CE_L(void);
void SPI_CSN_H(void);
void SPI_CSN_L(void);
u8   SPI_RW(u8 dat);


#endif



