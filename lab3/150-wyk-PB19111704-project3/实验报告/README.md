# Lab2 实验报告

PB19111704 王岩开



## 实验环境

​	Intel(R) Core(TM) i7-9750H CPU @ 2.60GHz   2.59 GHz

​	Window 10

## 实验内容

### 实验2.1：斐波那契堆

•step1：通过INSERT（要操作的数见input.txt）建立斐波那契堆H1-H4。

•step2:在H1下完成以下10个ops:

INSERT(H1,249);INSERT(H1,830);MINIMUM(H1);DELETE(H1,127);DELETE(H1,141); MINIMUM(H1);

DECREASE-KEY(H1,75,61);DECREASE-KEY(H1,198,169); EXTRACT-MIN(H1);EXTRACT-MIN(H1);

•Step3:在H2下完成以下10个ops:

INSERT(H2,816); MINIMUM(H2); INSERT(H2,345); EXTRACT-MIN(H2);DELETE(H2,504);DELETE(H2,203);

DECREASE-KEY(H2,296,87);DECREASE-KEY(H2,278,258);MINIMUM(H2);EXTRACT-MIN(H2);

•Step4:在H3下完成以下10个ops：

EXTRACT-MIN(H3); MINIMUM(H3);INSERT(H3,262); EXTRACT-MIN(H3);INSERT(H3,830);MINIMUM(H3);

DELETE(H3,134);DELETE(H3,177);DECREASE-KEY(H3,617,360);DECREASE-KEY(H3,889,353);

•Step5:在H4下完成以下10个ops：

MINIMUM(H4); DELETE(H4,708); INSERT(H4,281);INSERT(H4,347);MINIMUM(H4);DELETE(H4,415); 

EXTRACT-MIN(H4); DECREASE-KEY(H4,620,354);DECREASE-KEY(H4,410,80); EXTRACT-MIN(H4);

•Step6:将H1-H4进行UNION成H5

•Step7:在H5完成如下10个ops：

EXTRACT-MIN(H5); MINIMUM(H5); DELETE(H5,800); INSERT(H5,267);INSERT(H5,351); EXTRACT-MIN(H5); 

DECREASE-KEY(H5,478,444);DECREASE-KEY(H5,559,456);MINIMUM(H5); DELETE(H5,929);

分别统计step2-5,7的运行时间，并画图分析。

### 实验2.2：家族数

​	1.有 N 个人（N=10/15/20/25/30）。其中有些人是亲戚，有些则不是。他们的亲戚关系具有传递性。如果已知 A 是 B 的亲戚，B 是 C 的亲戚，那么我们可以认为 A 也是 C 的亲戚。所谓的家族，是指所有亲戚的集合。

​	2.给定一个 N * N 的矩阵 M，表示不同人之间的亲戚关系。如果M[i][j] = 1，表示已知第 i 个和 j 个人互为亲戚关系，否则不是亲戚关系。你必须输出所有人中的家族数。

	3.	必须用并查集解决，并要实现按秩合并，路径压缩两种优化手段。
	4.	记录不同N值的运行时间，并画图分析。

## 实验要求

### 实验2.1 斐波那契堆

![image-20211213230236596](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211213230236596.png)

### 实验2.2 家族数

![image-20211213230313769](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211213230313769.png)

## 实验方法和步骤

### 实验2.1：斐波那契堆

​	主要算法

​	完成了斐波那契堆的如下函数

​	![image-20211213231542124](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211213231542124.png)

FIB_HEAP结构体用来描述整个堆，FIB_NODE是堆中的每个节点；

各个函数大体实现和书上相同，这里着重介绍如何维护堆中各个指针的值；

插入函数中

![image-20211213231924810](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211213231924810.png)

注意插入的第一个需要将左兄弟右兄弟都指向自己

![image-20211213232057921](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211213232057921.png)

弹出最小值时，如果最小值有孩子节点，需要将孩子节点全部接到根节点上，这里其实不需要一个个孩子依次接入，直接将孩子作为第一个节点、他的左兄弟作为最后一个接入节点，直接整个接入根链表即可。

![image-20211213233313300](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211213233313300.png)

合并操作中，交换时要注意维护KEY_TO_NODE全局变量数组（用于储存每个key指对应的节点的）

![image-20211213233731547](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211213233731547.png)

LINK操作时，需要注意如果y是第一个孩子节点，要维护好y的左兄弟右兄弟

运行时间计算

​	使用Windows.h库中的QueryPerformanceFrequency、 QueryPerformanceCounter完成对时间的计算，测试matrix_chain_order函数的运行时间，输出ms为单位的时间。

![image-20211214085209388](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211214085209388.png)

### 实验2.2 家族数

主要算法

​	首先用链表实现不相交集合数据结构，

![image-20211214085359530](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211214085359530.png)

并完成MAKE_SET、LINK、UNION、FIND_SET函数

![image-20211214085423453](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211214085423453.png)

实现思路与课本基本相同，在LINK和UNION中增加bool型返回值，当没有真的合并两个链表时返回false，合并了返回true（用于计算出总家族数）

![image-20211214085603462](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211214085603462.png)

主要思路就是对于不同的N，先进行一次遍历，对每个成员建立SET，并将set_count设置为N，第二遍二重遍历时，对于每个操作数（即输入数据中用于表示二者是否为亲戚），如果是1，就将标识的两个成员进行union，如果union成功，即确实将两个链表合并，则使N减1。

统计时间方法和之前实验都一样，不再赘述。

## 结果与分析

### 实验2.1：斐波那契堆

​	输出结果如下图

![image-20211214090103172](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211214090103172.png)

​	时间统计如下

![image-20211214090118072](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211214090118072.png)

![image-20211214231619163](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211214231619163.png)

可以发现这些操作数运行时间并不像我们摊还分析时研究的那样，应该得到相近的结果，因此我们猜测，应该是堆的实际维护中和数据分布，os系统操作都有很大关系，且本次实验操作数较少，才导致了运行时间的分布不相近。

### 实验2.2家族数

​	家族数输出结果如下

![image-20211214090738526](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211214090738526.png)

​	输出运行时间如下

![image-20211214090752082](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211214090752082.png)

![image-20211214231807618](C:\Users\12198\AppData\Roaming\Typora\typora-user-images\image-20211214231807618.png)

家族数的运行时间也在一个范围内不断改变，我们推测应该也是因为数据的分布问题导致不同的集合中路径压缩次数的不同最终导致了查询时间不同进而导致生成时间不同。



