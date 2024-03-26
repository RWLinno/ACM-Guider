//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

int n,m,ans=-inf,sumq,a[N];
deque<int>dq;

void Solve(){
	cin>>n>>m;
	a[0]=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]+=a[i-1];
	}
	dq.push_back(0);
	for(int i=1;i<=n;i++){
		while(dq.size()&&dq.front()<i-m) dq.pop_front();
		ans=max(ans,a[i]-a[dq.front()]);
		while(dq.size()&&a[dq.back()]>a[i]) dq.pop_back();
		dq.push_back(i);
	}
	cout<<ans<<"\n"; 
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}