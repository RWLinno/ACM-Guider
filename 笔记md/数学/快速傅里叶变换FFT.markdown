---
tilte :  快速傅里叶变换FFT学习笔记
tags : ACM,数论
date : 2021-7-18

---
![在这里插入图片描述](https://img-blog.csdnimg.cn/d3b990dee1fc4b55bfe423f821c71736.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA57yE5ruF,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

### 简介

**FFT（Fast Fourier Transformation）**，中文名**快速傅里叶变换**，用来**加速多项式乘法**。

**DFT**，中文名**离散傅里叶变换**，用来把多项式转化成离散的点。

**IDFT**,中文名**离散傅里叶反变换**，用来把离散的点还原成多项式。

时间复杂度O(nlogn)

将一个用**系数表示**的多项式转换成它的**点值表示**的算法。

##### 系数表示法：

$f(x)=\{a_0,a_1,a_2,...,a_{n-1}\}$

##### 点值表示法：

$f(x)=\{(x_0,f(x_0)),(x_1,f(x1)),...,(x_{n-1},f(x_n-1))\}$

高精度乘法下，系数表示法将多项式相乘需要时间复杂度$O(n^2)$

而点值表示法只需要$O(n)$

##### 原因：

$$
设两个点值多项式分别为\\
f(x)=\{(x_0,f(x_0)),(x_1,f(x1)),...,(x_{n-1},f(x_{n-1}))\}\\
g(x)=\{(x_0,g(x_0)),(x_1,g(x1)),...,(x_{n-1},g(x_{n-1}))\}\\
设题目他们的乘积是h(x)，那么\\
h(x)=\{(x_0,f(x_0)·g(x_0)),(x_1,f(x_1)·g(x1)),...,(x_{n-1},f(x_{n-1})·g(x_{n-1}))\}\\
$$

然而朴素的系数表示法转点值表示法复杂度为$O(n^2)$（DFT和IDFT），这时候就需要用到我们今天要讲的快速傅里叶变换了。



### 原理

##### 三角函数

##### 复数性质

$复数相乘：模长相乘，极角相加，即\\(a_1,\theta_1)*(a_2,\theta_2)=(a_1a_2,\theta_1 +\theta_2)$

下面每一个n都默认为2的整数次幂
$$
我们记w_n^k为将单位元分成n份,编号为7的点表示的复数值\\
由复数相乘可知(w_n^1)^k=w_n^k,其中称w_n^1称为n次单位根。\\那么每个w都可以表示为w_n^k=cos\frac{k}{n}2\pi+isin\frac{k}{n}2\pi
$$

##### 单位根的一些性质

$$
w_n^k=w_{2n}^{2k}\\
w_n^{k+\frac{n}{2}}=-w_n^{k}\\
w_n^0=w_n^n\\
$$

### FFT计算过程

$$
①首先设一个多项式A(x)\\
A(x)=\sum_{i=0}^{n-1}a_ix^i=a_0+a_1x+a_2x^2+...+a_{n-1}x^{n-1}\\
②按照下标的奇偶性把A(x)分成两半，右边可以提一个x\\
A(x)=(a_0+a_2x^2+...+a_{n-2}x^{n-2})+x(a_1+a_3x^2+...+a_{n-1}x^{n-2})\\
③分别记A_1(x)和A_2（x）为上面化简的两项多项式，则\\
A(x)=A_1(x^2)+xA_2(x^2)\\
④ 我们设k<\frac{n}{2}，令x=w_n^k代入上式可得\\
A(w_n^k)=A_1((w_n^k)^2)+w_n^kA_2((w_n^k)^2)=\\
A_1(w_n^{2k})+w_n^kA_2(w_n^{2k})=A_1(w_{\frac{n}{2}}^{k})+w_n^kA_2(w_{\frac{n}{2}}^{k})\\
⑤对于A(w_n^{k+\frac{n}{2}})的话，代入w_n^{k+\frac{n}{2}}\\
A(w_n^{k+\frac{n}{2}})=A_1(w_n^{2k+n})+w_n^{k+\frac{n}{2}}A_2(w_n^{2k+n})=\\
A_1(w_n^{2k}w_n^n)-w_n^kA_2(w_n^{2k}w_n^n)=A_1(w_n^{2k})-w_n^kA_2(w_n^{2k})=A_1(w_{\frac{n}{2}}^k)-w^k_nA_2(w_{\frac{n}{2}}^k)\\
$$

我们可以得出一个结论
$$
A(w_n^k)与A(w_n^{k+\frac{n}{2}})只有后面的多项式符号不同。
$$


$已知A_1(w_\frac{n}{2}^k)和A_2(^k_\frac{n}{2})，我们可以同时知道A_1(w_n^k)和A_2(w^{k+\frac{n}{2}}_n)的值$

我们采用分治来做，这样我们知道前面一半的序列，就能直接得出后面一半序列的答案。当n==1时只有常数项，直接return。



### IFFT

对于快速傅里叶逆变换，需要记住一个结论：

一个多项式在分治过程中乘上单位根的共轭复数，分治完的每一项除以n即为原多项式的每一项系数。



### 模板

```C++
//迭代版——luoguP3803 【模板】多项式乘法（FFT）
#include<bits/stdc++.h>
#define int ll
using namespace std;
typedef long long ll;
typedef complex<double> cp;
const double pi=acos(-1);
const int maxn=1e7+7;

cp a[maxn],b[maxn];

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=f*-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

/*
struct complex{
	double x,y;
	complex (double xx=0,double yy=0){x=xx,y=yy;}
	complex operator + (complex a,complex b){return complex(a.x+b.x,a.y+b.y);}
	complex operator - (complex a,complex b){return complex(a.x-b.x,a.y-b.y);}
	complex operator * (complex a,complex b){return complex(a.x*b.x-a.y*b.y,a.y*b.y+a.y*b.x);}
};
*/

int n,m,limit=1;
int l,r[maxn];

void fft(cp *A,int type){ //迭代版本
	for(int i=0;i<limit;i++){ 
		if(i<r[i]) swap(A[i],A[r[i]]); //求出要迭代的序列
	}
	for(int mid=1;mid<limit;mid<<=1){//待合并区间的中点
		cp wn(cos(pi/mid),type*sin(pi/mid));//单位根
		for(int R=mid<<1,j=0;j<limit;j+=R){ //R是区间的右端点
			cp w(1,0); //幂
			for(int k=0;k<mid;k++,w=w*wn){ //枚举左半部分
				cp x=A[j+k],y=w*A[j+mid+k]; //蝴蝶效应
				A[j+k]=x+y;
				A[j+mid+k]=x-y;
			} 
		}
	}
}

signed main(){
	n=read();m=read();
	for(int i=0;i<=n;i++) a[i].real()=(double)read();
	for(int i=0;i<=m;i++) b[i].real()=(double)read();
	while(limit<=n+m) limit<<=1,l++;
	for(int i=0;i<limit;i++)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
    //再原序列中i和i/2的关系是：i可以看作i/2每一位左移一位的来
    //那么在反转后的数组中就需要右移一位，同时特殊处理一下复数
	fft(a,1); //FFT转化为点值表示法
	fft(b,1);
	for(int i=0;i<=limit;i++) a[i]=a[i]*b[i]; //点值相乘
	fft(a,-1); //IFFT
	for(int i=0;i<=n+m;i++)
		printf("%d ",(int)(a[i].real()/limit+0.5));
	return 0;
}
```

```C++
//递归版——luogu P1919 【模板】A*B Problem升级版（FFT快速傅里叶）
#include <bits/stdc++.h>
#define int long long
using namespace std;
const double PI=acos(-1);
const int maxn=4e5+10;
typedef complex<double> cp;

cp a[maxn],b[maxn],c[maxn];
int limit=1,len,len1,len2,ans[maxn];
string s1,s2;

void FFT(int n,cp *a,int op){
    if(n==1) return;
    cp a1[n>>1],a2[n>>1];
    for(int i=0;i<n/2;++i) {
        a1[i]=a[2*i];
        a2[i]=a[2*i+1]; //分为两个区间（奇偶性） 
    }
    FFT(n>>1,a1,op); //递归 
    FFT(n>>1,a2,op);
    cp wn=cp(cos(2*PI/n),sin(2*PI*op/n)); //单位根 
    cp w=cp(1,0); //幂 
    for(int i=0;i<(n>>1);++i,w=w*wn){
        a[i]=a1[i]+w*a2[i]; 
        a[i+(n>>1)]=a1[i]-w*a2[i];
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0); 
    cin>>s1>>s2;
    len1=s1.length(),len2=s2.length();
	for(int i=0;i<len1;++i) a[i]=(double)(s1[len1-i-1]-'0'); 
	for(int i=0;i<len2;++i) b[i]=(double)(s2[len2-i-1]-'0');
    len=len1+len2-2; //结果长度 
    while(limit<=len) limit=limit<<1;//区间长度 
    FFT(limit,a,1); //转化为点值表示法 
    FFT(limit,b,1);
    for(int i=0;i<=limit;++i) c[i]=a[i]*b[i]; 
    FFT(limit,c,-1); //IFFT
    for(int i=0;i<=len;++i) ans[i]=(int)(c[i].real()/limit+0.5);
    for(int i=1;i<=len;++i){ //进位操作 
        ans[i]=ans[i]+ans[i-1]/10;
        ans[i-1]=ans[i-1]%10;
    }
    int s=len;
    for(;s>=0;--s){
        if(ans[s]) break; //跳过前导0输出答案
    }
    for(int i=s;i>=0;--i) cout<<ans[i];  
    return 0;
}
```



### 参考资料

https://blog.csdn.net/enjoy_pascal/article/details/81478582

https://www.luogu.com.cn/record/53455334

https://www.bilibili.com/video/BV1Wb411v7yN

https://www.cnblogs.com/zwfymqz/p/8244902.html
