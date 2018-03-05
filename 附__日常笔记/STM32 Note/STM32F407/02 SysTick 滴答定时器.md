# 简介
SysTick 在 《STM32xx 中文参考手册》 里面基本没有介绍，其详细介绍，参阅
《STM32F3 与 F4 系列 Cortex M4 内核编程手册》第 230 页。可以利用 STM32 的内部 SysTick
来实现延时，这样既不占用中断，也不占用系统定时器。

SysTick 系统定时器是一个 24bit 的向下递减的计数器，计数器每计数一次的时间为 1/SYSCLK，一般我们设置系统时钟 SYSCLK 等于 168M。当重装载数值寄存器的值递减到 0 的时候，系统定时器就产生一次中断，以此循环往复。

# 01 SysTick 定义&寄存器

时钟树得知 `Systick` 的时钟源可以是 AHB 时钟 HCLK 或者 HCLK/8 ！

SysTick 定义了一个结构体。

```
/** \brief  Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  __IO uint32_t CTRL;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IO uint32_t LOAD;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
  __IO uint32_t VAL;                     /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
  __I  uint32_t CALIB;                   /*!< Offset: 0x00C (R/ )  SysTick Calibration Register        */
} SysTick_Type;
```

## 寄存器

SysTick 系统定时有 4 个寄存器，简要介绍如下。在使用 SysTick 产生定时的时候，只需要配置前三个寄存器，最后一个校准寄存器不需要使用。

| 寄存器名称 | 寄存器描述     |
| ------------- | ------------- |
| CTRL      | SysTick 控制及状态寄存器       |
| LOAD      | SysTick 重装载数值寄存器       |
| VAL       | SysTick 当前数值寄存器         |
| CALIB     | SysTick 校准数值寄存器         |

SysTick 控制及状态寄存器

|位段|名称|类型|复位值|描述|
|---|---|---|---|---|
|16 | COUNTFLAG|R/W|0|如果在上次读取本寄存器后, SysTick 已经计到了 0,则该位为 1。|
|2  |CLKSOURCE|R/W|0|时钟源选择位，0=AHB/8，1= 处理器时钟 AHB|
|1  |TICKINT  |R/W|0|1=SysTick 倒数计数到 0 时产生 SysTick 异常请求，0= 数到 0 时无动作。也可以通过读取 COUNTFLAG 标志位来确定计数器是否递减到 0|
|0  |TICKINT  |R/W|0|SysTick 定时器的使能位|

SysTick 重装载数值寄存器

|位段|名称|类型|复位值|描述|
|---|---|---|---|---|
| 23:0  |RELOAD |R/W|0|当倒数计数至零时，将被重装载的值|

SysTick 当前数值寄存器

|位段|名称|类型|复位值|描述|
|---|---|---|---|---|
|23:0|CURRENT|R/W|0|读取时返回当前倒计数的值，写它则使之清零，同时还会清除在 SysTick 控制及状态寄存器中的 COUNTFLAG 标志。|

SysTick 校准数值寄存器。 就不列出了, 可以查看手册。

SysTick 属于内核的外设，有关的寄存器定义和库函数都在内核相关的库文件 `core_cm4.h` 中。 内核外设的中断优先级由内核 SCB 外设的寄存器 `SHPRx(x=1.2.3)`配置。 这个寄存器在《Cortex-M4 内核编程手册》4.4.8 章节 有介绍。

### SysTick 中断时间的计算
重装载寄存器的值减到 0 的时候,  产生中断。那么中断一次的时间, 就等于 重装载值/时钟频率。 (例如: 168/168MHz) 那么就是 1us 。需要将重装载设置为 168

### SysTick 定时时间计算
设置好中断时间后, 可以设置一个变量 uptimer, 用来记录进入中断的次数， 那么 uptimer 乘上 中断的时间, 就可以计算出定时的时间。

### SysTick 定时函数
参考匿名

### SysTick 中断服务函数

```c
void SysTick_Handler(void)
{

  
}
```
中断复位函数调用了另外一个函数  原型如下

### 简洁的做法
使用了中断，而且经过多个函数的调用，还使用了全局变量，理解起来挺费劲的，其实还有另外一种更简洁的写法。我们知道，systick 的 counter 从 reload 值往下递减到 0 的时候，CTRL 寄存器的位 16:countflag 会置 1，且读取该位的值可清 0，所有我们可以使用软件查询的方法来实现延时。
