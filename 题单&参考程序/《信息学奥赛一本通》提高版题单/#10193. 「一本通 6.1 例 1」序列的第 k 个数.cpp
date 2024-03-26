#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int maxn=2e5+7;
const int mod=200907;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int fpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}

int t,a,b,c,d,k,ans,tmp;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>a>>b>>c>>k;
		if(c-b==b-a){ //等差
			d=b-a;
			ans=(k-1)*d%mod+a;
			ans%=mod; 
		}else{
			d=c/b;
			ans=a*fpow(d,k-1);
		}
		cout<<ans%mod<<"\n";
	}
	return 0;
}