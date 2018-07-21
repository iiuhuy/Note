# 最后再总结一下 Visual Studio 一些好用的插件
先看看知乎各位的回答 [Visual Studio 有哪些好用的插件？](https://www.zhihu.com/question/20617534) 。

# 0x01 插件
在官网能找到很多插件, 根据自己的需求和爱好来适配。
## 0x01 Image Watch
上面 链接回来里面就有人提到了这个插件。
是一个 能够在调试 OpenCV 程序的时候, 看到内存中的图像。对跟踪 bug 和理解一段代码非常有帮助。

支持 VS2012、2013、2015, 从 [Visual Studio](https://marketplace.visualstudio.com/items?itemName=VisualCPPTeam.ImageWatch) 下载, 下载完成后直接就能安装。

> 在 Linux 下可以参考这个 https://github.com/cuekoo/GDB-ImageWatch

### 食用方法
支持如下操作 :

* 放大、缩小图像.
* 将图像保存到指定目录.
* 显示图像大小、通道数.
* 拖拽图像.
* 可以查看指定坐标的像素值(按照在内存中的顺序显示)
* Link Views : 所以相同尺寸的图像共享一个视图
* 像素值以 十六进制 显示还是 十进制 显示
* 在 Watch 窗口可对图像进行操作

打开一个工程, 按下 `F5` 进入调试模式, 选择菜单 View -> Other Windows -> Image Watch, 就会出现 Image Watch 窗口。 在 Release 版本下调试, 好像是不能显示图像的。
该窗口左上角有两个单选的按钮。 Locals & Watch, 分别对应两种模式 : Locals 模式和 Watch 模式。 本地的 VS Locals&Watch 模式显示当前范围的变量和值(都是以文本的形式显示出来的), 而 Image Watch 内置了图片查看器。 Watch 模式, 则显示了手动添加的变量。例如定义一个数据结构变量储存 图像。就能在 Watch 窗口显示。

鼠标放到 图片列表上, 点击鼠标右键, 会有其他的功能。可以放大缩小、可以添加到

该插件详细使用介绍请参考 [IMAGE WATCH HELP](https://imagewatch.azurewebsites.net/ImageWatchHelp/ImageWatchHelp.htm).

## 0x02 Color Theme Editor
[Visual Studio 2012 Color Theme Editor](https://marketplace.visualstudio.com/items?itemName=MatthewJohnsonMSFT.VisualStudio2012ColorThemeEditor)

## ClaudiaIDE
这是一个换背景的插件,

# 0x02 快捷键

## 注释快捷键
Visual Studio 2012 的注释快捷键为 : 先按 `Ctrl + k`, 再接着按 `Ctrl + C`。
恢复注释快捷键为 : `Ctrl + K`, 再接着按 `Ctrl + U` 。

这样按觉得很别扭, 所以打算修改一下快捷键方式。

TOOLS -> Options -> Environment -> Keyboard -> 搜 `Comments`。 接着更改就好了。
