---
title : KD-Tree
date : 2022-4-7
tags : ACM,数据结构
author : Linno

---



# K-D tree

K-D树是在k维欧几里得空间中组织点的数据结构。在算法竞赛中，K-D树往往用于在二维平面内的信息检索。具体应用如：多维键值搜索（范围搜索及最邻近搜索）下面我们针对二维平面的KD-Tree进行讲解。



### 定义

K-D Tree是一颗存储k维信息的二叉树，代表对数据集合的划分，每个结点都对应着一个k维超矩形区域。

①在一维数据情况下，KD-Tree是一颗二叉搜索树。

②二维情况下，我们轮流按照x维和y维对数据进行划分。这是最简单的一种划分方式，使得每次划分都将平面分成不相交的两部分。



### 建树

对于KD-Tree每个结点的存储信息如下：

```cpp
struct KDTree{
    int ch[2],id;  //左右儿子和当前结点的编号
    Point p,r1,r2;
    //结点表示的点，子树赋改的矩形的左下角，右上角
}
```

每次新建结点是根据当前划分维度选中位数进行划分，注意$nth\_element$函数的使用，是线性时间选择中位数，并将比他小的元素排序到左边，比他大的元素排序到右边的。

```cpp
int build(int l,int r,int d) {  //KD-Tree建树 
    if (l>r) return 0;
    del=d;  //改变划分维度 
	int mid=(l+r)>>1,at=++ncnt;
    nth_element(ps+l,ps+mid,ps+r+1,cmp); //O(n)找到第mid大元素，将比他小的放左边，比他大的放右边 
    T[at]=Tree(ps[mid],mid);
    T[at].ch[0]=build(l,mid-1,d^1),T[at].ch[1]=build(mid+1,r,d^1);
    pushup(at);return at;
}
```



### 更新

对于KD-Tree每个结点表示的矩形，需要由左右儿子向上更新

```cpp
void pushup(int rt) {  //更新操作 
    T[rt].r1.x=min(min(T[ls].r1.x,T[rs].r1.x),T[rt].r1.x);
    T[rt].r1.y=min(min(T[ls].r1.y,T[rs].r1.y),T[rt].r1.y);
    T[rt].r2.x=max(max(T[ls].r2.x,T[rs].r2.x),T[rt].r2.x);
    T[rt].r2.y=max(max(T[ls].r2.y,T[rs].r2.y),T[rt].r2.y);
}
```



### 插入

插入是根据当前层比较的维度，较小的插左子树，较大的插右子树，比较简单。

```cpp
void modify(int rt,Point p){
    if(!rt){T[rt]=Tree(P,++ncnt);return;}
    int d=cmp(p,T[rt].p)^1;
    del^=1;
    modify(T[rt].ch[d],p);
    pushup(T[rt]);
}
```



### 查询

##### 最近点查询

1.设定答案ans为初始值$\infty$

2.将点P从根节点开始，先用根节点代表的点更新答案。由于根节点的左右儿子各表示一个矩形区域，而两个区域都有可能存在距离P最近的点，我们优先选择距离点P最近的矩形递归查询。

3.以P为圆心，ans为半径画圆，如果与之前未递归的矩形相交，则递归下去，否则不可能由更优解。

###### 事实上剪枝+搜素，单次查询均摊复杂度是$O(logn)$,最坏$O(\sqrt n)$

```cpp
void query(int rt,Point p) {  //查询操作 
    if (!rt) return;
    node st=node(dis(T[rt].p,p),T[rt].p.id);
    if (st<q.top()) q.pop(),q.push(st);
    double dis[2]={T[ls].dis(p),T[rs].dis(p)};
    int nxt=dis[0]<dis[1]; 
	query(T[rt].ch[nxt],p);  //优先选择两个儿子中矩形距离小的那个 
    if (node(dis[nxt^1],T[T[rt].ch[nxt^1]].id)<q.top()) query(T[rt].ch[nxt^1],p); //如果另一个儿子有可能比当前结果小，就递归下去 
}
```

##### K远点

在寻找最近点时，我们维护一个大根堆，一开始放k个$-\infty$，然后维护查询结果即可。



### 例题

##### luoguP4357 [CQOI2016]K 远点对

题意：给定k个点，求第k远点对的距离平方。

将所有点插进KD-Tree中维护小顶堆即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+7;

const double inf=1e16;
struct Point {  //二维平面的点 
    int x,y,id;
    Point (int x=0,int y=0):x(x),y(y) {}
}ps[N];

bool del;  //比较x为0，比较y为1 
bool cmp(Point p1,Point p2) { 
    if (!del) return (p1.x<p2.x||(p1.x==p2.x&&p1.y<p2.y));
    return (p1.y<p2.y||(p1.y==p2.y&&p1.x<p2.x));
}
int dis(Point p1,Point p2) { //计算两点距离 
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}
#define ls T[rt].ch[0]
#define rs T[rt].ch[1] 
struct Tree { //KD-Tree
    int ch[2],id;Point p,r1,r2; //左右儿子和当前结点编号，当前点和表示平面的左下右上角 
    Tree(Point p=Point(),int id=0):p(p),r1(p),r2(p),id(id) {}
    double dis(Point p) {  
        if (!id) return -inf;
        return max(max(::dis(p,r1),::dis(p,r2)),max(::dis(p,Point(r1.x,r2.y)),::dis(p,Point(r2.x,r1.y))));
    }
}T[N];
void pushup(int rt) {  //更新操作 
    T[rt].r1.x=min(min(T[ls].r1.x,T[rs].r1.x),T[rt].r1.x);
    T[rt].r1.y=min(min(T[ls].r1.y,T[rs].r1.y),T[rt].r1.y);
    T[rt].r2.x=max(max(T[ls].r2.x,T[rs].r2.x),T[rt].r2.x);
    T[rt].r2.y=max(max(T[ls].r2.y,T[rs].r2.y),T[rt].r2.y);
}
int ncnt=0;
void init() {  //初始化平面 
    T[0].r1=Point(0x3f3f3f3f,0x3f3f3f3f),T[0].r2=Point(-0x3f3f3f3f,-0x3f3f3f3f);
}
int build(int l,int r,int d) {  //KD-Tree建树 
    if(l>r) return 0;
    del=d;  //改变划分维度 
	int mid=(l+r)>>1,at=++ncnt;
    nth_element(ps+l,ps+mid,ps+r+1,cmp); //O(n)找到第mid大元素，将比他小的放左边，比他大的放右边 
    T[at]=Tree(ps[mid],mid);
    T[at].ch[0]=build(l,mid-1,d^1),T[at].ch[1]=build(mid+1,r,d^1);
    pushup(at);return at;
}
struct node {  //堆中的结点 
    int dis;int id;
    node(int dis=0,int id=0):dis(dis),id(id) {}
    bool operator < (node b) const {
        return dis>b.dis||(dis==b.dis&&id<b.id);
    }
};
priority_queue<node>q; //大根堆
priority_queue<int>ans;
 
void query(int rt,Point p) {  //查询操作 
    if(!rt) return;
    node st=node(dis(T[rt].p,p),T[rt].p.id);
    if(st<q.top()) q.pop(),q.push(st);
    double dis[2]={T[ls].dis(p),T[rs].dis(p)};
    int nxt=dis[0]<dis[1]; 
	query(T[rt].ch[nxt],p);  //优先选择两个儿子中矩形距离小的那个 
    if(node(dis[nxt^1],T[T[rt].ch[nxt^1]].id)<q.top()) query(T[rt].ch[nxt^1],p); //如果另一个儿子有可能比当前结果小，就递归下去 
}
signed main() {
    init();
	int n,k;
	scanf("%lld%lld",&n,&k);
    k*=2;
	for(int i=1;i<=n;i++) scanf("%lld%lld",&ps[i].x,&ps[i].y),ps[i].id=i;
    build(1,n,0);
    while (!q.empty()) q.pop();  //初始化队列 
    for(int j=1;j<=k;j++) q.push(node(-inf)); //设定答案初始值 
	for(int i=1;i<=n;i++) query(1,ps[i]);	
	cout<<q.top().dis;
	return 0;
}
```



##### luogu P2093 [国家集训队]JZPFAR

题意：求平面内距离给定点第k远的点。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7;

const double inf=1e16;
struct Point {  //二维平面的点 
    int x,y,id;
    Point (int x=0,int y=0):x(x),y(y) {}
}ps[N];

bool del;  //比较x为0，比较y为1 
bool cmp(Point p1,Point p2) { 
    if (!del) return (p1.x<p2.x||(p1.x==p2.x&&p1.y<p2.y));
    return (p1.y<p2.y||(p1.y==p2.y&&p1.x<p2.x));
}
double dis(Point p1,Point p2) { //计算两点距离 
    return (double)(p1.x-p2.x)*(p1.x-p2.x)+(double)(p1.y-p2.y)*(p1.y-p2.y);
}
#define ls T[rt].ch[0]
#define rs T[rt].ch[1] 
struct Tree { //KD-Tree
    int ch[2],id;Point p,r1,r2; //左右儿子和当前结点编号，当前点和表示平面的左下右上角 
    Tree(Point p=Point(),int id=0):p(p),r1(p),r2(p),id(id) {}
    double dis(Point p) {  
        if (!id) return -inf;
        return max(max(::dis(p,r1),::dis(p,r2)),max(::dis(p,Point(r1.x,r2.y)),::dis(p,Point(r2.x,r1.y))));
    }
}T[N];
void pushup(int rt) {  //更新操作 
    T[rt].r1.x=min(min(T[ls].r1.x,T[rs].r1.x),T[rt].r1.x);
    T[rt].r1.y=min(min(T[ls].r1.y,T[rs].r1.y),T[rt].r1.y);
    T[rt].r2.x=max(max(T[ls].r2.x,T[rs].r2.x),T[rt].r2.x);
    T[rt].r2.y=max(max(T[ls].r2.y,T[rs].r2.y),T[rt].r2.y);
}
int ncnt=0;
void init() {  //初始化平面 
    T[0].r1=Point(0x3f3f3f3f,0x3f3f3f3f),T[0].r2=Point(-0x3f3f3f3f,-0x3f3f3f3f);
}
int build(int l,int r,int d) {  //KD-Tree建树 
    if (l>r) return 0;
    del=d;  //改变划分维度 
	int mid=(l+r)>>1,at=++ncnt;
    nth_element(ps+l,ps+mid,ps+r+1,cmp); //O(n)找到第mid大元素，将比他小的放左边，比他大的放右边 
    T[at]=Tree(ps[mid],mid);
    T[at].ch[0]=build(l,mid-1,d^1),T[at].ch[1]=build(mid+1,r,d^1);
    pushup(at);return at;
}
struct node {  //堆中的结点 
    double dis;int id;
    node(double dis=0,int id=0):dis(dis),id(id) {}
    bool operator < (node b) const {
        return dis>b.dis||(dis==b.dis&&id<b.id);
    }
};
priority_queue<node> q; //大根堆 
void query(int rt,Point p) {  //查询操作 
    if (!rt) return;
    node st=node(dis(T[rt].p,p),T[rt].p.id);
    if (st<q.top()) q.pop(),q.push(st);
    double dis[2]={T[ls].dis(p),T[rs].dis(p)};
    int nxt=dis[0]<dis[1]; 
	query(T[rt].ch[nxt],p);  //优先选择两个儿子中矩形距离小的那个 
    if (node(dis[nxt^1],T[T[rt].ch[nxt^1]].id)<q.top()) query(T[rt].ch[nxt^1],p); //如果另一个儿子有可能比当前结果小，就递归下去 
}
int main() {
    init();
	int n,m;scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d%d",&ps[i].x,&ps[i].y),ps[i].id=i;
    build(1,n,0);
	scanf("%d",&m);
    int x,y,k;
    while (m--) {
		scanf("%d%d%d",&x,&y,&k);
        while (!q.empty()) q.pop();  //初始化队列 
        for (int i=1;i<=k;i++) q.push(node(-inf)); //设定答案初始值 
        query(1,Point(x,y));  //从根节点出发查询答案 
		printf("%d\n",q.top().id); 
    }
    return 0;
}
```



### 参考资料

https://blog.sengxian.com/algorithms/k-dimensional-tree

https://www.jianshu.com/p/4fd7cad27906
