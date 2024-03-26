#include<bits/stdc++.h>
using namespace std;
const int N=1e6+7;
typedef long long ll;

int n,tr[N][30],fail[N],cnt[N],tot=0;
vector<int>ed[N];
string a[205],ss;

void insert(string s){
	int p=0,len=s.length();
	for(int i=0;i<len;++i){
		int c=s[i]-'a';
		if(!tr[p][c]) tr[p][c]=++tot;
		p=tr[p][c];
	}
}

void build_fail(){
	int p=0; 
	queue<int>q;
	for(int i=0;i<27;++i) if(tr[p][i]) q.emplace(tr[p][i]);
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=0;i<27;++i){
			int y=tr[u][i];
			if(tr[u][i]){
				fail[tr[u][i]]=tr[fail[u]][i];
				q.emplace(tr[u][i]);
			}else tr[u][i]=tr[fail[u]][i];
		}
	}
	for(int i=1;i<=tot;++i) ed[fail[i]].emplace_back(i);
}

void dfs(int p){
	for(auto to:ed[p]){
		dfs(to);
		cnt[p]+=cnt[to];
	}
}

ll qry(string s){
	int p=0;
	for(int i=0;i<s.length();++i){
		p=tr[p][s[i]-'a'];
	}
	return cnt[p];
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); 
	cin>>n; 
	for(int i=1;i<=n;++i){
		cin>>a[i];
		insert(a[i]);
		ss+="{"+a[i];
	}
	build_fail();
	for(int i=0,p=0;i<ss.length();++i){
		p=tr[p][ss[i]-'a'];
		++cnt[p];
	}
	dfs(0);
	for(int i=1;i<=n;++i) printf("%lld\n",qry(a[i]));
	return 0;
}