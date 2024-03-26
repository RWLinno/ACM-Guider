#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=1e7+7;
const int mod=1e9+7;
int cnt=0,pri[N],is_pri[N];
int n,f,a[N],ans=1;

void get_phi(int maxn){
	memset(is_pri,1,sizeof(is_pri));
	for(int i=2;i<=maxn;i++){
		if(is_pri[i]) pri[++cnt]=i;
		for(int j=1;j<=cnt&&pri[j]*i<=maxn;j++){
			is_pri[i*pri[j]]=0;
			if(i%pri[j]==0) break;
		}
	}
}	
 
signed main(){
	get_phi(1000000);
	cin>>n;
	for(int i=1;i<=cnt;i++){
		f=pri[i];
		while(f<=n){
			a[i]+=n/f,f*=pri[i];
		}
	}
	for(int i=1;i<=cnt;i++){
		ans=ans*(a[i]<<1|1),ans%=mod;
	}
	cout<<ans<<"\n";
	return 0;
}