#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;

int n,rt=1,dp[N][3],val[N],vis[N];
vector<int>G[N];

void dfs(int x,int f){
	dp[x][0]=dp[x][1]=0; //不放，无/有儿子看 
	dp[x][2]=val[x]; //放
	int mi=0,d=inf;
	for(auto to:G[x]){
		if(to==f) continue;
		dfs(to,x);
		if(!mi) mi=to;
		dp[x][0]+=min(dp[to][2],dp[to][1]);
		dp[x][1]+=min(dp[to][2],dp[to][1]);
		d=min(d,dp[to][2]-min(dp[to][2],dp[to][1]));
		dp[x][2]+=min(dp[to][0],min(dp[to][1],dp[to][2])); //这里放,不用管儿子状态 
	}
	dp[x][1]+=d;
	//cout<<x<<" "<<dp[x][0]<<" "<<dp[x][1]<<" "<<dp[x][2]<<"\n";
}

void Solve(){
	cin>>n;
	for(int i=1,x,k;i<=n;i++){
		cin>>x;
		cin>>val[x]>>k;
		for(int j=1,y;j<=k;j++){
			cin>>y;
			G[x].push_back(y);
			G[y].push_back(x);
			vis[y]=1;
		}
	}
	while(vis[rt]) rt++;
	dfs(rt,0);
	cout<<min(dp[rt][1],dp[rt][2])<<"\n";
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