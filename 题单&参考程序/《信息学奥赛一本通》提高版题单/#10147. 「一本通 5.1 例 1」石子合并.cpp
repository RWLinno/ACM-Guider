//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define int long long
using namespace std;
const int N=505;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,ans1=inf,ans2=-inf,a[N];
int mx[N][N],mi[N][N],sum[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	sum[0]=0;
	memset(mi,inf,sizeof(mi));
	memset(mx,0,sizeof(mx));
	for(int i=1;i<=n;i++){cin>>a[i];a[i+n]=a[i];}
	for(int i=1;i<=2*n;i++) sum[i]=sum[i-1]+a[i],mi[i][i]=0;
	for(int len=2;len<=n;len++){ //枚举长度 
		for(int l=1;l+len-1<=2*n;l++){ //枚举起点 
			int r=l+len-1;
			for(int k=l;k<r;k++){ //枚举中间点 
				mx[l][r]=max(mx[l][r],mx[l][k]+mx[k+1][r]+sum[r]-sum[l-1]);
				mi[l][r]=min(mi[l][r],mi[l][k]+mi[k+1][r]+sum[r]-sum[l-1]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		ans1=min(ans1,mi[i][i+n-1]);
		ans2=max(ans2,mx[i][i+n-1]);
	}
	cout<<ans1<<"\n";
	cout<<ans2<<"\n";
	return 0;
}