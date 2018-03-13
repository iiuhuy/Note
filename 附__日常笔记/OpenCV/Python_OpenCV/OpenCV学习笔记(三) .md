# 官方例程

## 01 彩色目标追踪: Camshift
根据鼠标框选区域的色度光谱来进行摄像头读入的视频目标跟踪。

## 02 光流: optical flow


## 03 点追踪: lkdemo
程序运行后, 会自动启动摄像头, 按下键盘上的 `r` 键来启动自动点追踪。

## 04 人脸识别: objectDetection
OpenCV 官网有专门的教程和代码讲解其实现的方法。 历程是使用 `objdetect` 模块检测摄像头视频流中的人脸。需要注意的是, 要将 `opencv\source\data\haarcascades` 路径下的 `haarcascade_eye_tree_eyeglasses.xml` 和 `haarcascade_frontalface_alt.xml` 文件复制到源文件一个目录。

## 支持向量机引导
在 OpenCV 的机器学习模块中, 官方准备了两个示例程序。

* 第一个是使用 `CvSVM::train` 函数训练一个 SVM 分类器。
* 第二个是用于讲解在训练数据线性不可分时, 如何定义支持向量机的最优化问题。

# 编译 OpenCV 源代码
下载安装 Cmake https://cmake.org/download/
> 想要在 Windows 平台下生成 OpenCV 的解决方案, 需要 Cmake 这个开源软件。 它是一个跨平台的安装(编译)工具, 能够输出各种各样的 Makefile 或者 Project 文件。

## 使用 CMake 生成 OpenCV 源代码工程的解决方案

### 01 运行 cmake-gui
如果没有和我一样生成快捷图标, 在自己的安装目录下找到 `cmake-gui.exe` , 双击运行。

### 02 指定 OpenCV 的安装路径
点击 `Browse Source` 按钮, 在弹出的对话框中指定 OpenCV 安装时源代码的存储路径。 我的直接就是再 D 盘, 那么路径就是 `D:\opencv\sources`, 可以看到该路径下会有一个名为 `CMakeLists.txt` 的文件, 这就是给 CMake 留下的配置文件。 可以根据这个配置文件, 通过选择不同的编译器, 来生成不同的解决方案,  **Visual Studio** 的编译器对应的就是生成 Visual Studio 版的 `sln` 解决方案。

### 03 指定解决方案的存放路径
点击 `Browse Build` 按钮, 在弹出的对话框中指定存放生成的 opencv 解决方案的路径。

### 04 第一C次 Configure
点击 **Configure** 按钮, 进行第一次配置过程, 我这里选择了 `Visual Studio 11 2012 Win64`, 然后点击 Finish, 然后 CMake 就会自己开始配置源代码。稍等一会就会配置完成, 完成配置后地下会出现 `Configuring done`。 效果如下图 :

![](http://p2dak62rv.bkt.clouddn.com/2018.3.9_1.png)

> 注意用户路径中不能有中文字符, 否则会出现错误。 如果出现这中错误, 需要自己重新修改路径。 再次 `Configure`。

### 05 生成项目成功
点击 `Generate` 按钮, 来生成最终的解决方案。完成会出现 `Generating done`, 表示已经成功。

去到指定的路径下可以看到 `OpenCV.sln` 解决方案。如下图 :

![](http://p2dak62rv.bkt.clouddn.com/2018.3.9_2.png)

## 编译 OpenCV 源代码
打开刚刚目录下生成的 `OpenCV.sln` 解决方案, 一共有 71 个解决方案(版本是 2.4.13)。可以看到如下图 :

![](http://p2dak62rv.bkt.clouddn.com/2018.3.9_3.png)

随意点开一个, 就能看到该方案的结构, 在 `Src` 下就是它的源代码。 从而也可以直接进行 Debug 调试, 按下 F5 , 同时编译器会进行编译, 这时候就是体现电脑性能的时候了, 配置好点的编译会快点。

编译完成后, 有提示 64 个 项目已经编译成功, 同时会出现一个错误, 这个错误是正常的。 原因是 OpenCV 默认将 `ALL_BUILD` 这个项目设为了启动项, 编译成功后, 就会默认运行它, 它本身就不能运行。如下图 :

![]()

只需要指定另外的启动项目即可解决。 如下图 ：

![]()

## 命名规范约定
参考 「 代码大全 (第二版)」, 277 页, 表中的命名规则。

## 授之于鱼, 授之于渔
脱离书本依靠官方文档自学,  总的来说技术文档官方的才是最理想的。浅墨大神的入门书籍也是对照着官方的 doc, opencv_tutorials 来写的。 并且还省略其中一教程, 适合像我这种新手。
