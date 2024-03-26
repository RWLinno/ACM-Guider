#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=2e5+7;

inline int fpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	} 
	return res;
}

int n; 

inline int inv(int x){return fpow(x,mod-2);}

signed main(){
	cin>>n;
	int sum=0,odd=0,E=0, di=inv(fpow(2,n));
	for(int i=1,a;i<=n;++i){
		cin>>a;
		sum=(sum+a)%mod;
		odd+=(a%2);
	}
	E = n*odd%mod*inv(n-odd)%mod;
	cout<<(sum*E)%mod<<"\n";
	return 0;
} 

/*
ans = sum+期望多加的点赞数e
k = odd,odd+2,..odd+4,... 
e = lim k*(odd^k)/n^k+(k+2)*(odd^(k+2))/n^(k+2)+...
1*x+3*x^3+...5*x^5,+ 
 = 
 
 2
 1 2
 
 6
*/
