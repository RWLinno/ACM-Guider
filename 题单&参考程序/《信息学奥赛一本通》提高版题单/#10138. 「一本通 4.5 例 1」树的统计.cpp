//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,u,v,q,val[N];
string str;
vector<int>G[N];

int sz[N],fa[N],son[N],dep[N],bel[N],dfn[N],idfn[N],idx;
void dfs1(int x){
	sz[x]=1;
	for(int i=0;i<G[x].size();i++){
		int to=G[x][i];
		if(to==fa[x]) continue;
		fa[to]=x;
		dep[to]=dep[x]+1;
		dfs1(to);
		sz[x]+=sz[to];
		if(sz[to]>sz[son[x]]) son[x]=to;
	}
}

void dfs2(int x,int tp){
	dfn[x]=++idx;
	idfn[idx]=x;
	bel[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i=0;i<G[x].size();i++){
		int to=G[x][i];
		if(to==fa[x]||to==son[x]) continue;
		dfs2(to,to); 
	}
}

#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
int tr[N<<2],mx[N<<2];
void build(int p,int l,int r){
	if(l==r){
		tr[p]=mx[p]=val[idfn[l]];
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	tr[p]=tr[ls]+tr[rs];
	mx[p]=max(mx[ls],mx[rs]);
}

void update(int p,int l,int r,int pos,int v){
	//cout<<"update: "<<p<<" "<<l<<" "<<r<<" "<<pos<<" "<<v<<"\n";
	if(l==r){
		val[idfn[l]]=tr[p]=mx[p]=v;
		return;
	}
	if(pos<=mid) update(ls,l,mid,pos,v);
	else update(rs,mid+1,r,pos,v);
	tr[p]=tr[ls]+tr[rs];
	mx[p]=max(mx[ls],mx[rs]);
}

int q_sum(int p,int l,int r,int ql,int qr){
	//cout<<"q_sum: "<<p<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<"\n";
	if(ql<=l&&r<=qr) return tr[p];
	int res=0;
	if(ql<=mid) res+=q_sum(ls,l,mid,ql,qr);
	if(qr>mid) res+=q_sum(rs,mid+1,r,ql,qr);
	return res; 
}

int q_max(int p,int l,int r,int ql,int qr){
	//cout<<"q_max: "<<p<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<"\n";
	if(ql<=l&&r<=qr) return mx[p];
	int res=-inf;
	if(ql<=mid) res=q_max(ls,l,mid,ql,qr);
	if(qr>mid) res=max(res,q_max(rs,mid+1,r,ql,qr));
	return res; 
} 

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	fa[1]=dep[1]=1;
	for(int i=1;i<=n;i++) cin>>val[i];
	dfs1(1);
	dfs2(1,1);
	build(1,1,n);
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>str>>u>>v;
		if(str=="QMAX"){
			int ans=-inf;
			while(bel[u]!=bel[v]){
				if(dep[bel[u]]<dep[bel[v]]) swap(u,v);
				ans=max(ans,q_max(1,1,n,dfn[bel[u]],dfn[u]));
				u=fa[bel[u]];
			}
			if(dep[u]<dep[v]) swap(u,v);
			ans=max(ans,q_max(1,1,n,dfn[v],dfn[u])); 
			cout<<ans<<"\n";
		}else if(str=="QSUM"){
			int ans=0;
			while(bel[u]!=bel[v]){
				if(dep[bel[u]]<dep[bel[v]]) swap(u,v);
				ans+=q_sum(1,1,n,dfn[bel[u]],dfn[u]);
				u=fa[bel[u]];
			}
			if(dep[u]<dep[v]) swap(u,v);
			ans+=q_sum(1,1,n,dfn[v],dfn[u]);
			cout<<ans<<"\n"; 
		}else{
			update(1,1,n,dfn[u],v); 
		}
	}
	return 0;
}