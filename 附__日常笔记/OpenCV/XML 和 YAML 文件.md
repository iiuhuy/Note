# Opencv XML 和 YAML 文件读写
* 关于 [XML](https://www.w3.org/XML/)  
* 关于 [YAML](http://www.yaml.org)

# FlieStorage 类操作的使用指引
OpenCV 中一般使用如下过程来写入或者读取数据到 XML 或 YAML 文件中。

* 实例化一个 FileStorage 类的对象, 用默认代参的构造函数完成初始化, 或者用 FileStorage::open() 成员函数辅助初始化。
* 使用流操作符 `<<` 进行文件写入操作, 或者 `>>` 进行文件读取操作, 类似 C++ 中的文件输入输出流。
* 使用 `FileStorage::release()` 函数析构掉 FileStorage 类对象, 同时关闭文件。


网上搜了一下, 在 [Stack Overflow 这里解决了该问题](https://stackoverflow.com/questions/13550864/error-c4996-ctime-this-function-or-variable-may-be-unsafe) 即加上:

```cpp
#pragma warning(disable : 4996)
```
