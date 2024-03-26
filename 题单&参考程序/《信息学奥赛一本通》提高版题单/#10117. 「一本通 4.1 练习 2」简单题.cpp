//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
#define lb(x) (x&-x) 
using namespace std;
const int N=1e6+7;
const int mod=1e9+7;

int n,m,tr[N];

void upd(int x){for(;x<=n;x+=lb(x)) tr[x]^=1;}

int ask(int x){int res=0;for(;x;x-=lb(x)) res^=tr[x];return res;}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1,t,l,r;i<=m;i++){
		cin>>t;
		if(t==1){
			cin>>l>>r;
			upd(l);
			upd(r+1);
		}else{
			cin>>l;
			cout<<ask(l)<<"\n";
		}
	}
	return 0;
}