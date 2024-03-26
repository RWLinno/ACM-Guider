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
	int v,w,nxt;
}e[N<<2];
int head[N],cnt=0;

inline void addedge(int u,int v,int w){
	e[++cnt]=(E){v,w,head[u]};head[u]=cnt;
}

int n,m;
int sz[N],fa[N][40],w[N],dep[N];
inline void dfs(int x,int f){
	sz[x]=1;
	fa[x][0]=f;
	dep[x]=dep[f]+1;
	for(int i=1;i<=25;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=head[x];i;i=e[i].nxt){
		int to=e[i].v;
		if(to==fa[x][0]) continue;
		w[to]=w[x]+e[i].w;
		dfs(to,x);
		sz[x]+=sz[to];
	}
}

inline int lca(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=25;i>=0;i--) if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	if(u==v) return u;
	for(int i=25;i>=0;i--) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}

void Solve(){
	cin>>n>>m;
	for(int i=1,x,y,k;i<n;i++){
		cin>>x>>y>>k;
		addedge(x,y,k);
		addedge(y,x,k);
	}
	dfs(1,0);
	for(int i=1,x,y;i<=m;i++){
		cin>>x>>y;
		int lc=lca(x,y);
		cout<<w[x]+w[y]-2*w[lc]<<"\n";
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}