---
title: 嵌入式C编程之调试信息打印
date: 2017-06-05 23:53:29
tags: C
---

coding 最重要的是如何 debug， debug 当然少不了把程序信息输出， 如何清晰明了的打印出程序的信息， 可以快速判断程序运行情况， 定位程序出错的地方。

---

C语言中格式字符串的一般形式为： %[标志][输出最小宽度][.精度][长度]类型， 其中方括号[]中的项为可选项。

# 类型
用一定的字符用以表示输出数据类型， 格式符和意义如下：

|字符|意义|
|---|---|
|a/A|浮点数、十六进制数字和 p- 计数法(c99)|
|c|输出单个字符|
|d|以十进制形式输出带符号整数(正数不输出符号)|
|e/E|以指数形式输出单、双精度实数|
|f|以小数形式输出单、双精度实数|
|g/G|以 %f %e 中较短的输出宽度输出单、双精度实数，  %e 格式在指数小于 -4 或者大于等于精度时使用|
|i|有符号十进制整数(与 %d 相同)|
|o|以八进制形式输出无符号整数(不输出前缀 0 )|
|p|指针|
|s|输出字符串|
|x/X|以十六进制形式输出无符号整数(不输入前缀 0X)|
|u|以十进制形式输出无符号整数|

* 进行测试 (可以在 Linux 下进行测试，（因为我安装了 Ubuntu，所以直接测试还是挺方便的 ）)。

上代码:

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifndef __USE_DEBUG
#define __USE_DEBUG
#define USE_DEBUG
#ifdef USE_DEBUG
#define DEBUG_LINE() printf("[%s:%s] line=%d\r\n",__FILE__, __func__, __LINE__)

#define DEBUG_ERR(fmt, args...) printf("\033[46;31m[%s:%d]\033[0m "#fmt" errno=%d, %m\r\n", __func__, __LINE__, ##args, errno, errno)

#define DEBUG_INFO(fmt, args...) printf("\033[33m[%s:%d]\033[0m "#fmt"\r\n", __func__, __LINE__, ##args)

#else
#define DEBUG_LINE()
#define DEBUG_ERR(fmt, ...)
#define DEBUG_INFO(fmt, ...)
#endif

#endif

void func()
{
    DEBUG_LINE();
    DEBUG_INFO("Garfield test DEBUG_INFO() d: %d ; s: %s", 1 , __FUNCTION__);
    DEBUG_ERR("Garfield test DEBUG_ERR() d: %d ; s: %s", 2 , __FUNCTION__);

}

int main(int argc,char **argv)
{
    func();
    return 0;
}
```

## 分析

* 使用颜色打印调试信息:

```c
printf("\033[46;31m[%s:%d]\033[0m "#fmt" errno=%d, %m\r\n", __func__, __LINE__, ##args, errno, errno);
```

该 printf 时，在 Linux 命令行打印出带颜色的字体， 方便一眼区分不同种类的调试信息， 还需要加上一些颜色代码， 例如： 这里 46 代表底色， 31 代表字体的颜色。 使用 ASCII Code 对颜色调用的始末格式如下：

```
\033[; m ...... \033[0m
```

后面的 '\033[0m' 是对前面的颜色载入的结束， 恢复到终端原来的背景和字体色， 可以把后面哪个修改成如下试试:

```c
#define DEBUG_ERR(fmt, args...)  printf("\033[46;31m[%s:%d]\033[40;37m " #fmt "errno=%d, %m\r\n"， __func__, __LINE__, ##args, errno, errno);
```

下面列出 ASCII Code 的颜色值：

|字体背景颜色范围： 40 ~~ 49|字颜色：30 ~~ 39|
|---|---|
|40：黑色| 30：黑色|
|41：深红| 31：红色|
|42：绿色| 32：绿色|
|43：黄色| 33：黄色|
|44：蓝色| 34：蓝色|
|45：紫色| 35：紫色|
|46：深绿| 36：深绿|
|47：白色| 37：白色|

* 打印调试信息的跟踪位置：

```c
printf("[%s:%s] line=%d\r\n",__FILE__, __func__, __LINE__);
printf("\033[33m[%s:%d]\033[0m "#fmt"\r\n", __func__, __LINE__, ##args);
```

如上代码：

1. __FILE__ 打印出调试信息所在文件名；
2. __func__ 打印出调试信息所在的函数名；
3. __LINE__ 打印出调试信息所在的文件行号；

* 使用不定参数向打印信息里面加入自己想看到的调试信息：

```c
#define DEBUG_INFO(ftm, args...) printf("\033[33m[%s:%d]\033[0m "#fmt"\r\n", __func__, __LINE__, ##args);
```

调试方式入下：

```c
int i = 100;
char * s = "hello world!!!";
DEBUG_INFO("Garfield test DEBUG_INFO() d: %d; s: %s", i, s);
```

至于不定数量参数宏与不定参数函数的使用这里就不提了, 自行 Google 吧！
不过引用一位大侠列出常用的 debug 语句。他的博客现在好像失效了，具体位置目前也不太清楚：

```c
#ifdef DEBUG
#define F_OUT printf("%s:", __FUNCTION__);fflush(stdout);
#define L_OUT printf("%s:%d:", __FILE__, __LINE__);fflush(stdout);
#define A_OUT printf("%s:%d:%s:", __FILE__, __LINE__, __FUNCTION__);fflush(stdout);
#define D_OUT printf("DEBUG:");fflush(stdout);
#define F_PRINTF(fmt, arg...) F_OUT printf(fmt, ##arg)
#define L_PRINTF(fmt, arg...) L_OUT printf(fmt, ##arg)
#define A_PRINTF(fmt, arg...) A_OUT printf(fmt, ##arg)
#define PRINTF(fmt, arg...) D_OUT printf(fmt, ##arg)
#define DBUG(a) {a;}

#else
#define F_OUT
#define L_OUT
#define A_OUT
#define D_OUT
#define F_PRINTF(fmt, arg...)
#define L_PRINTF(fmt, arg...)
#define A_PRINTF(fmt, arg...)
#define PRINTF(fmt, arg...)
#define DBUG(a)
#endif

#define F_PERROR(fmt) F_OUT perror(fmt)
#define L_PERROR(fmt) L_OUT perror(fmt)
#define A_PERROR(fmt) A_OUT perror(fmt)
#define PERROR(fmt) D_OUT perror(fmt)
```

## 附--使用 printf 输出各种格式的字符串

### 01 原样输出字符
```
printf("%s", str);
```

### 02 输出指定长度的字符串， 超长时不截断， 不足时右对齐
```
printf("%Ns", str);    // --N 为指定长度的 10 进制数值
```

### 03 输出指定长度的字符串， 超长时不截断， 不足时左对齐
```
printf("%-Ns", str);    // --N 为指定长度的 10 进制数值
```

### 04 输出指定长度的字符串， 超长时不截断， 不足时右对齐
```
printf("%N.Ms", str);    // --N 为最终的字符串输出长度
                         // --M 为从参数字符串中取出的子串长度
```

### 05 输出指定长度的字符串， 超长时不截断， 不足时左对齐
```
printf("%-N.Ms", str);    // --N 为最终的字符串输出长度
                          // --M 为从参数字符串中取出的子串长度
```
关于不定参数的应用我也是 百度 或者 Google。
http://blog.csdn.net/arong1234/article/details/2456455

参考
[百度文库：C 语言printf()输出格式大全](https://wenku.baidu.com/view/065d62fff705cc1755270989.html)






