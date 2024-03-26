// dp+kmp+矩阵快速幂 
//dp[i][j]=\sum_{k=0}^{m-1} dp[i-1][k]*b[k][j]
//dp[i][j]表示文本串s前i位的后j位与模式串的前j位匹配上的方案数
//ans=\sum_{j=0}^{m-1}dp[n][j] 
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
int n,m,p,nxt[N];
char s[N];

struct Matrix{
	int c[25][25];
	Matrix(int x=0){memset(c,0,sizeof(c));for(int i=0;i<x;++i) c[i][i]=1;}
	Matrix operator *(Matrix B)const{
		Matrix res;
		for(int i=0;i<m;i++){
			for(int j=0;j<m;++j){
				for(int k=0;k<m;++k){
					res.c[i][j]+=c[i][k]*B.c[k][j];
					res.c[i][j]%=p;
				}
			}
		}
		return res;
	}
};

inline Matrix fpow(Matrix a,int b){
	Matrix res(m);
	while(b){
		if(b&1) res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}

void Solve(){
	scanf("%lld%lld%lld",&n,&m,&p);
	scanf("%s",s+1);
	Matrix ans,bas;
	nxt[1]=0;
	int pre=0,slen=strlen(s+1);
	for(int i=2;i<=slen;++i){
		while(pre&&s[pre+1]!=s[i]) pre=nxt[pre];
		if(s[pre+1]==s[i]) ++pre;
		nxt[i]=pre;
	}
	for(int i=0;i<m;++i){
		for(int j=0;j<=9;++j){  //枚举任意可能出现的数字 
			pre=i; //i<j可行
			while(pre&&s[pre+1]!=j+'0') pre=nxt[pre];
			if(s[pre+1]==j+'0') ++pre;
			if(i!=m){  //去掉非法状态，不需要能够全部匹配上的子串 
				bas.c[i][pre]=(bas.c[i][pre]+1)%p; 
			}  //跳到pre的方案数+1 
		}
	}
	ans.c[0][0]=1;
	ans=ans*fpow(bas,n);
	int sum=0;
	for(int i=0;i<m;++i){
		sum=(sum+ans.c[0][i])%p;
	} 
	printf("%lld\n",sum); 
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