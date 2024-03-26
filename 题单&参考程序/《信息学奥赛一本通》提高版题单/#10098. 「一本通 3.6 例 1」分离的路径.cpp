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
	int u,v,nxt;
}e[N<<1]; 
int head[N],cnt=0;

inline void addedge(int u,int v){
	e[++cnt]=(E){u,v,head[u]};head[u]=cnt;
}

int n,m,num=0;
vector<int>G[N];
vector<pair<int,int>>vt;
int low[N],dfn[N],deg[N],idx=0;
int vis[N],stk[N],top=0;
int bel[N],sccnum=0;

inline void tarjan(int x,int f){
	low[x]=dfn[x]=++idx;
	vis[x]=1;
	stk[++top]=x;
	for(int i=head[x];i;i=e[i].nxt){
		int to=e[i].v;
		if(to==f) continue;
		if(!dfn[to]){
			tarjan(to,x);
			low[x]=min(low[x],low[to]);
		}else if(vis[to]) low[x]=min(low[x],dfn[to]);
	}
	if(dfn[x]==low[x]){
		int y;
		while(y=stk[top--]){
			bel[y]=x;
			vis[y]=0;
			if(x==y) break;
		}
	}
}

void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) bel[i]=i;
	for(int i=1,u,v;i<=m;i++){ //这里要去一下重边 
		cin>>u>>v;
		if(u>v) swap(u,v);
		vt.push_back(make_pair(u,v)); 
	}
	sort(vt.begin(),vt.end());
	vt.erase(unique(vt.begin(),vt.end()),vt.end()); //去重 
	for(auto p:vt){
		addedge(p.first,p.second);
		addedge(p.second,p.first);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) tarjan(i,0);
	}
	for(int i=1;i<=cnt;i++){
		if(bel[e[i].u]!=bel[e[i].v]){
			deg[bel[e[i].u]]++;
			deg[bel[e[i].v]]++;
		}
	}
	for(int i=1;i<=n;i++){
		//cout<<i<<" "<<bel[i]<<" "<<deg[i]<<"\n";
		if(bel[i]==i&&deg[i]==2){
			num++;
		}
	}
	cout<<(num+1)/2<<"\n";
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