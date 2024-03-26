//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=107,M=1e5;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct E{
	int f,v,nxt;
}e[M];
int head[N],cnt=0;

inline void addedge(int f,int v){
	e[++cnt]=(E){f,v,head[f]};head[f]=cnt;
}

int dfn[N],low[N],idx=0;
int vis[N],top=0,stk[N],bel[N],sccnum=0;
inline void tarjan(int x){
	dfn[x]=low[x]=++idx;
	vis[x]=1;
	stk[++top]=x;
	for(int i=head[x];i;i=e[i].nxt){
		int to=e[i].v;
		if(!dfn[to]){
			tarjan(to);
			low[x]=min(low[x],low[to]);
		}else if(vis[to]) low[x]=min(low[x],dfn[to]);
	}
	if(dfn[x]==low[x]){
		int y;sccnum++;
		while(y=stk[top--]){
			bel[y]=sccnum;
			vis[y]=0;
			if(x==y) break;
		}
	}
}

int ct[N],mp[N][N],ru[N],chu[N];

void dfs(int x){
	ct[x]=1;
	for(int i=1;i<=sccnum;i++){
		if(!ct[i]&&mp[x][i]) dfs(i);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int n,to,ans1=0,ans2=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>to;
		while(to) addedge(i,to),cin>>to;
	}
	int p=0; 
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i); //缩点
	for(int i=1;i<=cnt;i++){ //重建图 
		int u=bel[e[i].f],v=bel[e[i].v];
		if(u!=v){ 
			mp[u][v]=1;
			ru[v]++;chu[u]++;
			p++; //记录边数 
		}
	}
	for(int i=1;i<=sccnum;i++) if(!ru[i]) ans1++; //起点个数
	for(int i=1;i<=sccnum;i++) if(!chu[i]) ans2++; //终点个数，实际上把每个终点连回起点即可 
	cout<<ans1<<"\n";
	if(!p&&sccnum==1) cout<<"0\n"; //只有一个点的情况 
	else cout<<max(ans1,ans2)<<"\n"; 
	return 0;
}
