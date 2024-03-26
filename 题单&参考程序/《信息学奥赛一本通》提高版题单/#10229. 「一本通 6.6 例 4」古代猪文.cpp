#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+7;
const int mod=999911658;
const int b[]={2,3,4679,35617}; 
int n,G,ans=0,frac[N],a[5];

inline int fpow(int a,int b,int p){
	int res=1;
	while(b){
		if(b&1) res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
	return res;
}

inline int Comb(int n,int m,int p){
	if(n<m) return 0;
	return frac[n]*fpow(frac[m],p-2,p)%p*fpow(frac[n-m],p-2,p)%p;
}

inline int Lucas(int n,int m,int p){
	if(n<m) return 0;
	if(!n) return 1ll;
	return Comb(n%p,m%p,p)*Lucas(n/p,m/p,p)%p;
}

void CRT(){
	for(int i=0;i<4;++i){
		ans=(ans+a[i]*(mod/b[i])%mod*fpow(mod/b[i],b[i]-2,b[i]))%mod;
	}
}

signed main(){
	scanf("%lld%lld",&n,&G);
	if(G%(mod+1)==0){  
		printf("0\n");
		return 0;
	}
	for(int k=0;k<4;++k){
		frac[0]=1;for(int i=1;i<=b[k];++i) frac[i]=frac[i-1]*i%b[k];
		for(int i=1;i*i<=n;++i){
			if(n%i==0){
				a[k]=(a[k]+Lucas(n,i,b[k]))%b[k];
				if(i*i!=n) a[k]=(a[k]+Lucas(n,n/i,b[k]))%b[k];
			}
		}
	}
	CRT();
	printf("%lld\n",fpow(G,ans,mod+1));
	return 0;
}