//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x7f7f7f7f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
int n,k,sum=0,a[N],dp[N],q[N];

void Solve(){
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		sum+=a[i];
	}
	//for(int i=1;i<=n+1;++i) dp[i]=inf;
	dp[0]=0;
	q[1]=0;
	int head=1,tail=1;
	for(int i=1;i<=n+1;++i){
		while(head<=tail&&i-q[head]>k) ++head; 
		dp[i]=dp[q[head]]+a[i];
		while(head<=tail&&dp[i]<=dp[q[tail]]) --tail;
		q[++tail]=i;
	}
	//for(int i=1;i<=n;++i) cout<<dp[i]<<" ";
	//cout<<"!!\n";
	cout<<dp[n+1]<<"\n";
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