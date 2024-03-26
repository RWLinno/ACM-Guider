//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,rt,dp[N][2];
vector<int>G[N];

void dfs(int x,int f){
	dp[x][0]=0;dp[x][1]=1;
	for(auto to:G[x]){
		if(to==f) continue;
		dfs(to,x);
		dp[x][1]+=min(dp[to][0],dp[to][1]);
		dp[x][0]+=dp[to][1]; //x为不放的最少 
	}
//	cout<<x<<" "<<dp[x][0]<<" "<<dp[x][1]<<"\n";
}

void Solve(){
	cin>>n;
	for(int i=1,x,k;i<=n;i++){
		cin>>x>>k;
		x++;
		for(int j=1,y;j<=k;j++){
			cin>>y;
			y++;
			G[x].push_back(y);
			G[y].push_back(rt=x);
		}
	}
	dfs(rt,0);
	cout<<min(dp[rt][0],dp[rt][1])<<"\n";
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}