#include "stdio.h"
#include "Drv_w25qxx.h"

typedef struct
{
	uint8_t Manufacturer;            /* Manufacturer ID 制造商 id */
	uint8_t Memory;               	 /* Density Code  */
	uint8_t Capacity;                /* Family Code 容量 */
	uint8_t rev;
}jedec_id_t;

/* Private define ------------------------------------------------------------*/
//#define W25QXX_DEBUG
#ifdef W25QXX_DEBUG
#define w25qxx_debug(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#else
#define w25qxx_debug(fmt, ...)
#endif

#define JEDEC_MANUFACTURER_ST       0x20
#define JEDEC_MANUFACTURER_MACRONIX 0xC2
#define JEDEC_MANUFACTURER_WINBOND  0xEF

/* JEDEC Device ID: Memory type and Capacity */
#define JEDEC_W25Q16_BV_CL_CV   (0x4015) /* W25Q16BV W25Q16CL W25Q16CV  */
#define JEDEC_W25Q16_DW         (0x6015) /* W25Q16DW  */
#define JEDEC_W25Q32_BV         (0x4016) /* W25Q32BV */
#define JEDEC_W25Q32_DW         (0x6016) /* W25Q32DW */
#define JEDEC_W25Q64_BV_CV      (0x4017) /* W25Q64BV W25Q64CV */
#define JEDEC_W25Q64_DW         (0x4017) /* W25Q64DW */
#define JEDEC_W25Q128_BV        (0x4018) /* W25Q128BV */

#define JEDEC_WRITE_ENABLE           0x06
#define JEDEC_WRITE_DISABLE          0x04
#define JEDEC_READ_STATUS            0x05
#define JEDEC_WRITE_STATUS           0x01
#define JEDEC_READ_DATA              0x03
#define JEDEC_FAST_READ              0x0b
#define JEDEC_DEVICE_ID              0x9F
#define JEDEC_PAGE_WRITE             0x02
#define JEDEC_SECTOR_ERASE           0x20

#define JEDEC_STATUS_BUSY            0x01
#define JEDEC_STATUS_WRITEPROTECT    0x02
#define JEDEC_STATUS_BP0             0x04
#define JEDEC_STATUS_BP1             0x08
#define JEDEC_STATUS_BP2             0x10
#define JEDEC_STATUS_TP              0x20
#define JEDEC_STATUS_SEC             0x40
#define JEDEC_STATUS_SRP0            0x80

#define DUMMY_BYTE     0xFF			 // 空字节.

// PA4: SPI1_NSS
#define W25QXX_CS_LOW()      GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET)
#define W25QXX_CS_HIGH()     GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_SET)

static flash_info_t flash_info;
static uint8_t Flash_ReadID ( jedec_id_t *id );
static uint8_t Flash_SendByte ( uint8_t byte );
static void Flash_WaitForEnd (void);


//---------------------------- function ------------------------------//
void Flash_Init(void)
{
	jedec_id_t flash_id;
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;

	// GPIO & SPI1 rcc open
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_SPI1, ENABLE);
	
	//SPI GPIO Configuration
	GPIO_PinAFConfig ( GPIOA, GPIO_PinSource5, GPIO_AF_SPI1 );
    GPIO_PinAFConfig ( GPIOA, GPIO_PinSource6, GPIO_AF_SPI1 );
    GPIO_PinAFConfig ( GPIOA, GPIO_PinSource7, GPIO_AF_SPI1 );

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;		// 复用
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		// 推挽输出
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;		// 下拉
    GPIO_Init ( GPIOA, &GPIO_InitStructure );

	//flash SPI CS
    GPIO_InitStructure.GPIO_Pin             = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode            = GPIO_Mode_OUT ;   // 输出
    GPIO_InitStructure.GPIO_OType           = GPIO_OType_PP;	// 推挽
    GPIO_InitStructure.GPIO_PuPd            = GPIO_PuPd_UP;		// 上拉
    GPIO_InitStructure.GPIO_Speed           = GPIO_Speed_2MHz;
    GPIO_Init ( GPIOA, &GPIO_InitStructure );
	
	//SPI configuration
    SPI_I2S_DeInit ( SPI1 );
    SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;	// 设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
    SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;					// 设置SPI工作模式:设置为主SPI
    SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;					// 设置SPI的数据大小:SPI发送接收8位帧结构
    SPI_InitStructure.SPI_CPOL              = SPI_CPOL_High;					// 选择了串行时钟的稳态:时钟悬空高
    SPI_InitStructure.SPI_CPHA              = SPI_CPHA_2Edge;					// 数据捕获于第二个时钟沿
    SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;						// NSS信号由硬件(NSS管脚)还是软件(使用SSI位)管理:内部NSS信号有SSI位控制
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;			// 定义波特率预分频的值:波特率预分频值为 16
    SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;					// 指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI_InitStructure.SPI_CRCPolynomial     = 7;								// CRC值计算的多项式
    SPI_Init ( SPI1, &SPI_InitStructure );
    SPI_Cmd ( SPI1, ENABLE );
    W25QXX_CS_HIGH();
	
	/* Select the FLASH: Chip Select low */    
	W25QXX_CS_LOW();
	/* Send "0xff " instruction */
    Flash_SendByte ( DUMMY_BYTE );
	
	W25QXX_CS_HIGH();

	/* Read Flash Id */
    Flash_ReadID ( &flash_id );

	if(flash_id.Manufacturer == JEDEC_MANUFACTURER_WINBOND)
	{
		flash_info.sector_size = 4096;                         /* Page Erase (4096 Bytes) */
		if(flash_id.Capacity == (JEDEC_W25Q128_BV & 0xff))
		{
			w25qxx_debug ( "W25Q128_BV detection\r\n" );
            flash_info.sector_count = 4096;                        /* 128Mbit / 8 / 4096 = 4096 */
		}
		else if(flash_id.Capacity == (JEDEC_W25Q64_DW & 0xff))
		{
            w25qxx_debug ( "W25Q64_DW or W25Q64_BV or W25Q64_CV detection\r\n" );
			flash_info.sector_count = 2048;
		}
		else if(flash_id.Capacity == (JEDEC_W25Q32_DW & 0xff))
		{
			w25qxx_debug ( "W25Q32_DW or W25Q32_BV detection\r\n" );
			flash_info.sector_count = 1024;
		}
		else if(flash_id.Capacity == (JEDEC_W25Q16_DW & 0xff))
		{
			w25qxx_debug ( "W25Q16_DW or W25Q16_BV detection\r\n" );
			flash_info.sector_count = 512;
		}
		else
		{
			w25qxx_debug ( "error flash capacity\r\n" );
            flash_info.sector_count = 0;
		}
		
		// flash 容量   
		flash_info.capacity = flash_info.sector_size * flash_info.sector_count;
	}
	else 
	{
		w25qxx_debug ( "Unknow Manufacturer ID!%02X\r\n", flash_id.Manufacturer );
        flash_info.initialized = 0;
        return;
	}
	   
	flash_info.initialized = 1;
}

/***************************************************************************
* 原型 Prototype: static uint8_t Flash_SendByte (uint8_t byte)
* 功能 Function : Flash_SendByte
* 参数 Parameter: uint8_t byte
* 返回值 Returned value: uint8_t 返回从 SPI 总线上读取的字节
****************************************************************************/
static uint8_t Flash_SendByte (uint8_t byte)
{
    /* Loop while DR register in not emplty */
    while ( SPI_I2S_GetFlagStatus ( SPI1, SPI_I2S_FLAG_TXE ) == RESET );

    /* Send byte through the SPI1 peripheral */
    SPI_I2S_SendData ( SPI1, byte );

    /* Wait to receive a byte */
    while ( SPI_I2S_GetFlagStatus ( SPI1, SPI_I2S_FLAG_RXNE ) == RESET );

    /* Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData (SPI1);
}

/***************************************************************************
* 原型 Prototype: uint8_t Flash_ReadID ( jedec_id_t *id )
* 功能 Function : Reads FLASH identification.
* 参数 Parameter: jedec_id_t *id
* 返回值 Returned value: Manufacturer id
****************************************************************************/
uint8_t Flash_ReadID ( jedec_id_t *id )
{
	uint8_t *recv_buffer = ( uint8_t* ) id;

    /* Select the FLASH: Chip Select low */
    W25QXX_CS_LOW();

    /* Send "RDID " instruction */
    Flash_SendByte ( JEDEC_DEVICE_ID );

    /* Read a byte from the FLASH */
    *recv_buffer++ = Flash_SendByte ( DUMMY_BYTE );

    /* Read a byte from the FLASH */
    *recv_buffer++ = Flash_SendByte ( DUMMY_BYTE );

    /* Read a byte from the FLASH */
    *recv_buffer++ = Flash_SendByte ( DUMMY_BYTE );

    /* Deselect the FLASH: Chip Select high */
    W25QXX_CS_HIGH();
	
	return id->Manufacturer;
}

/***************************************************************************
* 原型 Prototype: static void Flash_WriteEnable (void)
* 功能 Function : Flash_WriteEnable
* 参数 Parameter: none
* 返回值 Returned value: none
****************************************************************************/
static void Flash_WriteEnable (void)
{
    /* Select the FLASH: Chip Select low */
    W25QXX_CS_LOW();
    /* Send Write Enable instruction */
    Flash_SendByte ( JEDEC_WRITE_ENABLE );
    /* Deselect the FLASH: Chip Select high */
    W25QXX_CS_HIGH();
}

/***************************************************************************
* 原型 Prototype: void Flash_SectorErase (uint32_t address, uint8_t state)
* 功能 Function : Erases the specified FLASH sector. 擦除指定的扇区.
* 参数 Parameter: uint32_t address, uint8_t state
* 返回值 Returned value: none
****************************************************************************/
void Flash_SectorErase (uint32_t address, uint8_t state)
{
    Flash_WriteEnable();
    /* Select the FLASH: Chip Select low */
    W25QXX_CS_LOW();
    /* Send Sector Erase instruction */
    Flash_SendByte ( JEDEC_SECTOR_ERASE );
    /* Send SectorAddr high nibble address byte */
    Flash_SendByte ( ( address & 0xFF0000 ) >> 16 );
    /* Send SectorAddr medium nibble address byte */
    Flash_SendByte ( ( address & 0xFF00 ) >> 8 );
    /* Send SectorAddr low nibble address byte */
    Flash_SendByte ( address & 0xFF );
    /* Deselect the FLASH: Chip Select high */
    W25QXX_CS_HIGH();

    /* Wait the end of Flash writing */
    if ( state )
    {
        Flash_WaitForEnd();
    }
}

static void Flash_WaitForEnd (void)
{
    u8 FLASH_Status = 0;

    /* Loop as long as the memory is busy with a write cycle */
    do
    {
        /* Select the FLASH: Chip Select low */
        W25QXX_CS_LOW();
        /* Send "Read Status Register" instruction */
        Flash_SendByte ( JEDEC_READ_STATUS );
        /* Send a dummy byte to generate the clock needed by the FLASH
        and put the value of the status register in FLASH_Status variable */
        FLASH_Status = Flash_SendByte ( DUMMY_BYTE );
        /* Deselect the FLASH: Chip Select high */
        W25QXX_CS_HIGH();
    }
    while ( FLASH_Status & JEDEC_STATUS_BUSY );
}


