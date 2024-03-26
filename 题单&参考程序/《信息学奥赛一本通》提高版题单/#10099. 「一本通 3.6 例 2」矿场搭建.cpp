//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,root,sz,num,op,ans1,ans2,is[N];
vector<int>G[N];
int dfn[N],low[N],idx=0,vis[N];

void tarjan(int x,int f){
	dfn[x]=low[x]=++idx;
	int col=0; 
	for(auto to:G[x]){
		if(to==f) continue;
		if(!dfn[to]){
			col++; //子树大小 
			tarjan(to,x);
			low[x]=min(low[to],low[x]);
			if(x==root&&col>1||x!=root&&low[to]>=dfn[x]){
				is[x]=1; //标记割点 
			} 
		}else if(to!=f) low[x]=min(dfn[to],low[x]);
	}
}

void dfs(int x,int id){
	vis[x]=id;
	sz++;
	for(auto to:G[x]){
		if(is[to]&&vis[to]!=id){
			num++;
			vis[to]=id;
		}
		if(!vis[to]){
			dfs(to,id);
		}
	}
}

void Solve(int m){
	n=0; //这是点数 
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
		n=max(n,u);
		n=max(n,v);
	}
	for(int i=1;i<=n;i++){  //求割点 
		if(!dfn[i]){
			root=i;
			tarjan(i,0);
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]&&!is[i]){  //遍历联通块 
			num=0;sz=0;  //联通块中割点数目和总点数 
			dfs(i,++op); 
			if(!num){  //无割点 
				ans1+=2; //需要两个，因为选的那个可能塌了
				ans2*=sz*(sz-1)/2; 
			}else if(num==1){  //有一个割点，割点连接的每个区域发 
				ans1+=1;
				ans2*=sz; 
			}
		}
	} 
	for(int i=1;i<=n;i++) G[i].clear();
	memset(dfn,0,sizeof(dfn));
	memset(vis,0,sizeof(vis));
	memset(is,0,sizeof(is));
	idx=0;op=0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1,id=1;
	cin>>T;
	while(T){
		ans1=0,ans2=1;
		Solve(T);
		cout<<"Case "<<id<<": "<<ans1<<" "<<ans2<<"\n";
		id++;
		cin>>T;
	}
	return 0;
}