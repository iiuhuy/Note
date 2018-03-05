<!-- !# RT-Thread 论坛  [四轴飞控](https://www.rt-thread.org/qa/forum-33-1.html) 。 -->
<!-- from tianqing su -->

## 问题
>AN0001串口应用指南  之前

* 01 2.1 的消息队列创建结构体都和 3.0 不同
* 02 device 设备创建文档没有
* 03 注册怎样加底层也没有
* 04 device 里面的配置文件
* 没注册，查找设备返回了个 RT_Null

device 设备创建文档
```
static int stm32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct stm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct stm32_uart *)serial->parent.user_data;

    ch = -1;
    if (__HAL_UART_GET_FLAG(uart->huart, UART_FLAG_RXNE) != RESET)
        ch = uart->huart->Instance->DR & 0xff;
    return ch;
}
```


串口注册
> 确保 menuconfig 里面已经开启 serial_device。 具体怎么设置还没懂。
```
int stm32_hw_usart_init(void)
{
    struct stm32_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART1
    huart1.Instance = USART1;

    uart = &uart1;
    uart->huart = &huart1;

    serial1.ops    = &stm32_uart_ops;
    serial1.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&serial1,
                          "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART1 */

#ifdef RT_USING_UART3
    huart3.Instance = USART3;
    hdma_usart3_rx.Instance = DMA1_Stream1;

    uart = &uart3;
    uart->huart = &huart3;
    uart->dma.hdma_usart_rx = &hdma_usart3_rx;

    serial3.ops    = &stm32_uart_ops;
    serial3.config = config;

    /* register UART3 device , we suggest use DMA */

    /* polling mode */
    rt_hw_serial_register(&serial3,
                          "uart3",
                          RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX ,
                          uart);

#endif /* RT_USING_UART3 */

    return 0;
}
```

打开串口对应的宏, 注册。


## RTT

使用 RT-Thread 统一的设备 API 的流程为：注册->打开->读写-关闭。
