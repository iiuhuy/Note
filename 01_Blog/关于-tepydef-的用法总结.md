---
title: 关于 tepydef 的用法总结
date: 2017-05-11 21:49:47
tags: C
---

# 01 基本定义
typedef 是 C 语言的关键字， 作用是为一种数据类型定义一个新名字。 这里的数据类型包括内部数据类型（int,char 等）和自定义的数据类型（ struct 等）。 在编程中使用typedef目的一般有两个，一个是给变量一个易记且意义明确的新名字，另一个是简化一些比较复杂的类型声明。

在 C/C++ 代码中，typedef 都使用很多， 尤其是 C 语言中， 在一些大型的代码架构，很常见。 看了很多 typedef 的用法， 现在结合实际项目希望能更深刻的理解！

# 02 语言用法1: 与 #define 的区别
typedef 行为有点像 #define 宏，用其实际类型替代同义字。不同点是 typedef 在编译时被解释,因此让编译器来应付超越预处理器能力的文本替换。 举个例子理解：
下面有两种定义 pStr 数据类型的方法，两者有什么不同? 哪种更好点？
```c
typedef char* pStr1;

#define pStr2 char*
```
一般讲， typedef 要比 #define 要好， 特别是在指针的场合 ：
```c
typedef char* pStr1;

#define pStr2 char*

pStr1 s1, s2;

pStr2 s3, s4;
```
在上述的变量定义中，s1、s2、s3 都被定义为 char*，而 s4 则定义成了 char， 不是我们所预期的指针变量，根本原因就在于 #define 只是简单的字符串替换而 typedef 则是为一个类型起新名字。

上例中 define 语句必须写成 pStr2 s3, *s4; 这样才能正常执行。

# 03 语言用法2： 与 struct 结合使用
在 C 语言中， struct 的定义和声明要用 typedef 。
```c
typedef struct __Person  
{  
    string name;  
    int age;  
    float height;  
}Person;    //这是Person是结构体的一个别名  
Person person; 
```
如果不加 typedef ，必须用 struct Person person; 来声明：
```c
struct Person  
{  
    string name;  
    int age;  
    float height;  
};  
struct Person person;  

//或者

struct Person  
{  
    string name;  
    int age;  
    float height;  
}person; 
```

# 04 掩饰符合类型
typedef 还可以掩饰符合类型， 如数组和指针。
例如， 不用像下面这样重复定义有 81 个字符元素的数组：
```c
char line[81];
char text[81];
```
定义一个 typedef ， 每当要用到相同的类型和大小的组数时，可以这样：
```c
typedef char Line[81];
```
此时 Line 类型即代表了具有 81 个元素的字符数组， 使用方法如下：
```c
Line text, newline;
getline(text);
```
同样可以像下面这样隐藏指针语法：
```c
typedef char * pstr;  
int mystrcmp(pstr, pstr); 
```
这里将带我们到达第一个 typedef 陷阱。标准函数 strcmp() 有两个 const char* 类型的参数。因此，它可能会误导人们象下面这样声明 mystrcmp()：
```c
int mystrcmp(const pstr, const pstr);   
```
用 GNU 的 gcc 和 g++ 编译器，是会出现警告的，按照顺序，const pstr 被解释为 char* const（一个指向 char 的指针常量），两者表达的并非同一意思。 为了得到正确的类型，应当如下声明： 
```c
typedef const char* pstr;  

```

# 05 typedef 和存储类关键字（storage class specifier）
这中说法会不会有点惊讶，typedef 就像 auto、extern、mutable、static、register 一样，是一个储存类关键字。 并不是说 typedef 会真正有储存上的意义， 它只是说在语句上构成了像 static、extern、等类型的变量声明。例如:
```c
typedef register int THIS_IS_TEST; // 错误
```
编译不会通过， 问题出在你不能在声明中有多个储存类的关键字。 因为符号 typedef 已经占据了储存类型关键字的位置， 在 typedef 声明中不能用 register (或者其他的储存类关键字)。
测试结果如下：

![](http://i.imgur.com/h7dud7s.png)

运行环境在 ADS1.2 下测试。

参考文献：

1.[typedef 与 #define 的区别](http://blog.csdn.net/luoweifu/article/details/41630195)
2.[typedef 百度百科](http://baike.baidu.com/link?url=8op1g5SbQAbSDYr0VIDq3t2hlRuztktB8ILiWrQYK171l6nnaUDqh4VfG746guzORmhqu7KsoQ9zEv064hQApK)
3.[CSDN：C 语言 typedef 的用法](http://blog.csdn.net/sergeycao/article/details/3793756)
4.[关于typedef的用法总结](http://blog.csdn.net/wangqiulin123456/article/details/8284939)