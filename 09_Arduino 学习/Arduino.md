Arduino 开源硬件

# 01 Arduino UNO R3 

> 参考官网 [Arduino UNO R3 ！](https://www.arduino.cc/en/main/arduinoBoardUno?setlang=cn)

在淘宝上 ¥15.5 买了一块 Arduino UNO R3 的开发板。试着玩玩！
它有 14 个数字输入/输出引脚(其中 6 个可以用作 PWM 输出), 6 个模拟输入, 1 个 16 MHz 的陶瓷谐振器(即晶振), 1 个 USB 连接, 1 个电源插座, 1 个 ICSP 头和 1 一个复位按钮。


概要

* 处理器 ATmega328
* 工作电压 5V
* 输入电压（推荐） 7~12V
* 输入电压（范围） 6~20V
* 数字 IO 脚 14 (其中 6 路作为 PWM 输出）
* 模拟输入脚 6
* IO 脚直流电流 40 mA
* 3.3V 脚直流电流 50 mA
* Flash Memory 32 KB （ATmega328，其中 0.5 KB 用于 bootloader）
* SRAM 2 KB （ATmega328）
* EEPROM 1 KB （ATmega328）
* 工作时钟 16 MHz 

通讯接口

* 串口: ATmega328 内置的 UART 可以通过数字口 0（RX）和 1（TX）与外部实现串口通信；ATmega16U2 可以访问数字口实现 USB 上的虚拟串口。
* TWI（兼容 I2C）接口。
* SPI 接口。

>**目前 Arduino UNO 已成为 Arduino 主推的产品,也是学习用的最佳用板。<国产的兼容版本一般用 CH340 做为 USB 转串口芯片，这一点在安装板子的驱动的时候要注意>**

直接百度 `CH340 驱动 CSDN` 我一般喜欢这样搜。 当然能上 Google 的就不多说了。

参考 [Arduino 教程(入门篇)](http://www.arduino.cn/thread-1008-1-1.html) 和 [在Windows系统上入门Arduino/ Genuino](https://www.arduino.cc/en/Guide/Windows?setlang=cn)


# 02 