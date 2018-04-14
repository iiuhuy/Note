# Django 安装
Django 与 Python 版本安装关系

| Django Version    | Python Version   |
| :------------- | :------------- |
| 1.8            | 2.7、3.2(until)、3.3、3.4、3.5      |
| 1.9、1.1.0     | 2.7、3.4、3.5、3.6 |
| 1.11           | 2.7、3.4、3.5、3.6 |
| 2.0            | 3.4、3.5、3.6      |
| 2.1            | 3.5、3.6、3.7      |


## Windows 安装
* 使用 cmd 终端安装
    * 输入 `pip install Django == 1.11.4`, 然后等待。
    * 验证是够安装成功 `import django` `django.get_version()`

* 卸载 `pip uninstall Django`


## 01 创建新项目
找一个目录, 作为工程学习的地方。 不要有中文！

* 在适合的位置创建一个目录。
* 打开终端(cmd)进入该目录下(或者直接在该目录打开终端)。
* 输入 `django-admin startproject project`。
*


## 创建虚拟环境

* `python -m `
