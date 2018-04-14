# Altium  Designer 09

P+N						添加net
C+C						项目编译
P+L 						布线快捷键
U+选NET，点布线		删除NET之间的布线
L						调出BORDLAYERS
P+D+L					量尺寸
Ctrl+拖拽				SCH下连线跟着器件走
Shift+拖拽				SCH下复制元器件
Shift+A 					调用蛇形走线，再按1和2改变转角，按3和4改变间距，按，和。改变宽窄
Ctrl+M 					测量快捷，Q是公尺和英尺切换
空格键					在交互布线的过程中，切换布线方向。这很常用
主键盘上的1				在交互布线的过程中，切换布线方法（设定每次单击鼠标布1段线还是2段线）。
主键盘上的2				在交互布线的过程中，添加一个过孔，但不换层。
Shift+S					切换单层显示和多层显示
Q 						在公制和英制之间切换。
Shift+空格键				在交互布线的过程中，切换布线形状
J，L 					定位到指定的坐标的位置。这时要注意确认左下角的坐标值，如果定位不准，可以放大视图并重新定位，如果还是不准，则需要修改栅格吸附尺寸。（定位坐标应该为吸附尺寸的整数倍）
J，C					定位到指定的元件处。在弹出的对话框内输入该元件的编号。
R，M					测量任意两点间的距离
R，P					测量两个元素之间的距离。
G，G					设定栅格吸附尺寸
O，B					设置PCB属性
O，P					设置PCB相关参数
O，M					设置PCB层的显示与否
D，K					打开PCB层管理器
E，O，S					设置PCB原点
E，F，L 					设置PCB元件（封装）的元件参考点。（仅用于PCB元件库）元件参考点的作用：假设将某元件放置到PCB中，该元件在PCB中的位置（X、Y坐标）就是该元件的参考点的位置，当在PCB中放置或移动该元件时，鼠标指针将与元件参考点对齐。如果在制作元件时元件参考点设置得离元件主体太远，则在PCB中移动该元件时，鼠标指针也离该元件太远，不利于操作。一般可以将元件的中心或某个焊盘的中心设置为元件参考点。
E，F，C 				将PCB元件的中心设置为元件参考点。（仅用于PCB元件库）元件的中心是指：该 元件的所有焊盘围成的几何区域的中心
E，F，P 					将PCB元件的1号焊盘的中心设置为元件参考点。（仅用于PCB元件库）CTRL+F	在原理图里同快速查找元器件



## A.1环境快捷键
Ctrl+O					打开ChooseDocumenttoOpen(选择文档)对话框
Ctrl+F4					关闭当前文档Ctrl+S保存当前文档
Alt+F4					关闭AltiumDesigner
Ctrl+Tab 					遍历已打开文档（向右）
Shift+Ctrl+Tab 			遍历已打开文档（向左）
拖动文件到AltiumDesignerk中		将文档以自由文档的形式打开
Shift+F4					平铺已打开的文档

Shift+F5 					在活动面板和工作区间切换
移动面板的同时按下Ctrl 	防止面板的自动入坞、分组或边沿吸附

## A.2工程快捷键
C,C						编译当前的工程
C,R						重新编译当前工程
C,D						编译文档
C,O 						打开当前工程的Options或Project对话框
Ctrl+Alt+O				打开当前工程的Options或Document对话框
C,L						关闭活动工程的所有文档
C,T,L 					打开当前工程的LocalHistory

## A.4编辑器快捷键
1.原理图和PCB编辑器公共的快捷键
Shift						提高滚动速度
Y						放置对象的时候沿着Y轴转
X						放置对象的时候沿着X轴翻转
Ctrl+Shift+↑↓←→		按照方向键指向移动已选对象10个栅格
Shift+↑↓←→			按照方向键指向移动已选对象10个栅格
Ctrl+↑↓←→			按照方程键指向移动已选对象1个栅格
↑↓←→				按照方向键指向移动光标一个栅格
Esc						从当前处理中退出
End						刷新屏幕
Home					定位中心到光标同时刷新屏幕
Ctrl+Home				跳转到绝对原点(工作区的左下角)
Ctrl+鼠标滚轮下(或PageDown)		缩小
Ctrl+鼠标滚轮上(或PageUp)			在光标处放大(先定位到光标处,再放大)
鼠标滚轮				上下滚动
Shift+鼠标滚轮			左右滚动
A						显示排列子菜单
B						显示工具栏子菜单
J						显示跳转子菜单
K						显示工作区面板子菜单
M						显示移动子菜单
O						弹出右键选项菜单
S						显示选择子菜单
X						显示取消选定子菜单
Z						带缩放命令的弹出菜单
Ctrl+Z					撤销
Ctrl+Y					重新执行
Ctrl+A					全选
Ctrl+C(或Ctrl+Insert)		复制
Ctrl+X(或Shift+Delete)		剪切
Ctrl+V(或Shift+Insert)		粘贴
V,D						查看文档
V,F						查看符合的已放对象
X,A						全部取消选中
按住					右键显示捉取表示并进入滑动视图
单击					选中/取消选中光标上的对象
右击					弹出浮动菜单或退出当前操作
右击并选择Find Similar选项		将光标所指对象载入到Find Similar Objects对话框
按住左键并拖动鼠标		在区域内选中
按住左键				移动光标下选中的对象
双击					编辑对象
Shift+单击				从选中集合中添加或移除对象
Tab						放置的时候编辑属性
Shift+C					清除当前的过滤
Shift+F					单击对象以显示Find Similar Objects对话框
Y						弹出快速查询菜单
F11						切换Inspector或面板的开关
F12						切换过滤器面板的开关
Shift+F12				切换List面板的开关
Alt+F5					切换全屏模式

单击					在目标文档中交叉探测对象,并保持在源文档中
Ctrl+单击				在目标文档中交叉探测对象,并跳转到目标文档中
Shift+Ctrl+T				以顶栏排列选中对象
Shift+Ctrl+L				以左边栏排列选中对象
Shift+Ctrl+R				以右边栏排列选中对象
Shift+Ctrl+B				以底栏排列选中对象
Shift+Ctrl+H				水平平铺选中的对象
Shift+Ctrl+V				垂直平铺选中的对象
Shift+Ctrl+D				按照栅格排列对象
Ctrl+数字n				将当前选中对象存入存储单元n中
Alt+数字n				调出存储单元n的对象
Shift+Alt+数字n			调出存储单元n的对象并添加到工作区的已选对象中
Shift+Ctrl+数字n			按照存储单元n中的对象来执行过滤
2.仅在原理图编辑器中有效的快捷键
G						在跳转栅格设置间循环切换
F2						交替编辑
Ctrl+Page Down			调整视图以适合所有对象
Space					移动对象时逆时针90°旋转/放置导线、总线、直线时切换转角模式，
Space					使用高亮绘图时切换颜色
Shift+Space				移动对象时逆时针90°旋转/放置导线、总线、直线时在放置模式间循环切换
Ctrl+Space				拖动对象时顺时针90°旋转
Shift+Ctrl+Space			拖动对象时逆时针90°旋转，
Ctrl+在接口或图纸入口上单击		使用高亮画笔时高亮目标图纸的连接端口和网络
Shift+Ctrl+C				清除高亮应用
Back Space				在放置导线、总线、直线或多边形时移除最后一个顶点
单击，长按Delete键		移除选中导线的一个顶点
单击，长按Insert			为选中的导线添加一个顶点
Ctrl+单击并拖动			拖动对象
在Navigator或面板中单击		在原理图文档中交叉探测对象
在Navigator或面板中Alt+单击	在原理图文档和PCB中实现交叉探测对象
在网络对象中Alt+左击			在图纸中高亮所有在网络的元素
Ctrl+双击				将图纸符号降一个层次  将接口升一个层次
+（小键盘）				在放置或移动时扩大IEEE符号
-（小键盘）				在放置或移动时缩小IEEE符号
Ctrl+F					搜索文本
Ctrl+H					搜索和替换文本
F3						搜索下一个
Insert					放置相同类型对象的时候复制对象的属性
S						移动一个或多个选中的图纸入口时翻转图纸入口的位置
V						移动两个或多个选中的图纸入口时上下翻转图纸入口
T						移动一个或多个选中的图纸入口时切换图纸入口IO类型  重定义选中图纸符号尺寸时切换所有图纸入口的IO类型
T,P						打开Preference对话框中的Schematic-General页
3.仅在PCB编辑器中有效的快捷键
Shift+R					在三种布线模式间循环切换
Shift+E					开关电气栅格
Shift+B					建立查询
Shift+Page Up				以小幅度放大
Shift+Page Down			以小幅度缩小
Ctrl+Page	UP			放大到400%
Ctrl+Page Down			缩放到合适
Ctrl+End					跳转到工作区的相对起始坐标
Alt+End					重描画当前层
Alt+Insert				在当前层粘贴
Ctrl+G					弹出Snap Gird对话框
G						弹出Snap Gird菜单
N						移动元件时隐藏飞线
L						翻转正在移动的元件到板的另一边
Shift+F1					布线时按下可以显示合适的交互布线快捷键
Tab						布线、调整线长、放置元件或字符串时按下，可以显示合适的交互编辑对话框
F2						显示板卡洞察器（Board Insight）和平视（Heads Up）显视器选项
Ctrl+Space				在交互布线时循环切换走线模式
Back Space				交互布线时清除最后一个转角
Shift+S					开关单层模式
O,D,D,Enter				设置所有图元草图模式显示
O,D,F,Enter				设置所有图元以最终模式显示
O,D(或Ctrl+D)			打开View Configuration对话框
L						打开View Configurations对话框的板层和颜色页面
Ctrl+H					选中已连接的铜
Ctrl+Shift+长按左键		断线
Shift+Ctrl+单击			高亮光标所在的已连接网络
+（小键盘）				下一层
-（小键盘）				上一层
Ctrl+单击				在层面中高亮层
Ctrl+Shift+单击			在层页面中添加高亮
Ctrl+Alt+鼠标				在层页面中高亮显示鼠标接触的元件
`*`(小键盘)				下一个走线层
M						显示移动子菜单
Alt						按下来暂时从避免障碍模式切换到忽略障碍模式
Ctrl						走线时按下来暂时禁用电气栅格
Ctrl+M					测量距离
Space(交互过程中)		逆时针旋转
Space(交互布线时)		切换转角模式
Shift+Space(交互过程中)		顺时针旋转被移动的对象
Shift+Space(交互布线时)		交互布线时切换走线模式
[						降低过滤器的屏蔽水平
]						提高过滤器的屏蔽水平
Alt←					在活动的库文档中查看上一个元件
Alt→					在活动的库文档中查看下一个元件
Q						切换单位(公制/英制)
T,B						打开3D Body Manager对话框
T,P						打开Preferences对话框
~						显示交互式长度调整快捷清单
Back Space				移除最后依次交互式长度调整片段
Space					下一种交互式长度调整曲线
Shift+Space				上一种交互式长度调整曲线
Shift+R					切换走线模式
,(逗号)					以一个单元来降低交互式长度调整曲线的振幅
.(句号)					以一个单元来增加交互式长度调整曲线的振幅
1						降低交互式长度调整的半径
2						增加交互式长度调整的半径
3						以一个单元来降低交互式长度调整曲线的间距
4						以一个单元来增加交互式长度调整曲线的间距
Y						切换交互式长度调整振荡的方向
4.设备视图快捷键
F5						全部刷新
Esc						终止进程
Ctrl+F9					编译Bit文件
Ctrl+F10					重建Bit文件
F12						复位硬件
F9						编译Bit文件并下载
F10						重建Bit文件并下载
F11						下载Bit文件
Shift+Ctrl+F9				编译所有Bit文件
Shift+Ctrl+F10			重建所有Bit文件
Shift+F12				复位所有设备
Shift+F9					编译所有Bit文件并下载
Shift+F10				重建所有Bit文件并下载
Shift+F11				下载所有Bit文件
Alt+T，P				打开Preferences对话框中的FPGA-Devices	页面

5.3D可视化快捷键
0						旋转3D视图以使透视镜头正交于电路板，并旋转电路板使得水平面沿着编辑窗口的底部运动
9						旋转3D视图以使透视镜头正交于电路板，并废黜电路板使得水平面沿着编辑窗口的右侧运动
2						从3D切换到2D，采用最近使用过的2D查看配置
3						从2D切换到3D，采用最近使用过的3D查看配置
Shift						开启3D旋转运动球体
V,F						适合视图V,F沿着光标位置横向翻转电路板
鼠标滚轮				上下滚动
Shift+鼠标滚轮			左右滚动
Ctrl+鼠标滚轮			以步进单位进行缩放
Ctrl+右键拖拽			平滑缩放
Ctrl+C					在剪切板上创建一个三维体视图的位图图像
Page Up/Page Down		以步进单位进行缩放
T,P						访问PCB编辑器——显示Preferences对话框属性页
L						访问View  Configurations对话框的物理材质（三维体）

6.放置三维体的快捷键
+（加号）				下一板层
-（减号）				上一板层
L						在配对机械层上翻转三维体
X						沿着X轴翻转三维体
Y						沿着Y轴翻转三维体
Space					逆时针方向旋转三维体
Shift+Space				顺时针方向旋转三维体
2						围绕三维体自身的X轴顺时针方向旋转
3						以一个捕捉栅格的步长减小三维体的支架高度（Z轴）
4						围绕三维体自身的Y轴逆时针方向旋转
6						围绕三维体自身的
Y						轴顺时针方向旋转
8						围绕三维体自身的X轴顺时针方向旋转
9						以一个捕捉栅格的步长减小三维体的支架高度（Z轴）
←						以一个捕捉栅格的步长沿X轴方向向左移动三维体
Shift+←					以10个捕捉栅格的步长沿X轴方向向左移动三维体
→						以一个捕捉栅格的步长沿X轴方向向右移动三维体
Shift+→					以10个捕捉栅格的步长沿X轴方向向右移动三维体
↑						以一个捕捉栅格的步长沿Y轴方向向后移动三维体
Shift+↑					以10个捕捉栅格的步长沿Y轴方向向后移动三维体
↓						以一个捕捉栅格的步长沿Y轴方向向前移动三维体
Shift+↓					以10个捕捉栅格的步长沿Y轴方向向前移动三维体

7.PCB3D编辑器快捷键
Page Up					放大
Page Down				缩小
Alt+B					适合板卡尺寸


↑↓→←					沿箭头方向拉近
Insert					拉近
Delete					拉远
T,E						访问IGES/STEP格式导出对话框
T,P						访问PCB编辑器——Preference对话框下的PCB现有三维页面

8.PCB三维图形库编辑器快捷方式
Page Up					放大
Page Down				缩小
Alt+M					适应图纸大小
↑↓←→					按箭头方向平面移动
Insert					拉近
Delete					拉远
F2						重命名模型
Shift+Delete				删除模型
Ctrl+T					设置旋转角度
T,I						导入三维模型
T,E						以IGES模式导出模型
T,P						打开参数设置对话框

9.作业输出编辑器快捷方式
Ctrl+X(或Shift+Delete)	剪切
Ctrl+C(或Ctrl+Insert)	复制
Ctrl+V(或Shift+Insert)	粘贴
Ctrl+D					复制+粘贴
Delete					清除
Alt+Enter				确认
Ctrl+F9					运行并激活输出生成器
Shift+Ctrl+F9				运行并选择输出生成器
F9						批运行可用的输出生成器
Shift+Ctrl+O				打开作业输出选项对话框

10.CAM编辑器快捷键方式
Ctrl+Z(或Alt+BackSpace)		撤销上一次操作
Ctrl+Y(或Ctrl+BackSpace)	重复上一次操作
Ctrl+X					剪切
Ctrl+C(Ctrl+Insert)			复制
Ctrl+V(或Shift+Insert)	粘贴
Ctrl+E					清除
Ctrl+M					镜像
Ctrl+R					旋转
Ctrl+L					选择性排列
L						合并图层
Alt+C					选择使用中的多重窗口
Alt+P					选择先前的选项
Ctrl+F					切换Flash selection模式的开关
Ctrl+T					切换Trace selection模式的开关
Ctrl+A					排列对象
Ctrl+D					修改/改变对象
Ctrl+I					设置原点
Ctrl+U					测量对象
Home					适应图纸大小
Shift+P					观察特定区域


Ctrl+Mouse-wheel up（或Page Up）	放大
Ctrl+Mouse-wheel down（或Page Down）	缩小
Mouse-wheel up		向上水平移动
Mouse-wheel down	向下水平移动
Shift+Mouse-wheel up向左水平移动
Shift+Mouse-wheel down向右水平移动
Shift+V					聚集到最后一个
End						刷新
D						Dynamic panning mode
Shift+B					View  Film Box
Ctrl+Home				Zoom Film Box
Alt+Home				缩放到当前的Dcode
Shift+E					Toggle view of Extents Box On/Off
Shift+F					Toggle Fill Mode On/Off
Shift+H					Toggle highlight of current objects using current D code
N						改变反显状态
Shift+T					改变半透明状态
Shift+G					调出CAM编辑器
Q						查询对象
Shift+N					查询网络
Shift+M					测量点对点距离
Shift+A					打开也设置表格
K						打开已关闭图层设置对话框
Alt+K					打开当前图层设置对话框
Shift+S					改变对象捕捉模式
Esc						撤销操作
Shift+Ctrl+R				重复上一次操作
+（小键盘）				只下一个图层
-（小键盘）				只显示上一个图层
`*`（小键盘）				只显示下一个信号图层
13.文本类文档编辑器快捷方式
Ctrl+Z					撤销上一次操作
Ctrl+X(或Shift+Delete)		剪切
Ctrl+C(或Ctrl+Insert)		复制
Ctrl+V(或Shift+Insert)		粘贴
Enter					插入回车键
Ctrl+N					插入新的一行
Tab						插入Tab键
Shift+Tab					向后退一个Tab键
Insert					改变输入状态(插入或者覆盖)
Shift+Ctrl+C				清除筛选器标志
Ctrl+F					查找下一个目标
Ctrl+H(或Ctrl+R)			查找并替换文本
F3(或Ctrl+L)				查找搜索到下一个目标
Shift+Ctrl+F				查找下一个选定的目标
Ctrl+A					全选
Page Up					向上卷动一页
Page Down				向下卷动一页
Ctrl+↑					向上卷动一行
Ctrl+↓					各下卷动一行


Ctrl+Page Up				把光标移到窗口的上方
Ctrl+Page Down			把光标移动到窗口的下方
Home					把光标移动到该行的起始位置
End						把光标移动到该行的末端
Ctrl+Home				把光标移动到该文件的起始位置
Ctrl+End					把光标移动到该文件的末端
↑↓						按箭头方向把光标移动一行
←→					按箭头方向把光标移动一个字符
Ctrl+←					把光标向左移动一个单词
Ctrl+→					把光标向右移动一个单词
Shift+Ctrl+Home			选择光标以上的所有文本
Shift+Ctrl+End			选择光标以下的所有文本
Shift+Page Up				选择光标以上的一页文本
Shift+Page Down			选择光标以下的一页文本
Shift+Ctrl+Page Up		在当前窗口内选择光标以上的所有文本
Shift+Ctrl+Page Down		在当前窗口内选择光标以下的所有文本
Shif+Home				选择从当前光标到该行的起始位置的所有文本
Shift+End				选择从当前光标到该行的末端的所有文本
Shift+←					向左选中一个字符
Shift+→					向右选中一个字符
Shift+↑					选择当前光标到上一行光标所在列的所有字符
Shift+↓					选择当前光标到下一行光标所在列的所有字符
Shift+Ctrl+←				向左选中一个单词
Shift+Ctrl+→				向右选中一个单词
Alt+Shift+Ctrl+Home		选择当前光标至文件起始位置所在列
Alt+Shift+Ctrl+End		选择当前光标至文件末端所在列
Alt+Shift+Page Up			在上一页中,选择光标以上所在列
Alt+Shift+Page Down		在下一页中,选择光标以下所在列
Alt+Shift+Ctrl+Page Up		在当前窗口,选择光标以上所在列
Alt+Shift+Ctrl+Page Down	在当前窗口,选择光标以下所在列
Alt+Shift+Home			选择当前光标至该行起始位的所有字符
Alt+Shift+End				选择当前光标至该行末端的所有字符
Alt+Shift+←				在所在行,向左按列选择字符
Alt+Shift+→				在所在行,向右按列选择字符
Alt+Shift+↑				在所在列,向上按行选择字符
Alt+Shift+↓				在所在列,向下按行选择字符
Alt+Shift+Ctrl+←			在所在行,向左按列选择单词
Alt+Shift+Ctrl+→			在所在行,向右按列选择单词
Alt+	按住左键并拖动		通过鼠标按列选择文本
Delete					删除光标右边字符
Back Space				删除光标左边字符
Ctrl+Back Space			删除前一个单词
Ctrl+T					删除后一个单词
Ctrl+Y					重复上一次操作
Ctrl+Q+Y				删除该行从光标到行末端的文本
Alt+T,P					打开文本编辑器参数设置对话框
14.嵌入式软件编辑快捷方式
F9						运行并开始调试程序
Ctrl+F9					运行到光标处
F5						改变当前行断点的状态


在装订槽内单击			改变某行断点的状态
Ctrl+F5					增加观测目标
F7						跳入当前行代码
Ctrl+F7					评估
F8						执行下一行代码
Shift+F7					进入当前指令
Shift+F8					执行下一条指令
Ctrl+F2					复位当前调试块
Ctrl+F3					完成当前调试
单击代码分级栏的+/-		展开/合并代码段
Ctrl+双击代码分级栏的+/-	展开/合并所有代码段
Ctrl+单击变量/函数		跳到当前变量或者函数定义处
15.VHDL编辑器快捷方式
Ctrl+F9					编译
HDL					源代码
F9						执行
Ctrl+F5					按上次的时间执行仿真操作
Ctrl+F8					按设定的时间执行仿真操作
Ctrl+F11					执行到下一个断点
Ctrl+F7					执行一段时间的仿真操作
F6						执行仿真操作一小段时间
F7						跳入进程或函数,进行仿真操作
F8						跳出进程或函数
Ctrl+F2					复位当前仿真过程
Ctrl+F3					结束当前仿真过程
在装订槽内单击			改变某行断点的状态
左击代码分级栏的+/-		展开/合并代码段
Ctrl+单击代码分级栏的+/-	展开/合并所有代码段
脚本编辑器快捷方式
F9						运行脚本
Ctrl+F9					运行到光标处
F5						改变当前行断点的状态
在装订槽内单击			改变某行断点的状态
Ctrl+F7					评估
F8						执行下一行
Ctrl+F3					停止脚本执行
Ctrl+单击变量/函数		跳到当前变量或者函数定义处
