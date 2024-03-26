#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+7;

int n,m,mod;

#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
int tr[N<<2],lz[N<<2],tg[N<<2];
void pushdown(int p,int l,int r){
	if(l==r) return;
	if(tg[p]!=1){
		tg[ls]*=tg[p];tg[ls]%=mod;
		tg[rs]*=tg[p];tg[rs]%=mod;
		lz[ls]*=tg[p];lz[ls]%=mod;
		lz[rs]*=tg[p];lz[rs]%=mod;
		tr[ls]*=tg[p];tr[ls]%=mod;
		tr[rs]*=tg[p];tr[rs]%=mod;
		tg[p]=1;
	}
	if(lz[p]){
		lz[ls]+=lz[p];lz[ls]%=mod;
		lz[rs]+=lz[p];lz[rs]%=mod;
		tr[ls]+=(mid-l+1)*lz[p];tr[ls]%=mod;
		tr[rs]+=(r-mid)*lz[p];tr[rs]%=mod;
		lz[p]=0;
	}
}

void build(int p,int l,int r){
	tg[p]=1; //乘法标记 
	if(l==r){
		cin>>tr[p];
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	tr[p]=(tr[ls]+tr[rs])%mod;
}

int query(int p,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return tr[p];
	int res=0;
	pushdown(p,l,r);
	if(ql<=mid) res+=query(ls,l,mid,ql,qr)%mod;
	if(qr>mid) res+=query(rs,mid+1,r,ql,qr)%mod;
	return res%mod;
}

void add(int p,int l,int r,int ql,int qr,int c){
	if(ql<=l&&r<=qr){
		tr[p]+=(r-l+1)*c;tr[p]%=mod;
		lz[p]+=c;lz[p]%=mod;
		return;
	}
	pushdown(p,l,r);
	if(ql<=mid) add(ls,l,mid,ql,qr,c);
	if(qr>mid) add(rs,mid+1,r,ql,qr,c);
	tr[p]=(tr[ls]+tr[rs])%mod; 
}

void mul(int p,int l,int r,int ql,int qr,int c){
	if(ql<=l&&r<=qr){
		tr[p]*=c;tr[p]%=mod;
		lz[p]*=c;lz[p]%=mod;
		tg[p]*=c;tg[p]%=mod;
		return;
	}
	pushdown(p,l,r);
	if(ql<=mid) mul(ls,l,mid,ql,qr,c);
	if(qr>mid) mul(rs,mid+1,r,ql,qr,c);
	tr[p]=(tr[ls]+tr[rs])%mod;
}

signed main(){
	cin>>n>>mod;
	build(1,1,n);
	cin>>m;
	int op,l,r,c;
	for(int i=1;i<=m;i++){
		cin>>op>>l>>r;
		if(op==1){
			cin>>c;
			mul(1,1,n,l,r,c);
		}else if(op==2){
			cin>>c;
			add(1,1,n,l,r,c);
		}else{
			cout<<query(1,1,n,l,r)%mod<<"\n"; 
		}
	}
	return 0;
}