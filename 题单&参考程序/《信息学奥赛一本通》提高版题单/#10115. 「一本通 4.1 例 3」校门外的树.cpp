//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
#define lb(x) (x&-x)
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,tr1[N<<1],tr2[N<<1];

inline void update1(int x){
	for(;x<=n;x+=lb(x)) tr1[x]+=1;
}

inline void update2(int x){
	for(;x<=n;x+=lb(x)) tr2[x]+=1;
}

inline int query1(int x){
	int res=0;
	for(;x;x-=lb(x)) res+=tr1[x];
	return res;
}

inline int query2(int x){
	int res=0;
	for(;x;x-=lb(x)) res+=tr2[x];
	return res;
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int m,op,l,r;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>op>>l>>r;
		if(op==1){
			update1(l);
			update2(r);
		}else{
			cout<<query1(r)-query2(l-1)<<"\n";
		}
	}
	return 0;
}