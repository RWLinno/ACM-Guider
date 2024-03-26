//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,mod=10000;

struct Matrix{
	int c[2][2];
	Matrix(){memset(c,0,sizeof(c));}
	Matrix operator *(Matrix a){
		Matrix res;
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				for(int k=0;k<2;k++){
					res.c[i][j]+=c[i][k]*a.c[k][j];
					res.c[i][j]%=mod;				
				}
			}
		}
		return res;
	}
};


inline Matrix mfpow(Matrix a,int b){
	Matrix res;
	res.c[0][0]=res.c[1][1]=1;
	while(b){
		if(b&1) res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
} 

int s(int x){
	if(x==0) return 0;
	if(x==1) return 1;
	if(x==2) return 1;
}

void Solve(){
	Matrix ans,bs;
	ans.c[0][0]=1;ans.c[1][0]=1;
	bs.c[0][0]=bs.c[0][1]=bs.c[1][0]=1;
	if(n<2){
		cout<<s(n)<<"\n";
		return;
	} 
	ans=mfpow(bs,n-2)*ans;
	cout<<ans.c[0][0]<<"\n";
	return;
}


signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	int T=1;
	//cin>>T;
	while(1){
		cin>>n;
		if(n==-1) break;
		Solve();
	}
	return 0;
}