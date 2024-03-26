//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,mod;

struct Matrix{
	int c[3][3];
	Matrix(){memset(c,0,sizeof(c));}
	Matrix operator *(Matrix a){
		Matrix res;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				for(int k=0;k<3;k++){
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
	res.c[0][0]=res.c[1][1]=1;res.c[2][2]=1;
	while(b){
		if(b&1) res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
} 

void Solve(){
	cin>>n>>mod;
	Matrix ans,bs;
	ans.c[0][0]=2;ans.c[1][0]=1,ans.c[2][0]=1;
	bs.c[0][0]=bs.c[0][1]=bs.c[0][2]=1;
	bs.c[1][0]=bs.c[2][2]=1;
	ans=mfpow(bs,n-2)*ans;
	cout<<ans.c[0][0]<<"\n";
	return;
}


signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}