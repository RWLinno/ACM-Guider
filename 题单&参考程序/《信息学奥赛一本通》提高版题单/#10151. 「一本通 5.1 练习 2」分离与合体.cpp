#include<bits/stdc++.h>
using namespace std;
const int N=305;
int n,a[N],dp[N][N],pre[N][N],vis[N][N];

void print(int i,int j,int dep){
	if(i==j||dep==0) return;
	if(!vis[i][j]){
		cout<<pre[i][j]<<" ";
		vis[i][j]=1;
	}
	print(i,pre[i][j],dep-1);
	print(pre[i][j]+1,j,dep-1);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int len=2;len<=n;++len){
		for(int i=1;i+len-1<=n;++i){
			int j=i+len-1;
			for(int k=i;k<j;++k){
				if(dp[i][j]<dp[i][k]+dp[k+1][j]+(a[i]+a[j])*a[k]){
					dp[i][j]=dp[i][k]+dp[k+1][j]+(a[i]+a[j])*a[k];		
					pre[i][j]=k;
				}
			}
		}
	}
	cout<<dp[1][n]<<"\n";
	for(int i=1;i<=n;++i) print(1,n,i);
	return 0;
} 