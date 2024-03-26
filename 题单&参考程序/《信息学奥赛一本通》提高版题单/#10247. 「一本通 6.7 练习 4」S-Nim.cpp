#include<bits/stdc++.h>
using namespace std;
const int N=1e4+7;

int k,n,m,a[105],s[105],sg[N];
bool vis[N];

void get_sg(){
	sg[0]=0;
	for(int i=1;i<=10000;++i){
		memset(vis,0,sizeof(vis));
		for(int j=1;j<=k;++j){
			if(i-s[j]>=0) vis[sg[i-s[j]]]=1;
		}
		int j=0;
		while(vis[j]) j++;
		sg[i]=j;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	while(cin>>k){
		if(!k) break;
		for(int i=1;i<=k;++i){
			cin>>s[i];
		}
		get_sg();
		string ans="";
		cin>>m;
		for(int i=1;i<=m;++i){
			cin>>n;
			int res=0;
			for(int i=1;i<=n;++i) cin>>a[i],res^=sg[a[i]];
			if(res) ans+="W";
			else ans+="L"; 	
		}
		cout<<ans<<"\n";
	} 
	return 0;
} 