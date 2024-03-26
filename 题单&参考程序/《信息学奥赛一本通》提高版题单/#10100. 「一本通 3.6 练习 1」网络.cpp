//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
using namespace std;
const int N=107;
const int mod=1e9+7;

int read(int &data){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	data=x;
	if(ch=='\n') return 0; 
	return 1;
}

int st,n,rt,ans,tmp,flag;
char ch;
vector<int>G[N];

int dfn[N],bel[N],low[N],idx=0;
int is[N],vis[N],stk[N],top=0;

inline void tarjan(int x){
	dfn[x]=low[x]=++idx;
	vis[x]=1;
	stk[++top]=x;
	int col=0,cut=1;
	for(auto to:G[x]){
		if(!dfn[to]){
			col++;
			tarjan(to);
			low[x]=min(low[x],low[to]);
			if(x==rt&&col>1||x!=rt&&low[to]>=dfn[x]) is[x]=1;
		}else if(vis[to]) low[x]=min(low[x],dfn[to]);
	}
	/*
	if(dfn[x]==low[x]){
		int y;
		while(y=stk[top--]){
			bel[y]=x;
			vis[y]=0;
			if(x==y) break;
		}
	}*/
}

void Solve(){
//	for(int i=1;i<=n;i++) bel[i]=i;
	memset(vis,0,sizeof(vis));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(is,0,sizeof(is));
	top=0;idx=0;ans=0;
	while(1){
		cin>>st;
		if(st==0) break;
		else{
			while(1){
				flag=read(tmp);
				G[st].push_back(tmp);
				G[tmp].push_back(st);
				if(!flag) break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			rt=i;
			tarjan(i);
		}
	}
	for(int i=1;i<=n;i++){
		if(is[i]) ans++;
		G[i].clear();
	}
	cout<<ans<<" \n";
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	cin>>n;
	while(n){
		Solve();
		cin>>n;
	}
	return 0;
}