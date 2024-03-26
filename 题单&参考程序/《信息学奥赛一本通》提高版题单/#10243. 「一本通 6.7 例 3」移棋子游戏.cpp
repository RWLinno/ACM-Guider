#include<bits/stdc++.h>
using namespace std;
const int N=2007;

int n,m,k,sg[N],res=0;
vector<int>G[N];

inline int dfs(int x){ //sg函数 
	if(sg[x]!=-1) return sg[x];
	bitset<N>vis; 
	int flag=0,ma=-1;
	for(auto to:G[x]){
		flag=1;
		int w=dfs(to);
		ma=max(ma,w);
		vis[w]=1;
	} 
	if(!flag) return sg[x]=0;
	for(int i=0;i<=ma+1;++i){
		if(!vis[i]){
			sg[x]=i;
			break;
		}
	}
	return sg[x];
}
signed main(){	
	cin>>n>>m>>k;
	memset(sg,-1,sizeof(sg));
	for(int i=1,u,v;i<=m;++i){
		cin>>u>>v;
		G[u].emplace_back(v);
	}
	for(int i=1;i<=n;++i){
		if(sg[i]==-1){
			dfs(i);
		}
	}
	for(int i=1,x;i<=k;++i){
		cin>>x;
		res^=sg[x];
	}
	if(res) cout<<"win\n";
	else cout<<"lose\n"; 
	return 0;
}