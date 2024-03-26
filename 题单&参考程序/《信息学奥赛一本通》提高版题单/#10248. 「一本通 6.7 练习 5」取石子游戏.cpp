#include<bits/stdc++.h>
#define int long long
#define mk(i,j) ((1e7+7)*i+j)
#define pii long long
using namespace std;
const int N=1001;
int T,n,a[N];

void solve(){
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	if(abs(a[1]-a[n])<=1){
		cout<<((a[1]==1)||(a[n]==1))<<"\n";
	}else cout<<"1\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}