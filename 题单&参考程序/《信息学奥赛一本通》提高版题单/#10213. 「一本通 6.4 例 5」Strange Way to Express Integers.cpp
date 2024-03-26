//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
int n,M=1,m[N],a[N],b[N],t[N];

int mul(int a,int b,int mod){
    int res=0;
    while(b){
        if(b&1) res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return res;
}

inline int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}

inline int lcm(int a,int b){
	return a*b/gcd(a,b);
}

inline int exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1;y=0;
		return a;
	}
	int d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}

inline int excrt(){
	int x,y,M=a[1],ans=b[1];
	for(int i=2;i<=n;++i){
		int A=M,B=a[i],C=(b[i]-ans%B+B)%B;  //Ax ≡C(mod B)
		int g=exgcd(A,B,x,y),bg=B/g;
		if(C%g!=0) return -1; //判是否无解
		x=mul(x,C/g,bg);
		ans+=x*M; //更新前k个方程组的答案 
		M*=bg;  //M为前k个m的lcm
		ans=(ans%M+M)%M; 
	}
	return (ans%M+M)%M;
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
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;++i) cin>>a[i]>>b[i];
		cout<<excrt()<<"\n";
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;
	return 0;
}