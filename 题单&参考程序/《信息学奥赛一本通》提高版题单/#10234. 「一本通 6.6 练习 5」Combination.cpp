//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=10007;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,m,frac[N];

inline int fpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1; 
	}
	return res;
} 

inline int inv(int x){return fpow(x,mod-2);}

inline int C(int a,int b){
	if(a<b) return 0;
	return frac[a]*inv(frac[b])*inv(frac[a-b])%mod;
}

inline int Lucas(int a,int b){
	if(a<mod&&b<mod) return C(a,b);
	return Lucas(a/mod,b/mod)*C(a%mod,b%mod)%mod;
}

void Solve(){
	frac[0]=1;for(int i=1;i<N;i++) frac[i]=frac[i-1]*i%mod;
	cin>>n>>m;
	cout<<Lucas(n,m)%mod<<"\n";
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
	cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}