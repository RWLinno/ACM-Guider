//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct E{
	int v,nxt;
}e[N<<1];

int head[N],cnt=0;

inline void addedge(int u,int v){
	e[++cnt]=(E){v,head[u]};head[u]=cnt;
}

int sz[N],dep[N],fa[N][25],d[N];
void dfs(int x){
	sz[x]=1;
	for(int i=1;i<=20;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=head[x];i;i=e[i].nxt){
		int to=e[i].v;
		if(to==fa[x][0]) continue;
		fa[to][0]=x;
		dep[to]=dep[x]+1;
		dfs(to);
	}
} 

void getd(int x){
	for(int i=head[x];i;i=e[i].nxt){
		int to=e[i].v;
		if(to==fa[x][0]) continue;
		getd(to);
		d[x]+=d[to];
	}
}

inline int lca(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=20;i>=0;i--) if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	if(u==v) return v;
	for(int i=20;i>=0;i--) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int n,m,u,v,ans=0;
	cin>>n>>m;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		addedge(u,v);
		addedge(v,u);
	}
	fa[1][0]=dep[1]=1;
	dfs(1);
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		d[u]++;d[v]++; //树上差分
		d[lca(u,v)]-=2;
	}
	getd(1);
	for(int i=2;i<=n;i++){ 
		if(d[i]==0) ans+=m; //不经过环
		if(d[i]==1) ans+=1; //删除构成环的附加边 
	}
	cout<<ans<<"\n";
	return 0;
}