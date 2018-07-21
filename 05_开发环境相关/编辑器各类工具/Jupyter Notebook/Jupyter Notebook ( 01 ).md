# 0x01 What is Jupyter Notebook?
Jupyter Notebook, 以前又称为 IPython notebook, 是一个交互式笔记本, 支持运行 40+ 种编程语言. 可以用来编写漂亮的交互式文档.

Linux 下， Jupyter Notebook 的安装你可以参考 [Jupyter 官网](https://jupyter.readthedocs.io/en/latest/install.html), 其实只需要一句 `pip install jupyter ` 即可安装完成, 你也可以在 [GitHub](https://github.com/jupyter/notebook) 找到该项目，一些使用方法和技巧都可以找到。

使用 `jupyter notebook` 主要是用来记录一些带公式的笔记, 遇到 jupyter notebook 就使得这个记录的过程变得方便快捷 (可以使用 Python 画相关的图形)。

在浏览器中直接编辑，能把数据图表，代码，基于 Markdown 的文字笔记，数学公式直接显示出来，非常方便。 GitHub 也支持这类格式，不过反应是慢了点， 但你可以通过 [nbviewer](https://nbviewer.jupyter.org/) 来完美支持它。

由于我是在 Windows 下学习 Python 和数学，所以较好的开发环境是下载安装 [Anaconda](https://www.continuum.io/downloads) 即可, (PS: 如果下载太慢, 使用清华镜像会比较快)。


# 0x02 运行 Jupyter notebook

安装完成 Anaconda 后， 你会在菜单栏看到如下 `jupyter notebook` 的软件。

![Jupyter notebook](http://i.imgur.com/hIuDvwu.png)

也可以使用命令行的方式打开： `Ctrl+R`, 输入 `cmd`, 在命令行输入 `jupyter notebook`。

稍等一下就能在浏览器中打开 Jupyter notebook 了。 推荐使用 Google Chrome！ 启动后的主页面如下：

![](http://i.imgur.com/ep0vh5r.png)

新建一个 notebook ,点击 `new` 即可，支持 markdown 语法， Latex, Mathjax 语法。就可以愉快的进行编辑啦。

notebook 的界面包括以下几部分：

  * notebook 的名称。
  * 主工具栏、提供了保存、导出、重载 notebook ，以及重启内核等选项。
  * 快捷键
  * notebook 的编辑区。

慢慢熟悉界面的菜单和选项，详细可以查看菜单右栏的帮助菜单。

# 0x03 使用方法
`Jupyter notebook`的使用方法可以参考:

* [getting-started-Jupyter-notebook-1](https://www.packtpub.com/books/content/getting-started-jupyter-notebook-part-1) & [getting-started-Jupyter-notebook-2](https://www.packtpub.com/books/content/getting-started-jupyter-notebook-part-2)
* 也有人将这篇文章翻译过来了，[Jupyter notebook 快速入门](http://codingpy.com/article/getting-started-with-jupyter-notebook-part-1/)，也可以谷歌、百度。

### Jupyter Notebook 实现的效果

网上搜索会有很多 Jupyter Notebook 写的页面效果，例如:

* [01、XKCD plots in Matplotlib](http://nbviewer.jupyter.org/url/jakevdp.github.com/downloads/notebooks/XKCD_plots.ipynb) 仿制XKCD式手写图标。
* 02、各种用Notebook写出的Python教程
	* [Exploratory computing with Python](http://mbakker7.github.io/exploratory_computing_with_python/)
	* [中文 Python 笔记](http://lijin-thu.github.io/)
* [03、Colour Science for Python](http://nbviewer.jupyter.org/github/colour-science/colour-ipython/blob/master/notebooks/colour.ipynb)
* [04、以卡尔曼和贝叶斯滤波器为基础的信号处理教程](http://nbviewer.jupyter.org/github/rlabbe/Kalman-and-Bayesian-Filters-in-Python/blob/master/table_of_contents.ipynb)
* [05、如果英文水平不错,可以直接去看看源码](https://github.com/jupyter/jupyter/wiki/A-gallery-of-interesting-Jupyter-Notebooks)
* [06、Notebook Gallery](http://nb.bianp.net/sort/views/)

>jupyter notebook。


# 0x04 Jupyter Notebook 修改一打开文件夹目录
> 将 Jupyter Notebook 打开的目录修改为自己的的目录

* 打开 `Anaconda Prompt` 类似窗口命令的窗口。

* 输入命令 `jupyter notebook --generate-config`

* 打开 `C:\Users\Administrator\.jupyterjupyter_notebook_config.py` 修改 `#c.NotebookApp.notebook_dir = ''`为 `c.NotebookApp.notebook_dir =  u'E:\\4_Person\\08、JupyterNotebook'`。(目录改为你自己的目录)。

* 开始菜单找到 `jupyter notebook` 快捷键，右键 -> 属性 -> 打开文件所在位置，找打快捷方式在文件中的位置，右键 -> 属性 -> 目标，去掉最后的 `%USERPROFILE%`。 现在点击快捷方式就可以直接在你想要默认打开的文件夹启动了。

> 美滋滋!
