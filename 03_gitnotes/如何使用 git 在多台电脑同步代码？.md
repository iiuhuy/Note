如何使用 git 在多台电脑同步代码？ 提交到 GitHub！

1.像平时写代码一样，先创建一个工程，比如创建 qt 工程或者 vs 工程。

2.进入项目工程的文件夹，运行下面的命令创建 git 仓库。

	git init

3.然后添加 `.gitignore` 文件，关于这个文件的功能及创建方法可以参考这里。

4.将目前的文件添加到暂存区，其中`.`代表所有新创建或被修改的文件。

	git add .
	
5.提交本次修改。

	git commit -m "your commit message"

6.创建远程仓库，打开 github 的主页创建新的仓库，注意这里最好不要在仓库里初始化添加任何文件，否则后面会遇到麻烦。

7.添加远程仓库的链接。

	git remote add origin <url of your remote repository>

8.推送到远程仓库。

	git push
	
现在你可以在远程仓库查看是否推送成功

在另一台电脑上的话，你可以将远程仓库克隆的本地：

	git clone <url of your remote repository>

然后依次使用上面的步骤 4、5、8 即可将这台电脑的修改推送到远程仓库。如果决定使用 git 的话，建议深入学习下 git 的工作流程，建议 progit 这本书，官网有免费的电子版。