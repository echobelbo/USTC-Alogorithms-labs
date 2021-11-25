# Lab1 实验报告

**PB19111704 王岩开**



## 实验环境

​	Intel(R) Core(TM) i7-9750H CPU @ 2.60GHz   2.59 GHz

​	Window 10

## 实验内容

### 实验1.1：求矩阵链乘最优方案

​	1.	n个矩阵链乘，求最优链乘方案，使链乘过程中乘法运算次数最少。

​	2.	n的取值5, 10, 15, 20, 25，矩阵大小见1_1_input.txt。

​	3.	求最优链乘方案及最少乘法运算次数，记录运行时间，画出曲线分析。

​	4.	仿照P214 图15-5，打印n=5时的结果并截图。

### 实验1.2：求所有最长公共子序列

​	1.	给定两个序列X、Y，求出这两个序列的所有最长公共子序列。

​	2.	X, Y序列由A、B、C、D四种字符构成,序列长度分别取10、15、20、25、30，见1_2_input.txt。

​	3.	输出所有最长公共子序列个数，并打印所有最长公共子序列，记录运行时间，画出曲线分析。

## 实验要求

### 实验1.1 矩阵链乘 输入输出

​	ex1/input/1_1_input.txt（已给出）：

​		每个规模的数据占两行：

​			n

​			矩阵大小向量$p=(p_0, p_1,…, p_n )$，矩阵$A_i$大小为$p_(i-1)∗p_i$

​	ex1/output/

​		result.txt：每个规模的结果占两行

​			最少乘法运算次数

​			最优链乘方案（要求输出括号化方案，参考P215 print_opt_parens算法）

​		time.txt：每个规模的运行时间占一行

​	同行数据间用空格隔开

### 实验1.2 所有最长公共子序列 输入输出

​	ex2/input/1_2_input.txt（已给出）：

​		每个规模的数据占三行：

​			n：X、Y序列长度

​			X：X序列

​			Y：Y序列

​	ex2/output/

​		result_i.txt：X、Y序列长度为i的结果

​			最长公共子序列个数

​			最长公共子序列：每个最长公共子序列占一行

​		time.txt：每个规模的运行时间占一行	

## 实验方法和步骤

### 实验1.1：求矩阵链乘最优方案

​	**主要算法**

​	使用全局变量long long int数组mul_times来存所有乘法次数生成结果，long long int数组matrix_size来存输入的矩阵大小向量，int 数组来存打印括号化方案时的位置信息；

![image-20211125175059302](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125175059302.png)

​	在这里为了实现变长二维数组的参数传递，我使用了一种类似编译器进行编译时计算偏移量的方法，比如在声明mul_times\[n]\[n]时，不直接声明这样的二维数组，而是声明一个一维数组指针，然后malloc分配$n*n*sizeof(long\ long\ int)$的空间，然后对于其中的数组元素mul_times\[i]\[j]变成mul_times[$n*i + j$]。

​	算法实现部分采用自底向上迭代实现

![image-20211125175647205](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125175647205.png)

​	这里需要注意的是在计算q值时，如果matrix_size被声明为int数组，需要在每次乘法前进行类型转换，否则会出现溢出

​	括号化输出针对所有矩阵按顺序编号

![image-20211125175853953](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125175853953.png)

**运行时间计算**

​	使用Windows.h库中的QueryPerformanceFrequency、 QueryPerformanceCounter完成对时间的计算，测试matrix_chain_order函数的运行时间，输出ms为单位的时间。

![image-20211125180137307](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125180137307.png)

### 实验1.2 所有最长公共子序列 输入输出

**主要算法**

​	使用两个全局二维数组length和dir来存储对应起点和终点间最长公共子序列的长度和递归方向；num_LCS用来统计生成的最长公共子序列数量，MAX_LCS用来存储最长公共子序列的长度；output_str用来存储当前递归中得到的最长公共子序列，result用于存储所有最长公共子序列；

​	首先生成length和dir数组

![image-20211125181650445](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125181650445.png)

​	当需要向左上递归时，置dir为0，向上时，置为1，向左时置为-1；但其实区分-1和1在我们后面的算法中意义不大，这里只是为了和书上算法照应；

​	输出最大公共子序列时，使用LCS_output函数，也是这次实验最难的地方。

​	一开始时，我尝试直接对路径进行递归，也就是每次向左上方移动时，进行递归，当可以向左或向右移动时，向着那个方向递归。但这样就出现了一个问题，有些情况下可以同时向左或上移动（左，上位置length值相同），同时，向左上走的，也可以向左或上移动。我一开始写出的LCS_DFS函数虽然实现了动态指针分配空间，但实质是对所有生成路径不同的LCS都进行输出，这显然有大量的重复。且我忽略了同时向左上移动的可以向左向上移动的情况，所以又少了一些情况。最终我放弃了这个函数，找寻新的输出方法。

![image-20211125182115621](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125182115621.png)

​	然后我考虑了dir表和length表的本质，其实对于所有当前递归的点，他的左方和上方，只要和他length相同，都是可达的，且不会产生任何会被记录下来的LCS字符，而对于每个dir=1的点，他们的对的在XY中的位置肯定不相同，只在这些点进行递归就不会产生不同路径导致的重复。

​	![image-20211125182025019](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125182025019.png)

​	其实在length\[i][j]=0时直接输出output_str就可以输出所有最大公共子序列，但是为了满足先输出数目再输出字符串的需求，我又没学会怎么在文件中的不同位置输出，我只好开了个result数组暂存所有的结果，在之后再输出。

**运行时间计算**

​	同ex1，使用Windows.h库中的QueryPerformanceFrequency、 QueryPerformanceCounter完成对时间的计算，测试LCS_length函数的运行时间，输出ms为单位的时间。

​	![image-20211125185658871](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125185658871.png)

## 结果与分析

### 实验1.1：求矩阵链乘最优方案

​	输出括号化与乘法次数如下图

![image-20211125190054791](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125190054791.png)

​	时间统计如下![image-20211125190132251](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125190132251.png)

​	n = 5时，乘法次数和括号话位置表如下

​	![image-20211125190355941](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125190355941.png)

​	运行时间作图如下

![image-20211125190954357](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125190954357.png)

​	可见三次方时拟合效果较好，符合预期$\Omega (n^3)$复杂度。

### 实验1.2 所有最长公共子序列 输入输出

​	输出LCS结果如下(len = 10)

​	![image-20211125191213593](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125191213593.png)

​	输出运行时间如下

![image-20211125191407741](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125191407741.png)

作图如下

![image-20211125191652512](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211125191652512.png)

二次方时拟合效果较好，符合预期$\Theta (m*n)$时间复杂度。

