# 个人 Linux 常用命令

- 1、查看 SD 储存卡剩余空间
    ```
    `df -h` 显示已挂载的分区列表
    `du -h` 列出文件或文件夹的大小
     du -h 文件名，可以列出这个文件有多大，列出方式是以人比较好看懂的方式。不像 ls -l列出的都是以字节为单位。
     ```

- 2、查看 ip 地址
    `ifconfig`

- 3、压缩
    `tar -zcvf filename.tar.gz`

- 4、解压
    `tar -zxvf filrname.tar.gz`

    文件打包压缩与解压缩
    	tar -czvf dir.tar.gz dir/		将dir目录打包成dir.tar.gz
    	tar -cjvf dir.tar.bz2 dir/		将dir目录打包成dir.tar.bz2
    	tar -zxvf dir.tar.gz 			解压缩dir.tar.gz
    	tar -jxvf dir.tar.bz2			解压缩dir.tar.bz2

- 5、常用 apt(Advanced Package Tool) 软件安装工具命令
    * `sudo apt-get install xxx` 安装xxx软件
    * `sudo apt-get update` 更新软件列表
    * `sudo apt-get upgrade`    更新已经安装的软件
    * `sudo apt-get remove xxx` 删除xxx软件

- 6、查看操作系统版本
    `cat /proc/version`

- 7、查看主板版本
    `cat /proc/cpuinfo`

- 8、`pwd`
    以绝对路径的方式显示用户当前工作目录。

- 9、格式化文件系统
    ```
    mkfs	/dev/hd1
	mkfs -t vfat 32 -F /dev/hd1		创建一个FAT32文件系统
    ```

- 10、mount/umount
    ```
    功能：用来挂载磁盘到文件系统中
    举例：
        mount -t nfs -o nolock 192.168.1.141:/root/rootfs /mnt	挂载
	    umount /mnt 卸载
    ```

- 11、查看系统信息
    `uname`， 例如: uname -a

- 12、sed和awk
    正则表达式。匹配加替换。

- 13、开机和关机
    ```
	shutdown -h now		立即关机
	init 0				关机
	shutdown -r now		立即重启
	reboot				重启
    ```

- 14、find
    ```
    功能：在 linux 文件系统中，用来查找一个文件放在哪里了。
    举例：find /etc -name "interfaces"
    总结：
    (1)什么时候用 find？
       当你知道你要找的文件名，但是你忘记了它被放在哪个目录下，要找到该文件时，用 find。
    (2)怎么用 find？
	   find 路径 -name "文件名"
    ```

- 15、grep
    ```
    功能：在一个文本文件中，查找某个词。
    举例：grep -nr "SUN" *
    总结：
    (1)什么时候用 grep？
        当你想查找某个符号在哪些地方（有可能是一个文件，也有可能是多个文件组成的文件夹）出现过，就用 grep
    (2)怎么用？
    	grep -nr "要查找的符号" 要查找的目录或文件集合
    注意：-n 表示查找结果中显示行号，-r 表示要递归查找
    ```

- 16、which 和 whereis
    ```
    功能：查找一个应用程序（二进制文件）在哪里
    举例：which ls 		whereis ls
    区别：
    	which只显示二进制文件的路径
    	whereis显示二进制文件的路径，和其源码或man手册位置
	```

- 17、权限管理
    ```
    作用：用来管理系统中文件的权限。
    	chmod （change mode）修改文件权限，比较常用，要记得
    	chown （change owner，修改属主）
    	chgrp （change group，修改文件的组）
    ```

- 18、网络配置命令
    ```
	ifconfig eth0 192.168.1.13		设置IP地址
	ifconfig eth0 up             		启动网卡
	ifconfig eth0 down	      		禁用网卡
	ifup eth0						    启动网卡
	ifdown eth0						禁用网卡
	ifconfig eth0 192.168.1.1 netmask 255.255.255.0	   同时设置IP和子网掩码
    ```

- 19、 sed & awk






























# 相关命令备忘(这是一个网友的, 先放到这里, 后续做整理)

* 1、挂载 VirtaulBox 的. vdi 虚拟磁盘：
```
sudo modprobe nbd
sudo qemu-nbd -c /dev/nbd0  ~/VirtualBox\ VMs/DOS7.1/DOS7.1.vdi
sudo mount /dev/nbd0p1 /mnt

```

* 2、解挂载：
```
sudo umount /mnt
sudo qemu-nbd -d /dev/nbd0

```

* 3、压缩，会替代原文件：
`gzip data.sql`

* 4、解压：
` gzip -d data.sql.gz`

* 5、刻录系统安装 U 盘：
`sudo dd if=kali-linux-2.0-amd64.iso of=/dev/sdb`

* 6、查看刻录进度：
`sudo watch -n 5 pkill -USR1 ^dd$`

* 7、网站镜像：
` wget -m-p -E -k -K -np -v http://www.xxx.xxx`

* 8、firefox 启动参数：
`firefox -marionette`

* 9、一个自定义的有趣命令
` alias fun='fortune \| cowsay -f $(ls /usr/share/cowsay/cows \| sort -R \| head -n 1)'`

* 10、jekyll 显示草稿：(感觉用不到)
`jekyll s --drafts`

* 11、字符化图片:
```
mplayer -vo caca xxx.jpg
ffplay xxx.jpg
```

* 12、用 wget 镜像网站:
`wget -m -p -E -k -K -np -v http://www.wangning.site`

* 13、查看无线网卡是否支持 monitor 模式
`iw list`

* 14、将无线网卡设置为 monitor 模式:
```
sudo ifdown wlan0
sudo iwconfig wlan0 mode monitor
sudo ifconfig wlan0 up
```

* 15、查看无线网卡信道:
` iwlist wlan0 channel`

* 16、设置无线网卡监听信道
`iwconfig wlan0 channel 11`

* 17、合并多个 pdf 文件（可能会导致合并后的 pdf 在 Windows 下标题有重影，模糊不清）
` gs -q -dNOPAUSE -sDEVICE=pdfwrite -sOUTPUTFILE=Linuxidc.pdf -dBATCH \*.pdf`

* 18、一行 Python 搞定静态文件服务器
`  python -m SimpleHTTPServer`

* 19、gcc 编译时禁用堆栈保护
`gcc -fno-stack-protector -o strackoverflow strackoverflow.c`

* 20、利用 ssh 设置 sock5 代理
```
ssh -qTfnN -D 7000 username@xxx.xxx
    -q Quiet mode. 安静模式，忽略一切对话和错误提示。
    -T Disable pseudo-tty allocation. 不占用 shell 了。
    -f Requests ssh to go to background just before command execution. 后台运行，并推荐加上 -n 参数。
    -n Redirects stdin from /dev/null (actually, prevents reading from stdin). -f 推荐的，不加这条参数应该也行。
    -N Do not execute a remote command. 不执行远程命令，专为端口转发度身打造。
```

* 21、打包 war 文件
`jar -cvf myshell.war shell.jsp`

* 22、Ubuntu 中配置开机启动服务
`sysv-rc-conf`

* 23、Python 的交互式 shell
`python -c 'import pty;pty.spawn("/bin/sh")'`

* 24、搜索文件名 / 目录名：
`locate filename`

* 25、VirtualBox 中无界面模式启动与关闭虚拟机：
```
VBoxManage startvm MyTarget --type headless
VBoxManage controlvm MyTarget poweroff
```

mysql 命令

* 1、数据库导出为. sql 文件：
`mysqldump -u root -p databasename tablename > xxx.sql`

* 2、把. sql 文件导入为数据库：
`mysql -u root -p databasename < xxx.sql`

* 3、指定字符集为 utf8 创建数据库：
`CREATE DATABASE databasename DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;`

* 4、mysql 导入 csv 文件：
`LOAD DATA INFILE 'test.csv' INTO TABLE info  FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n';`

---

- ※ linux命令行中一些符号的含义：
    ```bash
	.		代表当前目录
	..	    代表上一层目录，当前目录的父目录
	-		代表前一个目录，我刚才从哪个目录cd过来
	~		代表当前用户的宿主目录
	/		代表根目录
	$		普通用户的命令行提示符
	#		root用户的命令行提示符
	*		万能匹配符
    ```

    宿主目录：所谓宿主目录，就是操作系统为当前用户所设计的用来存放文件、工作的默认目录。如 Windows 中的 "我的文档" 目录，就是 Windows 为我们设计的宿主目录。
    Linux 中每个用户都有自己的宿主目录，这个目录对于普通用户来说，在 /home/username/，而对于 root 用户来说，在 /root 。
