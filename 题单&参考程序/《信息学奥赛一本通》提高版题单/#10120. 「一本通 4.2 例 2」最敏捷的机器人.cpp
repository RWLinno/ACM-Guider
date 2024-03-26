//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

deque<int>mx,mi;  //单调递减和单调递增 
int n,k,a[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		while(mx.size()&&a[i]>a[mx.back()]) mx.pop_back(); //mx是单调递减序列 
		while(mi.size()&&a[i]<a[mi.back()]) mi.pop_back(); //mi是单调递增序列 
		mx.push_back(i);mi.push_back(i); //加入双端队列 
		while(mx.front()<i-k+1) mx.pop_front();
		while(mi.front()<i-k+1) mi.pop_front();
		if(i>=k) cout<<a[mx.front()]<<" "<<a[mi.front()]<<"\n"; 
	}
	return 0;
}