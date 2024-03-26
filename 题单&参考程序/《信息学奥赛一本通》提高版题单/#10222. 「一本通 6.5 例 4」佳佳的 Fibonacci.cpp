//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
int n,m;

struct Matrix{
	int c[4][4];
	Matrix(){memset(c,0,sizeof(c));}
	Matrix(int x){memset(c,0,sizeof(c));for(int i=0;i<x;++i) c[i][i]=1;}
	Matrix operator *(Matrix B)const{
		Matrix res;
		for(int i=0;i<4;++i){
			for(int j=0;j<4;++j){
				for(int k=0;k<4;++k){
					res.c[i][j]+=c[i][k]*B.c[k][j];
					res.c[i][j]%=m;
				} 
			}
		} 
		return res;
	}
};

inline Matrix fpow(Matrix a,int b){
	Matrix res(4);
	while(b){
		if(b&1) res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}

void Solve(){
	cin>>n>>m;
	Matrix bas,res;
	res.c[0][0]=1;res.c[1][0]=1;res.c[2][0]=1;res.c[3][0]=0;
	bas.c[0][0]=bas.c[0][1]=bas.c[1][0]=bas.c[2][0]=bas.c[2][2]=bas.c[3][2]=bas.c[3][3]=1;
	res=fpow(bas,n-1)*res;
	//cout<<res.c[0][0]<<" "<<res.c[1][0]<<" "<<res.c[2][0]<<" "<<res.c[3][0]<<" !!\n";
	int ans=(n*res.c[2][0]-res.c[3][0]+m)%m;
	cout<<ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
//	cin>>T;
//	clock_t start,finish;
//	start=clock();
	while(T--){
		Solve();
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;
	return 0;
}