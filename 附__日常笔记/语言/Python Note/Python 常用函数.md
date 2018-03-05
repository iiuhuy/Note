# Python 笔记
> Python 的一些函数(方法)。


## 字符

* `ord()`函数。 获取字符的整数表示。
* `chr()`函数。`ord()` 的逆过程。详情可以看 Python 3 文档。
* `encode()`函数。将 str 转换为 byte。(Python 中需要注意编码的格式。)
* `decode()`函数。将 byte 转换为 str。
* `len()`函数。 计算 str 中包含了多少个字节; 如果是字符串前面加了b, 即`b'ABC'`, 就是计算多少 byte。
* 输入相关
    * `input()`函数, 返回值是 str, 不能直接和整数相比较, 需要将 str 转换为 int(), Python 提供了 `int()` 函数。
## list(列表) 和 tuple(元组)
* `pop()`函数。删除指定位置的元素, pop(i), i 是索引位置。
* `enumerate` 函数。 python 内置函数.
