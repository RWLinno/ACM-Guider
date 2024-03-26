//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=3e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

struct E{
	int v,w,nxt;
}e[N<<1];
int head[N],cnt=0;
inline void addedge(int u,int v,int w){e[++cnt]=(E){v,w,head[u]};head[u]=cnt;}

int fa[N],sz[N],son[N],dis[N],dep[N],dfn[N],idfn[N],bel[N],idx=0;
inline void dfs1(int x){
	for(int i=head[x];i;i=e[i].nxt){
		int to=e[i].v;
		if(to==fa[x]) continue;
		fa[to]=x;
		dep[to]=dep[x]+1;
		dis[to]=dis[x]+e[i].w;
		dfs1(to);
		sz[x]+=sz[to];
		if(sz[to]>sz[son[x]]) son[x]=to;
	}
}

inline void dfs2(int x,int tp){
	dfn[x]=++idx;
	idfn[idx]=x;
	bel[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i=head[x];i;i=e[i].nxt){
		int to=e[i].v;
		if(to==fa[x]||to==son[x]) continue;
		dfs2(to,to);
	}
}

inline int LCA(int u,int v){
	while(bel[u]!=bel[v]){
		if(dep[bel[u]]>dep[bel[v]]) u=fa[bel[u]];
		else v=fa[bel[v]];
	}
	return dep[u]<dep[v]?u:v;
}

inline int D(int a,int b){
	int x=idfn[a],y=idfn[b];
	return dis[x]+dis[y]-2*dis[LCA(x,y)];
}

int n,m;

void Solve(){
	cin>>n;
	for(int i=1,u,v,w;i<n;++i){
		cin>>u>>v>>w;
		addedge(u,v,w);
		addedge(v,u,w);
	}
	dfs1(1);
	dfs2(1,1);
	char op;
	int lca=0,ans=0;
	set<int>st; 
	cin>>m;
	//for(int i=1;i<=n;++i) cout<<i<<" "<<dfn[i]<<" "<<idfn[i]<<" dfn!!\n";
	for(int i=1,x;i<=m;++i){
		cin>>op;
		if(op=='+'){
			cin>>x;
			if(st.size()){
				auto it=st.lower_bound(dfn[x]);
				if(it==st.end()||it==st.begin()){
					auto pre=st.begin(),nxt=st.end();--nxt; //s.end()是空指针
					ans-=D(*pre,*nxt);
					ans+=D(dfn[x],*pre);
					ans+=D(dfn[x],*nxt); 
				}else{
					auto pre=it,nxt=it;--pre;
					ans-=D(*pre,*nxt);
					ans+=D(dfn[x],*pre);
					ans+=D(dfn[x],*nxt); 
				}
			}
			st.insert(dfn[x]);
		}else if(op=='-'){
			cin>>x;
			st.erase(dfn[x]);
			if(st.size()){
				auto it=st.lower_bound(dfn[x]);
				if(it==st.end()||it==st.begin()){
					auto pre=st.begin(),nxt=st.end();--nxt;
					ans-=D(dfn[x],*pre);
					ans-=D(dfn[x],*nxt);
					ans+=D(*pre,*nxt);
				}else{
					auto pre=it,nxt=it;--pre;
					ans-=D(dfn[x],*pre);
					ans-=D(dfn[x],*nxt);
					ans+=D(*pre,*nxt);
				}
			}
		}else{
			cout<<ans/2<<"\n";
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
//	cin>>T;
//	clock_t start,finish;
//	start=clock();
	while(T--){
		Solve();
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;
	return 0;
}