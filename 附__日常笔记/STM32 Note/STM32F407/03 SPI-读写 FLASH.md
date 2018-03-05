# SPI 读写 FLASH

>参考 [SPI—读写串行 FLASH](http://www.cnblogs.com/firege/p/5805790.html)!
# SPI 协议简介
SPI 协议是由摩托罗拉公司提出的通讯协议 (Serial Peripheral Interface)，即 **串行外围设备接口**，是一种 **高速全双工** 的通信总线。它被广泛地运用在通讯速率较高的场合。

与 I2C 相比, 体会两种通讯总线的差异以及 EEPROM 存储器与 FLASH 存储器的区别。

## SPI 通讯
> 使用 3 条总线及片选, 3 条总线分别为 SCK、MOSI、MISO。

* (Slave Select): 从设备选择信号, 尝称为片选信号线, 也称为 NSS、CS。当有多个 SPI 从设备的时候与主机相连时, 设备的其他信号线 (含 SCK、MOSI、MISO) 同时并联到相同的 SPI 总线上。 SPI 和 IIC 不同在于, IIC 协议通过设备地址来寻址, 选中总线上的某个设备进行通讯; 而 SPI 协议中没有设备地址, 它使用 NSS(CS) 信号线来寻址, 当主机要选择从设备的时候, 把该设备的 NSS 信号线设置为 **低电平** , 该从设备即被选中, 即片选有效, 接着主机开始与被选中的从设备进行 SPI 通讯。 (所以 SPI 通信以 NSS 线置为低电平为开始信号, 以 NSS 线被拉高为结束信号。)

* SCK (serial clock): 时钟信号线, 用于通讯数据同步。由主机产生, 决定了通讯的速率。

* MOSI (Master Output, Slave Input): 这条线的数据方向为 主机到从机。

* MISO (Master Input, Slave Output): 这条线的数据方向为 从机到主机。

## 通讯时序
> 具体时序图参考 《SPI 总线协议介绍》

MOSI 与 MISO 的信号只在 NSS 为低电平的时候才有效，在 SCK 的每个时钟周期 MOSI 和 MISO 传输一位数据。

在 SCK 的下降沿时刻，MOSI 及 MISO 的数据有效，高电平时表示数据 "1"，为低电平时表示数据"0"。在其它时刻，数据无效，MOSI 及 MISO 为下一次表示数据做准备。

## 通讯模式
> SPI 一共有四种通讯模式

主要的区别就是 总线空闲时 SCK 的时钟状态以及数据采样时刻, 为此引入了 时钟极性 CPOL 和 时钟相位 CPHA。

* 时钟极性 (CPOL) 是指 SPI 通讯设备处于空闲状态。 那就是 SPI 通讯前, NSS 线为高电平 SCK 的状态, CPOL = 0, SCK 在空闲时状态为 低电平;  CPOL = 1, SCK 在空闲时状态为 高电平。

* 时钟相位 (CPHA) 是指数据的采样时刻, 当 CPHA = 0 时, MOSI 或者 MISO 数据线上的信号将会在 SCK 时钟线的 `奇数边沿` 被采样。 当 CPHA = 1 时, 数据线在 SCK 的 `偶数边沿` 采样。

    ![](https://images2015.cnblogs.com/blog/896704/201608/896704-20160825103423417-1300391438.jpg)

* 四种通讯模式如下表

    | SPI 模式 | CPOL | CPHA | 空闲时 SCK 时钟 | 采样时刻 |
    | --- | --- | --- | --- | --- |
    | 0   | 0   | 0   | 低电平 | 奇数边沿 |
    | 1   | 0   | 1   | 低电平 | 偶数边沿 |
    | 2   | 1   | 0   | 高电平 | 奇数边沿 |
    | 3   | 1   | 1   | 高电平 | 偶数边沿 |

   实际采用较多的 **模式 0 ** 和 **模式 3**。

# SPI 特性

* 和 IIC 一样, STM32 芯片也集成了专门用于 SPI 通讯的外设。很多芯片都有这种特性, 例如三星的芯片有的外设集成了打印机的功能。

* STM32 的 SPI 外设还支持 I2S 功能, I2S 功能是一种音频串行通信协议。音频相关的会接触。

SPI 引脚图如下:

  <table style="border-collapse: collapse;" border="0"><colgroup><col style="width: 62px;" /><col style="width: 94px;" /><col style="width: 137px;" /><col style="width: 128px;" /><col style="width: 90px;" /><col style="width: 90px;" /><col style="width: 91px;" /></colgroup>
  <tbody valign="top">
  <tr style="height: 23px; background: #70ad47;">
  <td style="padding-left: 9px; padding-right: 9px; border-top: solid 0.5pt; border-left: solid 0.5pt; border-right: solid 0.5pt;" rowspan="2" valign="middle">
  <p><span style="font-family: 黑体; font-size: 12pt;">引脚</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: solid 0.5pt; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" colspan="6" valign="bottom">
  <p style="text-align: center;"><span style="font-size: 12pt;"><span style="font-family: Times New Roman;">SPI</span><span style="font-family: 黑体;">编号</span></span></p>
  </td>
  </tr>
  <tr style="height: 23px; background: #70ad47;">
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: solid 0.5pt; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 12pt;">SPI1</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 12pt;">SPI2</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 12pt;">SPI3</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 12pt;">SPI4</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 12pt;">SPI5</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 12pt;">SPI6</span></p>
  </td>
  </tr>
  <tr style="height: 23px;">
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: solid 0.5pt; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="middle">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">MOSI</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PA7/PB5</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PB15/PC3/PI3</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PB5/PC12/PD6</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PE6/PE14</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PF9/PF11</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PG14</span></p>
  </td>
  </tr>
  <tr style="height: 23px; background: #ebf1de;">
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: solid 0.5pt; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="middle">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">MISO</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PA6/PB4</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PB14/PC2/PI2</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PB4/PC11</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PE5/PE13</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PF8/PH7</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PG12</span></p>
  </td>
  </tr>
  <tr style="height: 23px;">
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: solid 0.5pt; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="middle">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">SCK</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PA5/PB3</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PB10/PB13/PD3</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PB3/PC10</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PE2/PE12</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PF7/PH6</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PG13</span></p>
  </td>
  </tr>
  <tr style="height: 23px; background: #ebf1de;">
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: solid 0.5pt; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="middle">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">NSS</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PA4/PA15</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PB9/PB12/PI0</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;" valign="bottom">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PA4/PA15</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PE4/PE11</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PF6/PH5</span></p>
  </td>
  <td style="padding-left: 9px; padding-right: 9px; border-top: none; border-left: none; border-bottom: solid 0.5pt; border-right: solid 0.5pt;">
  <p><span style="font-family: Times New Roman; font-size: 10pt;">PG8</span></p>
  </td>
  </tr>
  </tbody>
  </table>

## 通讯过程
主模式收发流程及事件：

* 控制 NSS 信号线, 产生起始信号。

* 把发送的数据写入到 `数据寄存器 DR 中`, 该数据会被存储到发送缓冲区。

* 通讯开始, SCK 时钟开始运行时。 MOSI 把发送缓冲区的数据一位一位的传输出去, MISO 则把数据一位一位的存储进接收缓冲区。

* 当发送完第一帧数据的时候, `状态寄存器 SR ` 中的 `TXE` 标志位会被置 1, 表示传输完一帧, 发送缓冲区已空; 同理, 当接收完一帧数据的时候, `RXNE` 标志位会被置 1, 表示传输完一帧, 接收缓冲区非空。

* 等待到 `TXE` 标志位为 1 时, 若还要继续发送数据, 则再次往 `数据寄存器 DR` 写入数据; 等待到 `RXNE` 标志位为 1 时, 通过读取 `数据急寄存器 DR` 可以获取接收缓冲区中的内容。

### SPI 结构体初始化

初始化结构体定义在 `stm32f4xx_spi.h` 和 `stm32f4xx_spi.c` 中。查看英文注释就知道什么意思了。

```
/**
  * @brief  SPI Init structure definition  
  */

typedef struct
{
  uint16_t SPI_Direction;         // 设置 SPI 的单双向模式

  uint16_t SPI_Mode;              // 设置 SPI 的主/从机端模式

  uint16_t SPI_DataSize;          // 设置 SPI 的数据帧长度, 可选 8/16 位

  uint16_t SPI_CPOL;              // 设置 时钟极性 CPOL, 可选 高/低 电平

  uint16_t SPI_CPHA;              // 设置 时钟相位 CPHA, 可选 奇/偶数边沿采样

  uint16_t SPI_NSS;               // 设置 NSS 引脚由 SPI 硬件控制还是软件控制

  uint16_t SPI_BaudRatePrescaler; // 设置 时钟分频因子, fpclk/分频数 = fsck

  uint16_t SPI_FirstBit;          // 设置 MSB/LSB 先行  

  uint16_t SPI_CRCPolynomial;     // 设置 CRC 校验的表达式
}SPI_InitTypeDef;
```

该结构体每个成员的作用就初始化 SPI 基本设置。

### SPI-读写串行 FLASH
I2C 中, EEPROM 可以单字节的擦写。
使用 FLASH 芯片(型号: W25Q32FVZPIG),  FLASH 的 CS/SCK/SI/SO 分别对应 MCU 的 SPI1 NSS/SCK/MOSI/MISO, 片选 CS/NSS 引脚是一个普通的 GPIO, 使用软件设置即可控。

FLASH 中还有 WP 和 HOLD 引脚, WP 引脚可控制写保护功能, 当该引脚为低电平时, 禁止写入数据。 接 3.3V 电源不使用写保护; HOLD 引脚可用于暂停通讯, 该引脚为低电平时, 暂停通讯, 一样接电源不使用通讯暂停功能。数据输出引脚输出为高阻态, 时钟和数据输入引脚无效。

## 软件设计

可以将 SPI 号、时钟初始化函数、SCK 引脚、MISO 引脚、MOSI 引脚、CS(NSS) 引脚、控制 CS(NSS) 引脚输出高电平/低电平, 都使用宏定义封装起来, 定义 CS(NSS) 引脚输出电平的宏, 以便于配置产生起始信号和停止信号时使用。

* 将 SCK/MOSI/MISO 引脚初始化成复用推挽模式。而 CS(NSS) 引脚由于使用软件控制, 把它配置为普通的推挽输出模式。

* 配置 SPI 模式, 需要根据从机设备(这里是 FLASH W25Q32), 根据芯片的说明支持 SPI 的什么模式, 再进行 `SPI_InitTypeDef` 模式的初始化。 最后再通过 SPI_Cmd() 使能。

### 使用 SPI 发送和接收一个字节的数据
初始化完成后就能使用 SPI 进行通讯了, 复杂的数据通讯都是由单个字节数据收发组成。

```c
#define Dummy_Byte 0xFF

/**
  * @brief 使用 SPI 发送一个字节的数据
  * @param byte：要发送的数据
  * @retval 返回接收到的数据
  */
static uint8_t Flash_SendByte(uint8_t byte)
{
    // 等待 DR register 非空
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    // 通过 SPI1 发送一个字节
    SPI_I2S_SendData(SPI1, byte);

    // wait receive a byte
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    // 从 SPI 总线返回这个字节
    return SPI_I2S_ReceiveData(SPI1);
}

```

根据芯片手册, 将芯片常用的指令编码使用宏封装起来, 需要发送的时候直接使用宏就可以。

### 读 FLASH ID
>根据 "JEDEC" 指令的时序，我们把读取 FLASH ID 的过程编写成一个函数。

```
/* 开始通讯：CS 低电平 */

/* 发送 JEDEC 指令, 读取 ID --- 0x9F */

/* 读取一个字节 */

/* 读取一个字节 */

/* 读取一个字节 */

/* 停止通讯, CS 高电平 */

/* 把数据组合起来, 作为函数的返回值, 或者可以定义一个结构体把 id 值存放到结构体中 */
```

前提是要编写字节收发函数, SPI_FLASH_SendByte。

### FLASH 写使能以及读取当前状态
在向 FLASH 芯片储存矩阵写入数据前, 首先要使能写操作, 通过 `Write Enable` 命令即可写使能。如下：

```c
/**
  * @brief 向 FLASH 发送写使能命令
  * @param none
  * @retval none
  */
static void Flash_Write_Enable(void)
{
    /* 开始通讯, CS 低 */

    SPI_CS_LOW;     // 伪代码

    /* 发送写使能命令 */
    Flash_SendByte(JEDEC_WRITE_ENABLE);   // 发送 0x06 根据手册

    /* 通讯结束, CS 高 */
    SPI_CS_HIGH;    // 伪代码
}
```

和 EEPROM 一样, 由于 FLASH 芯片向内部存储矩阵写入数据需要消耗一定的时间, 并不是在总线借宿的一瞬间完成的, 所以在写操作后需要确认 FLASH `空闲` 时才能再次写入。 FLASH 芯片中定义了一个 状态寄存器, 见手册。 我们只需要判断这个状态寄存器的第 0 位 `BUSY`, 当这个位位 1, 表明 FLASH 芯片处于忙碌状态, 可能正在进行 `擦除` 或者 `数据写入` 的操作。

只要像 FLASH 芯片发送读状态寄存器的指令,  FLASH 芯片就会持续向主机返回最新的状态寄存器的内容, 直到收到 SPI 通讯的停止信号。

所以我们需要编写一个具有等待 FLASH 芯片写入结束功能的函数。

```c
// WIP(BUSY) 标志, FLASH 内部正在写入
#define WIP_Flag  0x01    // 来自手册

static void Flash_WriteForEnd(void)
{
    u8 FLASH_Flag = 0;

    do
    {
        CS_LOW;
        Flash_SendByte(RedStatusReg);   // 发送读取状态寄存器命令
        FLASH_Flag = Flash_SendByte(DUMMY_BYTE);    // 读取 FLASH  芯片的状态寄存器
        CD_HIGH;
    } while(FLASH_Flag & WIP);          // 等待写入完成
}
```

这个函数作用就是, 发送读 寄存器状态的指令编码 后, 在 while 循环里持续获取寄存器的内容并检验它的 `WIP` 标志位, 一直等待该置位表示写入结束时才退出本函数. 以便于后面的 Flash 芯片的数据通讯正常。

### FLASH 扇区擦除
由于 FLASH 存储器的特性, 决定了它只能把原来为 1 的数据改为 0, 而原来为 0 的数据位不能直接改写为 1, 所以涉及到了数据擦除的概念。在写入之前, 必须 要对目标存储矩阵进行擦除操作, 把矩阵中的数据位擦除为 1, 在数据写入的时候, 如果要存储数据 1, 那就不修改矩阵, 在需要存储数据 0 时, 才更改该位。

通常的擦除操作都是多个字节进行, 看芯片支持什么擦除方式。 例如: `扇区擦除`、`块擦除`、`整片擦除`。

| 擦除单位 | 大小     |
| :------------- | :------------- |
| 扇区擦除 (Sector Erase)      | 4 KB      |
| 块擦除 (Block Erase)         | 64 KB     |
| 整片擦除 (Chip Erase)        | 整个芯片完全擦除|

一个块包含了 16 个扇区, 使用扇区擦除指令 `Sector Erase` 可控制 FLASH 芯片开始擦写。根据时序得知:

扇区擦除指令的第一个字节为 **指令编码**, 紧接着发送 3 个字节用于表示要擦除的存储矩阵地址。 在扇区擦除指令前需要先发送 `写使能` 指令, 发送扇区擦除指令后, 通过读取寄存器状态等待扇区擦除操作结束完毕。 如下:

```c
/**
  * @brief 擦除 FLASH 扇区
  * @param SectorAddr：要擦除的扇区地址
  * @retval 无
  */

void Flash_SectorErase(uint32_t address, uint32_t address)
{
    Flash_Write_Enable();     // FLASH 写使能

    SPI_CS_LOW();             // SPI_CS_LOW

    Flash_SendByte(SECTOR_ERASE);   // 发送扇区擦除指令 0x20

    Flash_SendByte((address & 0xFF0000) >> 16);    // 发送擦除扇区地址 高位
    Flash_SendByte((address & 0x00FF00) >> 8);     // 发送擦除扇区地址 中位
    Flash_SendByte(address & 0xFF);                // 发送擦除扇区地址 低位

    SPI_CS_HIGH();            // SPI_CS_HIGH

    if (state)
    {
        Flash_WriteForEnd();  // 等待擦除完毕
    }
}
```
### FLASH 页写入
扇区被擦除完后, 就能写入数据。 与 EEPROM 类似, FLASH 芯片也有页写的命令, 使用页写入命令最多可以一次向 FLASH 传输 256 个字节的数据, 这就是一页的大小。 需要看时序, 第一个字节 `页写入指令` 编码, 2~4 个字节为要写入的 `地址A`, 接着是要写入的内容, 最多可以发送 256 个字节数据, 这些数据都会从 地址A 开始, 按顺序写入到 FLASH 存储矩阵。 如果数据超过 256 个,那么会覆盖前面发送的数据。

和擦除指令不同的是, 页写入指令的地址并不要求按 256 字节对齐, 只需要确认目标存储单元擦除状态即可(就是被擦除后没有被写入过)。 所以, 对于 `地址 xx` 执行页写入指令后, 发送了 200 个字节数据后终止通讯, 下一次再执行页写入指令, 从`地址 (xx+200)` 开始写入 200 个字节也是没有问题的(小于 256 均可)。 在实际应用中由于基本擦除单元是 4KB, 一般都是以扇区为单位进行读写。

把页写入时序封装成函数, 如下:

```c
/**
  * @brief 对 FLASH 按页写入数据, 调用本函数写入数据前需要擦除扇区
  * @param pBuffer    要写入数据的指针
  * @param WriteAddr  写入地址
  * @param NumByteToWrite   写入数据长度, 必须小于等于页大小
  * @retval 无
  */
void Flash_PageWrite (uint32_t address, uint8_t* buffer,  uint32_t lenght)
{
    Flash_WriteEnable();			// 写使能
    /* Select the FLASH: Chip Select low */
    W25QXX_CS_LOW();				  // CS_LOW
    /* Send "Write to Memory " instruction */
    Flash_SendByte (PAGE_WRITE);	// 发送写指令  0x02
    /* Send WriteAddr high nibble address byte to write to */
    Flash_SendByte ( ( address & 0xFF0000 ) >> 16 );
    /* Send WriteAddr medium nibble address byte to write to */
    Flash_SendByte ( ( address & 0xFF00 ) >> 8 );
    /* Send WriteAddr low nibble address byte to write to */
    Flash_SendByte ( address & 0xFF );

//    if(NumByteToWrite > SPI_FLASH_Per) errors

    /* while there is data to be written on the FLASH */
    while (lenght--)    // 写入数据
    {
        /* Send the current byte */
        Flash_SendByte ( *buffer );   // 发送前要写入的数据
        /* Point on the next byte to be written */
        buffer++;                     // 指向下一个字节的数据
    }

    /* Deselect the FLASH: Chip Select high */
    W25QXX_CS_HIGH();

    /* Wait the end of Flash writing */
    Flash_WaitForEnd();       // 查询 FLASH 状态, 等待 FLASH 写完成.
}
```    

### 从 FLASH 读取数据
相对于写入, 从 FLASH 中读取数据要简单些, 读取指令使用 `Read Data` 即可, 参考时序:
发送了指令编码及要读的起始地址后,  FLASH 芯片就会按地址递增的方式返回存储矩阵的内容, 读取的数据量没有限制, 只要没有停止通讯, FLASH 就会一直返回数据。 如下:

```c
/**
  * @brief  Reads a block of data from the FLASH.
  * @param buffer : pointer to the buffer that receives the data read
  *                  from the FLASH.
  * @param address : FLASH's internal address to read from.
  * @param lenght : number of bytes to read from the FLASH.
  * @retval : None
  */
void FLASH_PageRead(uint32_t address, uint8_t* buffer, uint32_t lenght)
{
    SPI_CS_LOW;

    Flash_SendByte(Read_Data);    // 发送读数据指令  0x03

    Flash_SendByte((address & 0xFF0000) >> 16);   
    Flash_SendByte((address & 0xFF00) >> 8);
    Flash_SendByte(address & 0xFF);

    while(lenght --)              // 读取数据
    {
        *buffer = Flash_SendByte(DUMMY_BYTE);
        buffer ++ ;
    }

    SPI_CS_HIGH;
}
```
