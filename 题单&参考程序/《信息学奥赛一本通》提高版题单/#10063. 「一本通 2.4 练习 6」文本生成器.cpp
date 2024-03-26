#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
const int mod=1e4+7;

int ch[N][26],ed[N],fail[N];
int n,m,sz,dp[105][N],ans;
char s[N];
queue<int>q;

void insert(char s[]){
	int now=0,len=strlen(s);
	for(int i=0;i<len;++i){
		int x=s[i]-'A';
		if(!ch[now][x]) ch[now][x]=++sz;
		now=ch[now][x]; 
	}
	ed[now]|=1;
}

void build_fail(){
	for(int i=0;i<26;++i) if(ch[0][i]) q.emplace(ch[0][i]);
	while(q.size()){
		int fro=q.front();
		q.pop();
		for(int i=0;i<26;++i){
			if(!ch[fro][i]){
				ch[fro][i]=ch[fail[fro]][i];
				continue;
			}
			ed[ch[fro][i]]|=ed[ch[fail[fro]][i]];
			fail[ch[fro][i]]=ch[fail[fro]][i];
			q.emplace(ch[fro][i]);
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>s;
		insert(s);
	}
	build_fail();
	dp[0][0]=1;
	for(int i=1;i<=m;++i){
		for(int j=0;j<=sz;++j){
			for(int k=0;k<26;++k){
				if(!ed[ch[j][k]]) dp[i][ch[j][k]]=(dp[i][ch[j][k]]+dp[i-1][j])%mod;
			}
		}
	}
	for(int i=0;i<=sz;++i) ans=(ans+dp[m][i])%mod;
	int sum=1;
	for(int i=1;i<=m;++i) sum=sum*26ll%mod;
	cout<<(sum-ans+mod)%mod<<"\n";
	return 0;
}