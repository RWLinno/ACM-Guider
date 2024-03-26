//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x7f7f7f7f
#define int long long
using namespace std;
const int N=5e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,m;
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
	cin>>n>>m;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	for(int i=1,x,y,z,a,b,c,ans;i<=m;i++){
		cin>>x>>y>>z;
		a=lca(x,y),b=lca(x,z),c=lca(y,z);
		if(dep[a]>=dep[b]&&dep[a]>=dep[c]) ans=a;
		else if(dep[b]>=dep[a]&&dep[b]>=dep[c]) ans=b;
		else if(dep[c]>=dep[b]&&dep[c]>=dep[a]) ans=c;
		int res=dep[x]+dep[y]+dep[z]+3*dep[ans];
		res-=2*dep[lca(x,ans)];
		res-=2*dep[lca(y,ans)];
		res-=2*dep[lca(z,ans)];
		cout<<ans<<" "<<res<<"\n";
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