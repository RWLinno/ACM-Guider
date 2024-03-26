//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int L,R,k,b,ans=0;
int num=0; //记录位数 
vector<int>vt;

void Solve(){
	cin>>L>>R;
	cin>>k>>b;
	int lim=1;
	while(lim<R) lim*=b,num++;
	for(int i=1;i<=num-k;i++) vt.push_back(0);
	for(int i=1;i<=k;i++) vt.push_back(1);
	do{
		int tmp=0;
		for(int i=0;i<num;i++){
			tmp*=b;
			if(vt[i]==1) tmp++;
		}
		if(L<=tmp&&tmp<=R) ans++;
	}while(next_permutation(vt.begin(),vt.end()));	
	/*
	for(int i=L;i<=R;i++){
		int res=0,tmp=i;
		while(tmp){
			if(tmp&1) res++;
			tmp/=b;
		}
		if(res==k) ans++;
	}*/
	cout<<ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}