《OpenCV3 编程入门》 一书的核心函数

| 函数名称     | 用途     |
| :------------- | :------------- |
| imread         | 用于读取文件中的图片到 OpenCV 中       |
| imshow         | 在指定的窗口显示一幅图像               |
| namedwindow    | 用于创建一个窗口                      |
| imwrite        | 输出图像到文件                        |
| createTrackbar | 用于创建一个可以调整数值的轨迹条        |
| getTrackbarPos | 用于获取轨迹条的当前位置               |
| SetMouseCallback| 为指定的窗口设置鼠标回调函数          |
| Mat::Mat()     | Mat 类的构造函数                      |
| Mat::Create()  | Mat 类的成员函数, 可用于 Mat 类的初始化操作|
| Point 类       | 用于表示点的数据结构                    |
| Scalar 类      | 用于表示颜色的数据结构                 |
| Size 类        | 用于表示尺寸的数据结构                 |
| Rect 类        | 用于表示矩形的数据结构                 |
| CvtColor()     | 用于颜色空间转换                       |
| line           | 绘制直线                             |
| ellipse        | 绘制椭圆                             |
| rectangle      | 绘制矩形                             |
| circle         | 绘制圆                               |
| fillPoly       | 绘制填充的多边形                      |
| addWeighted    | 计算两个数组(图像阵列)的加权和         |
| split          | 将一个多通道的数组分离成一个单通道的数组|
| merge          | 将多个数组组合合并成一个多通道的数组    |
| dft            | 对一维或者二维浮点数数组进行正向或反向离散傅里叶变换|
| getOptimaIDFTSize| 返回给定向量尺寸的傅里叶最优尺寸大小  |
| copyMakeBorder | 扩充图像边界                          |
| magnitude      | 计算二维矢量的幅值                     |
| log            | 计算每个数组元素绝对值的自然对数        |
| normalize      | 进行矩阵归一化                        |
| FileStorage 类 | 进行文件操作的类                       |
| boxFilter      | 使用方框滤波来模糊一张图片             |
| blur           | 对输入的图像进行均值滤波操作           |
| GaussianBlur   | 使用高斯滤波器来模糊一张图片           |
| medianBlur     | 使用中值滤波来模糊一张图片             |
| bilateralFilter| 使用双边滤波器来模糊一张图片           |
| dilate         | 使用像素邻域内的局部极大运算符来膨胀一张图片|
| erode          | 使用像素邻域内的局部极小运算符来腐蚀一张图片|
| morphologyEx   | 利用基本的膨胀和腐蚀技术, 来执行更加高级形态学变换, 如开闭运算、形态学梯度、顶帽、黑帽等, 也可以实现最基本的图像膨胀和腐蚀。|
| floodFill      | 用指定的颜色从种子点开始填充一个连接域, 实现漫水填充算法|
| pyrUp          | 向上采样并模糊一张图片, 说白了就是放大一张图片|
| pyrDown        | 向下采样并模糊一张图片, 说白了就是缩小一张图片|
| Threshold      | 对单通道数组应用固定阈值操作            |
| adaptiveThreshold| 对矩阵采用自适应阈值操作              |
| Canny          | 利用 Canny 算子来进行图像的边缘检测     |
| Sobel          | 使用扩展的 Sobel 算子, 来计算一阶、二阶、三阶或混合图像差分|
| Laplacian      | 计算出图像经过拉普拉斯变换后的结果       |
| Scharr         | 使用 Scharr 滤波器运算符计算 x 或 y 方向的图像差分 |
| HoughLines     | 找出采用标准霍夫变换 (PPHT) 来找出二值图像中的直线  |
| remap          | 根据指定的映射形式, 将源图像进行重映射几何变换      |
| warpAffine     | 依据公式对图像做仿射变换                           |
| getRotationMatrix2D| 计算二维旋转变化矩阵                          |
| equalizeHist   | 实现图像的直方图均衡化                            |
| findContours   | 在二值图像中寻找轮廓                              |
| drawContours   | 在图像中绘制外部或内部轮廓                        |
| convexHull     | 寻找图像点集中的凸包                              |
| boundingRect   | 计算并返回指定点集最外面 (up-right) 的矩形边界     |
| minAreaRect    | 寻找可旋转的最小面积的包围矩形                     |
| minEnclosingCircle| 利用一种迭代算法, 对给定的 2D 点集, 寻找面积最小的可包围他们的圆形|
| fitEllipse     | 用椭圆拟合二维点集                                |
| approxPolyDP   | 用指定精度逼近多边形曲线                           |
| moments        | 计算多边形和光栅形状的最高达三阶的所有矩(轮廓矩)     |
| contourArea    | 计算整个轮廓或者部分轮廓的面积                      |
| arcLenght      | 计算封闭轮廓的周长或者曲线的长度                    |
| watershed      | 实现分水岭算法                                    |
| inpaint        | 进行图像修补, 从扫描的照片中清除灰尘和划痕, 或者从静态图像或视频中去除不需要的物体|
| calcHist       | 计算一个或者多个阵列的直方图                        |
| minMaxLoc      | 在数组中找到全局最小值和最大值                      |
| compareHist    | 对两幅直方图进行比较                               |
| calcBackProject| 计算直方图的反向投影                               |
| mixChannels    | 由输入参数拷贝某通道到输出参数特定的通道中           |
| matchTemplate  | 匹配出和模版重叠的图像区域                          |
| ComerHarris    | 运行 Harris 角点检测算子来进行角点检测              |
| goodFeatureToTrack| 结合 Shi-Tomasi 算子确定图像的强角点            |
| cornerSubPix   | 寻找亚像素角点位置                                 |
| SURF 类、SurfFeatureDetector 类、SurDescriptorExtractor 类| 三者等价, 同用于在 OpenCV 中进行 SURF 特征检测|
| drawKeypoint   | 绘制关键点                                        |
| drawMatches    | 绘制出相匹配的两个图像的关键点                      |
| KeyPoint 类    | 用于便是特征点的信息                               |
| BruteForceMatcher 类| 进行暴力匹配相关的操作                        |
| FlannBasedMatcher 类| 实现 FLANN 特征匹配                          |
| DescriptorMatcher::match| 从每个描述符查询集中找到最佳匹配           |
| findHomography | 找到并返回源图像和目标图像之间的透视变换 H           |
| perspectiveTransform | 进行向量透视矩阵变换                         |
| ORB 类、OrbFeatureDetector 类、OrbDescriptorExtractor 类 | 三者等价, 同用于在 OpenCV 中进行 ORB 特征检测 |


# Mat 类函数
Mat 类作为新版 OpenCV 中最核心的数据结构, 有着健全的代码构造。需要学习, Mat 类的构造函数, 析构函数和成员函数。

## 构造函数 Mat::Mat
Mat 类众多的构造函数。
## 析构函数 Mat::~Mat
Mat 的析构函数为 `Mat::~Mat()` 。原型声明如下:

```cpp
c++: Mat::~Mat()
```
Mat 类的析构函数其实就是调用成员函数 `Mat::release()` 进行析构操作。
## Mat 类成员函数
成员函数很多。列表:
