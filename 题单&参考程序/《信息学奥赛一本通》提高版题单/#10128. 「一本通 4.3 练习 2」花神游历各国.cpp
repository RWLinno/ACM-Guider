//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
int n,m,tr[N<<2],tg[N<<2];
void build(int p,int l,int r){
	if(l==r){
		cin>>tr[p];
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	tr[p]=tr[ls]+tr[rs];
}

int query(int p,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return tr[p];
	int res=0;
	if(ql<=mid) res+=query(ls,l,mid,ql,qr);
	if(qr>mid) res+=query(rs,mid+1,r,ql,qr);
	return res;
}

void update(int p,int l,int r,int ql,int qr){
	if(tg[p]>=6) return; //这个区间已经被开过6次方了
	if(l==r){
		tr[p]=sqrt(tr[p]);
		tg[p]++;
		return;
	}
	if(ql<=mid) update(ls,l,mid,ql,qr);
	if(qr>mid) update(rs,mid+1,r,ql,qr);
	tr[p]=tr[ls]+tr[rs];
	tg[p]=min(tg[ls],tg[rs]);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	cin>>n;
	build(1,1,n);
	cin>>m;
	for(int i=1,op,l,r;i<=m;i++){
		cin>>op>>l>>r;
		if(op==1){
			cout<<query(1,1,n,l,r)<<"\n";
		}else{
			update(1,1,n,l,r);
		}
	} 
	return 0;
}