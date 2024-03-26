//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,m,c[N];
vector<int>G[N];

int sz[N],fa[N],dep[N],son[N],dfn[N],idfn[N],bel[N],idx=0;
void dfs1(int x){
	sz[x]=1;
	for(auto to:G[x]){
		if(to==fa[x]) continue;
		dep[to]=dep[x]+1;
		fa[to]=x;
		dfs1(to);
		sz[x]+=sz[to];
		if(sz[son[x]]<sz[to]) son[x]=to; 
	}
}

void dfs2(int x,int tp){
	dfn[x]=++idx;
	idfn[idx]=x;
	bel[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(auto to:G[x]){
		if(to==fa[x]||to==son[x]) continue;
		dfs2(to,to);
	}
}

#define ls (p<<1)
#define rs (p<<1|1)

struct T{
	int l,r,lc,rc,cnt,tg; //左边颜色和右边颜色,颜色段数,区间修改标记 
}tr[N<<2];

T pushup(T a,T b){ //合并左右段颜色 
	T res;
	res.l=a.l,res.r=b.r;
	res.lc=a.lc,res.rc=b.rc;
	res.cnt=a.cnt+b.cnt-(a.rc==b.lc);
	res.tg=0; 
	return res;
} 

void build(int p,int l,int r){ //建树 
	tr[p].l=l;tr[p].r=r;
	if(l==r){
		tr[p].lc=tr[p].rc=c[idfn[l]];
		tr[p].cnt=1;
		return;
	}
	int mid=((l+r)>>1);
	build(ls,l,mid);
	build(rs,mid+1,r);
//	tr[p]=pushup(tr[ls],tr[rs]);
	tr[p].cnt=tr[ls].cnt+tr[rs].cnt-(tr[ls].rc==tr[rs].lc);
	tr[p].lc=tr[ls].lc;
	tr[p].rc=tr[rs].rc;
}

inline void pushdown(int p){
	if(tr[p].l==tr[p].r) return;
	if(tr[p].tg){
		tr[ls].tg=tr[rs].tg=tr[p].tg;
		tr[ls].cnt=tr[rs].cnt=1;
		tr[ls].lc=tr[ls].rc=tr[rs].lc=tr[rs].rc=tr[p].tg;
		tr[p].tg=0;
	}
}

void update(int p,int ql,int qr,int col){
	pushdown(p);
	if(ql==tr[p].l&&tr[p].r==qr){
		tr[p].cnt=1;
		tr[p].lc=tr[p].rc=col;
		tr[p].tg=col;
		return;
	}
	int mid=((tr[p].l+tr[p].r)>>1);
	if(qr<=mid) update(ls,ql,qr,col);
	else if(ql>mid) update(rs,ql,qr,col);
	else{
		update(ls,ql,mid,col);
		update(rs,mid+1,qr,col);
	}
	tr[p].cnt=tr[ls].cnt+tr[rs].cnt-(tr[ls].rc==tr[rs].lc);
	tr[p].lc=tr[ls].lc;
	tr[p].rc=tr[rs].rc;
//	pushup(tr[ls],tr[rs]);
}

inline int query(int p,int ql,int qr){ 
	pushdown(p);
	if(ql==tr[p].l&&tr[p].r==qr) return tr[p].cnt;
	int mid=((tr[p].l+tr[p].r)>>1);
	if(ql>mid) return query(rs,ql,qr);
	else if(qr<=mid) return query(ls,ql,qr);
	else return query(ls,ql,mid)+query(rs,mid+1,qr)-(tr[ls].rc==tr[rs].lc);
}

int qc(int p,int pos){
	pushdown(p);
	if(tr[p].l==tr[p].r) return tr[p].lc;
	int mid=((tr[p].l+tr[p].r)>>1);
	if(mid<pos) return qc(rs,pos);
	else return qc(ls,pos);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	int u,v,col;
	char op;
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<n;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	} 
	dfs1(1);
	dfs2(1,1);
	build(1,1,n); 
	for(int i=1;i<=m;i++){
		cin>>op>>u>>v;
		if(op=='C'){
			cin>>col;
			while(bel[u]!=bel[v]){
				if(dep[bel[u]]<dep[bel[v]]) swap(u,v);
				update(1,dfn[bel[u]],dfn[u],col);
				u=fa[bel[u]];
			}
			if(dep[u]<dep[v]) swap(u,v);
			update(1,dfn[v],dfn[u],col);
		}else{
			int ans=0;
			while(bel[u]!=bel[v]){
				if(dep[bel[u]]<dep[bel[v]]) swap(u,v);
				ans+=query(1,dfn[bel[u]],dfn[u]);
				int c1=qc(1,dfn[bel[u]]),c2=qc(1,dfn[fa[bel[u]]]);
				if(c1==c2) ans--;
				u=fa[bel[u]];
			}
			if(dep[u]<dep[v]) swap(u,v);
			ans+=query(1,dfn[v],dfn[u]);
			cout<<ans<<"\n";
		}
	}
	return 0;
}