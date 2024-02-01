---
title : 二叉搜索树 
date ： 2021-8-3 
tags : ACM,数据结构
author : LINNO
---

![img](https://img-blog.csdnimg.cn/f7633ffa374a43c385e06023cc4f816f.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA57yE5ruF,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

### 二叉搜索树

BST（Binary Search Tree），二叉搜索树，又叫二叉排序树。

他的结构不像二叉堆一样可控，有时会被卡成 $O(n^2)$ 的操作复杂度（想象成一条链）。但掌握二叉搜索树相对于打开了平衡树的大门。掌握BST，有利于对Splay、替罪羊树等高效率的平衡树数据结构的学习。

### 性质

- 若左子树不为空，则左子树上的所有节点的值均小于父节点的值。

- 若右子树不为空，则右子树上的所有节点的值均大于父节点的值。

- 左右子树也分别为二叉排序树。

- 没有权值相同的节点。（可用计数器表示一个数出现过几遍）

### 操作

插入、查询、数值、前驱、后继都是向下传递的过程，类似于二叉堆的下沉操作。

在平衡的情况下，是$O(logn)$的复杂度，只需要走到目标结点执行相应操作便可。

直接上模板吧。以下是递归版：

```java
#include<bits/stdc++.h>
#define int long long
//luoguP5076 【深基16.例7】普通二叉树（简化版）
using namespace std;
const int maxn=1e4+7,INF=2147483647;

inline void read(int &data){ //快读优化 
	int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	data=x*f;
}

struct Node{
	int val,fa,ls,rs,cnt,sz;
}t[maxn];

int q,n,m,x,op;
int tot=0;//表示BST一共有多少节点

void insert(int now,int val){
	t[now].sz++; //节点的大小+1 
	if(t[now].val==val){  
		t[now].cnt++; //该权值出现次数+1 
		return;
	}
	if(t[now].val>val){ //说明val在now的左子树
		if(t[now].ls!=0) insert(t[now].ls,val); //向左继续找 
		else{ //插入到左子树 
			tot++;
			t[tot].val=val;
			t[tot].sz=t[tot].cnt=1;
			t[now].ls=tot;
		} 
	}else{
		if(t[now].rs!=0) insert(t[now].rs,val); //向右继续找 
		else{  //插入到右子树 
			tot++;
			t[tot].val=val;
			t[tot].sz=t[tot].cnt=1;
			t[now].rs=tot;
		}
	}
}

int get_pre(int now,int val,int ans){ //找前驱 
	if(t[now].val>=val){ //在左边找到第一个小于val的数 
		if(t[now].ls==0) return ans; //左子树中没有比val更小的数了 
		else return get_pre(t[now].ls,val,ans); //继续查找左子树 
	}else{ //找右边 
		if(t[now].rs==0) return t[now].val; //在左子树中找到了最右边的数 
		return get_pre(t[now].rs,val,t[now].val); //继续查找右子树 
	}
}

int get_nxt(int now,int val,int ans){ //找后继,和前驱类似 
	if(t[now].val<=val){
		if(t[now].rs==0) return ans;
		else get_nxt(t[now].rs,val,ans);
	}else{
		if(t[now].ls==0) return t[now].val;
		return get_nxt(t[now].ls,val,t[now].val);
	}
}

int get_val(int x,int val){
	if(x==0) return 0; //无排名
	if(val==t[x].val) return t[t[x].ls].sz; //左子树的大小就是排名 
	if(val<t[x].val) return get_val(t[x].ls,val); //向左子树缩小范围 
	return get_val(t[x].rs,val)+t[t[x].ls].sz+t[x].cnt;  //左子树大小+当前点次数+向右查找排名 
}

int get_rank(int x,int rk){ 
	if(x==0) return INF; //无值 
	if(t[t[x].ls].sz>=rk) return get_rank(t[x].ls,rk); //向左查找该数 
	if(t[t[x].ls].sz+t[x].cnt>=rk) return t[x].val; // 左子树的大小+当前节点的大小大于排名，直接返回 
	return get_rank(t[x].rs,rk-t[t[x].ls].sz-t[x].cnt); //在右子树中查找rk-左子树大小-当前节点次数的排名  
}

signed main(){
	read(q);
	while(q--){
		read(op);read(x);
		if(op==1) printf("%d\n",get_val(1,x)+1);//查询x数的排名 
		if(op==2) printf("%d\n",get_rank(1,x)); //查询排名为x的数 
		if(op==3) printf("%d\n",get_pre(1,x,-INF)); //查询x的前驱 
		if(op==4) printf("%d\n",get_nxt(1,x,INF)); //查询x的后继 
		if(op==5){ //插入节点 
			if(tot==0){ //建立最开始的节点 
				tot=1;
				t[tot].cnt=t[tot].sz=1;
				t[tot].val=x;
			}else insert(1,x);
		}
	}
	return 0;
}
```

非递归版的效率会稍微高一点：

```java
#include<bits/stdc++.h>
using namespace std;
const int N=10010;
const int INF=0x7fffffff;

inline void read(int &data){ //快读优化 
	int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	data=x*f;
}

#define ls tree[x].son[0] //左儿子 
#define rs tree[x].son[1] //右儿子 

struct Node{
	int val,sz,cnt,son[2];
}tree[N];

int n,rt,tot,opt,x;

inline void add(int v){ //插入操作 
	if(!tot){ //插入第一个节点 
		rt=++tot;  
		tree[tot].cnt=tree[tot].sz=1;
		tree[tot].son[0]=tree[tot].son[1]=0;
		tree[tot].val=v;
		return;
	}
	int x=rt,f=0; 
	do{
		++tree[x].sz; //当前节点大小+1 
		if(tree[x].val==v){ //val已经存在 
			++tree[x].cnt; //次数+1 
			break;
		}
		f=x; //更新父节点 
		x=tree[f].son[v>tree[f].val]; //决定向左或者向右搜索 
		if(!x){ //找到空节点 
			tree[f].son[v>tree[f].val]=++tot;
			tree[tot].son[0]=tree[tot].son[1]=0;
			tree[tot].val=v;
			tree[tot].cnt=tree[tot].sz=1;
			break; 
		}
	}while(1);
}

int get_pre(int val){ //找前驱 
	int x=rt,ans=-INF;
	do{
		if(x==0) return ans; //空节点 
		if(tree[x].val>=val){ //如果当前点大于那个值 
			if(ls==0) return ans; //没有比他小的数，直接返回 
			x=ls; //寻找左子树 
		}else{
			if(rs==0) return tree[x].val; //没有右子树 
			ans=tree[x].val;  //更新ans 
			x=rs; //寻找右子树 
		}
	}while(1);
}

int get_nxt(int v){ //找后继，操作类似 
	int x=rt,ans=INF;
	do{
		if(x==0) return ans;
		if(tree[x].val<=v){
			if(rs==0) return ans;
			x=rs;
		}else{
			if(ls==0) return tree[x].val;
			ans=tree[x].val;
			x=ls;
		}
	}while(1);
}

int get_rank(int rk){ //寻找排名rk的值 
	int x=rt;
	do{
		if(x==0) return INF; //不存在 
		if(tree[ls].sz>=rk) x=ls; //左子树大过那个排名，传下去 
		else if(tree[ls].sz+tree[x].cnt>=rk) return tree[x].val; //返回那个值 
		else rk-=tree[ls].sz+tree[x].cnt,x=rs; //减去左子树 
	}while(1);
}

int get_val(int v){ //寻找值val的排名 
	int x=rt,ans=0;
	do{
		if(x==0) return ans; 
		if(tree[x].val==v) return ans+tree[ls].sz; //返回答案 
		else if(tree[x].val>v) x=ls; //往右子树找 
		else ans+=tree[ls].sz+tree[x].cnt,x=rs;  //排名加上左子树的大小 
	}while(1);
}

int main(){
	read(n);
	while(n--){
		read(opt);read(x);
		if(opt==1) printf("%d\n",get_val(x)+1);
		if(opt==2) printf("%d\n",get_rank(x));
		if(opt==3) printf("%d\n",get_pre(x));
		if(opt==4) printf("%d\n",get_nxt(x));
		if(opt==5) add(x);
	}
	return 0;
}
```

### 参考资料

https://www.cnblogs.com/do-while-true/p/13566274.html

https://blog.csdn.net/hh66__66hh/article/details/82947113

