#include<bits/stdc++.h>
using namespace std;

int dp[55][300005];

int calc(int i,int j){
	int state=1;
	if(j) state&=dp[i][j-1];
	if(i) state&=dp[i-1][j];
	if(i&&j) state&=dp[i-1][j+1];
	if(i>=2) state&=dp[i-2][j+(j?3:2)];
	return (state^1);
}

void init(){
	for(int i=0;i<=50;++i){
		for(int j=0;j<=50500;++j){
			if(j==1) dp[i][j]=calc(i+1,0);
			else dp[i][j]=calc(i,j);
		}
	}
}

void solve(){
	int n,sum=0,cnt=0;
	cin>>n;
	for(int i=1,x;i<=n;++i){
		cin>>x;
		if(x==1) cnt++;
		else sum+=x+1;
	}
	if(sum) sum--;
	if(dp[cnt][sum]) cout<<"YES\n";
	else cout<<"NO\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	init();
	int T=1;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}