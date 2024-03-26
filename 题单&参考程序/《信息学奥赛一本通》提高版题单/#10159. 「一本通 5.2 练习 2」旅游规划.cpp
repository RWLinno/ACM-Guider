#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7;

int n,rt=0,ans=1,dep[N],mx[N],is[N]; 
vector<int>G[N];

void dfs1(int x,int f){
	for(auto to:G[x]){
		if(to==f) continue;
		dep[to]=dep[x]+1;
		if(dep[to]>dep[rt]) rt=to;
		dfs1(to,x);
	}
}

void dfs2(int x,int f){
	mx[x]=dep[x];
	for(auto to:G[x]){
		if(to==f) continue;
		dep[to]=dep[x]+1;
		dfs2(to,x);
		mx[x]=max(mx[to],mx[x]); 
	}
	ans=max(ans,mx[x]);
}

void Solve(){
	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	} 
	dep[0]=1;
	dfs1(0,-1); //获得最远的点
	dep[rt]=1;
	dfs2(rt,-1);
	for(int i=0;i<n;i++){
		if(mx[i]==ans) is[i]=1;
	}
	memset(mx,0,sizeof(mx));
	dfs1(rt,-1);
	dep[rt]=1;
	dfs2(rt,-1); //从最远的点开始计算 
	for(int i=0;i<n;i++){
		if(mx[i]==ans) is[i]=1;
	}
	for(int i=0;i<n;i++){
		if(is[i]) cout<<i<<"\n";
	}
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