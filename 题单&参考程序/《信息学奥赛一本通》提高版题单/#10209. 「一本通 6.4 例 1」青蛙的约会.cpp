//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
inline int gcd(int a,int b){
	return b?gcd(b,a%b):a;
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

void Solve(){
	int A,B,m,n,L,x,y;
	cin>>A>>B>>m>>n>>L;
	if(n<m){
		swap(n,m);
		swap(A,B);
	}
	int a=n-m,b=L,c=A-B,d=exgcd(a,b,x,y);
	if(n==m||c%d){
		cout<<"Impossible\n";
		return;
	}
	int tmp=b/d,ans;
	ans=((x*c/d)%tmp+tmp)%tmp;
	cout<<ans<<"\n";
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