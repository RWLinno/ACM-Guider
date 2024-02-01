---
title : 后缀自动机
date : 2021-11-11
tags : ACM,字符串
author : Linno

---
![在这里插入图片描述](https://img-blog.csdnimg.cn/8d98021ffbab4521a4f50da0f6aac7ea.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA57yE5ruF,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)



### 前置知识

KMP，Trie，AC自动机等字符串基础

DFA（有限状态自动机）



### 后缀自动机(Suffix automaton ,SAM)

##### 定义

字符串s的SAM是一个接受s的所有后缀的最小DFA（确定性有限自动机）。直观上SAM是给定字符串的所有字串的压缩形式。而构造的时间复杂度和空间复杂度仅为$O(n)$。一个SAM最多有2n-1个节点和3n-4条转移边。



##### 符号定义

endpos(t)为字符串s中t的所有结束位置，endpos的集合即为SAM的状态集

subs(sta)：SAM中sta状态所包含的所有**子串的集合**

mxsub(sta)：sta状态所包含的子串中**最长的子串**

mnsub(sta)：sta状态所包含的子串中**最短的子串**

sz[i]：sta表示的endpos集合大小，即i号点字符串集合在整个串出现次数

nxt(sta)：sta遇到的下一个字符集合

link(sta):



### 性质

**状态数**：不超过2n-1

**转移数**：不超过3n-4

$DAG性质$：SAM是有向无环图，因此可以用DP计算路径条数。

**状态集**：所有endpos的集合即为SAM的状态集。



##### 转移函数

$nxt(sta)=\{S[i+1]|i\in endpos(sta)\}$

$trans(sta,c)=\{x|mxsub(sta+(c\in subs(x))\}$

##### 后缀链接link

sta状态链接到下一个连续后缀所在的状态，叫做后缀链接。



##### 子串表示法

用一个点的集合以及长度len来描述一个子串

##### Parent树



##### 引理1

$两个非空子串u和w(假设|u|\leq|w|)的endpos相同，当且仅当字符串u是w的后缀。$

对于任意一个状态$sta$,任取$str\in subs(sta)$,都有$str$是$mxsub(sta)$的后缀。

例如：subs(7)={aabbab,abbab,bbab,bab}

任取一个字符串str,str是mxsub(7)=aabbab的后缀。

SAM中一个状态所包含的子串的集合是由长度连续的一系列字符串构成，并且由长到短，依次减少最前面的字符。



##### 引理2

两个非空子串u和w(假设$|u|\leq|w|$)，要么$endpos(u)\cap endpos(w)=\empty$，要么$endpos(w)\subseteq endpos(u)，取决于u是否为w的一个后缀$



##### 引理3

$$
对于任意状态sta,任取mxsub(sta)的后缀str,若str的长度满足：\\
|misub(sta)|\le|str|\le|mxsub(sta)|，那么str\in substr(sta)
$$

考虑一个$endpos$ 等价类，将类中的所有子串按长度非递增的顺序排序。每个子串都不会比它前一个子串长，与此同时每个子串也是它前一个子串的后缀。换句话说，对于同一等价类的任一两子串，较短者为较长者的后缀，且该等价类中的子串长度恰好覆盖整个区间 [x,y]。





##### 引理4

所有后缀链接构成一棵根节点为$t_0$的树。



##### 引理5

通过endpos集合构建的树（每个子节点的subset都包含在父节点的subset中）与通过后缀链接link构建的树相同。



### 构造流程

①令last为添加字符串c前，整个字符串对应的状态，初始last=0。

②创建新的状态cur，len(cur)=len(last)+1，此时link(cur)还未知。

③如果没有字符c的转移，就添加一个状态cur的转移，遍历后缀链接；否则停下并将这个状态标记为p。

④如果没有找到这个状态p，我们就达到了虚拟状态-1，将link(cur)赋值为0并退出。

⑤分类讨论两种状态，要么$len(p)+1=len(q)$，要么不是。

⑥如果$len(p)+1=len(q)$，我们只要将$link(cur)$赋值为q并退出。否则复制状态q，创建一个新的状态clone，复制除了len以外的所有信息，$len(clone)=len(p)+1$

⑦将last的值更新为状态cur。



### 实现

```c++
int sz,last; //SAM的大小以及末状态
struct state{ //状态节点
    int len,link;
    map<char,int>nxt; //转移的列表
}st[MAXLEN*2]; //因为最多2n-1个状态

void sam_init(){ //初始化sam
    st[0].len=0;
    st[0].link=-1; //-1表示虚拟状态
    sz++; 
    last=0;
}

void sam_extend(char c){ //添加字符c
    int cur=sz++; //创建新的状态
    st[cur].len=st[last].len+1;
    int p=last;
    while(p!=-1&&st[p].nxt.count(c)){ //遍历后缀链接
        st[p].nxt[c]=cur;
        p=st[p].link;
    }
    if(p==-1) st[cur].link=0; //没要找到这样的状态
    else{
        int q=st[p].nxt[c];
        if(st[p].len+1==st[q].len) st[cur].link=q;
        else{
            int clone=sz++; //复制一个状态
            st[clone].len=st[p].len+1;
            st[clone].nxt=st[q].nxt;
            st[clone].link=st[q].link;
            while(p!=-1&&st[p].nxt[c]==q){
                //后缀链接从状态p往回走
                st[p].nxt[c]=clone;
                p=st[p].link;
            }
            st[q].link=st[cur].link=clone;
        }
    }
    last=cur; //更新last为当前状态
}
```



### 检查子串是否出现

在SAM上向父亲跑边，跑完串还未跑到空状态则为原串子串。

后缀数组：跑出sa，然后从最小的后缀开始，一个个往后枚举，记录下当前匹配到的位置，如果匹配不上就下一个后缀，否则位置向后移一位。如果枚举完了后缀还没完全匹配则不是原串子串。



### 最小循环位移

字符串S+S对应的SAM中寻找最小的长度为|S|的路径。

从初始状态开始，贪心地访问最小的字符即可。



### 子串第一次出现位置

预处理每个状态第一次出现的位置$pos(i)$

只需要每次让$pos(np)=len(np)pos(nq)=pos(q)$就好了

查询答案为$pos(i)-|T|+1$



### 最短的没有出现的字符串

在SAM上做dp，设$dp[i]$表示到点i时的最短长度

如果这个点有不是T中字符的出边，则$dp[i]=1$，否则$dp[i]=1+min_{(i,j,c)\in SAM}dp[j]$



### 不同子串个数

对字符串S构造后缀自动机。每个S的子串相当于自动机中的一些路径，因此不同子串的个数等于自动机中以$t_0$为起点的不同路径条数。

考虑SAM为DAG，可用动态规划计算不同路径的条数。

$令d_v为从状态v开始的路径数量,则d_v=1+\sum_{w:(v,w,c)\in DAWG} d_w\\即d_v可以表示为所有v的转移的末端之和。$

##### luoguP2408 不同子串个数

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+7;

struct State{
	int len,fa,ch[26];
}st[N];

int n,lst=1,cnt=1,ans[N];
string str;

inline void ins(int c){ //SAM加点 
	int p=lst,np=lst=++cnt;
	st[np].len=st[p].len+1;
	for(;p&&!st[p].ch[c];p=st[p].fa) st[p].ch[c]=np;
	if(!p) return (void)(st[np].fa=1);
	int q=st[p].ch[c];
	if(st[q].len==st[p].len+1) return (void)(st[np].fa=q);
	int nq=++cnt;st[nq]=st[q];st[nq].len=st[p].len+1,st[q].fa=st[np].fa=nq;
	for(;p&&st[p].ch[c]==q;p=st[p].fa) st[p].ch[c]=nq;
}

inline int dfs(int x){//在SAM上跑dfs 
	if(ans[x]) return ans[x];
	for(int i=0;i<26;i++) if(st[x].ch[i]) ans[x]+=dfs(st[x].ch[i])+1;
	return ans[x]; 
}

signed main(){
	cin>>n;
	cin>>str;
	//memset(ans,0,sizeof(ans));
	for(int i=0;i<n;i++) ins(str[i]-'a');
	cout<<dfs(1)<<"\n";
	return 0; 
}
```



### 所有不同子串的总长度

与上述做法类似，递推式$ans_v=\sum_{w:(v,w,c)\in DAWG}(d_w+ans_w)$

##### luoguP3804 【模板】后缀自动机 (SAM)

所有出现次数不为1的子串的出现次数乘以该子串长度的最大值。

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2010000;
char s[N];
int fa[N],ch[N][26],len[N],siz[N];
int lst=1,cnt=1,l,t[N],A[N];
int ans;
void Extend(int c){
	int f=lst,p=++cnt;lst=p;  //lst为上一个节点,p为当前节点（编号） 
	len[p]=len[f]+1;siz[p]=1;  //len[i]记录i节点的longest,siz[i]记录集合元素大小 
	while(f&&!ch[f][c]) ch[f][c]=p,f=fa[f]; //创建新的节点并向后退 
	if(!f) {fa[p]=1;return;} 
	/*
	  把前面的一段没有c儿子的节点的c儿子指向p
	  Situation 1 如果跳到最前面的根的时候，那么把p的parent树上的父亲置为1(初始状态) 
	 */
	int x=ch[f][c],y=++cnt; //y是克隆状态 
	if(len[f]+1==len[x]) {fa[p]=x;cnt--;return;}
	/*
	  x表示从p一直跳parent树得到的第一个有c儿子的节点的c儿子
	  Situation 2 如果节点x表示的endpos所对应的字符串集合只有一个字符串，那么把p的parent树父亲设置为x
      Situation 2 和 Situation 3 本质不同！！！
	 */
	len[y]=len[f]+1; fa[y]=fa[x]; fa[x]=fa[p]=y;
	memcpy(ch[y],ch[x],sizeof(ch[y]));
	while(f&&ch[f][c]==x) ch[f][c]=y,f=fa[f];
	/*
	  Situation 3 把x点复制一遍（parent树父亲、儿子），同时len要更新
	             （注意len[x]!=len[f]+1,因为通过加点会使x父亲改变）
				  然后把x点和p点的父亲指向复制点y，再将前面所有本连x的点连向y
	 */
}
signed main(){
	//Part 1 建立后缀自动机
	scanf("%s",s); l=strlen(s);
	for(int i=l;i>=1;i--) s[i]=s[i-1];s[0]=0;
	for(int i=1;i<=l;i++) Extend(s[i]-'a');
	//Part 2 按len从大到小排序（和SA好像啊）后计算答案
	for(int i=1;i<=cnt;i++) t[len[i]]++;
	for(int i=1;i<=cnt;i++) t[i]+=t[i-1];
	for(int i=1;i<=cnt;i++) A[t[len[i]]--]=i;
	for(int i=cnt;i>=1;i--){ //从小到大枚举，实际上在模拟parent树的DFS
		int now=A[i];siz[fa[now]]+=siz[now];
		if(siz[now]>1) ans=max(ans,siz[now]*len[now]);
	}
	printf("%lld\n",ans);
	return 0;
}
```



### 字典序第k大子串

字典序第k大的子串对应于SAM中字典序第k大的路径，因此计算每个状态的路径数后，可以很容易的从SAM的根开始找到第k大的路径。$预处理O(|S|),单词询问O(|ans|·|\Sigma|)$

##### luoguP3975 [TJOI2015]弦论

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2010000;
char s[N];
int fa[N],ch[N][26],len[N],siz[N];
int lst=1,cnt=1,l,t[N],A[N];
int T,K,sum[N];
void Extend(int c){
	int f=lst,p=++cnt;lst=p;  //lst为上一个节点,p为当前节点（编号） 
	len[p]=len[f]+1;siz[p]=1;  //len[i]记录i节点的longest,siz[i]记录集合元素大小 
	while(f&&!ch[f][c]) ch[f][c]=p,f=fa[f]; //创建新的节点并向后退 
	if(!f) {fa[p]=1;return;} 
	int x=ch[f][c],y=++cnt; //y是克隆状态 
	if(len[f]+1==len[x]) {fa[p]=x;cnt--;return;}
	len[y]=len[f]+1; fa[y]=fa[x]; fa[x]=fa[p]=y;
	memcpy(ch[y],ch[x],sizeof(ch[y]));
	while(f&&ch[f][c]==x) ch[f][c]=y,f=fa[f];
}

void Print(int x,int k){ //深搜找到K小子串的位置 
	if(k<=siz[x]) return;
	k-=siz[x];
	for(int i=0;i<26;i++){
		int R=ch[x][i];
		if(!R) continue;
		if(k>sum[R]){k-=sum[R];continue;}
		putchar(i+'a');
		Print(R,k);
		return;
	}
}

signed main(){
	scanf("%s",s); l=strlen(s);
	scanf("%d%d",&T,&K); 
	for(int i=l;i>=1;i--) s[i]=s[i-1];s[0]=0;
	for(int i=1;i<=l;i++) Extend(s[i]-'a');
	for(int i=1;i<=cnt;i++) t[len[i]]++;
	for(int i=1;i<=cnt;i++) t[i]+=t[i-1];
	for(int i=1;i<=cnt;i++) A[t[len[i]]--]=i; //桶排序
	for(int i=cnt;i>=1;i--) siz[fa[A[i]]]+=siz[A[i]]; //累加子串个数 
	for(int i=1;i<=cnt;i++) T==0?(sum[i]=siz[i]=1):(sum[i]=siz[i]); //相同串个数 
	siz[1]=sum[1]=0;
	for(int i=cnt;i>=1;i--){
		for(int j=0;j<26;j++){
			if(ch[A[i]][j]) sum[A[i]]+=sum[ch[A[i]][j]]; //从后往前累加 
		}
	}
	if(sum[1]<K) puts("-1");
	else Print(1,K),puts("");
	return 0;
}
```



### 子串出现次数

对于每个状态$v$,预处理$cnt_v$，使之等于$endpos(v)$集合的大小。

##### CF802I Fake News (hard)

T组数据，对字符串s求$\sum_pcnt(s,p)^2$，cnt(s,p)表示子串p在s中的出现次数

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+7;

int t,n,ans=0;
string str;

namespace SAM{
	map<int,int>ch[N];
	int lst=1,cnt=1,len[N],fa[N],sz[N];
	inline void ins(int c){
		int p=lst,np=++cnt;lst=np;len[np]=len[p]+1;sz[np]=1;
		for(;!ch[p][c];p=fa[p]) ch[p][c]=np;
		if(!p) fa[np]=1;
		else{
			int q=ch[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else{
				int nq=++cnt;
				len[nq]=len[p]+1;ch[nq]=ch[q];
				fa[nq]=fa[q];fa[q]=fa[np]=nq;
				for(;ch[p][c]==q;p=fa[p]) ch[p][c]=nq;
			} 
		}
	}
	inline void clear(){
		memset(sz,0,sizeof(sz));
		for(int i=1;i<=cnt;i++) ch[i].clear();
		memset(len,0,sizeof(len));
		memset(fa,0,sizeof(fa));
		lst=cnt=1;
	}
};
using namespace SAM;

vector<int>G[N];
void init(){
	ans=0;
	for(int i=1;i<=cnt;i++) G[i].clear();
	clear();
}

void dfs(int u){
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		dfs(v);
		sz[u]+=sz[v];
	}
	ans+=(len[u]-len[fa[u]])*sz[u]*sz[u];
} 

signed main(){
	cin>>t;
	while(t--){
		init();
		cin>>str;
		n=str.length();
		for(int i=0;i<n;i++) ins(str[i]-'a');
		for(int i=2;i<=cnt;i++) G[fa[i]].push_back(i);//建立parent tree 
		dfs(1);
		cout<<ans<<"\n";
	}
	return 0; 
}
```



### 两个串的最长公共子串

对母串建SAM，然后第二个字符串一个个匹配过去。

如果现态p有Si的转移，则len++并跳到下一个字符；否则在parent树上向上跳直到有这个转移为止。

##### luoguSP1811 LCS - Longest Common Substring

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+7;

struct State{
	int len,fa,ch[26];
}st[N<<1];

int lst=1,cnt=1;
string str1,str2;

inline void ins(int c){ //SAM加点 
	int p=lst,np=lst=++cnt;
	st[np].len=st[p].len+1;
	for(;p&&!st[p].ch[c];p=st[p].fa) st[p].ch[c]=np;
	if(!p) return (void)(st[np].fa=1);
	int q=st[p].ch[c];
	if(st[q].len==st[p].len+1) return (void)(st[np].fa=q);
	int nq=++cnt;st[nq]=st[q];st[nq].len=st[p].len+1,st[q].fa=st[np].fa=nq;
	for(;p&&st[p].ch[c]==q;p=st[p].fa) st[p].ch[c]=nq;
}

int calc(int n){
	int p=1,ans=0,len=0;
	for(int i=0;i<n;i++){ //子串开始位置 
		int c=str2[i]-'a';
		if(st[p].ch[c]) len++,p=st[p].ch[c]; 
		else{
			for(;p&&!st[p].ch[c];p=st[p].fa); 
			if(p) len=st[p].len+1,p=st[p].ch[c]; //匹配下一个字符 
			else len=0,p=1; //返回初始状态 
		}
		ans=max(ans,len);
	}
	return ans;
}

signed main(){
	cin>>str1;
	cin>>str2;
	int n1=str1.length(),n2=str2.length();
	for(int i=0;i<n1;i++) ins(str1[i]-'a');
	cout<<calc(n2)<<"\n";
	return 0; 
}
```



### 多个字符串间的最长公共子串

还是对第一个串建SAM，然后一个一个串处理。在处理每一个串的时候记录当前节点的最大匹配长度，并且记录最大长度的最小值，就是所有串的匹配长度。

##### SP1812 LCS2 - Longest Common Substring II

```C++
#include<bits/stdc++.h>
#define N 2000010
#define inf 0x3f3f3f3f
using namespace std; 
int n,lst,tot=1,root=1,num,ans;
int fa[N],len[N],ch[N][30],siz[N][12];
char s[N];
vector<int>G[N];

void insert(int c,int id){  //SAM构造 
    int p=lst,np=lst=++tot;
    len[np]=len[p]+1,siz[np][id]++; //记录每个节点被多少字符串更新
    while(p&&!ch[p][c]) ch[p][c]=np,p=fa[p];
    if(!p) fa[np]=root;
    else{
        int q=ch[p][c];
        if(len[q]==len[p]+1) fa[np]=q;
        else{
            int nq=++tot;
            memcpy(ch[nq],ch[q],sizeof(ch[q]));
            len[nq]=len[p]+1,fa[nq]=fa[q],fa[q]=fa[np]=nq;
            while(ch[p][c]==q) ch[p][c]=nq,p=fa[p];
        }
    }
}
void dfs(int x){
    for(int i=0;i<G[x].size();i++){
        int y=G[x][i];
        dfs(y);
        for(int id=1;id<=num;++id)
            siz[x][id]+=siz[y][id]; //跑DFS处理子串信息 
    }
}

bool check(int p){
    if(!p) return false;
    for(int i=1;i<=num;++i) //如果所有字符串都有子串p 
        if(!siz[p][i])  
            return false;
    return true;
}

void work(){
    for(int i=2;i<=tot;++i)  G[fa[i]].push_back(i); 
    dfs(root);
    int p=root,l=0;
    for(int i=1;i<=n;++i){
        int c=s[i]-'a';
        if(check(ch[p][c])) l++,p=ch[p][c];
        else{
            while(p&&!check(ch[p][c])) p=fa[p];
            if(p) l=len[p]+1,p=ch[p][c];
            else l=0,p=root;
        }
        ans=max(ans,l);
    }
}
signed main(){
    while(scanf("%s",s+1)!=EOF){
		n=strlen(s+1);
		lst=root;
		num++;
		for(int i=1;i<=n;++i) insert(s[i]-'a',num); //广义SAM 
	}
    work();
	printf("%d\n",ans);
    return 0;
}
```





### 其他例题

##### 每次插入后的不同子串个数

luogu P4070 [SDOI2016]生成魔咒

每次新增字符时，对答案的贡献为$|max(p)|-|min(p)|+1=|max(p)|-|max(p->link)|$,新建的nq节点是没有贡献的。

```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+7;

int n,s[N],ans=0;
namespace SAM{
	map<int,int>ch[N];
	int lst=1,cnt=1,len[N],fa[N];
	inline void ins(int c){
		int p=lst,np=++cnt;lst=np;len[np]=len[p]+1;
		for(;!ch[p][c];p=fa[p]) ch[p][c]=np;
		if(!p) fa[np]=1;
		else{
			int q=ch[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else{
				int nq=++cnt;
				len[nq]=len[p]+1;ch[nq]=ch[q];
				fa[nq]=fa[q];fa[q]=fa[np]=nq;
				for(;ch[p][c]==q;p=fa[p]) ch[p][c]=nq;
			} 
		}
		ans+=len[np]-len[fa[np]];
	}
};

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		SAM::ins(s[i]);
		cout<<ans<<"\n"; 
	}
	return 0; 
}
```





### 参考资料

https://www.luogu.com.cn/blog/Kesdiael3/hou-zhui-zi-dong-ji-yang-xie

https://www.bilibili.com/video/BV1wa4y1a7Ag

https://www.bilibili.com/video/BV1ED4y1U7aU

https://www.cnblogs.com/maomao9173/p/10447821.html

https://www.cnblogs.com/mikufun-hzoi-cpp/p/12098738.html

https://www.luogu.com.cn/blog/lhm126/solution-sp1812
