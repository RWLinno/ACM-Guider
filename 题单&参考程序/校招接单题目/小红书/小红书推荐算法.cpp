#include<bits/stdc++.h>
using namespace std;
const int N=3e5+7;

string str,tag;
map<string,bool>mp;
int n,q;

struct G{
	string name;
	int num,sc,id;
	bool operator <(const G tmp){
		if(sc==tmp.sc) return sc < tmp.sc;
		return sc > tmp.sc; 
	}
}good[N];

signed main(){
	cin>>n>>q;
	for(int i=1;i<=q;++i){
		cin>>str;
		mp[str]=1;
	}
	for(int i=1;i<=n;++i){
		cin>>good[i].name>>good[i].num;
		good[i].sc = 0; good[i].id = i;
		for(int j=1;j<=good[i].num;++j){
			cin>>tag;
			if(mp.count(tag)) ++good[i].sc;
		}
	}
	sort(good+1,good+1+n);
	for(int i=1;i<=n;++i) cout<<good[i].name<<"\n";
	return 0;
}

/*
2 5
red book game music sigma
mozart 3
book classic music
arcaea 4
red music game hard 
*/
