//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=5000011;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
int n,k,ans=0,frac[N],ifrac[N];

inline int fpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}

inline int C(int n,int m){
	if(n<m) return 0;
	return frac[n]*ifrac[m]%mod*ifrac[n-m]%mod;
}

void Solve(){
	cin>>n>>k;
	frac[0]=1;
	for(int i=1;i<N;++i) frac[i]=frac[i-1]*i%mod;
	ifrac[N-1]=fpow(frac[N-1],mod-2);
	for(int i=N-1;i>=1;--i) ifrac[i-1]=ifrac[i]*i%mod; 
	for(int x=1;x<=n;++x){
		int lf=n-k*(x-1);
		if(lf<0) continue;
		ans=(ans+C(lf,x))%mod;
	}
	cout<<(ans+1)%mod<<"\n";  //全部都是牝牛的情况 
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
//	cin>>T;
//	clock_t start,finish;
//	start=clock();
	while(T--){
		Solve();
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;
	return 0;
}