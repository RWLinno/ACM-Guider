---
title : 数位DP
date : 2022-4-11
tags : ACM,动态规划
author : Linno


---



# 数位DP

数位dp是用到数字位数性质来计数的动态规划问题。一般形式比较固定：通常问一个范围内满足某种性质的数的计数问题。我们通过做差可以将问题转化为前n个数中满足条件的数的个数。要解决这个问题，一般步骤分为：①初始化；②计算每个数位对答案的贡献；③累加得到答案。



### 分析思路

这里强烈推荐yxc的数位dp分析法。将数字n分解为一棵树，然后求每一部分对答案的贡献。在初始化的过程，我们一般会求得前X位数关于数字X的答案。我们定义一个函数f(n)来解决前n个数中满足条件的数的个数。首先特判n是否为0，不为0就按位记录每个数码。我们在计算每位数的贡献时，在[0,num[i]-1]范围枚举数码，这样做是为了保证统计到的是小于n的答案，然后判一下最后一个数是否满足条件即可。



### 例题

##### 数字计数（模板题）

题意：输出[L,R]范围内每个数码的出现次数。

我们设f(i,j)表示i位数中j数码出现次数，就有以下递推公式
$$
\begin{cases}
f(i,j)=0,i=0\\
f(i,j)=10×f(i-1,j)+10^{i-1},i>0
\end{cases}
$$
预处理这个出来之后就是常规的数位DP了，处理前导0另外减去10的幂次即可。



```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=30;

int pw[N],num[N],cnt[10],dp[N],tmp[10];

void init(){ 
	pw[0]=1;for(int i=1;i<N;i++) pw[i]=pw[i-1]*10;
	dp[0]=0;for(int i=1;i<N;i++) dp[i]=(dp[i-1]*10+pw[i-1]);
}

int solve(int n){
	int len=0,res=0,lst=n;
	while(n){
		num[++len]=n%10;
		n/=10;
	}
	for(int i=len;i>=1;i--){
		for(int j=0;j<=9;j++)	cnt[j]+=dp[i-1]*num[i];
		for(int j=0;j<num[i];j++)	cnt[j]+=pw[i-1];
		lst-=num[i]*pw[i-1];
		cnt[num[i]]+=lst+1;
		cnt[0]-=pw[i-1];
	}
	return res;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	init();
	int L,R;
	cin>>L>>R;
	solve(R);
	for(int i=0;i<=9;i++) tmp[i]=cnt[i];
	memset(cnt,0,sizeof(cnt));
	solve(L-1);
	for(int i=0;i<=9;i++) cout<<tmp[i]-cnt[i]<<" ";
	return 0;
}
```



##### 数字游戏

题意：求[L,R]的不降数个数。定义不降数为从高位到低位的数字是不下降的。

```cpp
//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int a,b,dp[N][40],num[40];

void init(){ //预处理dp[i][j]表示最高位是j，一共有i位的不降数个数 
	for(int i=0;i<=9;i++) dp[1][i]=1;
	for(int i=2;i<35;i++){
		for(int j=0;j<=9;j++){
			for(int k=j;k<=9;k++)
				dp[i][j]+=dp[i-1][k]; 
		}
	}
}

int Solve(int n){
	int len=0,res=0,lst=0;
	if(n==0) return 1;
	while(n){
		num[++len]=n%10;
		n/=10;
	}
	for(int i=len;i>=1;i--){  //从高位向低位枚举 
		for(int j=lst;j<num[i];j++) res+=dp[i][j]; //当前位要填比上一位大的数 
		if(num[i]<lst) break; 
		lst=num[i]; //表示上一位的数 
		if(i==1) res++; //最低位满足的答案 
	}
	return res;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	init();
	while(cin>>a>>b){
		cout<<Solve(b)-Solve(a-1)<<"\n";
	}
	return 0;
}

```



##### 不要62

题意：求[L,R]中有多少个带有62或者带4的数。

这题数据范围出的巨水，暴力也可以过，数位DP的话多记录前面一个数码，剩下的就是模板了。

```cpp
/*  这里是暴力的代码
//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
using namespace std;
const int N=1e7+7;
const int mod=1e9+7;

int l,r,flag=0,tmp=0,sum[N];

signed main(){
	sum[0]=0;
	for(int i=1;i<=1e7;i++){
		tmp=i,flag=0;
		while(tmp){
			if(tmp%10==4) flag=1;
			else if(tmp>=62&&(tmp-62)%100==0) flag=1; 
			tmp/=10;
		}
		sum[i]=sum[i-1]+flag;
	}
	cin>>l>>r;
	while(l||r){
		cout<<(r-l+1)-(sum[r]-sum[l-1])<<"\n"; 
		cin>>l>>r;
	}
	return 0;
}*/

#include<bits/stdc++.h>
using namespace std;
const int N=10;

int L,R,dp[N][10],num[N];

void init(){
	for(int i=0;i<=9;i++) if(i!=4) dp[1][i]=1;
	for(int i=2;i<N;i++){
		for(int j=0;j<=9;j++){
			if(j==4) continue;
			for(int k=0;k<=9;k++){
				if(k==4||j==6&&k==2) continue;
				dp[i][j]+=dp[i-1][k];
			} 
		} 
	}
} 

int solve(int n){
	int len=0,res=0,lst=0;
	if(!n) return 1;
	while(n){
		num[++len]=n%10;
		n/=10;
	}
	for(int i=len;i>=1;i--){
		for(int j=0;j<num[i];j++){
			if(j==4||lst==6&&j==2) continue;
			res+=dp[i][j];
		}
		if(num[i]==4||lst==6&&num[i]==2) break;
		lst=num[i];
		if(i==1) res++;
	}
	return res; 
}

signed main(){
	init();
	while(cin>>L>>R,L||R){
		cout<<solve(R)-solve(L-1)<<"\n";
	}
}
```



##### Windy数

题意：求[L,R]有多少个满足相邻数位差的绝对值大于等于2的数字个数

```cpp
//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int L,R,dp[40][15],num[40];

void init(){
	for(int i=0;i<=9;i++) dp[1][i]=1;
	for(int i=2;i<=35;i++){
		for(int j=0;j<=9;j++){
			for(int k=0;k<=j-2;k++) dp[i][j]+=dp[i-1][k];
			for(int k=j+2;k<=9;k++) dp[i][j]+=dp[i-1][k];			
		}
	}
}

int Solve(int n){
	int len=0,res=0,lst=-2;
	if(!n) return 0; 
	while(n){
		num[++len]=n%10;
		n/=10;
	}
	for(int i=len;i>=1;i--){
		if(i==len) for(int j=1;j<num[i];j++) res+=dp[i][j];
		else{
			for(int j=0;j<num[i];j++)
				if(abs(j-lst)>=2) res+=dp[i][j]; 
		}
		if(abs(num[i]-lst)>=2) lst=num[i];
		else break;
		if(i==1) res++;
	}
	for(int i=1;i<len;i++) for(int j=1;j<=9;j++) res+=dp[i][j]; //处理前导零的情况 
	return res;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	init();
	cin>>L>>R;
	cout<<Solve(R)-Solve(L-1)<<"\n"; 
	return 0;
}

```



##### 数字游戏

题意：给定L,R,N，求[L,R]区间中有多少个数每位之和模N等于0。

多记录一维表示取模N的余数，并且记下前面k位的数字和。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=11,M=110;

int dp[N][10][M],L,R,P,num[N];

int mod(int x,int y){
	return (x%y+y)%y;
}

void init(){  //预处理dp[i][j][k]表示i位数最高位为j，取模为k的方案数 
	memset(dp,0,sizeof(dp));
	for(int i=0;i<=9;i++) dp[1][i][i%P]=1;
	for(int i=2;i<N;i++){
		for(int j=0;j<=9;j++){
			for(int k=0;k<P;k++){
				for(int x=0;x<=9;x++){
					dp[i][j][k]+=dp[i-1][x][mod(k-j,P)]; 
				}
			}
		}
	}
}

int solve(int n){
	int len=0,res=0,lst=0;
	if(!n) return 1;
	while(n){
		num[++len]=n%10;
		n/=10;
	}
	for(int i=len;i>=1;i--){
		for(int j=0;j<num[i];j++) res+=dp[i][j][mod(-lst,P)];	
		lst+=num[i];
		if(i==1&&lst%P==0) res++;
	}
	return res;
}

signed main(){
	while(cin>>L>>R>>P){
		init();
		cout<<solve(R)-solve(L-1)<<"\n";	
	}
}
```



##### 恨7不成妻

题意：给定[L,R]，求区间内满足（如下条件的）数字的平方和。

1. 整数中某一位是 7 ；
2. 整数的每一位加起来的和是 7 的整数倍；
3. 这个整数是 7 的整数倍。

这道题性质比较多，难度也较大。我们可以用记忆化搜索的写法，来处理dp\[i]\[j][k]表示前i为每一位加起来模7为j,整个数模7为k的数字的是否存在，记录个数和平方。

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
typedef long long ll;
const int N=25,P=1e9+7;

struct E{
	ll s0,s1,s2;
	E(){s0=-1;s1=s2=0;}
	E(ll s0,ll s1,ll s2):s0(s0),s1(s1),s2(s2){}
}dp[N][10][10];

ll num[N],pw[N];

E _DP(int len,int r1,int r2,bool flag){
	E ans,nxt;
	if(!len) return (r1!=0&&r2!=0)?E(1,0,0):E(0,0,0);
	if(!flag&&dp[len][r1][r2].s0!=-1) return dp[len][r1][r2];
	int mxflag=(flag)?num[len]:9;
	ans.s0=0;
	for(int i=0;i<=mxflag;i++){
		if(i==7) continue;
		E nxt=_DP(len-1,(r1+i)%7,(r2*10+i)%7,flag&&i==mxflag);
		ans.s0+=nxt.s0;
		ans.s0%=P;
		ans.s1+=(nxt.s1+((pw[len]*i)%P)*nxt.s0%P)%P;
		ans.s1%=P;
		ans.s2+=(nxt.s2+((2*pw[len]*i)%P)*nxt.s1)%P;
		ans.s2%=P;
		ans.s2+=((nxt.s0*pw[len])%P*pw[len]%P*i*i%P);
		ans.s2%=P; 
	}
	if(!flag) dp[len][r1][r2]=ans;
	return ans;
}

ll solve(ll n){
	int len=0;
	while(n){
		num[++len]=n%10;
		n/=10;
	}
	return _DP(len,0,0,1).s2;
}

signed main(){
	ll t,l,r,ans;
	pw[1]=1;for(int i=2;i<=20;i++) pw[i]=(pw[i-1]*10)%P;
	cin>>t;
	while(t--){
		cin>>l>>r;
		ans=solve(r)-solve(l-1);
		cout<<(ans%P+P)%P<<"\n";
	}
	return 0;
}
```



### 参考文献

https://www.bilibili.com/video/BV1yT4y1u7jW

https://www.luogu.com.cn/blog/writeSTL/solution-p4999

https://blog.csdn.net/hzf0701/article/details/116717851
