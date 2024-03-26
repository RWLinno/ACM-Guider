//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

int n,m,c[N],dp[N][2];
vector<int>G[N];

void dfs(int x,int f){
	dp[x][0]=dp[x][1]=1;
	if(c[x]==1) dp[x][0]=inf;
	else if(c[x]==0) dp[x][1]=inf;
	for(auto to:G[x]){
		if(to==f) continue;
		dfs(to,x);
		dp[x][0]+=min(dp[to][1],dp[to][0]-1);
		dp[x][1]+=min(dp[to][0],dp[to][1]-1);
	}
}

void Solve(){
	cin>>n>>m;
	memset(c,-1,sizeof c);
	for(int i=1;i<=m;++i) cin>>c[i];
	for(int i=1,u,v;i<n;++i){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u); 
	}
	dfs(m+1,0);
	cout<<min(dp[m+1][0],dp[m+1][1])<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
//	cin>>T;
//	clock_t start,finish;
//	start=clock();
	while(T--){
		Solve();
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;	return 0;
}