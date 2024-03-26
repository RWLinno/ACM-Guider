/*
//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
using namespace std;
const int N=1e7+7;
const int mod=1e9+7;

int l,r,flag=0,tmp=0,sum[N];

signed main(){
	sum[0]=0;
	for(int i=1;i<=1e7;i++){
		tmp=i,flag=0;
		while(tmp){
			if(tmp%10==4) flag=1;
			else if(tmp>=62&&(tmp-62)%100==0) flag=1; 
			tmp/=10;
		}
		sum[i]=sum[i-1]+flag;
	}
	cin>>l>>r;
	while(l||r){
		cout<<(r-l+1)-(sum[r]-sum[l-1])<<"\n"; 
		cin>>l>>r;
	}
	return 0;
}*/

#include<bits/stdc++.h>
using namespace std;
const int N=10;

int L,R,dp[N][10],num[N];

void init(){
	for(int i=0;i<=9;i++) if(i!=4) dp[1][i]=1;
	for(int i=2;i<N;i++){
		for(int j=0;j<=9;j++){
			if(j==4) continue;
			for(int k=0;k<=9;k++){
				if(k==4||j==6&&k==2) continue;
				dp[i][j]+=dp[i-1][k];
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
		for(int j=0;j<num[i];j++){
			if(j==4||lst==6&&j==2) continue;
			res+=dp[i][j];
		}
		if(num[i]==4||lst==6&&num[i]==2) break;
		lst=num[i];
		if(i==1) res++;
	}
	return res; 
}

signed main(){
	init();
	while(cin>>L>>R,L||R){
		cout<<solve(R)-solve(L-1)<<"\n";
	}
}