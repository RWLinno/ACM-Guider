---
title : 离散对数与BSGS
date : 2021-8-12
tags : ACM,数论
author Linno

---

![在这里插入图片描述](https://img-blog.csdnimg.cn/0c340f98702d498194ec4a1b9374fb63.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA57yE5ruF,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

### 阶

对与m互质的整数a，我们记满足$a^n\equiv 1\mod m$的最小正整数n为a模m的阶，记为$\delta_m(a)$。

##### 引理

$$
①若m>1并且gcd(a,m)=1,又满足a^n\equiv 1\mod m，那么\delta_m(a)|n\\
②由欧拉定理和定理一得：\delta_m(a)|\phi(m)
$$



### 欧拉定理

$若a与m互质，则a^{\phi(m)}\equiv1\mod m$



### 原根

若存在与m互质的整数g，并且g模m的阶为$\phi(m)$，那么我们称模m有原根，并称g为模m的一个原根。
$$
若一个数能分解为x=r*s,(r,s)=1，且r,s>2，那么x必定无原根\\
若满足x=p^k或者x=2*p^k的形式，x才有可能有原根
$$

##### 相关定理

$$
①一个正整数m有原根的充要条件是m=2,4,p^e,2p^e，其中，p为奇素数，e为正整数\\
②每一个素数p都有\phi(p-1)个原根，事实上，每一个正整数m都有\phi(\phi(m))个原根。\\
③若g是m的一个原根，则g,g^2,...,g^{\phi(m)}，\\各数对m取模的非负最小剩余就算小于m且与m互质的\phi(m)个数的一个排列。
$$

##### 原根的求法

$$
(1)首先求\phi(m)的素幂分解式：\phi(m)=p_1^{e_1}*p_2^{e_2}*...*p_k^{e_k}\\
然后枚举g，若恒满足g^{\frac{\phi(m)}{pi}}\neq1\mod m，其中i=1,2,...,k\\则g是m的一个原根
$$



### 离散对数

离散对数是一种再整数中基于同余运算和原根的对数运算。
$$
当模m有原根时，设G为模m的一个原根，\\
则当：x\equiv G^k \mod k时，log_G(x)\equiv k \mod \phi(m)\\
此处的log_G(x)是x以整数G为底模\phi(m)的离散对数值。
$$




### BSGS

Baby-Step-Giant-Step及其拓展算法（Extended BSGS）是用来求解$A^x\equiv B\mod C(0\le x<C)$类型问题（高次同余方程）的算法，以空间换时间，是对穷举法的一个改进。

##### 穷举法

由费马小定理得 如果方程有解，那么一定在循环节[0,C-1]之中（费马小定理），只需要在循环节中枚举x就可以求出方程的解。（p很大的时候就会爆）

##### 基础BSGS

只能解决C为素数的情况。
$$
设m=\sqrt C上取整，x=i*m+j，那么A^x=(A^m)^i*A^j,0\le i<m，0\le j<m\\
然后可以枚举i，这是O(\sqrt C)级别的枚举\\
对于一个枚举出来的i，令D=(A^m)^i。现在问题转化为求D*A^j\equiv B\mod C，\\如果把A^j当作一个整体，套上拓展欧几里得算法就可以解出来了。\\（而且因为C是质数，A是C的倍数的情况容易特判，\\除此之外必有GCD（D,C）=1，所以一定有解。
$$
求出来$A^j$，现在的问题是我怎么知道j是多少？先用$O(\sqrt C)$的时间，将A^j全部存进hash表里面，然后只要查表就在O(1)的时间内知道j是多少了。

##### luoguP2485 [SDOI2011]计算器

```C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fpow(ll a,ll b,ll mod){
	ll res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1; 
	}
	return res;
}

ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	ll gcd=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return gcd;
}

void bsgs(ll y,ll z,ll p){
	z%=p;
	if(y%p==0){
		if(z){
			cout<<"Orz, I cannot find x!"<<endl;
			return;	
		}else{
			if(p==1){
				cout<<0<<endl;
				return;
			}else{
				cout<<1<<endl;
				return;
			} 
		}
	}
	ll m=ceil(sqrt(p));
	map<ll,ll>mp;
	ll now=z%p,f=fpow(y,m,p);
	mp[now]=0;
	for(int j=1;j<=m;j++){
		now=now*y%p;
		mp[now]=j;
	}
	now=1;
	for(int i=1;i<=m;i++){
		now=now*f%p;
		if(mp[now]){
			cout<<((i*m-mp[now])%p+p)%p<<endl;
			return;
		}
	}
	cout<<"Orz, I cannot find x!"<<endl;
}


int t,k,y,z,p;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t>>k;
	if(k==1){
		for(int i=1;i<=t;i++){
			cin>>y>>z>>p;	
			cout<<fpow(y,z,p)%p<<endl; 
		}
	}else if(k==2){
		for(int i=1;i<=t;i++){
			cin>>y>>z>>p;
			ll x,d;
			ll gcd=exgcd(y,p,x,d);
			if(z%gcd) cout<<"Orz, I cannot find x!"<<endl;
			else{
				ll tmp=p/gcd;
				while(x<0) x+=tmp;
				cout<<((x*z/gcd)%tmp+tmp)%tmp<<endl;
			}
		}
	}else if(k==3){
		for(int i=1;i<=t;i++){
			cin>>y>>z>>p;
			bsgs(y,z,p);
		}
	}
	return 0;
}
```



##### 拓展BSGS

不要求C为素数，开始前先执行消除因子。

$a\equiv b\mod p $可转化为$\frac{a}{c}\equiv\frac{b}{c}\mod \frac{p}{c}$

那么$a^x\equiv b\mod p $可转化为$a^{x-k}\frac{a^k}{\prod _{i-1}^kd_i}\equiv\frac{b}{\prod _{i-1}^kd_i}\mod \frac{p}{\prod _{i-1}^kd_i}$

###### 步骤

（1）若b==1 那么x=0，算法结束；

（2）若gcd(a,p)不能整除b，则无解，算法结束；

（3）若gcd(a,p)!=1,令d=gcd(a,p)，若d不能整除b，则无解，算法结束；

（4）持续步骤三直到$gcd(A,\frac{p}{\prod _{i-1}^kd_i})=1$，我们就可以直接用普通BSGS求出结果，最后加上k即可。

##### luoguP4195 【模板】扩展 BSGS/exBSGS

```C++
#include<bits/stdc++.h>
#define LL long long
using namespace std;
int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
unordered_map<int,int>mp;
inline int gcd(int a,int b){return b?gcd(b,a%b):a;}
inline int BSGS(int a,int n,int p,int ad){
	mp.clear();
	int m=ceil(sqrt(p)),s=1;
	for(int i=0;i<m;i++,s=1ll*s*a%p) mp[1ll*s*n%p]=i;
	for(int i=0,tmp=s,s=ad;i<=m;i++,s=1ll*s*tmp%p)
		if(mp[s]) if(1ll*i*m-mp[s]>=0) return 1ll*i*m-mp[s];
	return -1;
}
inline int exBSGS(int a,int n,int p){
	a%=p;n%=p;
	if(n==1||p==1) return 0;
	int cnt=0;
	int d,ad=1;
	while((d=gcd(a,p))^1){
		if(n%d) return -1;
		cnt++;n/=d;p/=d;
		ad=(1ll*ad*a/d)%p;
		if(ad==n) return cnt;
	}
	LL res=BSGS(a,n,p,ad);
	if(res==-1) return -1;
	return res+cnt;
} 
signed main(){
	int a=read(),p=read(),n=read(),ans;
	while(a||p||n){
		ans=exBSGS(a,n,p);
		if(~ans) printf("%d\n",ans);
		else puts("No Solution");
		a=read();p=read();n=read();
	}
	return 0;
}
```



### 参考资料

https://www.cnblogs.com/cytus/p/9296661.html

https://www.bilibili.com/video/BV14A411h7oD

https://www.bilibili.com/video/BV17f4y1v7D5
