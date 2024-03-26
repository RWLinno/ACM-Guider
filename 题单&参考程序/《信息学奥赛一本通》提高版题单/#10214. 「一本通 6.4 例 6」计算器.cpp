//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=998244353;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

int n,inv[N],frac[N],ifrac[N];

int cnt=0,np[N],pri[N],phi[N],mu[N];
void init(){   //线性筛求质数、欧拉函数、莫比乌斯函数 
	np[1]=1;
	for(int i=2;i<N;++i){
		if(!np[i]){
			pri[++cnt]=i;
			phi[i]=i-1; 
			mu[i]=-1;
		}
		for(int j=1;j<=cnt&&i*pri[j]<N;++j){
			np[i*pri[j]]=1;
			if(i%pri[j]==0){
				phi[i*pri[j]]=pri[j]*phi[i];
				mu[i*pri[j]]=0; 
				break;
			}else{
				phi[i*pri[j]]=(pri[j]-1)*phi[i];
				mu[i*pri[j]]=-mu[i]; 
			}
		}
	}
} 

//------------------------------------------
inline int gcd(int a,int b){  //最大公约数 
	return b?gcd(b,a%b):a;
}

inline int lcm(int a,int b){  //最小公倍数 
	return a*b/gcd(a,b);
}

inline int exgcd(int a,int b,int &x,int &y){  //扩展欧几里得 
	//对于ax+by=c等价于ax ≡c mod b
	if(!b){
		x=1;y=0;
		return a;
	}
	int d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}

int mul(int a,int b,int p){  //普通的快速乘 
	int res=0;
	while(b){
		if(b&1) res=(res+a)%p;
		a=(a+a)%p;
		b>>=1;
	}
	return res;
}

inline int fpow(int a,int b,int p=mod){  //快速幂 
	int res=1;
	while(b){
		if(b&1) res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
	return res;
}
//------------------------------------------
inline int C(int n,int m){  //求组合数 
	if(n<m) return 0;
	return frac[n]*ifrac[m]%mod*ifrac[n-m]%mod;
} 

inline int A(int n,int m){  //求排列数 
	if(n<m) return 0;
	return frac[n]*ifrac[n-m]%mod;
}

inline int Lucas(int x,int y){  //卢卡斯定理求大组合数 
	if(!y) return 1;
	return C(x%mod,y%mod)*Lucas(x/mod,y/mod)%mod;
}

inline int katelan(int x){   //求卡特兰数;
	//前几项为1,2,5,14,132,429,1430,4862,16796,58786,208012,742900
	//常用公式:1.f(n)=C(2n,n)/(n+1)
	//         2.f(n)=f(n-1)*(4*n-2)/(n+1)
	//		   3.for(int i=0;i<=n-1;++i) f[n]+=f[i]*f[n-i-1];
	//		   4.f(n)=C(2n,n)-C(2n,n-1)
	//常见形式：二叉树计数、乘法加括号、AB排列问题、多边形分割
	return C(x<<1,x)*inv[x+1]%mod; 
}

//------------------------------------------
int BSGS(int a,int b,int p){ //解高次同余方程 a^x ≡b(mod p) 
   if((a%p==0&&b%p!=0)||(a%p!=0&&b%p==0)) return -1;
    map<int,int>mp; 
    int t=ceil(sqrt(p*1.0));
    for(int i=0;i<t;++i){
        int x=b*fpow(a,i,p)%p;
        mp[x]=i;
    }
    int ans=0;
    for(int i=0;i<=t;++i){
        int k=fpow(a,i*t,p);
        if(mp.count(k)&&i*t-mp[k]>=0){
            ans=i*t-mp[k];
            return ans;
        }
    }
    return -1;
}
//------------------------------------------
bool MillerRabin(int x){ //米勒拉宾质数判定 
	if (x < 2) return 0;
	int i,j,y=x-1,a,b;
	while(y&1^1) y>>=1; //相当于先化为奇数 
	for(i=0;i<9;i++){
		if (x%pri[i]<1)	return x == pri[i]; //不可以是质数p的倍数 
	}
	for (i=2;i<9;i++){
		for (a=b=fpow(pri[i],y,x),j=y;j<x&&a>1;j+=j,a=b){
			if (b=mul(b,b,x),b==1&&a!=x-1)	return 0; //二次检测 
			//b和x互质，b^2modx=1，要b=1,要么b=x-1,那么b==1时a应该为x-1 
		}
		if(a!=1) return 0; //最终a不为1，没有通过二次检验 
	}
	return 1;
}

inline int PollardRho(int x){ //Pollard Rho算法求素因子 
    int s=0,t=0,c=1ll*rand()%(x-1)+1;
    int stp=0,goal=1,val=1;
    for(goal=1;;goal<<=1,s=t,val=1){
        for(stp=1;stp<=goal;++stp){
            t=(t*t+c)%x;
            val=val*abs(t-s)%x;
            if((stp%127)==0){
                int d=gcd(val,x);
                if(d>1) return d;
            }
        }
        int d=gcd(val,x);
        if(d>1) return d;
    }
}

int max_factor=0;
inline void fac(int x){ //求最大因子 
    if(x<=max_factor||x<2) return;
    if(MillerRabin(x)){
        max_factor=max_factor>x?max_factor:x;
        return;		
    }
    int p=x;
    while(p>=x) p=PollardRho(x);
    while((x%p)==0) x/=p;
    fac(x),fac(p);
}

//------------------------------------------

signed main(){
	init();
	frac[0]=1;for(int i=1;i<=n;++i) frac[i]=frac[i-1]*i%mod;  //求阶乘 
	ifrac[n]=fpow(frac[n],mod-2);
	for(int i=n;i>=1;--i) ifrac[i-1]=ifrac[i]*i%mod;  //线性求阶乘的逆元 
	inv[0]=inv[1]=1;for(int i=2;i<=n;++i) inv[i]=inv[mod%i]*(mod-mod/i)%mod;  //线性求逆元 
	int t,k,y,z,p;
	cin>>t>>k;
	for(int i=1,ans;i<=t;++i){
		cin>>y>>z>>p;
		if(k==1){
			ans=fpow(y,z,p);
		}else if(k==2){
			int X,Y;
			int d=exgcd(y,p,X,Y);
			if(z%d){
				cout<<"Orz, I cannot find x!\n";
				continue;
			}else{
				int k=(z/d),md=p/d;
				X=X*k%md;
				X=(X+md)%md;
				ans=X;
			}
		}else{
			ans=BSGS(y,z,p);
			if(ans==-1){
				cout<<"Orz, I cannot find x!\n";
				continue;
			}
		}
		cout<<ans<<"\n"; 
	}
	return 0;
}