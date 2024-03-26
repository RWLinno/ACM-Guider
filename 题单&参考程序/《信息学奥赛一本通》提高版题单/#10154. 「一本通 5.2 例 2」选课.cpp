//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=107;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,m;
int sz[N],fa[N],dep[N],val[N];
int dp[N][N],F[N][N];
vector<int>G[N];
void dfs(int x,int f){
	sz[x]=1;fa[x]=f;
	dp[x][1]=val[x];
	for(auto to:G[x]){
		if(to==f) continue;
		dep[to]=dep[x]+1;
		dfs(to,x);
		for(int j=1;j<=m;j++) F[x][j]=dp[x][j];
		for(int j=1;j<=m;j++){ 
			for(int k=0;k<j;k++){
				dp[x][j]=max(dp[x][j],F[x][j-k]+dp[to][k]);
			}
		}
	}
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	cin>>n>>m;m++;
	for(int i=1,f;i<=n;i++){
		cin>>f>>val[i];
		G[f].push_back(i);
		G[i].push_back(f);		
	}
	dfs(0,-1);
	cout<<dp[0][m]<<"\n";
	return 0;
}