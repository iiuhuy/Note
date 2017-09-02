---
title: '#ifdef __cplusplus extern ＂C＂ { #endif'
date: 2017-04-25 23:22:06
tags: C

---

### 在好多程序中我们会遇到下面这样的一块代码段
```c
#ifdef __cplusplus
extern "C"{
#endif

// c 语言代码段 //

#ifdef __cplusplus
}
#endif
```
首先上网查了下，__cplusplus 是 CPP 中定义的宏， 则表示这是一段 CPP 的代码， 编译器按照 C++ 的方式去编译系统。 这个时候我们要使用 C 语言的代码， 那么就需要加上 extern "C"{ 来说明， 不然按照 C++ 的编译会出现问题。

要明白为何要使用 extern "C"{ ，那就得提 CPP 中对函数的重载处理， 自行去了解下，就是说 C++ 和 C 对产生的函数名字处理是不一样的。 加上 extern "C"{ 的目的， 就是主要实现 C 与 C++ 的相互调用问题。
```c
extern "C" 是连接声明(linkage declaration), 被 extern "C" 修饰的变量和函数是按照 C 语言方式编译和连接的。
```

关于 C 和 CPP 之间相互调用
* 可以参考 [CSDN知识库的解释](http://lib.csdn.net/article/c/25579)
