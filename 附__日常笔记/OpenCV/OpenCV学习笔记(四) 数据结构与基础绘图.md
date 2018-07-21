# 0x01 基础图像容器 Mat
Mat 是一个类, 由两个数据部分组成 : 矩阵头(包含矩阵尺寸、储存方法、储存地址等信息) 和一个指向存储地址所有像素值的矩阵(根据所选存储方法的不同, 矩阵可以是不同维度) 的指针。

由于矩阵的开销比较大, 不到万不得已, 不应该进行大图像的复制, 为了解决这个问题, OpenCV 使用了引用机制。 即让每个 Mar 对象有自己的信息头, 但共享同一个矩阵。 而 **拷贝构造函数** 则只复制信息头和矩阵指针, 而不复制矩阵。

```cpp
Mat A, C;   // 仅创建信息头
A = imread("1.jpg", CV_LOAD_IMAGE_COLOR); // 这里为矩阵开辟内存
Mat  B(A);  // 使用拷贝函数
C = A;      // 赋值运算符
```

* OpenCV 函数中输出图像的内存分配是自动完成的(如果不特别指定的话)。
* 使用 OpenCV 的 C++ 接口时不需要考虑内存释放的问题。
* 复制运算符和拷贝构造函数(构造函数)只复制信息头。
* 使用函数 clone() 或者 copyTo() 来复制一幅图像的矩阵。

## 显式创建 Mat 对象的七种方法
### 1. 使用 Mat() 构造函数
最常用的方法是直接使用 Mat() 构造方法, 简单明了。示例如下 :

```cpp
Mat M(2, 2, CV_8UC3, Scalar(0,0,255));
cout << "M = " << endl << " " << M << endl << endl;
```

### 2. 在 C\C++ 中同构构造函数来进行初始化
如下 :

```cpp
IplImage* img = cvIoadImage("1.jpg", 1);
Mat mtx(img);   // 转换 IplImage* -> Mat
```

### 3. 为已存在的 Ipllmage 指针创建信息头
如下 :
```cpp
IplImage* img = cvLoadImage("1.jpg",  1);
Mat mxt(img);   // 转换 IplImage* -> Mat
```

### 4. 利用 Create() 函数
方法四是利用 Mat 类中的 Create() 成员函数进行 Mat 类的初始化操作。如下 :

```cpp
M.Create(4, 4, CV_8UC(2));
cout << "M = " << endl << " " << M << endl << endl;
```

### 5. 采用 Matlab 式的初始化方式
采用 Matlab 形式的初始化方式: zeros(), ones(), eye()。 如下 :

```cpp
Mat E = Mat::eye(4, 4, CV_64F);
cout << "E = " << endl << " " << E << endl << endl;

Mat O = Mat::onse(2, 2, CV_32F);
cout << "O = " << endl << " " << O << endl << endl;

Mat Z = Mat::zeros(3, 3, CV_8UC1);
cout << "Z = " << endl << " " << Z << endl << endl;
```

### 6. 对小矩阵使用逗号分隔式初始化函数
如下 :
```cpp
Mat C = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
cout << "C = " << endl << " " << C << endl << endl;
```

### 7. 为已存在的对象创建新信息头
使用成员函数 `clone()` 或者 `copyTo()` 为一个已经存在的 Mat 对象创建一个新的信息头, 如下 :
```cpp
Mat RowCloone = C.row(1).clone();
cout << "RowClone = " << endl << " " << RowClone << endl << endl;
```

## 格式化输出方法

* OpenCV 默认风格。
* Python 风格。
* 逗号分隔风格。
* Numpy 风格。
* C 语言风格。


# 0x02 常用数据结构和函数
* Vec
* Point
* Scalar
* Size
* Rect
* RotatedRect

## 2.1 Vec 类
Vec 是一个模版类, 用于储存数值向量。

### 2.1.1 可以使用它来定义任意类型的向量
```cpp
Vec<doeble, 8> myVector;  // 定义一个存放 8 个 double 型变量的向量.
```

### 2.1.2 使用 [] 访问 Vec 向量成员
```cpp
myVector[0] = 0;
```

### 2.1.3 可使用以下预定于的类型
```cpp
typedef Vec<uchar, 2> Vec2b;  
typedef Vec<uchar, 3> Vec3b;  
typedef Vec<uchar, 4> Vec4b;  
typedef Vec<short, 2> Vec2s;  
typedef Vec<short, 3> Vec3s;  
typedef Vec<short, 4> Vec4s;  
typedef Vec<int, 2> Vec2i;  
typedef Vec<int, 3> Vec3i;  
typedef Vec<int, 4> Vec4i;  
typedef Vec<float, 2> Vec2f;  
typedef Vec<float, 3> Vec3f;  
typedef Vec<float, 4> Vec4f;  
typedef Vec<float, 6> Vec6f;  
typedef Vec<double, 2> Vec2d;  
typedef Vec<double, 3> Vec3d;  
typedef Vec<double, 4> Vec4d;  
typedef Vec<double, 6> Vec6d;
```

### 2.1.4 Vec 支持的运算如下
```cpp
v1 = v2 + v3  
v1 = v2 - v3  
v1 = v2 * scale  
v1 = scale * v2  
v1 = -v2  
v1 += v2  
v1 == v2, v1 != v2  
norm(v1) (euclidean norm)  

//-----------------------------------------------------//
// 示例代码如下
Vec<int, 6> v1, v2, v3;
for (int i = 0; i < v2.rows; i++)  // 返回向量 v2 的行数
{
	v2[i] = i;
	v3[i] = i + 1;
}

v1 = v2 + v3;

cout << "v2		  = " << v2 << endl;
cout << "v3		  = " << v3 << endl;
cout << "v1 = v2 + v3      = " << v1 << endl;
cout << "v1 = v2 * 2       = " << v2*2 << endl;
cout << "v1 = -v2	  = " << -v2 << endl;
cout << "v1 == v2	  = " << (v1 == v2) << endl;
cout << "v1 != v2	  = " << (v1 != v2) << endl;
cout << "norm(v2)	  = " << norm(v2) << endl;

system ("color A");
system ("pause");
```

## 2.2 颜色的表示 Scalar 类
### 2.2.1 cv::Scalar 结构
Scalar() 表示具有 4 个元素的数组, 在 OpenCV 中被大量用于传递像素值。

可以使用 [] 访问 Scalar 的值, 或者使用 `cv::Scalar(B,G,R)` 方式定义 RGB 三个通道的值。例如 :
```cpp
cv::Scalar myScalar;

myScalar = cv::Scalar(0,255,0);

cout << "myScalar = " << myScalar << endl;

system("color A");
system("pause");
```

### 2.2.2 读取彩色图像像素值
彩色图像的每个像素对应三个部分: RGB 三个通道。 因此包含彩色图像的 `cv::Mat` 类会返回一个向量, 向量中包含三个 8 bit 的数值。 OpenCV 为这样的短向量定义了一种类型, 即 `cv::Vec3b` 。 这个向量包含三个无符号 (unsigned character) 类型的数据。

储存的顺序确实相反的, 为 BGR。

访问彩色像素中元素的方法如下:
```cpp
Mat pImg = cv::imread("1.jpg", 1);
if(!pImg.data)
  return 0;

int x = 100, y = 100;
cv::Scalar pixel = pImg.at<Vec3b> (x,y);

cout << " B chanel of pixel is =" << pixel.val[0] << endl;
cout << " G chanel of pixel is =" << pixel.val[1] << endl;
cout << " R chanel of pixel is =" << pixel.val[2] << endl;

system("color A");
system("pause");
```

## 2.3 点的表示 Point 类
### 2.3.1 基本用法
Point 类数据结构表示了二维坐标系下的点, 即由图像坐标 x 和 y 指定的 2D 点。 用法如下:
```cpp
Point point;
point.x = 10;
point.y = 8;

// 或者
Point point = Point(10,8);

// ------------- 或者使用如下预定义 ----------------- //
typedef Point_<int> Point2i;  
typedef Point2i Point;  
typedef Point_<float> Point2f;  
typedef Point_<double> Point2d;  
```

### 2.3.2 基本计算
```cpp
cv::Point pt1(1,1);  
cv::Point pt2(5,5);  
cv::Point pt3(9,10);  
int x = 2;

pt1 = pt2 + pt3;
cout << "pt1 =  pt2 + pt3 = " << pt1 << endl;
pt1 = pt2 - pt3;
cout << "pt1 =  pt2 - pt3 = " << pt1 << endl;
pt1 = pt2 * x;
cout << "pt1 =  pt2 * 2   = " << pt1 << endl;
pt1 += pt2;
cout << "pt1 += pt2       = " << pt1 << endl;
pt1 -= pt2;
cout << "pt1 -= pt2       = " << pt1 << endl;
pt1 *= x;
cout << "pt1 *= 2         = " << pt1 << endl;
double value = norm(pt1);
cout << "norm(pt1)        = " << value << endl;
pt1 == pt2;
cout << "pt1 == pt2       = " << (pt1 == pt2) << endl;
pt1 != pt2;
cout << "pt1 != pt2       = " << (pt1 != pt2) << endl;

system("color A");
system("pause");
```

## 2.4 尺寸的表示 Size 类

使用频率最高的是下面这个构造函数 :

```
Size(_TP _width, _TP _height);
```

如下 :
```cpp
// Size 的用法
Size	size1(6,3);
Size	size2;

size2.width = 4;
size2.height = 2;
Mat mat1(size1, CV_8UC1, cv::Scalar(0));		// 单通道
Mat mat2(size2, CV_8UC3, cv::Scalar(1,2,3));	// 三通道
cout << "mat1 = " << endl << " " << mat1 << endl;
cout << endl << "mat2 = " << endl << " " << mat2 << endl;
system("color A");
system("pause");
````

## 2.5 矩形的表示 Rect 类
### 2.5.2 基本概念
Rect 的成员变量有 x,y, width, height。Rect 可以用来定义图像的 ROI 区域。
常用的成员函数有 :

* Size() 返回值为 Size
* area() 返回矩形的面积
* contains(Point) 判断点是否在矩形内
* inside(Rect) 判断矩形是否在矩形内
* tl() 返回左上角点的坐标
* br() 返回右下角点的坐标

### 2.5.2 使用方法
```cpp
Rect rect(x,y,width, height);
```

示例 :
```cpp
Mat pImg = imread("Lena.jpg", 1);	// 读取工程目录下的 Lena.jpg 图像 文件为 512x512 的图片
Rect rect(180,200,200,200);			// 定义选中的区域 (x,y) = (180,200) width = 200, height = 200
Mat	roi = cv::Mat(pImg, rect);		// 定义 roi 变量储存选中的区域
Mat pImgRect = pImg.clone();		
cv::rectangle(pImgRect, rect, cv::Scalar(0,255,0),2);	// 画制一个矩形轮廓
imshow("original image with rectangle", pImgRect);
imshow("roi", roi);

waitKey(0);
```

## 2.6 RotatedRect 类
### 2.6.1 基本概念
该数据类型是一个特殊的矩形, RotatedRect。 这个类通过中心点、宽度、高度、旋转角度来表示一个旋转矩阵。

### 2.6.2 使用方法
```cpp
RotatedRect(const Point2f& center, const Size2f& size, float angle);  
```
参数:

* center, 中心点坐标 Point2f 类型。
* size, 矩形宽度和高度, Size2f 类型。
* angle, 顺时针方向的旋转角度(单位°), float 类型。

### 2.6.3 示例
```cpp
Point2f center(100,100);
Size2f size(100, 100);
float angle = 45;	// 可以试以下其他角度 10, 30, 45 ,60

RotatedRect rRect(center, size, angle);
Mat image(200,200,CV_8UC3, Scalar(0));		// 创建一个图片

Point2f vertices[4];
rRect.points(vertices);		// 返回 rRect 矩形的四个顶点
for (int i = 0; i < 4; i++)
{
	// 在 image 中绘制线段
	line(image, vertices[i],vertices[(i+1)%4], Scalar(0,255,0));
}

Rect brect = rRect.boundingRect();		// 返回包含旋转矩阵的矩形
rectangle(image, brect, Scalar(255,0,0));

imshow("rectangles", image);

waitKey(0);
```

## 颜色空间转换 cvtColor() 函数
原型如下 :
```c++
void cvtColor(InputArray src, OutputArray dst, int code, int dstCn = 0)
```

第一个参数为输图像, 第二个参数为输出图像, 第三个参数为颜色空间转换的标识符。随着 OpenCV 版本的升级, 对颜色空间种类的支持也越来越多。

# 图形绘制函数的写法
> 编写代码的时候, 为了统一规范, 最好都按照一定的规范进行编码。这里简单提一下几个常用的函数

* DrawEllipse() 函数的写法
* DrawFilledCircle() 函数的写法
* DrawPolygon() 函数的写法
* DrawLine() 函数的写法

最后需要对这些方法结合起来做一些练习, 才能够熟悉起来。
