//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

vector<int>G[N];
int sz[N],fa[N][25],dep[N];
void dfs(int x){
	sz[x]=1;
	for(int i=1;i<=20;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
	for(auto to:G[x]){
		if(to==fa[x][0]) continue;
		dep[to]=dep[x]+1;
		fa[to][0]=x;
		dfs(to);
		sz[x]+=sz[to];
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
	int n,q,u,v;
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dep[1]=fa[1][0]=1;
	dfs(1);
	cin>>q;
	while(q--){
		cin>>u>>v;
		cout<<dep[u]+dep[v]-2*dep[lca(u,v)]<<"\n";
	}
	return 0;
}