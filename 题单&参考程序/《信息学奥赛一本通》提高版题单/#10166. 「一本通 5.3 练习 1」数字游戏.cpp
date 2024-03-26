#include<bits/stdc++.h>
using namespace std;
const int N=11,M=110;

int dp[N][10][M],L,R,P,num[N];

int mod(int x,int y){
	return (x%y+y)%y;
}

void init(){  //预处理dp[i][j][k]表示i位数最高位为j，取模为k的方案数 
	memset(dp,0,sizeof(dp));
	for(int i=0;i<=9;i++) dp[1][i][i%P]=1;
	for(int i=2;i<N;i++){
		for(int j=0;j<=9;j++){
			for(int k=0;k<P;k++){
				for(int x=0;x<=9;x++){
					dp[i][j][k]+=dp[i-1][x][mod(k-j,P)]; 
				}
			}
		}
	}
}

int solve(int n){
	int len=0,res=0,lst=0;
	if(!n) return 1;
	while(n){
		num[++len]=n%10;
		n/=10;
	}
	for(int i=len;i>=1;i--){
		for(int j=0;j<num[i];j++) res+=dp[i][j][mod(-lst,P)];	
		lst+=num[i];
		if(i==1&&lst%P==0) res++;
	}
	return res;
}

signed main(){
	while(cin>>L>>R>>P){
		init();
		cout<<solve(R)-solve(L-1)<<"\n";	
	}
}