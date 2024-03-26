//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int a,b,dp[N][40],num[40];

void init(){ //预处理dp[i][j]表示最高位是j，一共有i位的不降数个数 
	for(int i=0;i<=9;i++) dp[1][i]=1;
	for(int i=2;i<35;i++){
		for(int j=0;j<=9;j++){
			for(int k=j;k<=9;k++)
				dp[i][j]+=dp[i-1][k]; 
		}
	}
}

int Solve(int n){
	int len=0,res=0,lst=0;
	if(n==0) return 1;
	while(n){
		num[++len]=n%10;
		n/=10;
	}
	for(int i=len;i>=1;i--){  //从高位向低位枚举 
		for(int j=lst;j<num[i];j++) res+=dp[i][j]; //当前位要填比上一位大的数 
		if(num[i]<lst) break; 
		lst=num[i]; //表示上一位的数 
		if(i==1) res++; //最低位满足的答案 
	}
	return res;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	init();
	while(cin>>a>>b){
		cout<<Solve(b)-Solve(a-1)<<"\n";
	}
	return 0;
}