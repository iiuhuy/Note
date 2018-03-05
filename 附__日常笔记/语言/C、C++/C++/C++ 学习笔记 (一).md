>C++ 基础语法。参考慕课网!!!

C++ 和 C 的关系: 所有 C 程序都可以在 C++ 环境中运行。

比 C 语言增添了 bool 类型。

# 基础语法

### 新的初始化方法

```
int x = 0;  // 赋值初始化

int x(0);   // 直接初始化
```

### 随用随定义
这个特性 C 语言在 C99 之后是可以支持的。

### I/O 方式

输入过程：`输入设备 -> 输入流 -> cin -> 变量`。

输出过程：`输出设备 <- 输出流 <- cout <- 变量`。

```cpp
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(void)
{
    cout<<"请输入一个整数："<<endl;
    int x;
    cout<<"将该整数转变成 8  进制"<<oct<<x<<endl; // 将该整数转变成8进制
    cout<<"将该整数转变成 10 进制"<<dec<<x<<endl; // 将该整数转变成10进制
    cout<<"将该整数转变成 16 进制"<<hex<<x<<endl; // 将该整数转变成16进制
}
```

### C++ 的命名空间

命名空间的定义使用关键字 namespace, 后面跟命名空间的名称。例如：
```cpp
#include <iostream>
using namespace std;

namespace A
{
    void fun_1()
    {
        cout<<"这是 namespace_A"<<endl;
    }
}

namespace B
{
    void fun_2
    {
        cout<<"这是 namespace_B"<<endl;
    }
}

int main(void)
{
    // 调用第一个命名空间
    A::fun_1();

    // 调用第二个命名空间
    B::fun_2();

    return 0;
}
```

#### using 指令

使用 using 指令声明命名空间。使用命名空间的时候就不明加上命名空间的名称, 以上面的例子则可以。

```cpp
#include <iostream>
using namespace std;

namespace A
{
    void fun_1()
    {
        cout<<"这是 namespace_A"<<endl;
    }
}

namespace B
{
    void fun_2
    {
        cout<<"这是 namespace_B"<<endl;
    }
}

using namespace A;

int main(void)
{
    fun_1();

    return 0;
}
```

### 引用
引用就是变量的别名。

#### C++ 引用 & 指针
引用很容易与 指针 混淆, 它们之间有三个主要的区别:
* 不存在空引用, 引用必须连接到一块合法的内存。
* 一旦引用被初始化为一个对象, 就不能被指定到另一个对象。指针可以在任何时候指向一个对象。
* 引用必须在创建时被初始化。指针可以在任何时候被初始化。

#### 基本的数据类型引用

```cpp
#include <iostream>
using namespace std;

int main(void)
{
    int a = 3;
    int &b = a;   // 引用必须初始化

    b = 10;
    cout<< a <<endl;
    return 0;
}
```

结构体的引用

```cpp
// 定义一个结构体 Fun
typedef struct
{
    int x;
    int y;
}Fun;

// 然后再函数中使用这个结构体

int main(void)
{
    Fun f1;         // 定义这个结构体的变量 f1
    Fun &f = f1;    // 然后将 f1 起一个别名 f
    c.x = 10;       // 对该结构体的成员进行赋值
    c.y = 11;

    cout<<f1.x<<f1.y;
    return 0;
}
```

#### 指针类型的引用
`类型 *&指针引用名  = 指针`

```cpp
int main(void)
{
    int a = 1;
    int *p = &a;    // 定义一个 p 指针, 指向 a 的地址
    int *&p1 = p;   // 给 p 指针起一个别名 p1
    *p1 = 5;        // 通过 p1 来访问 a 的值
    cout<<a<<endl;
    return 0;
}
```

#### 函数参数做引用
```cpp
void fun(int &a, int &b)
{
    int c = 0;
    c = a;
    a = b;
    b = c;
}

int x = 10,y = 11;
fun(x,y);
```

C++ 的关键字 const : 是用来控制变量是否可以变化的。

const 与变量之间的关系: 就是将变量变为常量。 学 C 语言的时候 const 修饰的不是真正的常量, 可以看看 《C陷阱与缺陷》。

const 与指针类型的关系: `const int*p=NULL` 与 `int const*P=NULL` 是完全等价的。

#### 函数参数默认值
> 如果函数需要写默认值, 默认值必须写在最右边。如下:

```cpp
void fun(int i, int j = 1, int k = 3);    // 函数的声明

void fun(int i, int j, int k)   // 函数的定义
{
    cout<<i<<j<<k;
}
```

### 函数重载
> 就是两个函数的名字一样, 但是同名函数的形式参数(参数的个数、类型或者顺序)不同。

```cpp
void print(int i)
{
    cout<<"整数为: "<<i<<endl;
}

void print(double f)
{
    cout<<"浮点数为: "<<f<<endl;
}

void print(string c)
{
    cout<<"字符串为: "<<c<<endl;
}
```

#### 重载运算符
> 可以重定义或重载大部分 C++ 内置的运算符。这样, 就能使用自定义类型的运算符。

要区分哪些运算符可重载, 哪些运算符不能重载。

### 内联函数
内联函数关键字: inline

```cpp

```

在函数声明或定义中函数返回类型前加上关键字 inline 即把 min() 指定为内联。

#### 内联函数的编程风格
关键字 inline 必须与函数定义体放在一起才能使函数成为内联，仅将 inline 放在函数声明前面不起任何作用。

```cpp
void Fun(int x, int y);
inline void Fun(int x, int y) // inline 与函数定义体放在一起
{
}
```

下面这样的形式则不能称为内联函数：

```cpp
inline void Fun(int x, int y); // inline 仅与函数声明放在一起
void Fun(int x, int y)
{
}
```

定义在类声明之中的成员函数将自动地成为内联函数:

```cpp
class A
{
    public:
    void Fun(int x, int y) {  } // 自动地成为内联函数
}
```

慎用内联 !

### C++  内存管理
C++ 程序中的内存分为两个部分:

* 栈：在函数内部声明的所有变量都将占用栈内存。
* 堆：这是程序中未使用的内存，在程序运行时可用于动态分配内存。

申请内存，使用运算符：new；释放内存，使用运算符：delete 。

```cpp
int*p=new int;    // 申请内存
delete *p ;       // 释放内存

int *arr = new int[10];   // 申请一个块内存
delete [] arr;            // 释放快内存
```

判断申请内存是否失败,`if(NULL == p)` 则说明内存分配失败了, 申请内存时候需要判断是否申请成功, 释放内存需要将其设为 空指针。Example：

```cpp
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(void)
{
    int *p = new int;       // 申请内存
    // 判断内存是否申请成功
    if(NULL == p)
    {
        system("pause");
        return 0;           // 如果申请失败则退出, 申请成功了就给 p 赋值
    }

    *p = 1;
    cout<<*p<<endl;

    delete *p;              // 释放内存
    p = NULL;               // 将指针设置为 NULL

    system("pause");
    return 0;
}
```

### 类
>定义类后, 一定要写一个分号

#### 对象
**数据成员 + 成员函数 = 类**

##### 类的访问限定符
* public
* protected
* private
#### 实例化
> 有两种方式, 一种从堆中实例化, 一种从栈中实例化。

例如:

从栈中实例化对象
```cpp
class PEOPLE
{
public:
    char name[10];
    int type;

    void Sleep();
    void Study();
};

int main(void)
{
    PEOPLE people;
    PEOPLE people[10];
    return 0;
}
```

从堆中实例化对象
```cpp
class PEOPLE
{
public:
    char name[20];
    int type;

    void Sleep();
    void Study();
};

int main(void)
{
    PEOPLE *p = new PEOPLE();
    PEOPLE *q = new PEOPLE[20];

    //TODO
    delete p;
    delete q[];
    return 0;
}
```

从堆中实例化需要释放内存, 栈中不用。

##### 对象成员的访问

对象成员的访问方法。

栈对象的访问方法:
```cpp
int main (void)
{
    PEOPLE people;
    people.type = 0;
    people.Sleep();
    return 0;
}
```

堆对象的访问方法:
```cpp
int main (void)
{
    PEOPLE *p = new PEOPLE();
    p->type = 0;
    p->Sleep();
    delete p;
    p = NULL;
    return 0;
}
```

###### 小结 **堆和栈之间的区别**
内存的分配方式不同
* 1、栈区 (stack) , 由编译器自动分配释放, 存放函数的参数值, 局部变量的值等。 操作方式类似于数据结构中的栈。
* 2、堆区 (heap) , 一般由程序员分配释放, 若程序员不释放, 程序结束时可能由 OS 回收。 它与数据结构中的堆是两回事。

> 栈用 `.`, 堆用 `->`

如果是数组, 则可以:
```cpp
int main (void)
{
    PEOPLE *p = new PEOPLE[10];

    for (int i = 0; i < 10; i++)\
    {
      p[i] -> type = 0;
      p[i] -> Sleep();
    }
    delete []p;
    p = NULL;
    return 0;
}
```
访问一个类里面的数组, 那么要使用 `for` 语句。

| 初始化 string 对象的方式     |
| :------------- | :------------- |
| string s1;       | s1 为空串       |
| string s2("ABC") | 用字符串字面值初始化s2|
| string s3(s2)    | 将 s3 初始化为 s2 的一个副本|
| stirng s4(n,'C') | 将 s4 初始化为字符 'C' 的 n 个副本|

| string 的常用操作     |
| :------------- | :------------- |
| s.empty()      | 若 s 字符串为空, 则返回 true, 否则返回 false |
| s.size()       | 返回 s 中字符的个数   |
| s[n]           | 返回 s 中位置为 n 的字符, 返回新生成的串   |
| s1 + s2        | 将两个字符串连接成新串, 返回新生成的串|
| s1 = s2        | 把 s1 得内容替换为 s2 的副本|
| i == j         | 判断是否相等, 相等返回 true, 否则返回 false |
| i != j         | 判断不相等, 不等返回 true, 否则返回 false|

###### 数据的封装
> ...

###### 类外定义
两种方式: 1、同文件类外定义。2、(常用) 分文件类外定义。
`::` 这个在 cpp 中称为 **范围解析运算符**
```cpp
/*同文件类外定义*/
class char
{
public:
    void run();
    void stop();
    void changespeed();
};
void Car::run(){}
void Car::stop(){}
void Car::changespeed(){}
```

```cpp
/*分文件类定义*/
// Car.h
class char
{
public:
    void run();
    void stop();
    void changespeed();
};

// Car.cpp
#include "Car.h"
void Car::run(){}
void Car::stop(){}
void Car::changespeed(){}
```

定义一个头文件 `.h` , 然后再另一个 cpp 文件中使用。 在头文件里面定义 数据成员和声明成员函数。

h 文件需要包含常用库的头文件。
```cpp
#include <iostream>
#include <string>
using namespace std;
```

###### 内存按照用途划分的 5 个区

| 内存分区     |
| :------------- |
| 栈区 : int x = 0; int *p = NULL  |
| 堆区 : int *p = new int[20];|
| 全局区 : 存储全局变量及静态变量|
| 常用区 : string str = "alvinmi"; |
| 代码区 : 存储逻辑代码的二进制      |

栈区的特点就是内存由系统进行分配和控制。 堆区, 用 delete 来回收。

定义一个类, 在这个类被实例化之前是不会占用内存的。 对象的初始化: 两种类型, 有且只有一次的初始化, 和根据条件的初始化。

### 构造函数
> **重要**！ 作用就是初始化对象。在对象实例化的时候被自动调用。

* 构造函数要与类同名。    
* 构造函数没有返回值。
* 构造函数可以进行重载。

无参数构造函数:

```cpp
class Student
{
public:
    Student() { m_strName = "bob";}

private:
    string m_strName;
}
```

有参构造函数:
```cpp
class Student
{
public:
    Student(string name)
    {m_strName = name;}

private:
    stirng m_strName;
}
```

重载构造函数:
```cpp
class Student
{
public:
    Student() {m_strName = "bob";}

    Student(string name)
    {m_strName = name;}
private:
  string m_strName;

}
```

### 析构函数
> 在完成任务后被自动销毁, 为了释放内存。

定义格式: `~类名()` 例如:

```cpp
class Student
{
public:
    Student(){cout<<"这是构造函数"<<endl;}
    ~Student(){cout<<"这是析构函数"<<endl;}

private:
    string m_strName;
}
```

特点
* 如果没有自定义的析构函数, 则系统自动生成。
* 析构函数在对象销毁时, 自动调用。
* 析构函数没有返回值、没有参数也不能重载。

对象的声明历程：
`申请内存->初始化列表->构造函数->参与运算->析构函数->释放内存`。





###
