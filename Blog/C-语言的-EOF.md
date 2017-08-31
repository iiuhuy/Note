---
title: C 语言的 EOF
date: 2017-04-19 00:06:47
tags: C
---
### 在学 C 语言的时候, 遇到了到这么一个问题： [EOF](https://zh.wikipedia.org/wiki/%E6%AA%94%E6%A1%88%E7%B5%90%E5%B0%BE  ) 。

当时就懵逼了， 没看见定义或声明就能用了？ 直到后来才知道， 如下：

它是 End  Of File 的缩写， 表示"文字流" ( Stream ) 的结尾， 这里的"文字流"可以是文件 ( file ) ， 也可以是标准输入( stdin )。

 

一开始看到 带有 " EOF "的代码段： 例如

```c

int c;

while( (c = fgetc(fp)) != EOF ){

    putchar(c);

}

```

我就以为文件结尾的时候会默认有一个 EOF 的特殊字符， 读取到这个字符系统就认为文件结束了。

但是知道后来才知道， EOF 不是一个特殊的字符， 而是定义在头文件 "stdio.h" 里的常量， 一般等于 -1。

```c
#define  EOF ( - 1 )

```


后来看到， 如果一个 EOF 是一个特殊的字符， 那么假定每个文本文件的结尾都有一个 EOF (-1)， 还是可以做到， 毕竟 ASCII 码都是正值， 没有负值。但是遇到二进制文件怎么办呢？ 怎么处理文件内部包含的 ( -1 ) 呢？

** 原来在 Linux 系统中, EOF 根本不是一个字符， 而是当系统读取到文件结尾， 所返回的一个信号值 ( 也就是 -1 )** 。 至于系统怎么知道文件的结尾， 好像是说通过比较文件的长度。

处理文件则可以写成这样 : 

```c
int c;

while(( c = fgetc(fp)) != EOF){

    do something;

}

```

而这样写有一个问题。 fgetc() 不仅是遇到文件结尾时返回 EOF ， 而且当发生错误时， 也会返回 EOF 。 因此， C 语言有提供了 [feof() 函数](http://baike.baidu.com/link?url=K41I_NiKDBUWVdC_2Q0pkXfRL-Jl5L1ZWQQKz-PClCJ9gpwbi0NRQ18RZYVUehwvDCTWKM2Wcmti0PIn2kIy7q  )， 用来保证确实是到了文件结尾。 上面的代码 feof() 版本的写法:

```c
int c;

while( !feof(fp) ){
    c = fgetc(fp);
    do something;
}

```

当然这也不是最好的写法。

[参考 fgetc](http://www.drpaulcarter.com/cs/common-c-errors.php#4.2  )

[参考 EOF、getc() and feof() in C](http://www.geeksforgeeks.org/eof-and-feof-in-c/  )



Linux 中，在新的一行的开头，按下 Ctrl-D，就代表 EOF（如果在一行的中间按下 Ctrl-D，则表示输出"标准输入"的缓存区，所以这时必须按两次 Ctrl-D）；Windows 中，Ctrl-Z 表示 EOF。（顺便提一句，Linux 中按下 Ctrl-Z，表示将该进程中断，在后台挂起，用 fg 命令可以重新切回到前台；按下 Ctrl-C 表示终止该进程。）



那么，如果真的想输入 Ctrl-D 怎么办？这时必须先按下 Ctrl-V，然后就可以输入 Ctrl-D，系统就不会认为这是 EOF 信号。[Ctrl-V](https://en.wikipedia.org/wiki/Control-V  ) 表示按"字面含义"解读下一个输入，要是想按"字面含义"输入Ctrl-V，连续输入两次就行了。








