#include<bits/stdc++.h>
using namespace std;
 
struct X{
	int to,dis;
	X(int xx=0,int yy=0){
		to=xx,dis=yy;
	}
}; 

vector<X>G[105];
int n,q,u,v,w,dp[105][105]={0},vis[105]={0};

void dfs(int x){
	vis[x]=1;
	for(int i=0;i<G[x].size();i++){
		int to=G[x][i].to,w=G[x][i].dis;
		if(vis[to]) continue;
		dfs(to);
		for(int j=q;j>=1;j--){ //当前可以选的树枝根数 
			for(int g=j-1;g>=0;g--){ //逆序枚举留给子节点的树枝根数 
				dp[x][j]=max(dp[x][j],dp[to][g]+dp[x][j-g-1]+w); //一个子树留g,另一个子树留j-g-1,然后加上当前连边 
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); 
	cin>>n>>q;
	memset(dp,0,sizeof(dp));
	for(int i=1;i<n;i++){
		cin>>u>>v>>w;
		G[u].push_back(X(v,w));
	}
	dfs(1);
	cout<<dp[1][q]<<endl;
	return 0;
}