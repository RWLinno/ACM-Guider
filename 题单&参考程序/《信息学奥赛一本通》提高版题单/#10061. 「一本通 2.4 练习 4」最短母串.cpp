#include<bits/stdc++.h>
#define mk make_pair
#define pii pair<int,int>
#define F first
#define S second
using namespace std;
const int N=605;
int n,tr[N][30],fail[N],idx=0;
int st[N],mx,nod,tot,fa[N*(1<<12|1)],ans[N*(1<<12|1)];
bool vis[N][1<<12|1];
string str;
char C[N]; 

void insert(string s,int id){
	int p=0,len=s.length();
	for(int i=0;i<len;++i){
		int c=s[i]-'A';
		if(!tr[p][c]) tr[p][c]=++idx;
		p=tr[p][c];
	}
	st[p]|=(1<<(id-1));
}

void build(){
	int p=0; 
	queue<int>q;
	for(int i=0;i<26;++i) if(tr[p][i]) q.emplace(tr[p][i]);
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=0;i<26;++i){
			int y=tr[u][i];
			if(tr[u][i]){
				fail[tr[u][i]]=tr[fail[u]][i];
				st[tr[u][i]]|=st[tr[fail[u]][i]]; //它的fail指针包含的字符串它也包含 
				q.emplace(tr[u][i]);
			}else tr[u][i]=tr[fail[u]][i];
		}
	}
}

void bfs(){
	queue<pii>q;
	//first:在trie中的位置;second:状态压缩，表示包含了哪些要求的字符串 
	q.emplace(mk(0,0));
	vis[0][0]=1;int ti=0;
	while(q.size()){
		int now=q.front().F,s=q.front().S;
		q.pop();
		if(s==mx){
			while(ti){
				C[++nod]=ans[ti]; 
				ti=fa[ti];
			} //递归回去求答案 
			for(int i=nod;i>0;--i) putchar(C[i]+'A'); 
			return; 
		} 
		for(int i=0;i<26;++i){
			if(!vis[tr[now][i]][s|st[tr[now][i]]]){
				vis[tr[now][i]][s|st[tr[now][i]]]=1;
				q.emplace(mk(tr[now][i],(s|st[tr[now][i]])));
				fa[++tot]=ti;ans[tot]=i; //记录当前搜到的字符，建一棵关于答案的树，便于最后查询 
			}
		}
		++ti; //表示当前搜到的编号 
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); 
	cin>>n; 
	mx=(1<<n)-1;
	for(int i=1;i<=n;++i){
		cin>>str;
		insert(str,i);
	}
	build();
	bfs();
	return 0;
}