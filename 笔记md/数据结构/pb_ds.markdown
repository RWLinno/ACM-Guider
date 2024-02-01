---
title : pb_ds 
date : 2021-8-21 
tags : ACM,数据结构 
author : Linno
---



![img](https://img-blog.csdnimg.cn/71f02f692cfa45cbaa69c9c90a620d59.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA57yE5ruF,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

### 简介

pb_ds库全称Policy-Based Data Structures。

封装了很多数据结构入哈希表、平衡二叉树、字典树、堆等。

### 哈希表

声明方式

```java
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;

cc_hash_table<string,int>mp1;//拉链法
gp_hash_table<string,int>mp2;//查探法（快一点）
```

### 堆

声明方法

```java
#include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
__gnu_pbds::priority_queue<int>q;//带命名空间防止和std重复
__gnu_pbds::priority_queue<int,greater<int>,binary_heap_tag>pq;//二叉堆
__gnu_pbds::priority_queue<int,greater<int>,binomial_heap_tag>pq;//二顶堆
__gnu_pbds::priority_queue<int,greater<int>,rc_binomial_heap_tag>pq; //配对堆
__gnu_pbds::priority_queue<int,greater<int>,thin_heap_tag>pq;
__gnu_pbds::priority_queue<int,greater<int> >pq;
```

##### 常用操作

```java
push() //返回一个迭代器
	top() //返回堆顶
    size() //返回大小
    empty() //判断是否为空
	clear() //清空堆
    pop() //弹出堆顶元素
    join(priority_queue,&other) //合并两个堆.other会被清空
    split(Pred prd,priority_queue &other) //分离除两个堆
    modify(point_iterator it,const key //修改一个节点的值)
```

##### 更多用法

begin()和end()来获得iterator从而遍历

可以 increase_key,decrease_key和删除单个元素

可以合并

```java
__gnu_pbds::priority_queue<int>::point_iterator it; //迭代器
```

### 红黑树

##### 声明方式

```java
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>t;
/*定义一颗红黑树，
int为关键字类型，
null_type无映射,
less从小到大排序，
rb_tree_tag红黑树(splay_tree_tag)，
tree_order_statistics_node_update节点更新
*/
```

##### 常用方法

```java
t.insert()//插入
t.erase()//删除
t.order_of_key(k);//求k在树中是第几大
t.find_by_order(k); //求树中的第k大
t.lower_bound();//前驱
t.upper_bound();//后继
a.join(b)//b并入a，前提是两棵树的key的取值范围不相交
a.split(v,b)//key小于等于v的元素属于a，其余的属于b
t.lower_bound(x)//>=x的min的迭代器
t.upper_bound(x)//>x的min的迭代器
```

##### 迭代器

```java
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>::iterator it;//也可以使用auto来判断
```

##### 洛谷3369题解

修改了前辈的板子，位运算的意义是去重。

用splay_tree_tag的话会T掉一个点，改成红黑树就可以过了。

```java
//luoguP3369 【模板】普通平衡树
#include<bits/stdc++.h>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
tree<ll,null_type,std::less<ll>,rb_tree_tag,tree_order_statistics_node_update>sp;
ll T,ans,op,x;
signed main(){
   
	scanf("%lld",&T);
	for(int i=1;i<=T;i++)
    {
   
        scanf("%lld%lld",&op,&x);
        if(op==1) sp.insert((x<<20)+i); //去重 
        else if(op==2)sp.erase(sp.lower_bound(x<<20));
        else if(op==3)printf("%lld\n",sp.order_of_key(x<<20)+1); 
        else
        {
   
            if(op==4)ans=*sp.find_by_order(x-1);
            if(op==5)ans=*--sp.lower_bound(x<<20); 
            if(op==6)ans=*sp.lower_bound((x+1)<<20);
            printf("%lld\n",ans>>20);
        }
    }
    return 0;
}
```

### 参考资料

OI -wiki

《C的pb_ds库在OI中的应用》于纪平 pb_ds库的一些常用方法 CSDN

【学习笔记】用算法题介绍C++的pb_ds库中的可并堆 TRiddle

P3369 【模板】普通平衡树（Treap/SBT）（pb_ds版）自为风月马前卒

