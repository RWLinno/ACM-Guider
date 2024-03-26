#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define int long long
using namespace std;
const int maxn=205;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct X{
	int l,r;
}s[maxn];

int n,dp[maxn][maxn],ans;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i].l;
		s[i+n].l=s[i].l;
	}
	for(int i=1;i<=2*n;i++){
		s[i].r=s[i+1].l;
		dp[i][i]=0;
	}
	s[2*n].r=s[1].l;
//	for(int i=1;i<=n;i++) cout<<s[i].l<<" "<<s[i].r<<endl;
	for(int len=1;len<=n-1;len++){
		for(int i=1;i+len<=2*n;i++){
			int j=i+len;
			for(int k=i;k<=j-1;k++){
				dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]+s[i].l*s[k].r*s[j].r);
	//			cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
			}
		}
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,dp[i][i+n-1]);
	}
	cout<<ans<<"\n";
	return 0;
}