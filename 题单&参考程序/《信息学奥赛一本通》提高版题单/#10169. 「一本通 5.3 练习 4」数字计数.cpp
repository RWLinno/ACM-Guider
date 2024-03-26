//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=30;
//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int pw[N],num[N],cnt[10],dp[N],tmp[10];

void init(){ 
	pw[0]=1;for(int i=1;i<N;i++) pw[i]=pw[i-1]*10;
	dp[0]=0;for(int i=1;i<N;i++) dp[i]=(dp[i-1]*10+pw[i-1]);
}

int solve(int n){
	int len=0,res=0,lst=n;
	while(n){
		num[++len]=n%10;
		n/=10;
	}
	for(int i=len;i>=1;i--){
		for(int j=0;j<=9;j++)	cnt[j]+=dp[i-1]*num[i];
		for(int j=0;j<num[i];j++)	cnt[j]+=pw[i-1];
		lst-=num[i]*pw[i-1];
		cnt[num[i]]+=lst+1;
		cnt[0]-=pw[i-1];
	}
	return res;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	init();
	int L,R;
	cin>>L>>R;
	solve(R);
	for(int i=0;i<=9;i++) tmp[i]=cnt[i];
	memset(cnt,0,sizeof(cnt));
	solve(L-1);
	for(int i=0;i<=9;i++) cout<<tmp[i]-cnt[i]<<" ";
	return 0;
}