# OrCAD Capture CIS
OrCAD Capture CIS 是 Cadence 公司的一款原理图设计软件。

学习就实践的过程, 是有一个过程的, 并且做好笔记。 一步步深入。

## 新建原理图
`File->new->Porj` , 接着命名, 存放的路径。OK！

## 快捷键记录

* 01 按下键盘的 `P` 键, 那么 Place Part 就会显示出来。
* 02 连线快捷键 `W` 键。
* 03 总线 `B` , 总线没有电气属性, 值表示连接关系。
* 04 元器件旋转 `R` 。
* 05 放置电源 `F`。
* 06 放置地 `G`。

### 设置纸张大小
options -> schematic page properties -> page size  


## 04 OrCAD Capture CIS 与 Allegro 交互布局
> 引用自 [吴传斌的博客](http://www.mr-wu.cn/cross-probing-between-orcad-capture-and-allegro/)

激活 OrCAD 与 Allegro 的交互程序

* 1. 在 Options->Preference 在 Miscellaneous 里勾选 `Intertool Commuication` 下的 **Enable Intertool Communication**.

* 2. 同时打开 OrCAD 原理图设计界面及 Allegro PCB Design 界面。 在 Allegro PCB Design 里需要激活 Place -> Manually 命令, 此时用鼠标左键选中 OrCAD 原理图中的元件, 右键 -> PCB Editor Select(Shift+S)。 此时在右侧的 Place 命令框的预览窗口就会出现该元件的封装预览, 把鼠标移至元件放置去, 就会出现该元件封装。
