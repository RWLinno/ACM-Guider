#include<bits/stdc++.h>
using namespace std;

int a[20]; 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	for(int t=1,n;t<=10;++t){
		cin>>n;
		for(int i=0;i<n;++i) cin>>a[i]; 
		int res,flag=0;
		for(int s=1;s<=(1<<n)-1;++s){ //枚举巧克力棒子集 
			res=0;
			for(int j=0;j<n;++j){
				if(s&(1<<j)) res^=a[j];
			}
			if(!res){
				flag=1;
				break;
			}
		}
		if(!flag) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}