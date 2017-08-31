---
title: SSH 和 Samba 工具
date: 2017-08-26 01:39:37
tags: 嵌入式
---

#Linux 下 SSH 和 Samba 工具的搭建。

搭建这个工具主要是工作中在 Windows 下虚拟机和 Linux 中实现文件的共享。而且很方便！当然方法很多。

## ssh
### 客户端
#### 安装客户端

`# apt-get install ssh`

如果安装失败, 则使用下面的命令进行安装 (客户端不是必须的，在 Windows 下我们需要安装服务端可操作。)

`apt-get install openssh-client`

#### SSH 登录

    $ ssh 192.168.0.0
	$ ssh -l alvinmi 192.168.0.0
	$ ssh alvinmi@192.168.0.0

### 服务端
#### 安转服务器

`sudo apt-get install openssh-server`

然后根据下面的命令启动 ssh.

	# /etc/init.d/ssh stop             #停止
	# /etc/init.d/ssh start            #启动
	# /etc/init.d/ssh restart          #重启

#### SSH 配置

修改配置文件 `/etc/ssh/sshd_config`，并重新启动。

	# /etc/init.d/ssh restart

ssh 默认端口是 22 , 如果需要自行更改。(我默认 22 )

	Port 22

ssh 配置 root 登录, 可以修改配置表禁止其登录(注意: Ubuntu 14.04，默认是禁止 root 登录的。)

	PermitRootLogin no     //不准root登陆
	PermitRootLogin yes    //允许root登陆

然后就能在 Windows 下使用 Putty、SecureCRT、SSH Secure 进行登录。

Linux 下使用 `ifconfig` 查看 ip.

# Samba

>可以参考: [Linux 中 Samba 详细安装](http://www.cnblogs.com/whiteyun/archive/2011/05/27/2059670.html)

#### 服务查询

>rpm -qa | grep samba

如果没有安装 rpm ， 就安装 rpm, 然后再安装 Samba。
`sudo apt-get install rpm`

#### 安装 Samba 

>sudo apt-get install samba
 
#### 配置 smb.conf 文件

修改配置之前, 可以备份 Samba 配置文件。
	
	cd /etc/samba/
	tar -cvf smb.tar smb.conf
	ls
会看到 `smb.tar` 文件

#### 编辑配置文件

> vim /etc/samba/smb.conf

在文件底部增加修改内容。

	[mysamba]
			comment = alvinmi's file share
			path = /home
			read only = no
			public = yes
			writable = yes
			printabke = no
			create mask = 0765

其他配置或者配置详解网上找吧！

#### 启动 Samba 服务
启动 Samba 命令，在命令行输入: `smbd` 即可运行。
或者 `sudo /etc/init.d/smbd restart` 即可。

>这样配置起来就只能在 Windows 下进行操作。很方便、快捷。

在 Windows 下映射网络驱动器, `\\192.168.0.0` ip 填你自己的即可。就能共享文件了！

如果传输文件的时候，提示需要权限访问！使用 `chmod 777 /home` 即可。 根据你自己配置的路径来设置！
