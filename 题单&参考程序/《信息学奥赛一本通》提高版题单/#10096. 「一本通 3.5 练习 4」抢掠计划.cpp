#include<bits/stdc++.h>
using namespace std;
const int N=5e5+7;
const int mod=1e9+7;

int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct E{
	int u,v,nxt;
}e[N<<1];
int head[N],cnt=0;

inline void addedge(int u,int v){
	e[++cnt]=(E){u,v,head[u]};
    head[u]=cnt;
}

int n,m,s,p,val[N],is[N],ans=0;
int dfn[N],low[N],idx=0;
int vis[N],stk[N],bel[N],top=0;
vector<int>G[N];

inline void tarjan(int x){
	dfn[x]=low[x]=++idx;
	vis[x]=1;
	stk[++top]=x;
	for(int i=head[x];i;i=e[i].nxt){
		int to=e[i].v;
		if(!dfn[to]){
			tarjan(to);
			low[x]=min(low[x],low[to]);
		}else if(vis[to]) low[x]=min(low[x],low[to]);
	}
	if(dfn[x]==low[x]){
		int y;
		while(y=stk[top--]){
			vis[y]=0;
			bel[y]=x;
			if(x==y) break;
			val[x]+=val[y];
		}
	}
}

void dfs(int x,int num){
	if(is[x]) ans=max(ans,num);
	vis[x]=num;
	for(auto to:G[x]){
		if(vis[to]<num+val[to]) dfs(to,num+val[to]);
	}
}

void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) bel[i]=i;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		addedge(u,v);
	}
	for(int i=1;i<=n;i++) cin>>val[i];
	cin>>s>>p;
	for(int i=1;i<=n;i++){
		if(!dfn[i]) tarjan(i);
	}
	for(int i=1,x;i<=p;i++){
		cin>>x;
		is[bel[x]]=1; //标记酒吧 
	}
	for(int i=1;i<=cnt;i++){  //rebuild
		int u=bel[e[i].u],v=bel[e[i].v];
		if(u!=v) G[u].push_back(v);
	}
	memset(vis,0,sizeof(vis));
	dfs(bel[s],val[bel[s]]);
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