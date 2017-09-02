---
title: yocto 入门篇
date: 2017-08-22 23:26:42
tags: yocto 
---

# Yocto

现在做嵌入式, 学习 Linux 和相关知识, 同时接触了 Yocto 项目相关的知识。网上关于 Yocto 的介绍还是很多博客记录的, 但很多都是英文, 也有一些大牛的笔记。对于我这种新手来说, 并不是那么容易懂。

## About Yocto & Why using Yocto
### About Yocto
关于 Yocto , 可以通过这个链接看到 [Yocto Project](https://www.yoctoproject.org/about) 的官网是这样介绍的.

>就是说 Yocto 项目是一个开源协作项目，提供模板，工具和方法，帮助您为嵌入式产品创建自定义的基于 Linux 的系统，而不考虑硬件架构。它成立于 2010 年，作为许多硬件制造商，开源操作系统供应商和电子公司之间的合作，为嵌入式 Linux 开发的混乱带来了一些秩序。

**P.S.**  Yocto 项目有时也被称为 "Umbrella" 项目.

### Why using Yocto
它是一个完整的嵌入式 Linux 开发环境，包含工具 (tools) 、元数据 ( metadata ) 和文档 ( documentation )——你需要的一切。这些免费工具 (包含仿真环境 emulation environments、调试器 debuggers、应用程序开发工具 Application Toolkit Generator) 很容易上手，功能强大，并且它们可以让系统开发以最优化的方式不断前进，而不用担心在系统原形阶段的投资损失。它们允许项目随着时间推移而不断转移，而不会导致您失去优化和投资项目的原型阶段。Yocto 项目促进社区采用这种开放源码技术，使用户能够专注于其特定的产品特性和开发。 

另一个原因应该是 飞思卡尔 已经不再对 LITB 进行维护和更新, 转向 Yocto , 所以说 Yocto 开始不是那么好上手, 但官方也给出强烈的建议使用 Yocto, 毕竟这个项目还是有很多人一起维护的。
 
## Yocto Project 简介
有关 Yocto Project 的详细介绍可以参考： http://www.ibm.com/developerworks/cn/linux/l-yocto-linux/

Yocto Project 的两大主要组件由 Yocto Project 和 OpenEmbedded 项目一起维护，这两个组件是 BitBake 和 OpenEmbedded-Core，前者是构建引擎，后者是运行构建过程所使用的一套核心配方 (recipe)。后面会学习所有项目组件。

作为一个协作项目，Yocto Project 有时也称为 “umbrella” 项目，它吸纳了许多不同的开发流程部分。在整个 Yocto Project 中，这些部分被称为项目，包括构建工具、称为核心配方 的构建指令元数据、库、实用程序和图形用户界面 (GUI)。

### Poky 
Poky是 Yocto Project 的一个参考构建系统,包含 BitBake、OpenEmbedded-Core、一个板级支持包 (BSP) 以及整合到构建过程中的其他任何程序包或层。

Poky 这一名称也指使用参考构建系统得到的默认 Linux 发行版，它可能极其小 (core-image-minimal)，也可能是带有 GUI 的整个 Linux 系统 (core-image-sato)。可以将 Poky 构建系统看作是整个项目的一个参考系统，即运行中进程的一个工作示例。

### 元数据集
元数据集按层进行排列, 这样每层都可以为下面的层提供单独的功能。 基层是 `OpenEmbedded-Core` 或 `oe-core`，提供了所有构建项目的所必须的常见配方、类和相关功能. 可以通过在 `oe-ocore` 之上添加新层来定制构建。

`OpenEmbedded-Core` 由 `Yocto Project` 和 `OpenEmbedded` 项目共同维护。将 `Yocto Project` 与 `OpenEmbedded` 分开的层是 `meta-yocto` 层，该层提供了 Poky 发行版配置和一组核心的参考 BSP。

`OpenEmbedded` 项目本身是一个独立的开源项目，具有可与 `Yocto Project` 交换的配方（大部分）以及与 `Yocto Project` 类似的目标，但是两者具有不同的治理和范围。

### 板级支持包(Board Support Package)
BSP 包含为特定板卡或架构构建 Linux 必备的基本程序包和驱动程序。这通常由生产板卡的硬件制造商加以维护。BSP 是 Linux 操作系统与运行它的硬件之间的接口。注意，您也可以为虚拟机创建 BSP。

### BitBake
BitBake 是一个构建引擎。它读取配方并通过获取程序包来密切关注它们、构建它们并将结果纳入可引导映像。BitBake 由 Yocto Project 和 OpenEmbedded 项目共同维护。
>BitBake is a build engine that follows recipes in a specific format in order to perform sets of tasks. BitBake is a core component of the Yocto Project. 

你可以在 OpenEmbedded GitHub 找到 [Bitbake](https://github.com/openembedded/bitbake) 的开源项目，并且阅读它的源码。 Bitbake 的作用还不远远如此。有兴趣可以深入的去学习它！

### EGLIBC
嵌入式GLIBC（EGLIBC）是GNU C Library（glibc）的一个变种，旨在在嵌入式系统上运行良好。EGLIBC 努力与 glibc 进行源和二进制兼容。EGLIBC 的目标包括减少占用空间，可配置组件，更好地支持交叉编译和交叉测试。

该项目现已完全合并到 GNU C 库中。档案由 Yocto 项目维护：`http://www.eglibc.org`

### HOB
为了让嵌入式 Linux 开发更容易，Yocto Project 提供了几种不同的图形工作方法。项目的一个较新的添加项叫作 Hob，它向 BitBake 和构建过程提供一个图像前端。两者的开发工作仍在继续，包含社区用户研究。

在 Yocto Project 中 Hob 从 2.1 版本后就已经弃用了。你可以使用 Toaster 代替。Hob将仍然可以在Build Appliance中使用,但可能无法正常工作，因为它将不被长期维护。

Build Appliance 是一种虚拟机映像，可让您使用非 Linux 开发系统使用 Yocto Project 构建和引导自定义嵌入式 Linux 映像。不建议将 Build Appliance 用作日常生产开发环境。

> 关于 Build Appliance 参考：https://www.yoctoproject.org/tools-resources/projects 中的 [Build Appliance](https://www.yoctoproject.org/tools-resources/projects/build-appliance)

> 其他相关的就先不介绍了,到官网:https://www.yoctoproject.org/tools-resources 可以看到。

---

# 构建 Linux 发行版
使用 Poky（参考构建系统）构建一个基本的嵌入式 Linux 系统。这里描述的流程构建参考了发行版以及构建该发行版所需的所有工具。如果您愿意的话，也可以下载预编译好的二进制文件，以避免编译的需要。

请阅读官方 [Yocto Project Quick Start Guide](https://www.ibm.com/developerworks/cn/linux/l-yocto-linux/index.html#resources)，翻译成中文的请参考。 [Yotoc Project 快速指南]()

#### Yocto Project books
Submitted by jefro on Mon, 2016-01-04 10:18

* [Embedded Linux Development with Yocto Project](https://www.packtpub.com/application-development/embedded-linux-development-yocto-project)  --by Otavio Salvador and Daiane Agolini
* [Embedded Linux Projects Using Yocto Project Cookbook](https://www.packtpub.com/virtualization-and-cloud/embedded-linux-projects-using-yocto-project-cookbook) --by Alex Vaduva  
* [Learning Embedded Linux using the Yocto Project](https://www.packtpub.com/application-development/learning-embedded-linux-using-yocto-project) --by Alex Gonzales
* [Using Yocto Project with BeagleBone Black](https://www.packtpub.com/hardware-and-creative/yocto-beaglebone) --by H M Irfan Sadiq
* [Yocto for Raspberry Pi](https://www.packtpub.com/hardware-and-creative/yocto-raspberry-pi) --by Pierre-Jean Texier and Petter Mabäcker

>很难找到中文版的书, 我网上找了一下! 
有兴趣的话自己看看，网上直接搜名字还是有 PDF 的, 个人觉得还是看 user manual 或者 Yocto 的官方手册来得快。
PS：坚持看官方文档, 哪怕英文差。 强迫自己, 坚持下去！

