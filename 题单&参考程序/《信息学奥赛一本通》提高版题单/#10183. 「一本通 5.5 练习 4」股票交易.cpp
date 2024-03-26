//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
//#define inf 0x3f3f3f3f
//#define int long long
using namespace std;
const int N=2007;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
int n,mxp,W,dp[N][N],ap[N],bp[N],as[N],bs[N],q[N];

void Solve(){
	cin>>n>>mxp>>W;
	for(int i=1;i<=n;++i){
		cin>>ap[i]>>bp[i]>>as[i]>>bs[i];
	}
	memset(dp,128,sizeof(dp));
	for(int i=1;i<=n;++i){
		for(int j=0;j<=as[i];++j) dp[i][j]=-j*ap[i]; //初始化买入金额 
		for(int j=0;j<=mxp;++j) dp[i][j]=max(dp[i][j],dp[i-1][j]); //可以挑最划算的一天买入 
		if(i<=W) continue;  //前W天不可卖出 
		int head=1,tail=0;  //单调队列优化,以股数为单调递增 
		for(int j=0;j<=mxp;++j){  //枚举股票数 
			while(head<=tail&&q[head]+as[i]<j) ++head;  
			while(head<=tail&&dp[i-W-1][q[tail]]+q[tail]*ap[i]<=dp[i-W-1][j]+j*ap[i]) --tail;
			q[++tail]=j;
			if(head<=tail) dp[i][j]=max(dp[i][j],dp[i-W-1][q[head]]+q[head]*ap[i]-j*ap[i]);
		}
		head=1,tail=0;
		for(int j=mxp;j>=0;--j){
			while(head<=tail&&q[head]>j+bs[i]) ++head;
			while(head<=tail&&dp[i-W-1][q[tail]]+q[tail]*bp[i]<=dp[i-W-1][j]+j*bp[i]) --tail;
			q[++tail]=j;
			if(head<=tail) dp[i][j]=max(dp[i][j],dp[i-W-1][q[head]]+q[head]*bp[i]-j*bp[i]);
		}
	}
	cout<<dp[n][0]<<"\n";
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