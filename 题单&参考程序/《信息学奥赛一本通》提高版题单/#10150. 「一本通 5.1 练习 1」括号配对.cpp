#include<bits/stdc++.h>
using namespace std;
int dp[105][105];
char s[105];

signed main(){
	scanf("%s",s+1); 
	int n=strlen(s+1);
	for(int i=1;i<=n;++i) dp[i][i]=1;
	for(int len=2;len<=n;++len){
		for(int i=1;i+len-1<=n;++i){
			int j=i+len-1;
			if(s[i]=='('&&s[j]==')'||s[i]=='['&&s[j]==']') dp[i][j]=dp[i+1][j-1];
			else dp[i][j]=dp[i][j-1]+1;
			for(int k=i;k<j;++k) dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
		}
	}
	printf("%d",dp[1][n]);
	return 0;
}