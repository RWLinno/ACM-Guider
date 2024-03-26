#include<bits/stdc++.h>
using namespace std;

const int N=1e5+7,M=1e5+7;
int n,m,F[200],pos[N][105];
char S[N*100],T[N][105];

struct ACAM{
	int tr[N*100][4],fail[N*100],tg[N*100],ed[N*100],idx=0;
	queue<int>q;
	void insert(char *s,int id){
		int p=0,len=strlen(s);
		for(int i=0,c;i<len;++i){
			c=F[s[i]];
			if(!tr[p][c]) tr[p][c]=++idx;
			pos[id][i]=p=tr[p][c];
		}
		++ed[id];
	}
	void build_fail(){
		for(int i=0;i<4;++i) if(tr[0][i]) q.emplace(tr[0][i]),fail[tr[0][i]]=0;
		while(q.size()){
			int u=q.front();
			q.pop();
			for(int i=0;i<4;++i){
				int y=tr[u][i];
				if(y){
					fail[y]=tr[fail[u]][i];
					q.emplace(y);
				} else tr[u][i]=tr[fail[u]][i];
			}
		}
	}
	void query(char *s){
		int p=0,len=strlen(s);
		for(int i=0;i<len;++i){
			int c=F[s[i]]; 
			p=tr[p][c];
			for(int j=p;j&&!tg[j];j=fail[j]) tg[j]=1;
		}
	}
}AC;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	F['E']=0,F['S']=1;F['W']=2,F['N']=3;
	cin>>n>>m>>S;
	for(int i=1;i<=m;++i){
		cin>>T[i];
		AC.insert(T[i],i);
	}
	AC.build_fail();
	AC.query(S);
	for(int i=1;i<=m;++i){
		int res=0,len=strlen(T[i]);
		for(int j=len-1;j>=0;--j){
			if(AC.tg[pos[i][j]]){
				res=j+1;
				break;
			}
		}
		cout<<res<<"\n";
	}
}