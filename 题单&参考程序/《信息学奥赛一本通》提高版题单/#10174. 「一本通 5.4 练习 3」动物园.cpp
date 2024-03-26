#include<bits/stdc++.h>
using namespace std;
const int N=10007,M=50;

int n,c,e,f,l;
int dp[N][M],num[N][M],ans;

signed main(){
	cin>>n>>c;
	for(int i=1;i<=c;i++){
		int num1=0,num2=0; 
		cin>>e>>f>>l;
		for(int j=0,x;j<f;j++){ //害怕的动物集合 
			cin>>x;
			x=(x-e+n)%n;
			num1=num1|(1<<x);
		}
		for(int j=0,x;j<l;j++){ //喜欢的动物集合 
			cin>>x;
			x=(x-e+n)%n;
			num2=num2|(1<<x);
		}
		for(int j=0;j<32;j++){ //该小朋友对连续的五个栅栏的每个状态是否高兴 
			if((num1&j)||(num2&(~j))) num[e][j]++;	
		}
	}
	for(int k=0;k<32;k++){ //枚举五个连续栅栏的状态 
		memset(dp[0],-0x3f,sizeof(dp[0]));
		dp[0][k]=0;
		for(int i=1;i<=n;i++){ //枚举栅栏数量 
			for(int j=0;j<32;j++){  //状态转移 
				dp[i][j]=num[i][j]+max(dp[i-1][(j&15)<<1],dp[i-1][((j&15))<<1|1]);
			}
		}
		ans=max(ans,dp[n][k]);
	}
	cout<<ans<<"\n";
	return 0;
} 