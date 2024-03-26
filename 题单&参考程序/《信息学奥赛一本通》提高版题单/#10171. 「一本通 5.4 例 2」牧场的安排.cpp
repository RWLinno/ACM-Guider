#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7;
const int mod=1e8;

int n,m,flag,ans=0,mp[20][20],dp[20][N];

void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=m;j>=1;j--){ 
			cin>>mp[i][j];
		}
	}
	for(int i=0;i<(1ll<<m);i++){  //枚举第一行可用状态 
		if(((i<<1)&i)||((i>>1)&i)) continue;
		int flag=0;
		for(int j=1;j<=m;j++){
			if(mp[1][j]==0&&((i>>(j-1))&1)){  //不可以在0上种草,也不可以相邻1 
				flag=1;
				break;
			}
		} 
		if(!flag) dp[1][i]=1;
	}
	for(int i=2;i<=n;i++){
		for(int j=0;j<(1ll<<m);j++){  //枚举当行状态 
			if(((j<<1)&j)||((j>>1)&j)) continue;
			flag=0;
			for(int x=1;x<=m;x++){
				if(mp[i][x]==0&&((j>>(x-1))&1)){
					flag=1;
					break;
				}
			}
			if(flag) continue;	 
			for(int k=0;k<(1ll<<m);k++){  //枚举上一行的状态 
				if(((k<<1)&k)||((k>>1)&k)) continue;
				flag=0;
				for(int x=1;x<=m;x++){
					if(mp[i-1][x]==0&&((k>>(x-1))&1)||((k>>(x-1))&1)&&((j>>(x-1))&1)){
						flag=1;
						break;
					}
				}
				if(flag) continue;
				dp[i][j]+=dp[i-1][k];
				dp[i][j]%=mod;
			}
		}
	}
	for(int i=0;i<(1ll<<m);i++){
		ans+=dp[n][i];
		ans%=mod;
	}
	cout<<ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}