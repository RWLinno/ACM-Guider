//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int L,R,dp[40][15],num[40];

void init(){
	for(int i=0;i<=9;i++) dp[1][i]=1;
	for(int i=2;i<=35;i++){
		for(int j=0;j<=9;j++){
			for(int k=0;k<=j-2;k++) dp[i][j]+=dp[i-1][k];
			for(int k=j+2;k<=9;k++) dp[i][j]+=dp[i-1][k];			
		}
	}
}

int Solve(int n){
	int len=0,res=0,lst=-2;
	if(!n) return 0; 
	while(n){
		num[++len]=n%10;
		n/=10;
	}
	for(int i=len;i>=1;i--){
		if(i==len) for(int j=1;j<num[i];j++) res+=dp[i][j];
		else{
			for(int j=0;j<num[i];j++)
				if(abs(j-lst)>=2) res+=dp[i][j]; 
		}
		if(abs(num[i]-lst)>=2) lst=num[i];
		else break;
		if(i==1) res++;
	}
	for(int i=1;i<len;i++) for(int j=1;j<=9;j++) res+=dp[i][j];
	return res;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	init();
	cin>>L>>R;
	cout<<Solve(R)-Solve(L-1)<<"\n"; 
	return 0;
}