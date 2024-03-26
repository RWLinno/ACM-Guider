//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=20;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int count(int x){int res=0;while(x){res++;x&=(x-1);}return res;}
int lb(int x){return x&(-x);}

int n,K,ans=0,dp[N][(1<<10)][N*N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>K;
	for(int j=0;j<(1<<n);j++){
		if(j&(j<<1)) continue;
		dp[1][j][count(j)]=1; 
	} 
	for(int i=2;i<=n;i++){
		for(int j=0;j<(1<<n);j++){ //枚举子集 
			if(j&(j<<1)) continue; //左右互不侵犯 
			for(int k=0;k<(1<<n);k++){ //前一行的状态
				if(k&(k<<1)) continue;
				if(!((j&k)||(j&(k<<1))||((j<<1)&k))){ //当前状态满足和上一行的状态互不侵犯 
					int num=count(j);//,num2=count(k);
					for(int p=0;p<=K;p++){
						dp[i][j][p+num]+=dp[i-1][k][p];
					}
				}
			}
		}
	}
	for(int j=0;j<(1<<n);j++){
		if(j&(j<<1)) continue;
		ans+=dp[n][j][K];
	}
	cout<<ans<<"\n";
	return 0;
}