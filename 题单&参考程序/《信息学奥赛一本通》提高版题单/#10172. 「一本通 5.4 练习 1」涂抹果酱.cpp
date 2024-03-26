#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7;
const int mod=1e6;

int n,m,K,ban=0,flag=0,ans=0,dp[10005][300],hs[10000][10];

inline int get(int a,int b){
	while(b--) a/=3;
	return a%3;
}

void Solve(){
	cin>>n>>m;
	cin>>K;
	for(int i=1,x,lst=0;i<=m;i++){
		cin>>x;
		if(x==lst) flag=1;
		ban=ban*3+(x-1);
		lst=x;
	}
	if(flag){
		cout<<0<<"\n";
		return;
	}
	int M=1;
	for(int i=1;i<=m;i++) M*=3; 
	for(int i=0;i<M;i++){
		for(int j=0;j<m;j++) hs[i][j]=get(i,j);
	}
//	#define get(i,j) hs[i][j]
	for(int i=0;i<M;i++){ //获得第一行的可行方案 
		flag=0;
		for(int j=1;j<m;j++){
			if(hs[i][j]==hs[i][j-1]){ //不能有相邻格子一样 
				flag=1;
				break;
			}
		}
		if(!flag) dp[1][i]=1;
	}
	if(K==1){
		for(int j=0;j<M;j++) dp[1][j]=0;
		dp[1][ban]=1; //只能是这个颜色 
	}
	for(int i=2;i<=n;i++){
		for(int j=0;j<M;j++){  //枚举上一行状态 
			flag=0;
			for(int x=1;x<m;x++){
				if(hs[j][x]==hs[j][x-1]){
					flag=1;
					break;
				}
			}
			if(flag) continue;
			for(int k=0;k<M;k++){ //枚举当前行状态 
				flag=0;
				if(hs[k][0]==hs[j][0]) flag=1;
				else for(int x=1;x<m;x++){
					if(hs[k][x]==hs[k][x-1]||hs[j][x]==hs[k][x]){
						flag=1;
						break;
					}
				}
				if(flag) continue;
				dp[i][k]+=dp[i-1][j];
				dp[i][k]%=mod;	
			}
		}
		if(i==K) for(int j=0;j<M;j++){ 
			if(j!=ban) dp[i][j]=0;
			else if(dp[i][j]==0){
				ans=0;
				break;
			}	
		}
	}
	for(int i=0;i<M;i++){
		ans+=dp[n][i];
		ans%=mod;
	}
	cout<<ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}