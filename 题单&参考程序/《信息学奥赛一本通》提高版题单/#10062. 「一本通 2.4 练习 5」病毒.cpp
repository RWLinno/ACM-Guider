#include<bits/stdc++.h>
using namespace std;
const int N=3e5+7;

int n,idx=0,tr[N][2],fail[N],ed[N],vis[N],ins[N];
char str[N];

inline void insert(char *s){
	int p=0,len=strlen(s);
	for(int i=0;i<len;++i){
		int c=s[i]-'0';
		if(!tr[p][c]) tr[p][c]=++idx;
		p=tr[p][c];
	}
	ed[p]=1;
}

void build(){
	queue<int>q;
	if(tr[0][0]) q.emplace(tr[0][0]);
	if(tr[0][1]) q.emplace(tr[0][1]);
	while(q.size()){
		int p=q.front();
		q.pop();
		for(int i=0;i<=1;++i){
			if(tr[p][i]){
				fail[tr[p][i]]=tr[fail[p]][i];
				ed[tr[p][i]]|=ed[fail[tr[p][i]]];
				q.emplace(tr[p][i]);
			}else tr[p][i]=tr[fail[p]][i];
		}
	}
}

void dfs(int p){
	if(ins[p]){puts("TAK");exit(0);}
	if(vis[p]||ed[p]) return;
	vis[p]=ins[p]=1;
	dfs(tr[p][0]);
	dfs(tr[p][1]);
	ins[p]=0;
}

signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%s",str);
		insert(str);
	}
	build();
	dfs(0);
	puts("NIE");
	return 0;
}