> 先参考 官方论坛 [关于 env 工具的常见问答](https://www.rt-thread.org/qa/thread-5699-1-1.html)

第四点有说到, 可以在官网的相关下载找到 env 工具的[下载链接](https://www.rt-thread.org/page/download.html)。

根据 [env 工具使用手册](https://github.com/RT-Thread/rtthread-manual-doc/blob/master/zh/5chapters/01-chapter_env_manual.md)。


> 注：可以使用 env 内置命令 pkgs --upgrade 来更新软件包列表和 env 的功能代码.

## 如何学习使用 env 呢？
>同上, 根据 env 工具使用手册。

* 下载完 env 后, 查看 env 文件夹下的 env 工具介绍 ppt, 跟着 ppt 里面的动图进行操作一次 (注意 ppt 中的都是动图)，可以初步入门 env 工具的使用。(没发现有 PPT)

* 在 env 下使用 scons 和在 Windows 的 cmd 中使用是一样的, 编译和生成工程的命令都相同, 使用 `scons--target=mdk/mdk4/mdk5/iar/cb -s` 生成相应的工程并在工程中编译，或者直接使用 scons 命令使用 gcc 工具链编译 bsp。
