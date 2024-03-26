#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e5+7;

int k,x,a[N],b[N];

int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
template<class type_name> inline type_name qr(type_name sample){
    type_name ret=0,sgn=1;
    char cur=getchar();
    while(!isdigit(cur)) sgn=(cur=='-'?-1:1),cur=getchar();
    while(isdigit(cur)) ret=(ret<<1)+(ret<<3)+cur-'0',cur=getchar();
    return sgn==-1?-ret:ret;
}

inline int gcd(int a,int b){
	return b?gcd(b,a%b):a;
} 

inline int fpow(int a,int b,int p){
	int res=1;
	while(b){
		if(b&1) res=res*a%p;
		a=a*a%p;
		b>>=1; 
	}
	return res;
}	

inline int get_C(int n,int m){
	for(int i=m;i>=1;--i) a[i]=(n-m+i),b[i]=i;
	for(int i=1;i<=m;++i){
		if(b[i]==1) continue;
		for(int j=1;j<=m;++j){
			int e=gcd(a[j],b[i]);
			a[j]/=e,b[i]/=e;
			if(b[i]==1) break;
		} 
	}
	memset(b,0,sizeof(b));
	b[0]=b[1]=1;
	for(int i=1;i<=m;++i){
		int g=0;
		if(a[i]==1) continue;
		for(int j=1;j<=b[0];++j){
			b[j]=b[j]*a[i]+g;
			g=b[j]/10;
			b[j]%=10;
			if(j==b[0]&&g) b[0]++;
		}
	}
}

signed main(){
	cin>>k>>x;
	int g=fpow(x,x,1000ll);
	get_C(g-1,k-1);
	for(int i=b[0];i>=1;--i) cout<<b[i];
	return 0;
}