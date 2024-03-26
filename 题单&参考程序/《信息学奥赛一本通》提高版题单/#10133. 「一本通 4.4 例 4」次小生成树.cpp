#include<bits/stdc++.h>
#define int long long
#define INF 98765432109876543

using namespace std;
const int maxn=3e5+7; 

inline void read(int &data){ //快读优化 
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=f*-1;
		ch=getchar(); 
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	data=x*f;
}
 
struct node{ 
	int to,w,nxt;
}e[maxn<<2]; //这里存最小生成树 

struct Node{
	int u,v,w;
	inline bool operator < (const Node &x)const{ //重定义<运算方便排序 
		return w<x.w; 
	}
}a[maxn]; //这是一开始的图 

int n,m,cnt,head[maxn],fa[maxn],sum;
int dep[maxn];
int f[maxn][20]; //存储祖先信息 
int g[maxn][20]; //存储最大距离 
int h[maxn][20]; //存储次大距离 
bool vis[maxn];

void addedge(int u,int v,int w){ //链式前向星存图 
	e[++cnt]=(node){v,w,head[u]};
	head[u]=cnt;
}

int find(int x){ //并查集的查找操作 
	return x==fa[x]?x:fa[x]=find(fa[x]);
}

void kruskal(){ //得到最小生成树 
	int num=0,u,v,w,x,y; 
	for(int i=1;i<=m;i++){
		u=a[i].u,v=a[i].v,w=a[i].w;
		x=find(u);y=find(v);
		if(x!=y){
			vis[i]=1; //表示这条边被选中 
			num++; 
			fa[x]=y; //合并两集合 
			sum+=w; //记录最小生成树的权值和 
			addedge(u,v,w); //构建最小生成树 
			addedge(v,u,w);
			if(num==n-1) break; //边数=点数-1跳出 
		}
	}
}

void dfs(int u,int fa,int w){ //倍增来维护每个点的信息 
	dep[u]=dep[fa]+1; //u点的深度 
	f[u][0]=fa; //u的上一级父亲 
	g[u][0]=w; //到上一级祖先的边的最大值 
	h[u][0]=-INF;//到上一级祖先的边的次大值
	for(int i=1;i<=18;i++){ 
		f[u][i]=f[f[u][i-1]][i-1];
		g[u][i]=max(g[u][i-1],g[f[u][i-1]][i-1]);
		h[u][i]=max(h[u][i-1],h[f[u][i-1]][i-1]);
		if(g[u][i-1]>g[f[u][i-1]][i-1]) h[u][i]=max(h[u][i],g[f[u][i-1]][i-1]); //替换次大值 
		else if(g[u][i-1]<g[f[u][i-1]][i-1]) h[u][i]=max(h[u][i],g[u][i-1]);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to,w=e[i].w;
		if(v==fa) continue;
		dfs(v,u,w);  //遍历下一个节点 
	}
}

int LCA(int x,int y){ //lca求公共祖先 
	if(dep[x]<dep[y]) swap(x,y); //x的深度比y大 
	for(int i=15;i>=0;i--){
		if(dep[f[x][i]]>=dep[y]) x=f[x][i];  //拉近到同一深度 
	}
	if(x==y) return x; //y是x的祖先，直接返回 
	for(int i=15;i>=0;i--){
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];//同时向上跳 
	}
	return f[x][0]; 
}

int get(int u,int v,int mx,int ans=-INF){
	for(int i=18;i>=0;i--){
		if(dep[f[u][i]]>=dep[v]){
			if(mx!=g[u][i]) ans=max(ans,g[u][i]); //比较ans和u跳2^i路径的最大值 
			else ans=max(ans,h[u][i]);//比较ans和u跳2^i路径的次大值
			u=f[u][i]; //往上跳 
		}
	}
	return ans;
} 

void output(){
	int u,v,w,lca,x,y,ans=INF;
	for(int i=1;i<=m;i++){
		if(vis[i]) continue; //如果是最小生成树上的边直接跳过 
		u=a[i].u,v=a[i].v,w=a[i].w,
		lca=LCA(u,v); //找到这两点的LCA 
		x=get(u,lca,w); //获取u到lca的最大边权 
		y=get(v,lca,w);
		ans=min(ans,sum-max(x,y)+w); //最小生成树权值和-所选最大边+新边 
	}
	for(int i=1;i<=m;i++){
		if(vis[i]) continue;
		u=a[i].u,v=a[i].v,w=a[i].w,lca=LCA(u,v);
		x=get(u,lca,w);
		y=get(v,lca,w);
		ans=min(ans,sum-max(x,y)+w);
	}
	printf("%lld",ans);
}

signed main(){
	read(n);read(m);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++){
		read(a[i].u);read(a[i].v);read(a[i].w);
	}
	sort(a+1,a+1+m); //对边排序 
	kruskal(); //最小生成树 
	dfs(1,0,0); //以1为根遍历这棵树 
	output();
	return 0;
}
 