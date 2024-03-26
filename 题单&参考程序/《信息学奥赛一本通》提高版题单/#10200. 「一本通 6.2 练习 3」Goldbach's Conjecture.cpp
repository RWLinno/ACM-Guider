#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=1e7+7;
const int maxn=1e5+7;
const int mod=1e9+7;

int cnt,flag[N],phi[N],p[N];
void Get_phi(int maxn){
	cnt=0;
	memset(flag,1,sizeof(flag));
	phi[1]=1;
	for(int i=2;i<maxn;i++){
		if(flag[i]){
			p[cnt++]=i;
			phi[i]=i-1;
		}
		for(int j=0;j<cnt;j++){
			if(i*p[j]>maxn) break;
			flag[i*p[j]]=false;
			if(i%p[j]==0){
				phi[i*p[j]]=p[j]*phi[i];
				break;
			}else phi[i*p[j]]=(p[j]-1)*phi[i];
		}
	}
}	
 
int n,a[maxn],ans[maxn];
map<int,int>mp;

signed main(){
	Get_phi(10000000); 
	cin>>n;
	while(n){
		for(int i=0;i<cnt;i++){
			if(flag[n-p[i]]){
				cout<<n<<" = "<<p[i]<<" + "<<n-p[i]<<"\n";
				break;
			}
		}
		cin>>n;
	}
	return 0;
}