# Lab3 实验报告

PB19111704 王岩开



## 实验环境

​	Intel(R) Core(TM) i7-9750H CPU @ 2.60GHz   2.59 GHz

​	Window 10

## 实验内容

### 实验3.1：Bellman-Ford算法

实现求单源最短路径的Bellman-Ford算法。有向稀疏图的顶点数 N 的取值分别为: 27、81、243、729 ，每个顶点作为起点引出的边的条数取值分别为：$log_5N$、$log_7N$（取上整），其邻接矩阵存放在输入文件中。输入规模总共有4\*2=8个，统计算法所需运行时间 ，画出时间曲线，分析程序性能。

### 实验3.2：Johnson算法

实现求所有点对最短路径的Johnson算法。输入数据与实验3.1相同。图的输入规模总共有4\*2=8个，统计算法所需运行时间 ，画出时间曲线，分析程序性能。



## 实验要求

### 实验3.1 Bellman-Ford算法

![image-20211230165705292](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230165705292.png)

### 实验3.2 Johnson算法

![image-20211230165723741](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230165723741.png)

## 实验方法和步骤

### 实验3.1：Bellman-Ford算法

​	因为系数矩阵是稀疏矩阵，所以使用邻接表来储存图结构，在graph.h和graph.cpp中声明了了GRAPH、VERTEX、EDGE三个类，并完成了初始化和插入边的函数。

![image-20211230170323610](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230170323610.png)

![image-20211230170353642](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230170353642.png)

BF算法中在main.cpp中完成了RELAX函数和算法主体函数

![image-20211230170451901](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230170451901.png)

此处为了处理c语言中实际没有无限大的情况，在将MAX声明为一个较大后，RELAX时判定若两个点的distance都为最大值则直接返回（此时两个点都不可达）

输出结果时，对于路径上每个点倒序存在PATH数组中，然后逆着输出

![image-20211230170847334](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230170847334.png)

统计时间方法和之前实验都一样，不再赘述。

### 实验3.2 Johnson算法

​	使用了和3.1中相同的数据结构，RELAX和BELLMAN_FORD函数也相同，不同的是在创建图数据结构时多创建了一个G_temp，点数比G多1，

![image-20211230171814201](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230171814201.png)

并使其与其他所有边建立一条权重为0的边，然后以这个点为源结点应用BELLMAN_FORD算法，计算出调整权重的值。对图G遍历更新新的权重

![image-20211230172010753](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230172010753.png)

然后对图G每个点使用DIJKSTRA算法，每次确定完后直接输出该点的所有可达点的距离

![image-20211230173112734](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230173112734.png)

在DIJKSTRA算法中，我使用了c++标准库中的优先队列，

![image-20211230173338493](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230173338493.png)

使用bool数组S表示一个一个点是否已经确定到源节点的距离，源节点的邻点入队后，每次弹出优先队列第一个元素，如果还没有确定他到源节点的距离，就对其的所有出边进行RELAX操作，并将其邻点入队，然后设置其对应的S为true，当队列清空后终止DIJKSTRA算法。

## 结果与分析

### 实验3.1：Bellman-Ford算法

​	输出结果较多可以查看文件

​	这里截取了result42.txt的一部分![image-20211230174454417](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230174454417.png)

​	时间统计如下

![image-20211230175332110](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230175332110.png)

因为最后两个值差距较远，我们忽略他们两个后作图

![image-20211230180211262](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230180211262.png)



横轴的值为$NE$发现线性拟合效果较好，符合$O(NE)$的理论时间复杂度

### 实验3.2Johnson算法

​	输出结果较多可以查看文件

​	这里截取了result41.txt的一部分

![image-20211230180930567](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230180930567.png)

时间统计为

![image-20211230180958026](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230180958026.png)

忽略最后两个值后作图

![image-20211230181440022](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211230181440022.png)

纵轴的值为$NlogNE$拟合效果较好，符合使用优先队列优化后N次DIJKSTRA的预期时间

我们都可以看到在N值较小时有一定的偏差，这可能是因为N较小时优先队列的优化作用不明显导致的。
