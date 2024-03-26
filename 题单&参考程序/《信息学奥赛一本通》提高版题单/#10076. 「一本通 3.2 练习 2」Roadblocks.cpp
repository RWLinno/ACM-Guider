//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define pii pair<int,int>
#define mk make_pair
#define fi first
#define se second
using namespace std;
const int N=5005,M=2e5+7;
const int mod=1e9+7;

int ds[N],dd[N]; //记录每个点的最短路和次短路 
map<int,int>vis[N];

struct E{
	int v,w,nxt;
}e[M];

int head[N],cnt=0;
inline void addedge(int u,int v,int w){
	e[++cnt]=(E){v,w,head[u]};head[u]=cnt;
}

void dij(int s){
	memset(ds,0x3f,sizeof(ds));
	memset(dd,0x3f,sizeof(dd));
	ds[s]=0;
	priority_queue<pii>q;
	q.push(mk(0,s));
	while(!q.empty()){
		pii fro=q.top();
		q.pop();
		if(-fro.fi>dd[fro.se]||vis[fro.se][-fro.fi]) continue; //大于第二短路不考虑 
		vis[fro.se][-fro.fi]=1;
		for(int i=head[fro.se];i;i=e[i].nxt){
			int to=e[i].v,d=e[i].w-fro.fi;
			if(ds[to]>d){ 
				swap(ds[to],d);
				q.push(mk(-ds[to],to));
			}
			if(dd[to]>d&&d>ds[to]){
				dd[to]=d;
				q.push(mk(-dd[to],to));
			}
		}
	}
}

void Solve(){
	int n,m,x,mx=0;
	cin>>n>>m;
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		addedge(u,v,w);
		addedge(v,u,w);
	}
	dij(1);
	cout<<dd[n]<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	while(T--){
		Solve();
	}
	return 0;
}
