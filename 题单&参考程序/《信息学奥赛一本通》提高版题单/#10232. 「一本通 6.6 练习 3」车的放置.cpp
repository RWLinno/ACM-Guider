#include<bits/stdc++.h>
using namespace std;
const int N=2e3+7,mod=1e5+3;

int a,b,c,d,k,v[N],dp[N][N];

signed main(){
	scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
	for(int i=1;i<=c;++i) v[i]=d,dp[i][0]=1;
	for(int i=1;i<=a;++i) v[i+c]=d+b,dp[c+i][0]=1;
	dp[0][0]=1;
	for(int j=1;j<=a+c;++j){
		for(int i=1;i<=k;++i){
			dp[j][i]=(dp[j-1][i]+dp[j-1][i-1]*(v[j]-i+1))%mod;
		} 
	}
	printf("%d\n",dp[a+c][k]);
	return 0;
} 