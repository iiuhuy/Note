> 来自 [OpenCV—基本矩阵操作与示例](http://blog.csdn.net/iracer/article/details/51296631)
这博主写得挺详细的。
# OpenCV 的基本矩阵操作与示例
OpenCV 中的矩阵操作非常重要。 要熟悉起来！

学习该博主的基本示例:

* 创建与初始化
* 矩阵加减法
* 矩阵乘法
* 矩阵转置
* 矩阵求逆
* 矩阵非零元素个数
* 矩阵均值与标准差
* 矩阵全局极值及位置
* 其他矩阵运算函数列表

## 0x01 创建与初始化矩阵
### 1.1 数据类型

建立矩阵必须要指定矩阵储存的数据类型, 图像处理中常用的几种数据类型如下 :

```cpp
CV_8UC1   // 8 bit 无符号单通道
CV_8UC3   // 8 bit 无符号 3 通道
CV_8UC4   //
CV_32FC1  // 32 bit 浮点型单通道
CV_32FC1  // 32 bit 浮点型 3 通道
```

### 1.2 基本方法
可以通过载入图像来创建 Mat 类型矩阵, 也可以直接手动创建矩阵, 基本方法是指定矩阵尺寸和数据类型:

```cpp
// 1.2 基本方法
	cv::Mat a(cv::Size(5,5), CV_8UC1);		// 单通道
	cv::Mat b = cv::Mat(cv::Size(5,5), CV_8UC3);		// 3 通道每个矩阵元素包含 3 个 uchar 值

	cout << "a = " << endl << a << endl << endl;
	cout << "b = " << endl << b << endl << endl;

	system("color A");
	system("pause");
```

![](http://p2dak62rv.bkt.clouddn.com/2018.3.16_1.png)

3 通道矩阵中, 一个矩阵元素包括 3 个变量。

### 1.3 初始化方法
可以看到上面的矩阵数值并没有初始化, 避免这种情况, 使用 Mat 类的几种初始化创建矩阵的方法 :
```cpp
// 1.3 初始化方法
cv::Mat m_Zeros = cv::Mat::zeros(cv::Size(5,5), CV_8SC1);	// 全零矩阵
cv::Mat m_One = cv::Mat::ones(cv::Size(5,5), CV_8UC1);		// 全 1 矩阵
cv::Mat m_Eye = cv::Mat::eye(cv::Size(5,5), CV_32FC1);		// 对角线为 1 的矩阵

cout << "m_Zeros = " << endl << m_Zeros << endl << endl ;
cout << "m_One = " << endl << m_One << endl << endl ;
cout << "m_Eye = " << endl << m_Eye << endl << endl ;

system("color A");
system("pause");
```

![](http://p2dak62rv.bkt.clouddn.com/2018.3.16_2.png)

## 0x02 矩阵的运算
### 2.1 基本概念
OpenCV 的 Mat 类允许所有的矩阵运算。

### 2.2 矩阵加减法
使用 `+` 或者 `-` 符号进行矩阵加减运算。

```cpp
// 2.2 矩阵加减法
Mat a = Mat::eye(Size(3,2), CV_32F);
Mat b = Mat::ones(Size(3,2), CV_32F);
Mat c = a+b;
Mat d = a-b;

cout << "a" << endl << a << endl << endl ;
cout << "b" << endl << b << endl << endl ;
cout << "c = a+b" << endl << c << endl << endl ;
cout << "d = a-b " << endl << d << endl << endl ;

system("color A");
system("pause");
```

![](http://p2dak62rv.bkt.clouddn.com/2018.3.16_3.png)

### 2.3 矩阵乘法
矩阵与矩阵相乘, 必须满足矩阵相乘的行列数对应规则。

```cpp
// 2.3 矩阵乘法
Mat m1 = Mat::eye(2,3, CV_32F);
Mat m2 = Mat::ones(3,2, CV_32F);
cout << "m1 =" << endl << m1 << endl << endl;
cout << "m2 =" << endl << m2 << endl << endl;

// Scalar by Matrix
cout << "\nm1.*2 = \n" << m1*2 << endl;

// Matrix per element multiplication
cout << "\n(m1+m2).*(m1+m3) = \n" << (m1+1).mul(m1+3) << endl;

// Matrix mutiplication
cout << "\nm1*m2 = \n" << m1*m2 << endl;

system("color A");
system("pause");
```

![](http://p2dak62rv.bkt.clouddn.com/2018.3.16_4.png)

### 2.4 矩阵转置
矩阵转置是将矩阵的行与列顺序对调, 将第几行转变为第几列。OpenCV 通过 Mat 类的 `t()` 函数实现。

```cpp
// 2.4 矩阵转置
Mat m1 = Mat::eye(2,3, CV_32F);
Mat m1_t = m1.t();

cout << "m1 = " << endl << m1 << endl << endl;
cout << "m1t = " << endl << m1_t << endl << endl;

system("color A");
system("pause");
```

![](http://p2dak62rv.bkt.clouddn.com/2018.3.16_5.png)

### 2.5 矩阵求逆
逆矩阵在一些算法中经常出现, 在 OpenCV 中通过 Mat 类的 `inv()` 方法实现。

```cpp
// 2.5 求逆矩阵
Mat me = Mat::eye(5,5, CV_32FC1);
Mat meinv = me.inv();

cout << "me = "<< endl << " "<< me << endl << endl;
cout << "meinv = "<< endl << " " << meinv << endl << endl;

// 单位矩阵的逆就是本身.
system("color A");
system("pause");
```

![](http://p2dak62rv.bkt.clouddn.com/2018.3.16_6.png)

### 2.6 计算矩阵非零元素个数
计算物体的像素或者面积常需要用到矩阵中的非零元素个数, OpenCV 中使用 countNonZero() 函数实现。

```cpp
Mat me = Mat::eye(6,6, CV_32FC1);
int nonZerosNum = countNonZero(me);	// me 为输入矩阵或者图像

cout << "me = " << endl << " " << me << endl << endl;
cout << "me 中非零元素的个数 =" << nonZerosNum << endl << endl;

system("color A");
system("pause");
```

![](http://p2dak62rv.bkt.clouddn.com/2018.3.16_7.png)

### 2.7 均值和标准差
OpenCV 提供了矩阵均值和标准差计算功能, 可以使用 `meanStdDev(src, mean, stddev)` 函数实现

* 参数一 **src**, 输入矩阵或者图像
* 参数二 **mean**, 均值, OutputArray
* 参数三 **stddev**, 标准差, OutputArray

```cpp
Mat me = Mat::eye(5,5, CV_32FC1);
Mat mean;
Mat stddev;

meanStdDev(me, mean, stddev); // me 为定义的对角矩阵
cout << "me = " << endl << " " << me << endl << endl;
cout << "mean = " << endl << " " << mean << endl << endl;
cout << "stddev = " << endl << " " << stddev << endl << endl;

system("color A");
system("pause");
```

单通道运行结果:

![](http://p2dak62rv.bkt.clouddn.com/2018.3.16_8.png)

如果 src 是多通道图像或者多维矩阵, 则函数分别计算不同通道的均值与标准差, 因此返回值 mean 和 stddev 为对应维度的向量。

```cpp
Mat mean3;
Mat stddev3;
Mat m3(cv::Size(5,5), CV_8UC3, Scalar(255,200,100));
cout << "m3 = " << endl << " " << m3 <<endl <<endl;

meanStdDev(m3, mean3, stddev3);
cout << "mean3 = " << endl << " " << mean3 << endl << endl;
cout << "stddev3 = " << endl << " " << stddev3 << endl << endl;

system("color A");
system("pause");
```

多通道运行结果 :
![](http://p2dak62rv.bkt.clouddn.com/2018.3.16_9.png)

### 2.8 求最大值和最小值
求输入矩阵的全局最大值最小值及其位置, 可使用函数:

```cpp
void minMaxLoc(InputArray src, CV_OUT double* minVal,  
                           CV_OUT double* maxVal=0, CV_OUT Point* minLoc=0,  
                           CV_OUT Point* maxLoc=0, InputArray mask=noArray());  
```
参数 :

* `src`,  输入单通道矩阵(图像).
* `minVal`, 指向最小值的指针, 如果未指定则使用 NULL.
* `maxVal`, 指向最大值的指针, 如果未指定则使用 NULL.
* `minLoc`, 指向最小值位置(2 维情况) 的指针, 如果未指定则使用 NULL.
* `mask`, 可选的蒙版, 用于选择待处理区域.

```cpp
// 求极值: 最大值、最小值及其位置
Mat img = imread("Lena.jpg",0);
imshow("original image", img);

ofstream fout("lena1.txt");		// 保存数据的文件

double minVal = 0, maxVal = 0;
cv::Point minPt, maxPt;
minMaxLoc(img, &minVal, &maxVal, &minPt, &maxPt);

cout << "min value = " << minVal << endl;
cout << "max value = " << maxVal << endl;
cout << "minPt = " << minPt << endl;
cout << "maxPt = " << maxPt << endl;

fout << "min value = " << minVal << endl;
fout << "max value = " << maxVal << endl;
fout << "minPt = " << minPt << endl;
fout << "maxPt = " << maxPt <<endl;

Rect rectMin(minPt.x - 10, minPt.y - 10, 20, 20);
Rect rectMax(maxPt.x - 10, maxPt.y - 10, 20, 20);

rectangle(img, rectMin, cv::Scalar(200,2));
rectangle(img, rectMax, cv::Scalar(255,2));

imshow("img with min max loction", img);

system("color A");
waitKey(0);
```

![](http://p2dak62rv.bkt.clouddn.com/2018.3.16_10.png)

### 0x03 其他矩阵运算
> 其他详情矩阵操作可以参考 [OpenCV Operations on Arrays](https://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html)
