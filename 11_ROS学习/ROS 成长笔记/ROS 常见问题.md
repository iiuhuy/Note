# ROS 常见问题 FAQ

* 在同一台 Ubuntu 电脑可以安装多个不同的 ROS 版本吗？
    * 可以！ 只需要 source 不同的 setup.bash 就可以。
    * source /opt/ros/indigo/setup.bash
    * source /opt/ros/jade/setup.bash
    * source /opt/ros/kinetic/setup.bash

* 多台 ROS 怎么通信？
    * 修改 `.bashrc` 文件
    * Master:
        * export ROS_HOSTNAME=192.168.1.102
        * export ROS_MASTER_URI=http://192.168.1.103:11311
    * Slave A
        * export ROS_HOSTNAME=192.168.1.103
        * export ROS_MASTER_URI=http://192.168.1.103:11311

* 做 ROS 使用串口的时候, 会遇到权限问题?
    * chmod 方式给权限 or 直接将当前用户加入到 `dialout` 组中(建议, 这样以后就一直有串口使用了)。
    * 使用这个命令来将当前的用户添加到 `dialout` 组中, `sudo usermod -aG dialout xxx`, xxx 就是当前系统用户名。
    * 然后 logout 或者重启下系统就行了, 通过 groups 命令就可以看到当前用户已经在 dialout 组了, 方便以后随便控制串口。 
