#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7;

int n,m,mx,vis[N],sg[N],a[N],b[N],c[N];

void get_SG(){
	sg[0]=0;
	for(int i=1;i<=mx;++i){
		int ma=-1;
		memset(vis,0,sizeof(vis));
		for(int j=1;j<=m&&(i-b[j])>=0;++j){
			vis[sg[i-b[j]]]=1;
			ma=max(ma,sg[i-b[j]]);
		}
		int j=0;
		while(vis[j]) ++j; 
		sg[i]=j; 
	}
}

int tmp[15];
bool check(int x,int y){
	for(int i=1;i<=n;++i) tmp[i]=a[i];
	tmp[x]-=y;
	int ans=0;
	for(int i=1;i<=n;++i) ans^=sg[tmp[i]];
	if(ans) return false;
	else return true;
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i],mx=max(mx,a[i]);	
	cin>>m;
	for(int i=1;i<=m;++i) cin>>b[i],c[b[i]]=1;
	get_SG();
	int ans=0;
	for(int i=1;i<=n;++i) ans^=sg[a[i]];
	if(!ans) cout<<"NO\n";
	else{
		cout<<"YES\n";
		bool flag=0;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=a[i];++j){
				if(check(i,j)&&c[j]){
					flag=1;
					cout<<i<<" "<<j<<"\n";
					break;
				}
			}
			if(flag) break;
		}
	}
	return 0;
}