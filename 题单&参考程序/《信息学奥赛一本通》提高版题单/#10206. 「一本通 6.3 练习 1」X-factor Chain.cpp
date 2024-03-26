//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e6+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int np[N],pri[N],frac[150],cnt=0;
int ans[N],sum[N],sz[N],num[N];

void init(){
	np[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]) pri[++cnt]=i;
		for(int j=1;j<=cnt&&pri[j]*i<N;j++){
			np[i*pri[j]]=1;
			if(i%pri[j]==0) break; 
		}
	}
}

inline int _A(int x){return frac[x];}

inline void Solve(int x){
	int tot=0,n=x;
	if(sum[n]&&ans[n]){
		cout<<sum[n]<<" "<<ans[n]<<"\n";
		return;
	}
	for(int i=1;i<=cnt&&pri[i]*pri[i]<=x;i++){
		if(x%pri[i]==0){
			num[++tot]=pri[i];
			while(x%pri[i]==0) x/=pri[i],sz[tot]++;
			
		}
	}
	if(x>1) num[++tot]=x,sz[tot]=1;
	for(int i=1;i<=tot;i++)	sum[n]+=sz[i];
	ans[n]=_A(sum[n]);
	for(int i=1;i<=tot;i++) ans[n]/=_A(sz[i]);
	for(int i=1;i<=tot;i++) sz[i]=num[i]=0;
	cout<<sum[n]<<" "<<ans[n]<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	init();
	frac[0]=1;for(int i=1;i<100;i++) frac[i]=frac[i-1]*i; 
	memset(ans,0,sizeof(ans));
	memset(sum,0,sizeof(sum));
	int T=1;
	while(cin>>T){
		Solve(T);
	}
	return 0;
}