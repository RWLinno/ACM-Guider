#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int maxn=2e5+7;
const int mod=200907;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int fpow(int a,int b,int m){
	int res=1;
	while(b){
		if(b&1) res=res*a%m;
		a=a*a%m;
		b>>=1;
	}
	return res;
}

int t,a,b,m,ans;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>a>>b>>m;
	ans=fpow(a,b,m);
	cout<<ans<<"\n";
	return 0;
}