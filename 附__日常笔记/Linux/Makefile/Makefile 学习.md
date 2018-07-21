# Makefile 详解
> 百度贴吧: [Makefile 详解（超级好）](https://tieba.baidu.com/p/591519800?red_tag=3241787878) 很早之前陈皓写的了。


# Make 介绍
make 执行命令的时候, 需要一个 Makefile 文件, 以告诉 make 怎样去编译和链接程序。

用一个实例来认识 makefile 的书写规则, 示例源于 GNU 的 make 使用手册。在这个示例工程中, 有 8 个 C 文件, 和 3 个头文件, 需要我们写一个 Makefile 来告诉 make 命令如何编译和链接这几个文件。 规则如下 :

* 如果这个工程没有编译过, 那么我们所有的 C 文件 都需要编译并且被链接。
* 如果这个工程中某几个 C 文件被修改过, 那么只需要编译被修改过的 C 文件, 并链接到目标程序。
* 如果这个工程的头文件被修改了, 那么我们需要编译引用了这个头文件的 C 文件, 并链接到目标程序。

## Makefile 规则
先简单的看一下 Makefile 的规则。

```makefile
target ...:prerequisites ...
command
...
...
```

* target 就是一个目标文件, 可以是 Object File, 也可以是执行文件。 还可以是标签(Label), 对于标签这种特性, 后续学习 **伪目标** 章节总会涉及。
* prerequisites 就是, 要生成那个 target 所需要的文件或者是目标。
* command 也就是 make 需要执行的命令。(任意的 Shell 命令)

下面开始第一个示例。 也就是前面说的 8 个 C 文件和 3 个头文件。那 Makefile 可以是这样子的。

```Makefile
edit: main.o kbd.o command.o display.o\
insert.o search.o file.o utils.o
cc -o edit main.o kbd.o command.o display.o\
insert.o search.o file.o utils.o

main.o : main.c defs.h
cc -c main.c
kbd.o : kbd.c defs.h command.h
cc -c kbd.c
command.o : command.c defs.h command.h
cc -c command.c
display.o : display.c defs.h buffer.h
cc -c display.c
insert.o : insert.c defs.h buffer.h
cc -c insert.c
search.o : search.c defs.h buffer.h
cc -c search.c
file.o : file.c defs.h buffer.h command.h
cc -c file.c
utils.o : utils.c defs.h
cc -c  utils.c
clean:
rm edit main.o kbd.o command.o display.o\
insert.o search.o file.o utils.o
```
