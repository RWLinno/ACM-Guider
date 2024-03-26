#include<bits/stdc++.h>
using namespace std;
const int N=1e6+7;

int n;
char str[N];

namespace AC{
	const int SZ=(N<<1); 
	int tot=0,tr[SZ][30];
	int fail[SZ],ed[SZ]; 
	queue<int>q;
	void clear(){
		memset(fail,0,sizeof(fail));
		memset(ed,0,sizeof(ed));
		memset(tr,0,sizeof(tr));
		while(q.size()) q.pop();
		tot=0;
	}
	void insert(char *s){
		int p=0,len=strlen(s);
		for(int i=0;i<len;i++){
			int c=s[i]-'a';
			if(!tr[p][c]) tr[p][c]=++tot;
			p=tr[p][c];
		}
		++ed[p];
	}
	void build_fail(){
		for(int i=0;i<26;++i) if(tr[0][i]) q.emplace(tr[0][i]),fail[tr[0][i]]=0;
		while(q.size()){
			int u=q.front();
			q.pop();
			for(int i=0;i<26;++i){
				int y=tr[u][i];
				if(y){
					fail[y]=tr[fail[u]][i];
					q.emplace(y);
				}else tr[u][i]=tr[fail[u]][i];
			}
		}
	}
	int query(char *s){ //查询文章中一共有多少个出现过的单词 
		int p=0,ans=0,len=strlen(s);
		for(int i=0,y;i<len;++i){
			int c=s[i]-'a';
			p=y=tr[p][c];
			while(y){
				ans+=ed[y];
				ed[y]=0;
				y=fail[y];
			}
		}
		return ans;
	}
}
using namespace AC; 

void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%s",str);
		insert(str);
	}
	build_fail();
	scanf("%s",str);
	printf("%d\n",query(str));
	clear();
}

signed main(){
	int T=1; 
	scanf("%d",&T);
	while(T--){
		solve();
	}
	return 0;
}