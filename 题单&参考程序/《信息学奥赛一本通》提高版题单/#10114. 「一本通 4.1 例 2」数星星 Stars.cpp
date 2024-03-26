//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
#define lb(x) (x&-x)
using namespace std;
const int N=1e5+7;
const int mod=1e9+7;

int n,u[N],v[N],tr[N],ans[N];

inline void upd(int x){
	for(;x<N;x+=lb(x)) tr[x]++;
} 

inline int ask(int x){ //查询前缀和 
	int res=0;
	for(;x;x-=lb(x)) res+=tr[x];
	return res;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	cin>>n;
	for(int i=1,x,y;i<=n;i++){ //y按增序，y相同x按增序 
		cin>>x>>y;
		x++;
		ans[ask(x)]++; 
		upd(x);
	}
	for(int i=0;i<n;i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}