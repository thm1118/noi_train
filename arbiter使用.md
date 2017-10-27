# arbiter 评测软件使用
  
    安装noi_linux 1.4

## 1、新建比赛，选择目录 
- 比如 在~/Doucumnets 下新建目录 match，选择该目录。以后关闭软件再打开时还需要选择该目录下的setup.cfg
- 注意随时保存，包括后续任何步骤

## 2、新建考试和 新建试题
- ![试题创建](img/createtest.png)

## 3、试题测试数据拷贝目录
-  evaldata目录/ 试题名称+编号(.in/.ans)    （编号就是试题创建 的测试点编号 1-10）
- .in  表示输入；.ans 表示 核对的答案
- ![测试数据](img/evaldata.png)

## 4、添加选手，注意编号
- ![创建选手](img/cadinate.png)

## 5、选手提交的待测评源码
- players 目录/ 选手编号/试题名称/ 源码文件-->试题名称.cpp
- ![测评源码](img/source.png)
- 注意源码中 输入输出文件的指定 ：试题名.in / 试题名.out
- ![输出和输出](img/input_output.png)

## 6、测评
- ![测评](img/starttest.png)

## 7. 问题排查
- 在考试目录 match下，result 目录记录了测评的输出，会记录 测评失败原因的提示信息
- match目录下的tmp 目录应是存放最近一个试题代码，编译后文件，以及输入输出文件

