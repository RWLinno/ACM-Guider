#include<bits/stdc++.h>
using namespace std;
const int N=1e3+7;

int tr[N][2],ed[N],cnt[N],tot=0;
string str;

void insert(string s){
	int p=0,len=s.length();
	++cnt[0];
	for(int i=0;i<len;++i){
		int c=s[i]-'0';
		if(!tr[p][c]) tr[p][c]=++tot;
		p=tr[p][c];
		++cnt[p];
	}
	++ed[p];
}

bool check(int p){
	int f=1;
	if(tr[p][0]) f&=check(tr[p][0]);
	if(tr[p][1]) f&=check(tr[p][1]);
	if(cnt[p]>=2&&ed[p]) f=0;
	tr[p][0]=tr[p][1]=cnt[p]=ed[p]=0; //清空 
	return f;
}

signed main(){
	int idx=0;
	while(cin>>str){
		++idx;tot=0; 
		while(str!="9"){
			insert(str);
			cin>>str;
		}
		if(check(0)) cout<<"Set "<<idx<<" is immediately decodable"<<"\n";
		else cout<<"Set "<<idx<<" is not immediately decodable"<<"\n";
	}
	return 0;
}