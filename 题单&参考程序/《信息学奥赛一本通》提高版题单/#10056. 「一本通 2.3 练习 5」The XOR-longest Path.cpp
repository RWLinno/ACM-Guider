#include<bits/stdc++.h>
#define mk make_pair
#define pii pair<int,int>
#define F first
#define S second 
using namespace std;
const int N=2e6+7;

int n,m,d[N];
vector<pii>G[N];
int cnt[N],tr[N][2],ed[N],idx=0;

void dfs(int x,int f,int dis){
	d[x]=dis;
	for(auto p:G[x]){
		int to=p.F,w=p.S;
		if(to!=f) dfs(to,x,dis^w);
	}
}

void insert(int val){
	int p=0;++cnt[0];
	for(int i=30;i>=0;--i){
		int c=((val>>i)&1);
		if(!tr[p][c]) tr[p][c]=++idx;
		p=tr[p][c];
		++cnt[p];
	}
	ed[p]=val;
}

int query(int val){
	int p=0,mx=0;
	for(int i=30;i>=0;--i){
		int c=((val>>i)&1);
		if(tr[p][c^1]) p=tr[p][c^1],mx|=(1<<i);
		else p=tr[p][c];
	}
	return mx;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1,u,v,w;i<n;++i){
		cin>>u>>v>>w;
		G[u].emplace_back(mk(v,w));
		G[v].emplace_back(mk(u,w));
	}
	dfs(1,0,0);
	int ans=0;
	for(int i=1;i<=n;++i){
		ans=max(ans,query(d[i]));
		insert(d[i]);
	}
	cout<<ans<<"\n";
	return 0;
}