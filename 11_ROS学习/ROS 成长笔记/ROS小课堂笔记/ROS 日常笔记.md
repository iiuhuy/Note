#### ROS 小课堂 SVN 地址
>svn://101.132.35.195/ros_classroom_documents 

#### 发布 v1.1 版本 ubuntMate16.04 的 kinetic 完整版树莓派 3B 镜像
>https://pan.baidu.com/s/1cqCM7c

* 01 群主前几天发布了这个镜像, 安装到树莓派之后发现无法连接到 wifi, 点击 wifi 链接的图标没有反应。在 ` /etc/wpa_supplicant` 目录下没有 ` /etc/wpa_supplicant/wpa_supplicant.conf` 该配置文件。

    * 可能树莓派放的路径不一样, 到根目录下 `sudo find ./ -name "wpa_supplicant.conf"` 来搜索一下在哪个路径下面。

    * 虽然找到了 `wpa_supplicant.conf` 这个文件配置名是对的, 但是群主说内容分不对！ 待他后面实验测试一下。
