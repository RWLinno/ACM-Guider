//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

inline int fpow(int a,int b,int mod){
	int res=1;
	while(b){
		if(b&1) res=a*res%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}

inline int C(int n,int m,int mod){  //n!/(m!*(n-m)!)
	if(n<m) return 0; 
	if(m>n-m) m=n-m;
	int s1=1,s2=1;
	for(int i=1;i<=m;i++){
		s1=s1*(n-i+1)%mod;
		s2=s2*i%mod;
	}
	return s1*fpow(s2,mod-2,mod)%mod;
}

inline int Lucas(int a,int b,int p){
	if(b==0) return 1;
	return C(a%p,b%p,p)*Lucas(a/p,b/p,p)%p;
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int t,n,m,p;
	cin>>t;
	while(t--){
		cin>>n>>m>>p;
		cout<<Lucas(n,m,p)<<"\n";
	}
	return 0;
}