#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7;

int n,tr[N][30],fail[N],ed[N],tot=0;
int stk[N],f[N],top;
char S[N],T[N];

void insert(char *s){
	int p=0,len=strlen(s);
	for(int i=0;i<len;++i){
		int c=s[i]-'a';
		if(!tr[p][c]) tr[p][c]=++tot;
		p=tr[p][c];
	}
	ed[p]=len;
}

void build_fail(){
	int p=0; 
	queue<int>q;
	for(int i=0;i<26;++i) if(tr[p][i]) q.emplace(tr[p][i]),fail[tr[p][i]]=0;
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=0;i<26;++i){
			int y=tr[u][i];
			if(tr[u][i]){
				fail[tr[u][i]]=tr[fail[u]][i];
				q.emplace(tr[u][i]);
			}else tr[u][i]=tr[fail[u]][i];
		}
	}
}

void solve(char *s){
//stk记录为记录答案字符串的栈,f记录字符串每个位置对应AC自动机上的结点 
	int p=0,len=strlen(s);
	for(int i=0;i<len;++i){
		int c=s[i]-'a';
		p=tr[p][c];
		stk[++top]=i,f[i]=p;
		if(ed[p]){
			top-=ed[p];
			p=f[stk[top]];
		} 
	} 
}

signed main(){
	scanf("%s",S);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%s",T);
		insert(T); 
	}
	build_fail();
	solve(S);
	for(int i=1;i<=top;++i) printf("%c",S[stk[i]]);
	return 0;
}