---
title: Keil MDK5 的相关使用
date: 2017-05-11 00:28:55
tags: IDE
---

# 01 keil MDK5 自动补全设置
之前使用 keil4.7 的时候就已经可以自动补全， 现在重新安装了突然不能自动补全， 原来是需要这样配置。
Edit->Configuration


![2017.5.4](http://i.imgur.com/GpVGEtb.png)


# 02 keil STM32 调试， 使用 J-link 下载程序的时候提示 「 flash timerout.reset the target and try it again 」

由于环境没配置好的问题，出现了这个原因， 下面解决了这个问题：

![2017.5.17](http://i.imgur.com/kEHSV2j.png)

然后就可以下载程序进行仿真了。  可以参考这篇 [电子产品世界论坛](http://forum.eepw.com.cn/thread/263327/1) 。



### 本文持续更新中......