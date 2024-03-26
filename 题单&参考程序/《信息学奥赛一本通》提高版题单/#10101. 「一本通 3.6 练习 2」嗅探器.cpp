#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=1007;
const int mod=1e9+7;

int n,A,B,ans=inf;
vector<int>G[N];
int dfn[N],low[N],idx=0;
int vis[N],is[N]; 

inline void tarjan(int x,int f){
	dfn[x]=low[x]=++idx;
	int col=0;
	for(auto to:G[x]){
		if(!dfn[to]){
			tarjan(to,x);
			low[x]=min(low[x],low[to]);
			if(low[to]>=dfn[x]){
				col++;
				if((x!=A||col>1)&&dfn[B]>=dfn[to]) is[x]=1;
			}
		}else low[x]=min(low[x],dfn[to]);
	}
}

int u,v,a,b;

void Solve(){
	cin>>n;
	cin>>u>>v;
	while(u||v){
		G[u].push_back(v);
		G[v].push_back(u);
		cin>>u>>v;
	}
	cin>>A>>B;
	tarjan(A,0);
	for(int i=1;i<=n;i++){
		if(is[i]){
			cout<<i<<"\n";
			return;
		}
	}
	cout<<"No solution\n";
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