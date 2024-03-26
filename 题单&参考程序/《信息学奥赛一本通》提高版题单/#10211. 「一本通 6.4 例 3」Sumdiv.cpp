//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=9901;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int np[N],pri[N],cnt=0;

void init(){
	np[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]) pri[++cnt]=i;
		for(int j=1;j<=cnt&&pri[j]*i<N;j++){
			np[pri[j]*i]=1;
			if(i%pri[j]==0) break;
		}
	}
}

int fpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}

int inv(int x){return fpow(x,mod-2);}

int A,B,k,p[N],num[N];

void Solve(){
	cin>>A>>B;
	for(int i=1;i<=cnt;i++){
		if(A%pri[i]==0){
			p[++k]=pri[i];
			while(A%pri[i]==0){
				num[k]++;
				A/=pri[i];
			}
		}
	}
	if(A>1) p[++k]=A,num[k]=1;
	int ans=1;
	for(int i=1;i<=k;i++){
		ans=ans*(fpow(p[i],B*num[i]+1)-1)%mod;
		ans=ans*inv(p[i]-1)%mod;
	}
	cout<<ans;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	//cin>>T;
	init();
	while(T--){
		Solve();
	}
	return 0;
}