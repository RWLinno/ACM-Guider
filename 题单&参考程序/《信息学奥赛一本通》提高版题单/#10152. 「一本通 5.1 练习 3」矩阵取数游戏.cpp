#include<bits/stdc++.h>
#define int __int128
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

int n,m,pw[150],dp[105][105];
int res=0,ans=0,idx,mp[150][105];

inline void dfs(int l,int r,int num,int sum){
	if(num==m){
		res=max(res,sum);
		return;
	}
	if(dp[l][r]>=sum) return;
	dp[l][r]=sum;
	dfs(l+1,r,num+1,sum+mp[idx][l]*pw[num+1]); //弹出左边 
	dfs(l,r-1,num+1,sum+mp[idx][r]*pw[num+1]); //弹出右边 
}

void Solve(){
	n=read();m=read();
	pw[0]=1;for(int i=1;i<=100;i++) pw[i]=pw[i-1]*2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			mp[i][j]=read();
		}
	}
	for(int i=1;i<=n;i++){
		memset(dp,-1,sizeof(dp));
		idx=i;res=0;
		dfs(1,m,0,0);
		ans+=res;
	}
	write(ans);
}

signed main(){
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}