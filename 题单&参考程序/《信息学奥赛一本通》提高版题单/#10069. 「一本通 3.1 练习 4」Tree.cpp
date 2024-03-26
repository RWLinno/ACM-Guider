//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7;

int n,m,nd,ans,fa[N];
int s[N],t[N],c[N],col[N];

struct E{
	int u,v,w,col;
}e[N<<1];
/*
int head[N],cnt=0;
inline void addedge(int u,int v,int w,int col){
	e[++cnt]=(E){u,v,w,col,head[u]};head[u]=cnt;
}*/

bool cmp(E a, E b){
	if(a.w==b.w) return a.col<b.col;
	return a.w<b.w;
}

int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}

bool check(int x){
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++){
		e[i]=(E){s[i],t[i],c[i]+x*(col[i]^1),col[i]};
	}
	sort(e+1,e+1+m,cmp);
	int res=0,num=0;
	for(int i=1;i<=m;i++){
		int u=find(e[i].u),v=find(e[i].v);
		if(u!=v){
			if(!e[i].col) num++;
			fa[u]=v;
			res+=e[i].w;
		}
	}
	if(num>=nd) ans=res-x*nd;
	return num>=nd;
}

void Solve(){
	cin>>n>>m>>nd;
	for(int i=1;i<=m;i++){
		cin>>s[i]>>t[i]>>c[i]>>col[i];
		s[i]++;t[i]++;
	}
	int L=-1001,R=1001,mid;
	while(R-L>1){
		mid=(L+R)>>1;
		if(check(mid)) L=mid;
		else R=mid;
	}
	cout<<ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}
