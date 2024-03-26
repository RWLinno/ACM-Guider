//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7,M=100;
const int mod=2009;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

int n,m,t;

struct Matrix{
	int c[M][M];
	Matrix(int x=0){
		memset(c,0,sizeof(c));
		for(int j=0;j<M;++j) c[j][j]=x;	
	}
	Matrix operator *(const Matrix &B)const{
		Matrix res;
		for(int i=0;i<M;++i){
			for(int j=0;j<M;++j){
				for(int k=0;k<M;++k){
					res.c[i][j]+=c[i][k]*B.c[k][j];
					res.c[i][j]%=mod;
				}
			}
		}
		return res;
	}
	Matrix operator ^(int b)const{
		Matrix res(1),a=*this;
		while(b){
			if(b&1) res=res*a;
			a=a*a;
			b>>=1; 
		}
		return res;
	}
};


void Solve(){
	scanf("%d%d",&n,&t);
	m=9*n;
	Matrix ans,bas;
	int tmp;
	for(int i=1;i<=n;++i){
		for(int j=1;j<9;++j){
			bas.c[(i-1)*9+j][(i-1)*9+j+1]=1;//连接拆点 
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			scanf("%1d",&tmp);
			if(tmp) bas.c[(i-1)*9+tmp][(j-1)*9+1]=1;
		}
	}
	ans=(bas^t);
	printf("%d\n",ans.c[1][m-8]);
	return;
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
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