---
title: '解决Git提交, 文件路径太长问题'
date: 2017-04-21 15:57:20
tags: git

---

今天在使用 git 备份自己之前基于 Hexo + GitHub Pages 搭建的博客遇到的问题。

主要遇到的问题就是提交文件的时候， 有个文件的路径太长导致提交不了。



```
git config --system core.longpaths true
```

然后再提交就可以了。