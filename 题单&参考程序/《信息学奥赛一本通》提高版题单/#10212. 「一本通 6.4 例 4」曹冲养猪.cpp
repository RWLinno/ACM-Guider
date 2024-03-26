//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=15;
const int mod=1e9+7;

int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

int n,a[N],b[N],m[N],t[N],M=1;

inline int exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1;y=0;
		return a;
	}
	int d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}

inline int inv(int a,int b){
	int d,x,y;
	d=exgcd(a,b,x,y);
	return (x<0)?(x+b):x;
}

void Solve(){
	n=read();
	for(int i=1;i<=n;++i){
		a[i]=read();b[i]=read();
		M*=a[i];
	}
	int ans=0;
	for(int i=1;i<=n;++i){
		m[i]=M/a[i];
		t[i]=inv(m[i],a[i]); //找m[i]在a[i]意义下的逆元
		ans+=b[i]*m[i]%M*t[i]%M;
		ans%=M;
		/*
		for(int j=1;;++j){  //直接枚举逆元 
			if(m[i]*j%a[i]==1){
				ans+=b[i]*m[i]%M*j%M;
				ans%=M;
				break;
			}
		}*/
	}
	write(ans);putchar('\n');
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
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