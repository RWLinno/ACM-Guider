//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x7f7f7f7f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

int n,m,a[N],st[N][70];
int pw[70];

void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		st[i][0]=a[i];
	}
	for(int j=1;j<=62;j++)	for(int i=1;i<=n&&i+pw[j]-1<=n;i++){
		st[i][j]=max(st[i][j-1],st[i+pw[j-1]][j-1]);
	}
	cin>>m;
	for(int i=1,l,r;i<=m;i++){
		cin>>l>>r;
		int dep=log2(r-l+1);
		cout<<max(st[l][dep],st[r-pw[dep]+1][dep])<<"\n";
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	pw[0]=1;for(int i=1;i<=63;i++) pw[i]=pw[i-1]<<1;
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}