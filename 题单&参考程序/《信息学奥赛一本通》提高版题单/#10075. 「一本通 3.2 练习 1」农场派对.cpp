//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define pii pair<int,int>
#define mk make_pair
#define fi first
#define se second
//#define int long long
using namespace std;
const int N=1007;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int dis[N][N],vis[N][N];

struct E{
	int v,w,nxt;
}e[N];
int head[N],cnt=0;
inline void addedge(int u,int v,int w){
	e[++cnt]=(E){v,w,head[u]};head[u]=cnt;
}

void dij(int x){
	dis[x][x]=0;
	priority_queue<pii>q;
	q.push(mk(0,x));
	while(!q.empty()){
		pii fro=q.top();
		q.pop();
		vis[x][fro.se]=0;
		for(int i=head[fro.se];i;i=e[i].nxt){
			int to=e[i].v;
			if(dis[x][to]>dis[x][fro.se]+e[i].w){
				dis[x][to]=dis[x][fro.se]+e[i].w;
				if(!vis[x][to]){
					vis[x][to]=1;
					q.push(mk(-dis[x][to],to));
				}
			}
		}
	}
}

void Solve(){
	int n,m,x,mx=0;
	cin>>n>>m>>x;
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		addedge(u,v,w);
	}
	memset(dis,inf,sizeof(dis));
	dij(x);
	for(int i=1;i<=n;i++){
		dij(i);
		if(dis[i][x]<inf&&dis[x][i]<inf&&dis[i][x]+dis[x][i]>mx) mx=dis[i][x]+dis[x][i];
	}
	cout<<mx<<"\n";
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
