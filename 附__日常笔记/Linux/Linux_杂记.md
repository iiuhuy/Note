* 熟练使用 Linux 系统，掌握常用的系统管理命令，如文件查找、创建用户、磁盘管理、进程管理等。
* 理解 TCP/IP，理解网络原理，会组网、配置路由器，掌握 Linux 系统下的 socket progamming，access point 创建等操作

# Linux 查看某个包是否安装

* `dpkg -l libuu*`


关于 Ubuntu 下的软件源, 软件源的列表就在 `/etc/apt/source.list` 这个列表里面。在 `/etc` 下的文件, 需要有 root 权限才能进行操作。

二进制文件放在了 `/usr/bin`, 库文件放在了 `/usr/lib`, 配置文件放在了 `/etc/`, 其他一些文档文件放在了 `/usr/share`, 还有一些数据放在了 `/var`。
