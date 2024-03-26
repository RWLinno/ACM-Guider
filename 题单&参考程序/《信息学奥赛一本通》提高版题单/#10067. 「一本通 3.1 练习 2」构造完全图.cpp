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
	int u,v,w,nxt;
}e[N<<1];
int head[N],cnt=0;

inline void addedge(int u,int v,int w){
	e[++cnt]=(E){u,v,w,head[u]};head[u]=cnt;
}

bool cmp(E a,E b){return a.w<b.w;}

int n,ans=0,sz[N],fa[N];

int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}

void Solve(){
	cin>>n;
	for(int i=1,u,v,w;i<n;i++){
		cin>>u>>v>>w; 
		addedge(u,v,w);
		addedge(v,u,w);
		ans+=w;
	}
	sort(e+1,e+1+cnt,cmp);
	for(int i=1;i<=n;i++) sz[i]=1,fa[i]=i;
	for(int i=1;i<=cnt;i++){
		int u=find(e[i].u),v=find(e[i].v);
		if(u!=v){
			ans+=(sz[u]*sz[v]-1)*(e[i].w+1);
			fa[u]=v;
			sz[v]+=sz[u];
		}
	}
	cout<<ans<<"\n"; 
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}
