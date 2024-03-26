//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
#define pii pair<int,int>
#define mk make_pair
#define fi first
#define se second
using namespace std;
const int N=1e5+7;
const int mod=100003;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,m,dis[N],vis[N],ans[N];
vector<int>G[N];

struct E{
	int v,w,nxt;	
}e[N<<2];

int head[N],cnt=0;
inline void addedge(int u,int v,int w){
	e[++cnt]=(E){v,w,head[u]};head[u]=cnt;
}

void dij(int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	priority_queue<pii>q;
	q.push(mk(0,s));
	while(q.size()){
		pii fro=q.top();
		q.pop();
		if(vis[fro.se]) continue;
		vis[fro.se]=1;
		for(auto to:G[fro.se]){
			if(dis[to]>dis[fro.se]+1){
				dis[to]=dis[fro.se]+1;
				q.push(mk(-dis[to],to));
			}
		}
	}
}

void bfs(int s){
	memset(vis,0,sizeof(vis));
	ans[1]=1;
	queue<int>q;
	q.push(1);
	while(!q.empty()){
		int fro=q.front();
		q.pop();
		if(vis[fro]) continue;
		vis[fro]=1;
		for(auto to:G[fro]){
			if(dis[to]==dis[fro]+1){
				ans[to]+=ans[fro];
				ans[to]%=mod;
				q.push(to);	
			}
		}
	} 
}

void Solve(){
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dij(1);
	bfs(1);
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<"\n";
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
