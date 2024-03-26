//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x7f7f7f7f
#define int long long
using namespace std;
const int N=2e6+7;

int n,st,vis[N],nxt[N],val[N];
int ans,tmp,dp[N][2];
vector<int>G[N];

int find_loop(int x){
	vis[x]=1;
	if(vis[nxt[x]]) return nxt[x];
	return find_loop(nxt[x]);
}

void dfs(int x){
	vis[x]=1;
	dp[x][0]=0;
	dp[x][1]=val[x];
	for(auto to:G[x]){
		if(to==st){
			dp[to][1]=-inf;
			continue;
		}
		dfs(to);
		dp[x][0]+=max(dp[to][0],dp[to][1]);
		dp[x][1]+=dp[to][0];
	}
}

void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>val[i]>>nxt[i];
		G[nxt[i]].push_back(i);
	} 
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		st=find_loop(i);
		dfs(st);vis[st]=1;
		tmp=max(dp[st][0],dp[st][1]);
		st=nxt[st];
		dfs(st);
		ans+=max(tmp,max(dp[st][0],dp[st][1]));
	}
	cout<<ans<<"\n";
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