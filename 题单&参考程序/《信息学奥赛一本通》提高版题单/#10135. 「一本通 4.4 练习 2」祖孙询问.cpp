//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x7f7f7f7f
#define int long long
using namespace std;
const int N=1e5+7;
const int mod=1e9+7;

int n,m,root;
int dep[N],sz[N],fa[N][30];
vector<int>G[N];

inline void dfs(int x,int f){
	dep[x]=dep[f]+1;
	sz[x]=1;
	fa[x][0]=f;
	for(int i=1;i<=25;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
	for(auto to:G[x]){
		if(to==fa[x][0]) continue;
		dfs(to,x);
		sz[x]+=sz[to];
	}
}

inline int lca(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=25;i>=0;i--) if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	if(u==v) return v;
	for(int i=25;i>=0;i--) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}

void Solve(){
	cin>>n;
	for(int i=1,u,v;i<=n;i++){
		cin>>u>>v;
		if(v==-1){
			root=u;
		}else{
			G[u].push_back(v);
			G[v].push_back(u);
		}
	}
	dfs(root,0);
	cin>>m;
	for(int i=1,x,y;i<=m;i++){
		cin>>x>>y;
		int g=lca(x,y);
		if(x==g) cout<<1<<"\n";
		else if(y==g) cout<<2<<"\n";
		else cout<<0<<"\n";
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