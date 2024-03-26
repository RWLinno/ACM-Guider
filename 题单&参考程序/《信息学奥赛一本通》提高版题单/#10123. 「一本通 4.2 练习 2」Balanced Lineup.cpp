//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x7f7f7f7f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

int n,m,a[N],mx[N][70],mi[N][70];
int pw[70],lg[N];

void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mx[i][0]=mi[i][0]=a[i];
	}
	for(int j=1;j<=62;j++)	for(int i=1;i<=n&&i+pw[j]-1<=n;i++){
		mx[i][j]=max(mx[i][j-1],mx[i+pw[j-1]][j-1]);
		mi[i][j]=min(mi[i][j-1],mi[i+pw[j-1]][j-1]);
	}
	for(int i=1,l,r;i<=m;i++){
		cin>>l>>r;
		int dep=log2(r-l+1);
		int ans=max(mx[l][dep],mx[r-pw[dep]+1][dep])-min(mi[l][dep],mi[r-pw[dep]+1][dep]);
		cout<<ans<<"\n";
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	pw[0]=1;for(int i=1;i<=63;i++) pw[i]=pw[i-1]<<1;
	lg[0]=-1;for(int i=1;i<N;i++) lg[i]=lg[i/2]+1;
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}