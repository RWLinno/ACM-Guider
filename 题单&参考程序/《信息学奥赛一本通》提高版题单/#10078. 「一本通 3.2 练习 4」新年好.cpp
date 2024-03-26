//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x7f7f7f7f
#define int long long
#define pii pair<int,int>
#define mk make_pair 
#define fi first
#define se second
using namespace std;
const int N=1e5+7;
int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,m,ans=inf;
int dis[10][N];
vector<int>vt;
priority_queue<pii>q;
map<int,int>mp;

struct E{
	int v,w,nxt;
}e[N<<2];
int head[N],cnt=0;

inline void addedge(int u,int v,int w){
	e[++cnt]=(E){v,w,head[u]};head[u]=cnt; 
}

inline void dij(int start,int s){
	for(int i=1;i<=n;i++) dis[s][i]=inf;
	dis[s][start]=0;
	q.push(mk(0,start));
	while(!q.empty()){
		pii fro=q.top();
		q.pop();
		if(dis[s][fro.se]<(-fro.fi)) continue;
		for(int i=head[fro.se];i;i=e[i].nxt){
			int to=e[i].v;
			if(dis[s][to]>dis[s][fro.se]+e[i].w){
				dis[s][to]=dis[s][fro.se]+e[i].w;
				q.push(mk(-dis[s][to],to));
			}
		} 
	}
	return;
}

void Solve(){
	n=read(),m=read();
	for(int i=0,x;i<5;i++){
		x=read(); 
		vt.emplace_back(x);
		mp[x]=i+2;
	} 
	for(int i=1,u,v,w;i<=m;i++){
		u=read();v=read();w=read();
		addedge(u,v,w);
		addedge(v,u,w);
	}
	dij(1,1);
	for(int i=0;i<5;i++) dij(vt[i],i+2);
	sort(vt.begin(),vt.end());
	do{
		int res=0;
		res+=dis[1][vt[0]];
		if(res>ans) continue;
		res+=dis[mp[vt[0]]][vt[1]];
		if(res>ans) continue;
		res+=dis[mp[vt[1]]][vt[2]];
		if(res>ans) continue;
		res+=dis[mp[vt[2]]][vt[3]];
		if(res>ans) continue;
		res+=dis[mp[vt[3]]][vt[4]];
		ans=min(res,ans);
	}while(next_permutation(vt.begin(),vt.end()));
	cout<<ans<<"\n";
}

signed main(){
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}
