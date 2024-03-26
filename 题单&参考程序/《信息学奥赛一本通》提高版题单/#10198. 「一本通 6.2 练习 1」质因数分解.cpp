#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=1e7+7;
int n;

signed main(){
	cin>>n;
	for(int i=2;i<n;i++){
		if(n%i==0){
			cout<<n/i<<endl;
			return 0;
		}
	} 
	return 0;
}