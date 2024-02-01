---
title : dfs序与树链剖分
date : 2021-8-12
tags : 图论,ACM
author : Linno

---

![在这里插入图片描述](https://img-blog.csdnimg.cn/e4da2dfc731a4d1886a632ee0960807d.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA57yE5ruF,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)


### 支持操作

在子树上或者是两点路径上的所有节点的求和、修改、查询等操作。

具体操作大致为：

（1）dfs进行树链剖分处理节点信息；

（2）根据dfs序把树拉直然后套数据结构。



### dfs序

把树搞成了“连续的”。

一个节点的子树上的节点的时间戳，一定大于这个节点的时间戳且连续。

某些链上的时间戳也是连续的。

因为dfs序的性质——重链上的时间戳是连续的。





### 树链剖分

#### 重链剖分——常用

$O(logn)$

将每个点子树大小最大的儿子标记为重儿子。

#### 长链剖分——不常用

$O(\sqrt n)$

长链剖分十分类似于轻重链剖分，但是我们稍加修改，将每次选择子树大小最大的儿子作为重儿子变成了选择子树深度最大的那个儿子作为重儿子。然后将所有点和它的重儿子之间的边认为是重边，如果我们把他们在树中全部加粗，那么原树就被分割成了若干条链。

##### 性质

（1）所有链的长度和是O(n)级别的。

（2）任意一点x的k级祖先y所在的长链长度大于等于k

（3）任意一点到根节点的重链数量不超过\sqrt n

##### 应用

（1）O(nlogn)预处理，O(1)算k次祖先。

对于每一条长链的顶端x,记长链长度为L，预处理x沿长链从上往下的每一个点，以及x的L个祖先。要求点u的k次祖先，取$r=2^p$(p+1是k二进制的最高位)，r>k/2,u的r次祖先由预处理得到，记为y。由性质2，y的k-r次祖先可直接求得。

（2）O(n)统计每个子树中以深度为下标的可合并信息。
用指针维护动规数组，在重儿子传递给父亲时将指针左移/右移一位。对于轻儿子，暴力统计信息。



##### 实链剖分（搞LCT）

**重儿子**：一个节点的所有儿子中，大小最大的儿子（只有1个，如果相等则随便选）

**轻儿子**：一个节点除了重儿子之外的儿子都是轻儿子

**重链**：从一个轻儿子开始（根节点也是轻儿子），一路向重儿子走，连出的链叫做重链。除根节点外的任何一个节点的父亲节点都一定在一条重链上。

**轻链**：除了重链全是轻链

剖分好再dfs一遍标出dfs序即可实现上述四种操作。





### 树链剖分与线段树

树链剖分和线段树可以结合使用，来解决树上路径修改、查询的问题。

##### LuoguP4315 月下“毛景树”

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

struct E{
	int v,w,n;
}e[N<<2];

int head[N],bk[N<<1],cnt=0;
inline void addedge(int u,int v,int w){
	e[++cnt]=(E){v,w,head[u]};head[u]=cnt;
	e[++cnt]=(E){u,w,head[v]};head[v]=cnt;
}

int sz[N],fa[N],son[N],val[N],dep[N],dfn[N],idx,idfn[N],bel[N];
void dfs1(int x){
	sz[x]=1;
	for(int i=head[x];i;i=e[i].n){
		int to=e[i].v;
		if(to==fa[x]) continue;
		fa[to]=x;
		val[to]=e[i].w;
		dep[to]=dep[x]+1;
		dfs1(to);
		sz[x]+=sz[to];
		if(sz[son[x]]<sz[to]) son[x]=to;
	}
}

void dfs2(int x,int tp){
	dfn[x]=++idx;
	idfn[idx]=x;
	bel[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i=head[x];i;i=e[i].n){
		int to=e[i].v;
		if(to==son[x]||to==fa[x]) continue;
		dfs2(to,to);
	}
}

int tr[N<<2],lazy[N<<2],tg[N<<2];
#define MID int mid=l+r>>1
#define ls p<<1
#define rs p<<1|1
void build(int p,int l,int r){
	tg[p]=-1;
	if(l==r){
		tr[p]=val[idfn[l]];
		return;
	}
	MID;
	build(ls,l,mid);
	build(rs,mid+1,r);
	tr[p]=max(tr[ls],tr[rs]);
}

void pushdown(int p,int l,int r){
	if(tg[p]>=0){
		lazy[ls]=lazy[rs]=0;
		tg[ls]=tg[p];tg[rs]=tg[p];
		tr[ls]=tg[p];tr[rs]=tg[p];
		tg[p]=-1;
	}
	if(lazy[p]){
		lazy[ls]+=lazy[p];
		lazy[rs]+=lazy[p];
		tr[ls]+=lazy[p];
		tr[rs]+=lazy[p];
		lazy[p]=0;
	}
}
 
void cover(int p,int l,int r,int ql,int qr,int w){
	if(ql<=l&&r<=qr){
		tr[p]=w;
		tg[p]=w;
		lazy[p]=0;
		return;
	}
	MID;
	pushdown(p,l,r);
	if(ql<=mid) cover(ls,l,mid,ql,qr,w);
	if(qr>mid) cover(rs,mid+1,r,ql,qr,w);
	tr[p]=max(tr[ls],tr[rs]); 
}

void add(int p,int l,int r,int ql,int qr,int w){
	if(ql<=l&&r<=qr){
		tr[p]+=w;
		lazy[p]+=w;
		return;
	}
	MID;
	pushdown(p,l,r);
	if(ql<=mid) add(ls,l,mid,ql,qr,w);
	if(qr>mid) add(rs,mid+1,r,ql,qr,w);
	tr[p]=max(tr[ls],tr[rs]);
}

int query(int p,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return tr[p];
	MID;int res=0;
	pushdown(p,l,r);
	if(ql<=mid) res=max(res,query(ls,l,mid,ql,qr));
	if(qr>mid) res=max(res,query(rs,mid+1,r,ql,qr));
	return res;
}

int n,u,v,w,rt;
string str;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
  	//freopen("in.cpp","r",stdin);
  	//freopen("out.cpp","w",stout);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v>>w;
		addedge(u,v,w);
		bk[i]=v;
	}
	for(int i=1;i<=n;i++) if(bk[i]) rt=i;
	dfs1(rt);
	dfs2(rt,rt);
	build(1,1,n);
	while(cin>>str){
		if(str=="Stop") break;
		if(str=="Max"){
			cin>>u>>v;
			int res=0;
			while(bel[u]!=bel[v]){
				if(dep[bel[u]]<dep[bel[v]]) swap(u,v);
				res=max(res,query(1,1,n,dfn[bel[u]],dfn[u]));
				u=fa[bel[u]];
			}
			if(dep[u]<dep[v]) swap(u,v);
			if(u!=v) res=max(res,query(1,1,n,dfn[v]+1,dfn[u]));
			cout<<res<<"\n";
		}
		if(str=="Add"){
			cin>>u>>v>>w;
			while(bel[u]!=bel[v]){
				if(dep[bel[u]]<dep[bel[v]]) swap(u,v);
				add(1,1,n,dfn[bel[u]],dfn[u],w);
				u=fa[bel[u]];
			}
			if(dep[u]<dep[v]) swap(u,v);
			if(u!=v) add(1,1,n,dfn[v]+1,dfn[u],w);	
		}
		if(str=="Change"){
			cin>>u>>v;
			u=dep[e[u*2-1].v]<dep[e[u<<1].v]?e[u<<1].v:e[u*2-1].v;
			cover(1,1,n,dfn[u],dfn[u],v);	
		}
		if(str=="Cover"){
			cin>>u>>v>>w;
			while(bel[u]!=bel[v]){
				if(dep[bel[u]]<dep[bel[v]]) swap(u,v);
				cover(1,1,n,dfn[bel[u]],dfn[u],w);
				u=fa[bel[u]];
			}
			if(dep[u]<dep[v]) swap(u,v);
			if(u!=v) cover(1,1,n,dfn[v]+1,dfn[u],w);	
		}
	}
	return 0;
}
```



##### luoguP3833 [SHOI2012]魔法树

```C++
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
vector<int>G[N];
inline void addedge(int u,int v){
	G[u].push_back(v);
	G[v].push_back(u);
}

int sz[N],dep[N],fa[N],son[N],bel[N],dfn[N],idx;
inline void dfs1(int x){
	sz[x]=1;
	for(int i=0;i<G[x].size();i++){
		int to=G[x][i];
		if(to==fa[x]) continue;
		fa[to]=x;
		dep[to]=dep[x]+1;
		dfs1(to);
		sz[x]+=sz[to];
		if(sz[son[x]]<sz[to]) son[x]=to; 
	}
}

inline void dfs2(int x,int tp){
	dfn[x]=++idx;
	bel[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i=0;i<G[x].size();i++){
		int to=G[x][i];
		if(to==son[x]||to==fa[x]) continue;
		dfs2(to,to);
	}
}

#define MID int mid=l+r>>1;
#define ls p<<1
#define rs p<<1|1
int tr[N<<2],lazy[N<<2];

void pushdown(int p,int l,int r){
	if(lazy[p]){
		MID;
		lazy[ls]+=lazy[p];
		lazy[rs]+=lazy[p];
		tr[ls]+=(mid-l+1)*lazy[p];
		tr[rs]+=(r-mid)*lazy[p];
		lazy[p]=0;
	}
}

void update(int p,int l,int r,int ql,int qr,int val){
	if(ql<=l&&r<=qr){
		lazy[p]+=val;
		tr[p]+=(r-l+1)*val;
		return;
	}
	MID;
	pushdown(p,l,r);
	if(ql<=mid) update(ls,l,mid,ql,qr,val);
	if(qr>mid) update(rs,mid+1,r,ql,qr,val);
	tr[p]=tr[ls]+tr[rs];
}

int query(int p,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return tr[p];
	MID;int res=0;
	pushdown(p,l,r);
	if(ql<=mid) res+=query(ls,l,mid,ql,qr);
	if(qr>mid) res+=query(rs,mid+1,r,ql,qr);
	return res;
}

int n,u,v,q,d;
char op;

signed main(){
//	ios::sync_with_stdio(0);//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);freopen("out.cpp","w",stout);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		addedge(u+1,v+1);
	}
	dfs1(1);
	dfs2(1,1);
	cin>>q;
	while(q--){
		cin>>op;
		if(op=='A'){
			cin>>u>>v>>d;
			u+=1;v+=1;
			while(bel[u]!=bel[v]){
				if(dep[bel[u]]<dep[bel[v]]) swap(u,v);
				update(1,1,n,dfn[bel[u]],dfn[u],d);
				u=fa[bel[u]];
			}
			if(dep[u]<dep[v]) swap(u,v);
			update(1,1,n,dfn[v],dfn[u],d);
		}else{
			cin>>u;
			u+=1;
			cout<<query(1,1,n,dfn[u],dfn[u]+sz[u]-1)<<"\n";
		}
	}
	return 0;
}
```





### **参考资料**

https://www.bilibili.com/video/BV1Qt411u77f?from=search&seid=6685906805699952409

https://www.bilibili.com/video/BV1RT4y1L7Sb
