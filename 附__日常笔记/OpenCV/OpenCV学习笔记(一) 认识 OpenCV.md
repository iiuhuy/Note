# 认识 OpenCV

* OpenCV 官网主页 : https://opencv.org
* OpenCV github 主页 : https://github.com/opencv
* OpenCV 中文网 : http://www.opencv.org.cn

# OpenCV 基本架构分析
官网下载 OpenCV , 解压放到 D 盘, 进入到 `...\opencv\build\include` 目录, 可以看到有 `opencv` 和 `opencv2` 两个文件夹。 `opencv` 里面包含了旧版的头文件, 而 `opencv2` 则包含了新版的稳定的 OpenCV2 系列头文件。

`...\opencv\build\include\opencv` 里面 11 个头文件, 大概是 OpenCV 1.0 最核心的, 我们可以理解为一个大组件。

再来看看 `...\opencv\build\include\opencv2` 里面的文件很多, 其中会有一个 `opencv_modules.hpp` 的 hpp 文件, 里面是 OpenCV 所有组件的宏, 具体如下。

```cpp
/*
 *      ** File generated automatically, do not modify **
 *
 * This file defines the list of modules available in current build configuration
 *
 *
*/

#define HAVE_OPENCV_CALIB3D
#define HAVE_OPENCV_CONTRIB
#define HAVE_OPENCV_CORE
#define HAVE_OPENCV_FEATURES2D
#define HAVE_OPENCV_FLANN
#define HAVE_OPENCV_GPU
#define HAVE_OPENCV_HIGHGUI
#define HAVE_OPENCV_IMGPROC
#define HAVE_OPENCV_LEGACY
#define HAVE_OPENCV_ML
#define HAVE_OPENCV_NONFREE
#define HAVE_OPENCV_OBJDETECT
#define HAVE_OPENCV_OCL
#define HAVE_OPENCV_PHOTO
#define HAVE_OPENCV_STITCHING
#define HAVE_OPENCV_SUPERRES
#define HAVE_OPENCV_TS
#define HAVE_OPENCV_VIDEO
#define HAVE_OPENCV_VIDEOSTAB
```

按照宏定义的顺序依次介绍。如下:

* 1. 「 calib3d 」 Calibration(校准) 和 3D 这两个词组合缩写。 该模块主要是相机校准和三维重建相关的内容, 包括基本的多视角几何算法、单个立体摄像头标定、物体姿态估计、立体相似性算法、3D 信息的重建等。

* 2. 「 contrib 」 contributed/Experimental Stuf 的缩写。 该模块包含了一些近期添加的可选性功能, 不用去多管, 例如新增的 人脸识别、立体匹配、人工视网膜模型等技术。

* 3. 「 core 」核心功能模块, 包含了下面的内容。
    * OpenCV 基本数据结构。
    * 动态数据结构。
    * 绘图函数。
    * 数组操作相关函数。
    * 辅助功能与系统函数和宏。
    * 与 OpenGL 的互操作。

* 4. 「 imgproc 」 image 和 process 两个单词的缩写组合。 图像处理模块, 包含以下内容。
    * 线性和非线性的图像滤波。
    * 图形几何变换。
    * 其他 (Miscellaneous) 图像转换。
    * 直方图相关。
    * 结构分析和形状描述。
    * 运动分析和对象跟踪。
    * 特征检测。
    * 目标检测等内容。

* 5. 「 features2d 」 Features2D, 即 2D 功能框架, 包含如下内容。
    * 特征检测和描述。
    * 特征检测器 (Feature Detectors) 通用接口。
    * 描述符提取器 (Descriptor Extractors) 通用接口。
    * 描述符匹配器 (Descriptor Matchers) 通用接口。
    * 通用描述符 (Generic Descriptor) 匹配器通用接口。
    * 关键点绘制函数和匹配功能绘制函数。

* 6.「 flann 」 Fast Library for Approximate Nearest Neighbors, 高维的近似近邻快速搜索算法库, 包含以下两个部分:
    * 快速近似最近邻搜索。
    * 聚类。

* 7. 「 gpu 」运用 GPU 加速的计算机视觉模块。

* 8. 「 highgui 」 高层 GUI 图形用户界面, 包含了媒体的输入输出、视频捕捉、图像和视频的编码解码、图形交互界面的接口等内容。

* 9. 「 legacy 」 一些废弃的代码库, 保留下来作为向下兼容, 包含如下内容:
    * 运动分析。
    * 期望最大化。
    * 直方图。
    * 平面细分(C API)。
    * 特征检测和描述 (Feature Detection and Description)。
    * 描述符提取器 (Descriptor Extractors) 的通用接口。
    * 通用描述符 (Generic Descriptor Matchers) 的常用接口。
    * 匹配器。

* 10. 「 ml 」Machine Learning, 机器学习模块, 基本上是统计模型和分类算法, 包含如下内容：
    * 统计模型 (Statistical Models)。
    * 一般贝叶斯分类器 (Normal Bayes Classifier)。
    * K-近邻 (K-Nearest Neighbors)。
    * 支持向量机 (Support Vector Machines)。
    * 决策树 (Decision Trees)。
    * 提升 (Boosting)。
    * 梯度提高树 (Gradient Boosted Trees)。
    * 随机树 (Random Trees)。
    * 超随机树 (Extremely randomized trees)。
    * 期望最大化 (Expectation )。
    * 神经网络 (Neural Networks)。
    * MLData 。

* 11. 「 nonfree 」 一些专利的算法模块, 包含特征检测和 GPU 相关的内容, 最好不要商用。

* 12. 「 objdetect 」 目标检测模块, 包含 Cascade Classification(级联分类) 和 Latent SVM 这两个部分。

* 13. 「 ocl 」 OpenCL-accelerated Computer Vision, 运用 OpenCL 加速的计算机视觉组件模块。

* 14. 「 photo 」 Computational Photography, 包含了图像修复和图像去噪两部分。

* 15. 「 stiching 」 images stitching, 图像拼接模块, 包含以下部分:
    * 拼接流水线。
    * 特点寻找和匹配图像。
    * 估计旋转。
    * 自动校准。
    * 图片歪斜。
    * 接缝估测。
    * 曝光补偿。
    * 图片混合。

* 16. 「 superres 」 SuperResolution, 超分辨率技术的相关功能模块。

* 17. 「 ts 」 OpenCV 测试相关代码, 不用去管。

* 18. 「 video 」 视频分析组件, 该模块包含运动估计、背景分离、对象跟踪等视频处理相关内容。

* 19. 「 Videostab 」 Video stabilization, 视频稳定相关的组件, 官方文档中没有多做介绍, 不用管它。

这样一来, 对 OpenCV 的模块框架就有了一定的认识, 其实就是很多个模块组合起来的一个 软件包, 也叫 SDK (Software Development Kit, 软件开发工具包) 并没有多稀奇。

OpenCV 2.0 的发布也就意味着 OpenCV2 时代的来临。 2 带来了全新的 C++ 接口, 同时新增了新的平台支持, 包括 iOS 和 Android, 通过 CUDA 和 OpenCL 实现了 GPU 加速, 为 Python 和 Java 用户提供了接口。都说稳定易用的 **OpenCV 2.4.x** 。

# 架构的改变

然而随着功能的增加, OpenCV 主体集成了各种各样的功能模块, 变得越来越臃肿。 这时, 3.0 的出现, 就是为了造福人类 `^_^`。 OpenCV3 决定像其他大项目一样, 抛弃整体架构, 使用内核 + 插件的架构形式。

在 [GitHub](https://github.com/opencv) 主页, 可以看到除了一个 `opencv` 仓库, 还有一个 `opencv_contrib` 仓库显示在上方。这个新仓库中有很多好玩的功能 : 包括脸部识别和文本探测, 以及文本识别、新的边缘检测器、充满艺术感的图像修复、深度地图处理、新的光流和追踪算法等。

## opencv 和 opencv_contrib 仓库的区别

* 1. 都由 OpenCV 官网开发团队持续集成系统维护, 虽然可能新的仓库很多功能不稳定。

* 2. opencv 仓库在 GitHub 中由 Itseez 提供, 其有着非常稳定的 API 以及少部分的创新。

* 3. opencv_contirb 仓库是大多数实验性代码放置的地方, 一些 API 可能会有改变, 一直会欢迎广大开发者们贡献新的精彩算法。

* 4. opencv_contirb 中这些额外模块可以在 CMake 中使用 `OPENCV_EXTRA_MODULES_PATH=/modules` 传递给 CMake 文件, 和 OpenCV3 主体中的代码一起编译运行。

* 5. opencv_contirb 的文档是自动生成的, 在 GitHub 仓库 readme.md 也包含了,  https://docs.opencv.org/master/ 。

# 实践

将 opencv2.4.13 下载到电脑, 直接解压放到 D 盘 根目录, 使用了 浅墨的 [HelloOpenCV](http://download.csdn.net/download/zhmxy555/6954393) 工程项目。 需要注意, 工程下载过来, 还需要根据自己的电脑配置环境变量, 项目里面需要配置通用属性。

通用属性配置 :
VC++ Directories , 配置 Include 目录和 Library 目录。

链接库输入配置: Linker->Input 输入一堆 ``.lib`
2.4.13 输入如下。

```2.4.13
opencv_calib3d2413d.lib
opencv_contrib2413d.lib
opencv_core2413d.lib
opencv_features2d2413d.lib
opencv_flann2413d.lib
opencv_gpu2413d.lib
opencv_highgui2413d.lib
opencv_imgproc2413d.lib
opencv_legacy2413d.lib
opencv_ml2413d.lib
opencv_nonfree2413d.lib
opencv_objdetect2413d.lib
opencv_ocl2413d.lib
opencv_photo2413d.lib
opencv_stitching2413d.lib
opencv_superres2413d.lib
opencv_ts2413d.lib
opencv_video2413d.lib
opencv_videostab2413d.lib

opencv_calib3d2413.lib
opencv_contrib2413.lib
opencv_core2413.lib
opencv_features2d2413.lib
opencv_flann2413.lib
opencv_gpu2413.lib
opencv_highgui2413.lib
opencv_imgproc2413.lib
opencv_legacy2413.lib
opencv_ml2413.lib
opencv_nonfree2413.lib
opencv_objdetect2413.lib
opencv_ocl2413.lib
opencv_photo2413.lib
opencv_stitching2413.lib
opencv_superres2413.lib
opencv_ts2413.lib
opencv_video2413.lib
opencv_videostab2413.lib
```

这样就能跑起来了, 环境变量需要根据自己电脑解压的目录进行设置。
