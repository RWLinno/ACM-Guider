---
title : CDQ分治
date : 2021-9-12
tags : ACM,分治

---


![在这里插入图片描述](https://img-blog.csdnimg.cn/4ffb77feddac41909f72ef9c9d780633.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAUldMaW5ubw==,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

### 简介

CDQ分治与普通分治的不同，在于需要同时考虑[L,M]内的修改对[M+1,R]内的查询产生的影响。



### CDQ分治解决什么问题

（1）和点对相关的问题

（2）优化DP的转移

（3）将一些动态的问题转化为静态问题

（4）三维偏序问题



### 一般步骤

（1）将整个操作序列分为两个长度相等的部分

（2）递归处理前一部分的子问题

（3）计算前一部分的子问题中的修改操作对后一部分子问题的影响

（4）递归处理后一部分的子问题



### 三维偏序

我们首先以a为第一关键字,b为第二关键字,c为第三关键字排序，我们可以保证整个区间a是递增的，那么就变成了二维偏序的问题。

于是，对于每一个i，只可能1到i-1的元素会对它产生贡献，那么直接查找1到i-1的元素中满足$b_j<=b_i$的元素个数就可以了。具体就是树状数组。

##### 具体做法

在保证a有序的情况下，对左右区间，运用CDQ给b排序，左区间的a依然是小于右区间的a的。

计算右区间的答案，对于右区间的任意一个位置i，在左区间里面找一个最大位置j，满足b[j]<b[i]，那么左区间里面只可能1到j的元素会对i这个位置产生贡献。所以只要查找左区间的元素$z_j<z_i$有多少个就好了。



```cpp
//luoguP3810 【模板】三维偏序（陌上花开）
#include<bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int N=1e5+7;
int n,m,c[N<<1],ans[N],cnt; 
struct node{
	int a,b,c,w,f; 
}e[N],t[N];

inline int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

bool cmp(node x,node y){ //先排序a 
	if(x.a!=y.a) return x.a<y.a;
	if(x.b!=y.b) return x.b<y.b;
	return x.c<y.c;
}

void update(int x,int y){ for(;x<=m;x+=lowbit(x)) c[x]+=y;} //树状数组单点加 

int sum(int x){ //单点查询前缀和
	int ans=0;
	for(;x;x-=lowbit(x)) ans+=c[x];
	return ans;
}

void CDQ(int l,int r){ //CDQ分治 
	int mid=(l+r)>>1; 
	if(l==r) return; 
	CDQ(l,mid);CDQ(mid+1,r);
	int p=l,q=mid+1,tot=l;
	while(p<=mid&&q<=r){ //按b权值大小排序 
		if(e[p].b<=e[q].b) update(e[p].c,e[p].w),t[tot++]=e[p++]; //t是排序后的数组 
		else e[q].f+=sum(e[q].c),t[tot++]=e[q++]; //对后半段累计f[i] 
	}
	while(p<=mid) update(e[p].c,e[p].w),t[tot++]=e[p++];  
	while(q<=r) e[q].f+=sum(e[q].c),t[tot++]=e[q++]; //累加f[i]
	for(int i=l;i<=mid;i++) update(e[i].c,-e[i].w); //清零 
	for(int i=l;i<=r;i++) e[i]=t[i]; 
}

signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++) e[i].a=read(),e[i].b=read(),e[i].c=read(),e[i].w=1;
	sort(e+1,e+n+1,cmp);
	cnt=1;
	for(int i=2;i<=n;i++){ //去重 
		if(e[i].a==e[cnt].a&&e[i].b==e[cnt].b&&e[i].c==e[cnt].c) e[cnt].w++;
		else e[++cnt]=e[i];
	}
	CDQ(1,cnt);
	for(int i=1;i<=cnt;i++) ans[e[i].f+e[i].w-1]+=e[i].w;
	for(int i=0;i<n;i++) printf("%d\n",ans[i]);
	return 0;
}

```



##### [CQOI2011\]动态逆序对

现在给出$1\sim n$ 的一个排列，按照某种顺序依次删除 $m$ 个元素，你的任务是在每次删除一个元素**之前**统计整个序列的逆序对数。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;

int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}return x*f;}

struct node{
    int x,y;
}a[N],b[N];

int pos[N],n,m;
ll ans[N];

struct BIT{ //树状数组:单点修改和单点查询 
    int t[N];
    inline int lowbit(int x){return x&(-x);}
	inline int ask(int x){int res=0;for(;x;x-=lowbit(x))res+=t[x];return res;}
    inline void add(int x,int v){for(;x<=n;x+=lowbit(x))t[x]+=v;}
}B1,B2;

void CDQ(int l,int r){ //CDQ分治 
    if(l>=r)return;
    int mid=(l+r)>>1;
    CDQ(l,mid),CDQ(mid+1,r);
    for(int i=l;i<=mid;i++) B1.add(n-a[i].y+1,1);//在出现的位置加 
    for(int k=l,i=l,j=mid+1;k<=r;k++){ //计算部分 
        if(j>r||i<=mid&&a[i].x<=a[j].x){
            b[k]=a[i++];
            B1.add(n-b[k].y+1,-1);
            ans[b[k].y]-=B2.ask(n-b[k].y+1); //第b[k].y次删除后的逆序对少的部分 
        }else{
            b[k]=a[j++]; 
            B2.add(n-b[k].y+1,1);
            ans[b[k].y]-=B1.ask(n-b[k].y+1);
            ans[0]+=mid-i+1; //这是最开始的逆序对结果 
        }
    }
    for(int i=mid+1;i<=r;i++) B2.add(n-a[i].y+1,-1);
    memcpy(a+l,b+l,sizeof(node)*(r-l+1)); //排序后的结果 
}

signed main(){
    n=read();m=read();
    for(int i=1;i<=n;i++) pos[a[i].x=read()]=i; //记录每个数出现的位置 
    for(int i=1,x;i<m;i++) a[pos[x=read()]].y=i; //记录第几次删除 
    for(int i=1;i<=n;i++) if(!a[i].y) a[i].y=n; //不用删除的数 
    CDQ(1,n);
    for(int i=1;i<m;i++) ans[i]+=ans[i-1]; //前缀和 
    for(int i=0;i<m;i++) printf("%lld\n",ans[i]);
    return 0;
}
```





### 待续

##### 整体二分

满足询问答案可二分，且题目允许离线操作，就可以考虑是否可以用整体二分。

之后会另外出一篇学习整体二分，现在我的知识太薄弱了。

##### 四维偏序

还是之后再掌握吧。大概的方法有CDQ套CDQ套树状数组，复杂度$O(nlog^3n)$左右

更高维的偏序问题可以用Bitset进行优化。



# 参考资料

https://www.luogu.com.cn/blog/Owencodeisking/post-xue-xi-bi-ji-cdq-fen-zhi-hu-zheng-ti-er-fenhttps://oi-wiki.org/misc/cdq-divide/

https://www.luogu.com.cn/record/65026051
