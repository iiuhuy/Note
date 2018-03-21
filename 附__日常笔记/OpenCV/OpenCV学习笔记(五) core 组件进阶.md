# 学习目标
* 操作图像中的像素
* 设置感兴趣区域(ROI)
* 如何进行图像混合
* 如何分离颜色通道
* 如何进行多通道图像混合
* 如何调整图像的对比度和亮度值
* 如何对图像进行傅里叶变换
* 如何输入输出 XML 和 YAML 文件

# 访问图像中的元素
## LUT 函数(Look up table) 操作
用于批量进行图像元素查找、扫描与操作图像。如下 :

```cpp
// 创建一个 Mat 类, 用于查表
Mat lookUpTable(1, 256, CV_8U);
uchar* p = lookUpTable.data;
for(int i = 0; i < 256; ++i)
{
  p[i] = table[i];
}

// 然后调用函数
for(int i = 0; i<times; ++i)
{
  LUT(I, lookUpTable, J);
}
```

## 计时函数
* getTickCount()
* getTickFrequency()

## 访问图像中的三类方法

* 方法一, 指针访问 : C 操作符[]。该速度最快！
* 方法二, 迭代器 Iterator
* 方法三, 动态地址计算

三者在访问速度上有一定的差异。 debug 模式下, 这种差异比较明显。 在 release 模式下, 这种差异就不太明显。

遍历图像的像素的 14 种方法, 浅墨大神书中提到, 这 14 中方法, 来自国外一本 OpenCV2 书籍的配套例程, 比较经典。

# 感兴趣区域 ROI(region of interest)
定义 ROI 区域有两种方法 :

* 第一种, 使用表示矩形区域的 Rect。指定矩形的左上角坐标(构造函数的前两个参数) 和矩形的长宽(构造函数的后两个参数)。

```cpp
// 定义一个 Mat 类型, 并设定 ROI 区域
Mat imgaROI;
// 方法一
imageROI = image(Range(500,250, logo.cols, logo.rows));
```

* 第二种, 指定感兴趣行或列的范围 (Range)。 Range 是指从起始索引到终止索引(不包括终止索引)的一连段连续序列。cRange 可以用来定义 Range, 如果使用 Range 来定义 ROI。

```cpp
// 方法二
imageROI = image(Range(250, 250+logoImage.rows), Range(200, 200+logoImage.cols));
```

## 计算数组加权和 addWeighted() 函数
函数原型如下 :

```cpp
void addWeighted(InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray dst, int dtype = -1);
```

* 第一个参数, InputArray 类型的 src1, 表示需要加权的第一个数组, 通常填一个 Mat。
* 第二个参数, double 类型的 alpha , 表示第一个数组的权重。
* 第三个参数, InputArray 类型的 src2, 表示第二个数组, 需要和第一个数组拥有相同的尺寸和通道数。
* 第四个参数, double 类型的 beta, 表示第二个数组的权重值。
* 第五个参数, double 类型的 gamma, 一个加到权重总和上的标量值。
* 第六个参数, OutputArray 类型的 dst, 输出的数组, 它和输入的两个数组拥有相同的尺寸和通道数。
* 第七个参数, int 类型的 dtype , 输出阵列的可选深度, 有默认值 -1。 当两输入数组具有相同的深度时, 这个参数设置为 -1(默认值), 即等同于 src1.depth()。

addWeighted() 函数的作用矩阵表达式 :
```
dst = src1[i] * alpha + src2[i] * beta + gamma;
```

即用 addWeighted 函数计算两个数组(src1 和 src2)的加权和, 得到结果输出给第四个参数。
