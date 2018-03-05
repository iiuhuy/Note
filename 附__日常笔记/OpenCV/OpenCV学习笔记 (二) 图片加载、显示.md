# 关于 OpenCV 命名空间

OpenCV 中的 C++ 类和函数(方法)都是定义在命名空间 `cv` 之内的, 有两种方法可以访问。

第一种是 : 在代码开头的适当位置, 加上 `using namespace cv` 这句。

另外一种是 : 在使用 OpenCV 类和函数时，都加入 `cv::` 命名空间。不过这种情况难免会不爽，每用一个 OpenCV 的类或者函数，都要多敲四下键盘写出 cv::, 很麻烦。 所以还是直接在开头加上 `using namespace cv` 较方便。

# Mat 类型

`cv::Mat` 类是用于保存图像以及其他矩阵数据的数据结构。

## 图像的载入和显示

### 1. imread 函数
可以在 cv 官方文档中看到

```cpp
Mat cv::imread	(	const String & 	filename,
int 	flags = IMREAD_COLOR
)
```

第一个参数, 是需要我填入载入图片的路径名或者名字。 第二个参数是一个标识, 具体在一个枚举里面详细定义。查看官方文档即可知道。
如下图 :
![](http://p2dak62rv.bkt.clouddn.com/2018.3.2_1.png)

flag 是 int 型变量, 如果不在枚举中取值的话, 可以这样来 :

* flag > 0, 返回一个 3 通道的彩色图像。
* flag = 0, 返回灰度图像。
* flag < 0, 返回包含 Alpha 通道的加载图像。

> 需要注意的是: 输出的图像默认情况下是不载入 Alpha 通道进来的。 如果需要载入 Alpha 通道, 就需要给负值。


载入图像的函数, Windows 操作系统下, OpenCV 的 imread 函数支持如下类型 :

* Windows 位图, `*.bmp`, `*.dib`
* JPEG 文件, `*.jpeg`, `*.jpg`, `*.jpe`
* JPEG 2000 文件, `*.jp2`
* PNG 图片, `*.png`
* 便携式文件格式, `*.pbm`, `.pgm`, `.ppm`
* Sun rasters 光栅文件, `*.sr`, `*.ras`
* TIFF 文件 `*.tiff`, `*.tif`

### 2. namedWindow 函数
用于创建一个窗口。namedWindow 函数的作用是，通过指定的名字，创建一个可以作为图像和进度条的容器窗口。如果具有相同名称的窗口已经存在，则函数不做任何事情。

可以使用 `destroyWindow()` 或者 `destroyAllWindows()` 函数来关闭窗口, 并取消之前分配的与窗口相关的所以内存空间。一般不会手动调用这两个函数, 在退出时, 操作系统会自动关闭资源和应用程序的窗口。

### 3. imshow 函数
在指定的窗口中显示一幅图像。

函数原型 :

```cpp
void imshow(const string& winname, InputArray mat);  
```

第一个参数为窗口的名字, 第二个参数为要显示的图像。

### 4. imwrite 函数
输出图像到文件。 函数如下 :

```cpp
bool imwrite(const string& filename,InputArray img, const vector<int>& params=vector<int>());  
```

* 第一个参数, const string & 类型的 filename, 填需要写入的文件名就行了, 带上后缀。如 `output.jpg`
* 第二个参数, InputArray 类型的 img, 一般填一个 Mat 类型的图像数据就行了。
* 第三个参数, const vector<int>& 类型的 params, 表示为特定格式保存的参数编码, 它有默认值 vector<int>(), 所以一般情况下不需要填写。
