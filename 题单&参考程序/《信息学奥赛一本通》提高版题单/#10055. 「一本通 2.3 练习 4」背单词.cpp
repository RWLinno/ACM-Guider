#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
typedef long long ll;
const int N=2e6+7,M=1e5+7;

ll ans=0;
char str[N];
int n,cnt,ed[N],tot=1,tr[N][28],fa[N],id[N],sz[N],num;
vector<int>G[N];

int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x;
}

int find(int x){
	return (fa[x]==x)?x:fa[x]=find(fa[x]);
}

void insert(char *s,int bh){
	int len=strlen(s),p=1;
	for(int i=len-1;i>=0;--i){
		int c=s[i]-'a';
		if(!tr[p][c]) tr[p][c]=++tot;
		p=tr[p][c];
	}
	ed[p]=bh;
}

void make(int x){
	for(int i=0;i<26;++i){
		int v=tr[x][i];
		if(v){
			if(!ed[v]) fa[v]=find(x);
			else{
				G[ed[find(x)]].pb(ed[v]);
			}
			make(v);
		}
	}
}

int cmp(int x,int y){
	return sz[x]<sz[y];
}

void dfs1(int x){
	sz[x]=1;
	for(auto v:G[x]){
		dfs1(v);
		sz[x]+=sz[v];
	}
	sort(G[x].begin(),G[x].end(),cmp);
}

void dfs2(int x){
	id[x]=num++;
	for(auto to:G[x]){
		ans+=num-id[x];
		dfs2(to);
	}
}

signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		scanf("%s",str);
		insert(str,i);
	}	
	for(int i=1;i<=tot;++i) fa[i]=i;
	make(1);
	dfs1(0);
	dfs2(0);
	printf("%lld\n",ans);
	return 0;
}