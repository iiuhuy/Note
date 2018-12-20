# Ubuntu 16.04 + 64bit 系统重装初始配置
有时候可能由于环境、依赖、GUI等问题导致系统需要重装！记录一下个人的电脑重装后安装的环境. 至于怎么装, 这里不赘述了, 网上找教程折腾就完事儿了。

## Ubuntu 下将终端背景设置成透明
这样有时候网上的命令就可以看到直接敲了。
只需要打开终端在标题栏的编辑里面设置就行。
## 软件
- 科学上网工具
ss || ssr(最好还是自己花点钱和朋友合租一个。)

这个是必须的, Ubuntu 16.04 下, 由于界面的一下限制原因, 导致比在 Windows 下更折腾一点, 不过网上都有解决的方案。

> [shadowsocks QT5]()

## Chrome 
这个是必备的, 加上很多插件, 玩起来真是太爽了。在这里[下载安装](https://www.google.com/chrome/browser/desktop/)。或者其他方法。

可以查看我的 [Chrome 插件篇]()， 首先说这里吧, 需要安装 [Proxy Switch Omega](https://github.com/FelisCatus/SwitchyOmega) 插件, 因为 Ubuntu 下代理服务的限制, 就算你 Ubuntu 下能科学上网, 在 Chrome 中还未必能上。 所以需要设置一下。
网上搜 shadowsocks + Ubuntu + Switch Omega 。

## 搜狗拼音

## Git
现在主流的版本控制工具, 开发前需要做简单的配置。
- 配置 git
    ```
    git config --global user.name "your username"
    git config --global user.email "your email"
    ```
- 生成本地公钥
    ```
    ssh-keygen -t rsa
    cat ~/.ssh/id_rsa.pub
    ```
    将生成的公钥复制到 github/gitlab 之类的仓库中。

## VSCode
目前比较火的开源编辑器了, 以前我也通过 Atom, 这个快很多。安装几个常用的几个插件：
### 首要插件 `Sync`
因为如果你有好几台电脑的话, 不可能每次换电脑都重新配置的。这不是浪费时间吗？以前用 Atom 的时候, 有 Sync 插件, VSC 也同样有的。例如 VSC 的 `Setting Sync` 插件, 可以轻松从 github 备份拉取, 然后重启 IDE。
- 1.首先从插件库安装 `Setting Sync`.
- 2.然后 `Ctrl/Command + Shift + P` 打开控制面板, 搜索 `Sync`, 选择`update/upload` 可以上传自己的配置, 选择 `Download` 会下载远程的配置。
- 3.如果是第一次使用的话, 在上传的时候需要授权在 Github 上创建一个授权码, 允许 IDE 在 gist 中创建资源, 下载远程配置。有了授权码后回到 vsc 直接填入 gist 的 id 就行了。。
- 4.或者登录自己 `github>Your profile> settings>Developer settings>personal access tokens>generate new token`，输入名称，勾选 `Gist`，提交。还是按照之前的方式, 打开命令面板, 输入 sync , 输入 id。  

- 1.`ESLint`, 检查代码格式。
- 2.`Insert Date String`, 插入日期的字符串, 有时候会用到, 或者经常写博客的时候会用到。
- 3.`Prettify JSON`, 格式化 JSON 文件。
- 4.`Markdown Preview`, 预览 Markdown 文件。
- 5.`View In Browser`, 打开 HTML 文件。
- 6.`File Peek`, 类似于 Go To Definition， 点击后定位文件。
- EditorConfig for VS Code
- HTML Snippets
- language-stylus
- Path Intellisense
- Prettier
- Vetur     -- VUE 的工具.
- Beautify  -- 代码格式化
- Debugger for Chrome  -- 在 Chrome 上调试的插件， 打断电直接在 VSCode 调试
- jQuery Code Snippets
- npm Intellisense (对 package.json 内中的依赖包的名称提示)
- Path Intellisense (文件路径补全)
- cssrem (px 转换为 rem)
- CSS Modules (对使用了 css modules 的 jsx 标签的类名补全和跳转到定义位置 )

React 插件相关:
- Reactjs code snippets 代码提示类插件
- react-beautify
- React Native Tools
- React Redux ES6 Snippets 
- JavaScript (ES6) code snippets
- Typescript React code snippets  这是 tsx 的 react 组件


### 关于 Visual Studio 代码无法监视此大型工作空间中的文件更改 -- 记录一下, 以便今后查找
由于我是很多文件放到一个目录下的, 所以每次打开 VSCode 的时候, 右下角会弹出 `Visual Studio 代码无法监视此大型工作空间中的文件更改` 英文的是 `Visual Studio Code is unable to watch for file changes in this large workspace`。

然后去到官网看了一下, 需要对本地的配置文件设置一下:
- 1.查看现有文件, 监控数目:
    ```
    cat /proc/sys/fs/inotify/max_user_watches
    ```
    我的显示的是 8192, 这个 Ubuntu 16.04 下的默认值, 其他系统以具体的为准。 
- 2.考虑到实际监控文件的时候, 会消耗内, 我将新的文件数目为原来的 10 倍, 即 81920, 使用 vi 或者 gedit 进行编辑。
    ```js
    sudo vi /etc/sysctl.conf
    ```
    在这个配置文件里面最后加上这句:
    ```js
    fs.inotify.max_user_watches=81920
    ```
- 3.使配置文件的新文件监控数目生效
    ```
    sudo sysctl -p
    ```
    然后:
    ```
    cat /proc/sys/fs/inotify/max_user_watches
    ```

    输出结果为 81920。
    现在重新打开 VSCode 就不会有这个警告消息了。

## NodeJS
前端开发必备, 主要是换源, 添加常用的全局模块。
安装 node 环境:
- nvm
- nrm
- npm
```js
npm i -g nrm http-server
nrm use taobao
yarn config set registry 'https://registry.npm.taobao.org'
```

未完...

## oh-my-zsh
[oh-my-zsh](https://github.com/robbyrussell/oh-my-zsh). 

- 1.安装 zsh
```
sudo apt-get install zsh
```
- 2.把默认的 shell 设置成 zsh
```
chsh -s /bin/zsh
```
出现 PAM 认证问题就修改 `/etc/passwd` 下的文件。
- 3.安装 oh-my-zsh
用于快速配置 zsh
```
sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
```
- 4.安装插件和配置主题. 

## 安装 python-Anaconda!
[Anaconda](https://www.anaconda.com/download/#linux)

下载完成后运行 

```
bash 下载安装包的名字即可自动安装
```


## 安装 VLC
```
sudo add-apt-repository ppa:videolan/master-daily
sudo apt-get update
sudo apt-get install vlc
```

## 安装录屏软件 kazam
有时候需要在 Ubuntu 下录制屏幕, 所以找了一下录屏软件. 有一款简单易用的.
```
sudo apt-get install kazam
```
安装后, 打开是一款很简洁的界面. 自己研究一下, 很快就上手了. 不行就网上搜一下. 个人觉得很好用.

## 安装 Andriod Studio

## 安装 VirtualBox
VirtualBox 下载地址: https://www.virtualbox.org/wiki/Linux_Downloads

### 安装模拟器 Genymotion
https://www.genymotion.com/thank-you-freemium/


## 安装 zeal
离线 API 文档
```
sudo apt-get install zeal
```

然后我是将离线文档下载到自己本地盘的目录。不要和系统盘放一个目录。

## 安装全网音乐软件
http://listen1.github.io/listen1/ 
我放到了 `/opt/my_software` 目录下面。

## inkscape 矢量图软件(跨平台)
Ubuntu 下直接就有。 

## Filezilla Client
```
sudo apt-get install filezilla
```

## 安装 CSS 预编译器 Sass
- 需要先安装 ruby
- 再装 Sass