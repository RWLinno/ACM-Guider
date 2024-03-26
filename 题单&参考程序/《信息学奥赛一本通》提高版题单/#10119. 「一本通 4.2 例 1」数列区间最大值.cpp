//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,m;

#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
 
int tr[N<<2];
void build(int p,int l,int r){
	if(l==r){
		cin>>tr[p];
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	tr[p]=max(tr[ls],tr[rs]);
}

int query(int p,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return tr[p];
	int res=-inf;
	if(ql<=mid) res=query(ls,l,mid,ql,qr);
	if(qr>mid) res=max(res,query(rs,mid+1,r,ql,qr));
	return res;
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	cin>>n>>m;
	build(1,1,n);
	for(int i=1,l,r;i<=m;i++){
		cin>>l>>r;
		cout<<query(1,1,n,l,r)<<"\n";
	}
	return 0;
}