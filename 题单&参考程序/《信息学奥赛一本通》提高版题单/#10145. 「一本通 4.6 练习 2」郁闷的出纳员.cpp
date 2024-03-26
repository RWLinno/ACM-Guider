#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;

struct FHQ{
	int ch[2],sz,pri,val;
}T[N];

int n,mi,ans=0,root=0,cnt=0;
int stk[N],top=0; //废物利用 
#define val(x) T[x].val
#define ls(x) T[x].ch[0]
#define rs(x) T[x].ch[1]
#define pri(x) T[x].pri
#define sz(x) T[x].sz

inline void update(int x){sz(x)=sz(ls(x))+sz(rs(x))+1;}

inline int cre(int v){
	T[++cnt].val=v;
	T[cnt].pri=rand();
	T[cnt].sz=1;
	return cnt;
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

inline void split(int p,int k,int &x,int &y){ //按值分离 
	if(!p) x=y=0;
	else{
		if(val(p)<=k) x=p,split(rs(x),k,rs(x),y);
		else y=p,split(ls(y),k,x,ls(y));
		update(p);
	}
}

inline int kth(int p,int k){
	while(1){
		if(sz(ls(p))+1>k) p=ls(p);
		else if(sz(ls(p))+1==k) return p;
		else k-=sz(ls(p))+1,p=rs(p);
	}
}

signed main(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>mi;
	char op;
	int k,x,y,z,bias=0;
	for(int i=1;i<=n;i++){
		cin>>op>>k;
		if(op=='I'){  //插入 
			if(k<mi) continue;
			split(root,k-bias,x,y);
			root=merge(merge(x,cre(k-bias)),y);
		}else if(op=='A'){  //所有员工上调工资 
			bias+=k;
		}else if(op=='S'){  //所有员工下调工资 
			bias-=k;
			split(root,mi-bias-1,x,y);
			ans+=sz(x); 
			root=y;  //前面的都离开了公司 
		}else if(op=='F'){  //查询第k多的工资 
			if(sz(root)<k){
				cout<<"-1\n";
			}else{
				k=sz(root)-k+1;
				cout<<val(kth(root,k))+bias<<"\n";
			}
		}
	}		
	cout<<ans<<"\n";
	return 0;
}