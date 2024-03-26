//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
#define mk make_pair
#define pii pair<int,int>
using namespace std;
const int N=2e5+7;

int n,m,u,v,s,z,len,flag=-1;
int deg[N],vis[N],ans[N];
vector<pii>G[N];

inline void dfs(int x){
	for(auto pi:G[x]){
		int to=pi.first,e=pi.second;
		if(vis[e]) continue;
		vis[e]=1;
		dfs(to);
		ans[++len]=e;
	}
}

void clr(){
	for(int i=1;i<=n;i++) G[i].clear();
	flag=-1;len=0;n=0;m=0;
	memset(vis,0,sizeof(vis));
	memset(deg,0,sizeof(deg));
}

void Solve(){
	for(int i=1;i<=n;i++){
		if(deg[i]&1) flag=1;
	}
	if(flag) cout<<"Round trip does not exist.\n";
	else{
		dfs(s);
		if(m!=len) cout<<"Round trip does not exist.\n";
		else{
			for(int i=len;i>=2;i--){
				cout<<ans[i]<<" ";
			}
			cout<<ans[1]<<"\n";
		}
	} 
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	while(cin>>u>>v){ 
		if(!u&&!v){
			if(!n) break;
			Solve();
			clr();
			continue;
		}
		cin>>z;
		n=max(n,u);
		n=max(n,v);
		if(flag==-1){
			s=u<v?u:v;
			flag=0;
		}
		G[u].push_back(mk(v,z));
		G[v].push_back(mk(u,z));
		deg[u]++;deg[v]++;m++;
	}
	return 0;
}