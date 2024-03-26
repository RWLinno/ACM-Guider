#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
#define ld long double
using namespace std;
const int maxn=5e4+7;

int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,L,head=1,tail=0,tmp;
int Q[maxn],S[maxn],dp[maxn];

inline int X(int x){return S[x];}

inline int Y(int x){return dp[x]+(S[x]+L)*(S[x]+L);}

inline ld slope(int a,int b){
	return (ld)(Y(a)-Y(b))/(X(a)-X(b));
}

signed main(){
	n=read();L=read();
	++L;
	memset(S,0,sizeof(S));
	for(int i=1;i<=n;i++) S[i]=read()+S[i-1]+1; 
	Q[++tail]=0;
	for(int i=1;i<=n;i++){
		while(head<tail&&slope(Q[head],Q[head+1])<=2*S[i]) ++head;
		tmp=Q[head];
		dp[i]=dp[tmp]+(S[i]-S[tmp]-L)*(S[i]-S[tmp]-L);
		while(head<tail&&slope(Q[tail-1],Q[tail])>=slope(Q[tail-1],i)) --tail;
		Q[++tail]=i;
	}
	printf("%lld",dp[n]);
	return 0;
}