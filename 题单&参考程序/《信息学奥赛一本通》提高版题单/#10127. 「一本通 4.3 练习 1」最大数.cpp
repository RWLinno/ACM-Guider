#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
const int maxn=2e5+7;

char ch;
int x,m,mod,a=0,tr[maxn<<2];

void add(int p,int l,int r,int pos,int x){
	if(l==r){
		tr[p]=(x+a+mod)%mod;
		return;
	}
	int mid=l+r>>1;
	if(pos<=mid) add(p<<1,l,mid,pos,x);
	else add(p<<1|1,mid+1,r,pos,x);
	tr[p]=max(tr[p<<1],tr[p<<1|1]);  
}

int query(int p,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return tr[p]; 
	int mid=l+r>>1,res=0;
	if(ql<=mid) res=max(res,query(p<<1,l,mid,ql,qr));
	if(qr>mid) res=max(res,query(p<<1|1,mid+1,r,ql,qr));
	return res; 
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>m>>mod;
	memset(tr,0,sizeof(tr));
	int len=0;
	for(int i=1;i<=m;i++){
		cin>>ch>>x;
		if(ch=='A'){
			add(1,1,m,len+1,x);
			len++;
		}
		if(ch=='Q'){
			a=query(1,1,m,len-x+1,len);
			cout<<a<<endl;
		}
	//	for(int i=1;i<=4*len;i++) cout<<tr[i]<<" ";
	}
	return 0;
}