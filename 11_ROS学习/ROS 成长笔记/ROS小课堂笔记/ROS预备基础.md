
>「 ROS 的设计目标是把机器人的控制和传感器处理的软件和它的硬件隔离开，用上 ROS 以后，你可以方便地用到很多能直接跑的软件代码。但是 ROS 从入门到精通需要至少一年以上的时间，你必须不断地用，不断地尝试新的代码和硬件，才能对它熟悉起来。 」

# ROS 预备预备基础

* [ ] Linux 基础

* [ ] vim 编辑器

* [ ] Git 实战教程
* [ ] GDB 简明教程

* [ ] 玩转 Makefile
* [ ] 数据结构

* [ ] Python 使劲写代码教程
* [ ] C 语言入门到放弃使劲写代码教程

* [ ] GitHub 实战教程
* [ ] C++ 实战教程


## 图形概念

* [Nodes](http://wiki.ros.org/Nodes):  节点, 一个节点即为一个可执行文件，它可以通过 ROS 与其它节点进行通信。
* [Messages](http://wiki.ros.org/Messages): 消息，消息是一种 ROS 数据类型，用于订阅或发布到一个话题。
* [Topics](http://wiki.ros.org/Topics):  话题, 节点可以发布消息到话题，也可以订阅话题以接收消息。
* [Master](http://wiki.ros.org/Master): 节点管理器，ROS 名称服务 (比如帮助节点找到彼此)。
* [rosout](http://wiki.ros.org/rosout):  ROS 中相当于 stdout/stderr。
* [roscore](http://wiki.ros.org/roscore): 主机 + rosout + 参数服务器 (参数服务器会在后面介绍)。
