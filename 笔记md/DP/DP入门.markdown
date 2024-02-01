---
title : DP入门
tags : ACM,动态规划
date : 2021-10-31
author : Linno
---
![在这里插入图片描述](https://img-blog.csdnimg.cn/b5b42591cf3d4851a8d4f4b98d1a0052.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA57yE5ruF,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)



# DP入门

### 简介

动态规划（Dynamic programming，简称DP）

把复杂的问题分成若干个子问题进行求解，最终递推至整个大问题的答案。



### 适用范围

①满足最优子结构：不管过去状态和决策如何，对前面的决策所形成的状态而言，余下的诸决策必须构成最优策略。

②无后效性：以前各阶段的状态无法直接影响它未来的决策。

③子问题重叠性：由于DP实现过程中，需要不断储存各种状态，空间复杂度比较大，子问题的决策在规模上是重叠的。



### 动态规划的一般步骤

①确认状态转移方程

②确认初始状态

③计算和储存各个状态

④考虑输出

⑤考虑能否状态压缩

其中确认状态转移方程是每一道DP题的核心步骤。



### 经典问题

最长连续不下降子序列

涂色问题

最长公共子序列

背包九讲（之后会另外出一个专题）



### LIS 最长上升子序列

以某个固定点作为上升子序列的最后一个元素，求出它的最长上升子序列。

取每个固定点的最大值

Dp[i]表示的是：以第i个点作为最后的一个元素的上升子序列的最长长度是多少

```C++
//O(n^2)做法
for(int i=1;i<=n;i++){
    cin>>a[i];
    dp[i]=1;
    for(int j=1;j<i;j++){
        if(a[i]>a[j]){
            dp[i]=max(dp[i],dp[j]+1);
        }
    }
    ans=max(ans,dp[i]);
}
```

```C++
//O(nlogn)做法
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7;
const int inf=0x3f3f3f3f;

int n;
int dp[N],a[N],b[N];

int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    memset(b,inf,sizeof(b));
    cin>>n;
    int ans=1;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        int p=lower_bound(b+1,b+ans+1,a[i])-b-1; //找第一个比a[i]大的元素
        dp[i]=p+1; //表示前i位lis长度
        b[dp[i]]=a[i]; //b数组维护一个lis序列
        ans=max(ans,p+1); //更新答案
    }
    return 0;
}
```



### 最长公共子序列 LCS

Dp\[i][j]表示考虑第一个数组的前i位，以及第二个数组的前j位的公共子序列最长长度。

```C++
//复杂度O(n^2)
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int n,m;
int dp[N][N];

int main(){
    cin>>n>>m;
    string a,b;
    cin>>a>>b;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i-1]==b[j-1]) dp[i][j]=dp[i-1][j-1]+1;
        }else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
    }
    cout<<dp[n][m]<<endl;
    return 0;
}
```

##### 空间优化

```C++
for(int i=1;i<=len1;i++){
    pre=0;
    for(int j=1;j<=len2;j++){
        tmp=dp[j];
        if(s1[i-1]==s2[j-1]) dp[j]=pre+1;
        else dp[j]=max(dp[j-1],dp[j]);
        pre=tmp;
    }
}
```



#####  稀疏性优化

保证一个串重复出现的元素不会特别多。

```C++
//复杂度O(nlogn)
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int n,m;
int dp[N],a[N],b[N],p[N];

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        p[x]=i;
    }
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        a[i]=p[x];
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        int p=lower_bound(b+1,b+1+ans,a[i])-b-1;
        dp[i]=p+1;
        b[dp[i]]=a[i];
        ans=max(ans,p+1);
    }
    cout<<ans<<"\n";
    return 0;
}
```





### 参考资料

https://www.bilibili.com/video/BV11A411A7bQ
