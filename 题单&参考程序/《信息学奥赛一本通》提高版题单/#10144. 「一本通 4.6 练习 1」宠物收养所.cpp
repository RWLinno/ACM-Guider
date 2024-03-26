#include<bits/stdc++.h>
//#define int long long
#define inf 1e17
#define val(x) T[x].val
#define pri(x) T[x].pri
#define sz(x) T[x].sz
#define ls(x) T[x].ch[0]
#define rs(x) T[x].ch[1]
using namespace std;
const int N=2e5+7;
const int mod=1e6;

struct FHQ{
	int val,pri,sz,ch[2];
}T[N];
int n,root=0,fl=0,tot=0;
int st[N],top=0;  //垃圾回收 
inline void update(int x){sz(x)=sz(ls(x))+sz(rs(x))+1;}

inline int cre(int v){
	int p=(top)?st[top--]:++tot;
	T[p].val=v;
	T[p].pri=rand();
	T[p].sz=1;
	T[p].ch[0]=T[p].ch[1]=0;
	return p;
}

int merge(int x,int y){
	if(!x||!y) return x|y;
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

int kth(int p,int k){ //返回以p为根，第k个点的编号 
	while(1){
		if(sz(ls(p))+1>k) p=ls(p);
		else if(sz(ls(p))+1==k) return p;
		else k-=sz(ls(p))+1,p=rs(p);
	}
}

void split(int p,int v,int &x,int &y){  //按值分离 
	if(!p) x=y=0;
	else{
		if(val(p)<=v) x=p,split(rs(x),v,rs(x),y);
		else y=p,split(ls(y),v,x,ls(y));
		update(p);
	}
}

inline void ins(int v){int x,y;split(root,v,x,y);root=merge(merge(x,cre(v)),y);}

inline void del(int v){int x,y,z;split(root,v,x,z);split(x,v-1,x,y);st[++top]=y;root=merge(x,z);}

int pre(int v){
	int x,y,p;
	split(root,v,x,y);
	p=x;
	while(rs(p)) p=rs(p);
	root=merge(x,y);
	return p;
}

int suf(int v){
	int x,y,p;
	split(root,v,x,y);
	p=y;
	while(ls(p)) p=ls(p);
	root=merge(x,y);
	return p;
}

signed main(){
	srand(time(0)^998244353);
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	int idx=0,x,y,z,pr,nx,ans=0;
	for(int i=1,a,b;i<=n;i++){
		cin>>a>>b;
		if(a==fl) ins(b);  //直接存宠物 
		else if(!sz(root)) fl=a,ins(b); //将人存进去 
		else{  //让宠物领人 
			pr=pre(b),nx=suf(b);
			if(!nx) ans=(ans+b-val(pr))%mod,del(val(pr));
			else if(!pr) ans=(ans+val(nx)-b)%mod,del(val(nx));
			else if(b-val(pr)<=val(nx)-b) ans=(ans+b-val(pr))%mod,del(val(pr));
			else ans=(ans+val(nx)-b)%mod,del(val(nx)); 
	//		cout<<val(pr)<<" "<<val(nx)<<" "<<ans<<"\n";
		}
	}
	cout<<ans<<"\n";
	return 0;
}