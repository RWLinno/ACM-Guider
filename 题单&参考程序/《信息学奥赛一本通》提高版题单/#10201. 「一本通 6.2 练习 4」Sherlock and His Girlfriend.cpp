#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=1e7+7;
int cnt=0,pri[N],is_pri[N];
int n,vis[N],col[N],ans=0;

void get_phi(int maxn){
	memset(is_pri,1,sizeof(is_pri));
	for(int i=2;i<=maxn;i++){
		if(is_pri[i]) pri[++cnt]=i,col[i]=1;
		for(int j=1;j<=cnt&&pri[j]*i<=maxn;j++){
			is_pri[i*pri[j]]=0;
			col[i*pri[j]]=j+1;
			if(i%pri[j]==0) break;
		}
	}
}	
 
signed main(){
	get_phi(1000000);
	cin>>n;
	
	cout<<((n<3)?1:2)<<"\n";
	for(int i=2;i<=n+1;i++) cout<<(is_pri[i]?1:2)<<" ";
	return 0;
}