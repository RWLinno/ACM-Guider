//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
#define mk make_pair
#define pii pair<int,int>

using namespace std;
const int N=2e5+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,m,mod,deg[N],len[N],ans[N];
vector<int>G[N];
queue<int>q;
map<pii,bool>mp;

struct E{
	int u,v,nxt;
}e[N<<3];
int head[N],cnt=0;
inline void addedge(int u,int v){
	e[++cnt]=(E){u,v,head[u]};head[u]=cnt;
}

int dfn[N],low[N],idx=0;
int stk[N],top=0,vis[N],bel[N],sz[N];
inline void tarjan(int x){
	dfn[x]=low[x]=++idx;
	stk[++top]=x;
	vis[x]=1;
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
			sz[x]+=sz[y];
		}
	}
}

void Solve(){
	cin>>n>>m>>mod;
	for(int i=1;i<=n;i++) sz[i]=1,bel[i]=i;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		addedge(u,v);
	} 
	for(int i=1;i<=n;i++){  //缩点 
		if(!dfn[i]) tarjan(i);
	}
	for(int i=1;i<=cnt;i++){
		int u=bel[e[i].u],v=bel[e[i].v];
		if(u!=v&&!mp[mk(u,v)]){
			mp[mk(u,v)]=1;
			G[u].push_back(v);
			deg[v]++;
		}
	}
	for(int i=1;i<=n;i++){
		if(!deg[i]&&bel[i]==i){
			q.push(i);
			len[i]=sz[i]; //到达i点的最长链长度和方案数 
			ans[i]=1;
		}
	}
	int mx=0,res=0;
	while(!q.empty()){
		int fro=q.front();
		q.pop();
		for(auto to:G[fro]){ //对每个儿子记录最长链长度和方案数 
			if(sz[to]+len[fro]==len[to]){
				ans[to]+=ans[fro];
				ans[to]%=mod;
			}else if(sz[to]+len[fro]>len[to]){
				len[to]=sz[to]+len[fro];
				ans[to]=ans[fro];
			}
			deg[to]--;
			if(!deg[to]) q.push(to);
		}
	//	cout<<fro<<" "<<len[fro]<<" "<<ans[fro]<<" !!\n";
		if(len[fro]>mx){
			mx=len[fro];
			res=ans[fro];
		}else if(len[fro]==mx){
			res+=ans[fro];
			res%=mod;
		}
	}
	cout<<mx<<"\n";
	cout<<res<<"\n";
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
