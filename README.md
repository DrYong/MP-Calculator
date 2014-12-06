# 标准C++数学计算器程序

### 程序共计277行代码，是最简短、完整的大数计算器程序。
* 我的联系方式：
* QQ：13387073000
* Email：lhjok@live.cn
* 博客地址：[华军的博客](http://gogae.org/)

### 程序实现的功能与特征：
该程序支持四则混合运算，无限表达式长度，支持（2560位）超大数运算、求模运算、乘方运算、开方运算等实用功能。

支持四则混合运算（例）：【 '^'为乘方运算符 . '%'为求模运算符 】

`10-3*(2/1-(6*2+(21+3/5)*8/3)*-2)+8*2^2%3`

支持函数混合运算（例）：【 "A=ABS" . "S=SQRT" . "P=PI"（'P'被直接视为数字）】

`10*(2/1-(6*2+(21.5A+3/5)-8*P/3)*23.5S)+8*2^2%3`

函数对应标记符（标记符为大写）：

A=【 ABS 绝对值 】 S=【 SQRT 平方根 】 P=【 PI 圆周率 】

### 程序使用了GMP大数运算库：
GMP是一个开源的任意精度运算库，也是GNU项目的一部分，它的目标是成为最快的大数运算库。

### 安装MinGW-MSYS开发环境：
1、安装MinGW开发套件，可直接安装QT官网提供的软件包【[QT-MinGW](http://www.qt.io/)】

2、安装MSYS辅助环境，直接运行安装[MSYS](http://www.mingw.org/)可执行文件即可：

### 编译GMP库文件：
1、下载[GMP](https://gmplib.org/)库文件，将其解压到C盘根目录下：

2、编辑MSYS配置文件：`C:/msys/1.0/etc/fstab.sample`

`C:/gmp`

3、运行MSYS进入环境：

`cd /c/gmp`

4、依次执行下面命令：

`./configure --enable-cxx`

`make`

`make check`

`make install`

5、设置GCC环境变量：

`C_INCLUDEDE_PATH= C:\msys\1.0\local\include`

`CPLUS_INCLUDE_PATH= C:\msys\1.0\local\include`

`LIBRARY_PATH= C:\msys\1.0\local\lib`

### 开源软件GCC编译环境下生成可执行文件：
1、新建一个图标("icon.rc")文件：
    
`1 ICON "ICON.ico"`
    
2、使用"windres"命令来将.rc文件编译成目标文件：
    
`windres icon.rc icon.o`
    
3、成生带图标的可执行程序：
    
`g++ -Wall -o Calculator -static Calculator.cpp icon.o -lgmpxx -lgmp`

4、注：GMP大数运算库我已经编译好了，有兴趣的同学可以直接使用（已经附上）。
