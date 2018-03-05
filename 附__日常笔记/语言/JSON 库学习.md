> 来自 https://zhuanlan.zhihu.com/json-tutorial

# 0x01 JSON is what ?

JSON（JavaScript Object Notation）是一个用于数据交换的文本格式。同 JSON 类似的还有, XML、YAML, 以 JSON 最为简单。

JSON 是树状结构，而 JSON 只包含 6 种数据类型 :

* null : 表示为 null。
* boolean : 表示为 true 或 false。
* number : 一般的浮点数表示方式, 后面详细说明。
* string : 表示为 "..."
* array : 表示为 [...]
* object : 表示为 {...}

需要完成 JSON 库, 主要是完成 3 个需求:

* 1. 把 JSON 文本解析为一个树状数据结构(parse)。
* 2. 提供接口访问该数据结构(access)。
* 3. 把数据结构转换为 JSON 文本(stringify)。

![](https://pic1.zhimg.com/80/75eecb0312e129d64dd3b028e1479e3d_hd.jpg)

首先实现最简单的 null 和 boolean 解析。

# 0x02 搭建基本环境
> 做的库是跨平台,跨编译器的, 可以在任意平台进行练习。

JSON 库名为 leptjson, 代码文件只有 3 个:

* 1. leptjson.h : leptjson 的头文件 (head file), 含有对外的类型和 API 函数声明。
* 2. leptjson.c : leptjson 的实现文件 (implementation file), 含有内部的类型声明和函数实现。此文件会编译成库。
* 3. test.c : 使用测试驱动开发, 此文件包含测试程序, 需要链接 leptjson 库。

为了跨平台开发, 使用一个现时最流行的软件配置工具 **CMake** 。
在 Windows 下, 下载安装 CMake 后, 可以使用其 cmake-gui 程序。

在 UBuntu 下, 使用 `apt-get` 来安装:
```
$ apt-get install cmake
```


# 0x03 单元测试

做练习的时候或者刷题的时候, 都是以 printf/cout 打印结果, 再肉眼对比结果是否合乎预期。但是当软件项目越来越复杂, 这个做法会越来越低效, 那么一般就会采取自动的测试方式, 例如 **单元测试**(unit testing)。 单元测试也能保证其他人修改代码后, 原来的功能维持正确。(这称为回归测试／regression testing)。

常见的单元测试框架有 xUnit 系列, 如 C++ 的 Google Test、C# 的 NUint。 为了简单可以编写一个极简单的单元测试方式。

一种软件开发方法论，称为测试驱动开发（test-driven development, TDD），它的主要循环步骤是：
* 1. 加入一个测试。
* 2. 运行所以测试, 新的测试应该会失败。
* 3. 编写实现代码。
* 4. 运行所以测试, 若有测试失败回到 3 。
* 5. 重构代码。
* 6. 回到 1 。

TDD 是先写测试, 再实现功能。 好处是实现只会刚好满足测试, 而不会写一些不需要的代码, 或者是没有被测试的代码。

# 0x04 关于断言

断言(assertion) 是 C 语言中常用的防御式编程方式, 减少编程错误。 最常用的是在函数开始的地方, 检测所有参数。有时候也可以在调用函数后
, 检查上下文是够正确。

C 语言的标准库含有 `assert()` 这个宏(需要 include <assert.h>), 提供断言功能。 当程序以 release 配置编译时(定义了 NDEBUG 宏), `assert()` 不会做这个检查; 而在 debug 配置时(没定义 `NDEBUG` 宏), 则会在运行时检测 `assert(cond)` 中的条件是否为真 (非 0), 断言失败会直接令程序崩溃。

初学者可能会难于分辨何时使用断言，何时处理运行时错误（如返回错误值或在 C++ 中抛出异常）。简单的答案是，如果那个错误是由于程序员错误编码所造成的（例如传入不合法的参数），那么应用断言；如果那个错误是程序员无法避免，而是由运行时的环境所造成的，就要处理运行时错误（例如开启文件失败）。
