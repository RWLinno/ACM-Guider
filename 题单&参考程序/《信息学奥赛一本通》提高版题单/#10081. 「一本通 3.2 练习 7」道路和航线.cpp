//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define int long long
#define pii pair<int,int>
#define mk make_pair
#define fi first
#define se second
using namespace std;
const int N=1e5+7;
const int mod=1e9+7;

int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct E{
	int v,w,nxt;
}e[N<<2];
int cnt=0,head[N];
inline void addedge(int u,int v,int w){
	e[++cnt]=(E){v,w,head[u]};head[u]=cnt;
}

int n,r,p,s,dis[N],vis[N];

inline void dij(int s){
	memset(dis,inf,sizeof(dis));
	dis[s]=0;vis[s]=1;
	priority_queue<int>q;
	q.push(s);
	while(q.size()){
		int fro=q.top();
		q.pop();
		vis[fro]=0;
		for(int i=head[fro];i;i=e[i].nxt){
			int to=e[i].v;
			if(dis[to]>dis[fro]+e[i].w){
				dis[to]=dis[fro]+e[i].w;
				if(!vis[to]){
					vis[to]=1;
					q.push(to);
				}
			}
		}
	}	
}

void Solve(){
	n=read();r=read();p=read();s=read();
	for(int i=1,u,v,w;i<=r;i++){
		u=read();v=read();w=read(); 
		addedge(u,v,w);
		addedge(v,u,w);
	}
	for(int i=1,u,v,w;i<=p;i++){
		u=read();v=read();w=read(); 
		addedge(u,v,w);
	}
	dij(s);
	for(int i=1;i<=n;i++){
		if(dis[i]>=inf) printf("NO PATH\n");//cout<<"NO PATH\n";
		else printf("%d\n",dis[i]); //cout<<dis[i]<<"\n";
	}
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}
