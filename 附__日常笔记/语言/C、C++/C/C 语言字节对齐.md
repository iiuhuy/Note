<!-- # TAG_stm32 -->

> 参考: wiki [Data_structure_alignment](https://en.wikipedia.org/wiki/Data_structure_alignment).
[C 语言字节对齐问题详解](https://www.cnblogs.com/clover-toeic/p/3853132.html), 这篇文章写的很详细。

## ARM 下的对齐处理
> 参考
[1、stm32 中字节对齐问题( __align(n), __packed 用法 )](http://www.cnblogs.com/King-Gentleman/p/5940480.html)
[2、stm32 中使用 #pragma pack（非常有用的字节对齐用法说明）](http://www.cnblogs.com/King-Gentleman/p/5297355.html)
[3、正点原子开源电子论坛_ mymalloc 函数没有实现 4 字节对齐!](http://www.openedv.com/thread-7415-1-1.html)

### 对齐的使用

#### 01 `align(num)`

用于修改最高级别对象的字节边界。在汇编中使用 LDRD 或者 STRD 时就要用到此命令 `__align(8)` 进行修饰限制。来保证数据对象是相应对齐。

修饰对象的命令最大是 8 个字节限制, 可以让 2 字节的对象进行 4 字节对齐, 但是不能让 4 字节的对象 2 字节对齐。

`__align` 是存储类修改, 他只修饰最高级类型对象不能用于结构或者函数对象。

#### 02 `__packed`
`__packed` 用于表示 C 语言中结构的压缩，即：没有填充和对齐。`__packed` 是进行一字节对齐。

* 不能对 packed 的对象进行对齐。
* 所有对象的读写访问都进行非对齐访问。
* float 及包含 float 的结构联合及未用 `__packed` 的对象将不能字节对齐。
* `__packed` 对局部整形变量无影响。
* 强制由 unpacked 对象向 packed 对象转化是未定义, 整形指针可以合法定义为 packed。
```c
__packed int* p;  //__packed int 则没有意义
```
* 对齐或非对齐读写访问带来问题。


已知 32 位机器上各数据类型的长度为：char 为 1 字节、short 为 2 字节、int 为 4 字节、long 为 4 字节、float 为 4 字节、double 为 8 字节。那么上面两个结构体大小如何呢？

结果是：sizeof(strcut A) 值为 8；sizeof(struct B) 的值却是 12。

结构体 A 中包含一个 4 字节的 int 数据，一个 1 字节 char 数据和一个 2 字节 short 数据；B 也一样。按理说 A 和 B 大小应该都是 7 字节。之所以出现上述结果，就是因为编译器要对数据成员在空间上进行对齐。
