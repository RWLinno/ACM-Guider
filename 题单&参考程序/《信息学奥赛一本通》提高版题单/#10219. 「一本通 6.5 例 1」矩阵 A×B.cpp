//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,m,p;

struct Matrix{
	int r,c,m[105][105];
	Matrix(){memset(m,0,sizeof(m));}
};

Matrix operator * (Matrix a,Matrix b){
	Matrix res;
	res.r=a.r;res.c=b.c;
	for(int i=1;i<=a.r;i++){
		for(int j=1;j<=a.c;j++){
			for(int k=1;k<=b.c;k++){
				res.m[i][k]+=a.m[i][j]*b.m[j][k];
			}
		}
	}
	return res;
}


signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	cin>>n>>m;
	Matrix A,B; 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>A.m[i][j];
		}
	}
	cin>>p;
	A.r=n,A.c=m;B.r=m,B.c=p;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=p;j++){
			cin>>B.m[i][j];
		}
	}
	Matrix C=A*B;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=p;j++){
			cout<<C.m[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}