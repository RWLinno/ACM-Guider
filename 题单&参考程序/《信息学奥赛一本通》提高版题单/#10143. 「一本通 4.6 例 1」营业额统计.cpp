#include<bits/stdc++.h>
#define int long long
#define inf 1e17
#define ls(x) (T[x].ch[0])
#define rs(x) (T[x].ch[1])
#define sz(x) (T[x].sz)
#define val(x) (T[x].val)
#define pri(x) (T[x].pri)
using namespace std;
const int N=1e5+7;

struct FHQ{
	int ch[2],val,pri,sz;
}T[N];

int n,tot,ans=0;

inline void update(int x){
	T[x].sz=sz(ls(x))+sz(rs(x))+1;
}

int cre(int v){
	sz(++tot)=1;
	val(tot)=v;
	pri(tot)=rand();
	return tot; 
}

int merge(int x,int y){
	if(!x||!y) return x+y;
	if(pri(x)<pri(y)){
		rs(x)=merge(rs(x),y);
		update(x);
		return x;
	}else{
		ls(y)=merge(x,ls(y));
		update(y);
		return y;
	}
}

void split(int p,int k,int &x,int &y){  //按值分离 
	if(!p) x=y=0;
	else{
		if(val(p)<=k) x=p,split(rs(p),k,rs(p),y);
		else y=p,split(ls(p),k,x,ls(p));
		update(p);
	} 
}

int kth(int p,int k){  //查询排名 
	while(1){
		if(k<=sz(ls(p))) p=ls(p);
		else if(k==sz(ls(p))+1) return p;
		else k-=sz(ls(p))+1,p=rs(p); 
	}
}

signed main(){
	srand(time(0)^998244353);
	cin>>n;
	int root=0,x,y,z,op,a;
	root=merge(cre(-inf),root);
	root=merge(root,cre(inf));
	for(int i=1,a;i<=n;i++){
		cin>>a;	
		if(i!=1){ //算波动值 
			
			split(root,a,x,y);
			int pr=val(kth(x,sz(x))),nx=val(kth(y,1)); //前驱（或相同的数）和后继 
			root=merge(x,y);
				
			ans+=min(abs(a-pr),abs(a-nx));
		}else ans+=a;
		split(root,a,x,y);
		root=merge(merge(x,cre(a)),y);
	} 
	cout<<ans; 
	return 0;
}