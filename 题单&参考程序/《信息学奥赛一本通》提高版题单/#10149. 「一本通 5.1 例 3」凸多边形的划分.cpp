#include<bits/stdc++.h>
#define int __int128
using namespace std;

int n,dp[55][55],a[55]; 

inline int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x; 
}

inline void write(int x){
	if(x>9) write(x/10);putchar(x%10+'0');
}

signed main(){
	n=read();
	for(int i=1;i<=n;++i) a[i]=read();
	for(int len=2;len<n;++len){
		for(int i=1;i+len<=n;++i){
			int j=i+len;
			dp[i][j]=1e30;
			int tmp=1ll*a[i]*a[j];
			for(int k=i+1;k<j;++k){
				dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]+1ll*a[k]*tmp);
			}
		}
	}
	write(dp[1][n]);putchar('\n');
	return 0;
}