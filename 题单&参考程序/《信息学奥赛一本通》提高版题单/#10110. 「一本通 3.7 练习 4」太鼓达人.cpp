#include<bits/stdc++.h>
const int N=1e4;
 
using namespace std;
int n,bin,vis[N],ans[N];
bool dfs(int val,int step){
    if(vis[val]) return 0;
    if(step==bin)return 1;
    vis[val]=1;
    int nxt1=(val<<1)&(bin-1),nxt2=(val<<1|1)&(bin-1);
    ans[step]=val&1;
    if(dfs(nxt1,step+1)||dfs(nxt2,step+1)) return 1;
    vis[val]=0;
    return 0;
}
signed main(){
    scanf("%d",&n);
	bin=1<<n;
    printf("%d ",bin);
    dfs(0,1);
    for(int i=1;i<n;i++) putchar('0');
    for(int i=1;i<=bin-n+1;i++) printf("%d",ans[i]);
    return 0;
}