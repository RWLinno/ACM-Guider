#include<bits/stdc++.h>
using namespace std;
const int N=2e6+7;

int n,m,idx=0,tr[N][2],ed[N],cnt[N],vt[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1,k;i<=n;++i){
		cin>>k;
		int p=0;;
		for(int j=1,x;j<=k;++j){
			cin>>x;
			if(!tr[p][x]) tr[p][x]=++idx;
			p=tr[p][x];
			++cnt[p];
		}
		++ed[p]; //在这个结点结尾的结点 
	}
	for(int i=1,k;i<=m;++i){
		cin>>k;
		int p=0,ans=0,flag=1;
		for(int j=1;j<=k;++j) cin>>vt[j];
		for(int j=1,x;j<=k;++j){
			x=vt[j];
			if(!tr[p][x]){
				flag=0;
				break;
			}
			p=tr[p][x];
			ans+=ed[p];
		}
		if(flag) ans=ans+cnt[p]-ed[p]; 
		cout<<ans<<"\n";
	}
	return 0; 
}