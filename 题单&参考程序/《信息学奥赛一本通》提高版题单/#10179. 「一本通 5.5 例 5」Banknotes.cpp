//算法3-单调队列优化
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define make_pair mk
#define pii pair<int,int>
using namespace std;
const int N=1e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct ITEM{
	int v,w,id;
}it[N];

int n,m,cnt=0,v[N],sz[N],dp[N],f[N],q[N];

void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>v[i];
	for(int i=1;i<=n;++i) cin>>sz[i];
	cin>>m;
	memset(dp,inf,sizeof(dp));
	memset(f,inf,sizeof(f));
	dp[0]=f[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++) f[j]=dp[j]; //因为要顺序更新，所以要先备份 
		for(int j=0;j<v[i];j++){ //拆分为v类 
			int head=0,tail=-1;
			for(int k=j;k<=m;k+=v[i]){ //对每一类使用单调队列 
				dp[k]=f[k];
				if(head<=tail&&q[head]<k-sz[i]*v[i]) head++; //q[h]不在窗口[k-sz*v,k-v]内，队头出队 
				if(head<=tail){  //使用队头最大值更新dp值 
					dp[k]=min(dp[k],f[q[head]]+(k-q[head])/v[i]);
				}
				while(head<=tail&&f[q[tail]]-(q[tail]-j)/v[i]>=f[k]-(k-j)/v[i]) tail--; //当前值比队尾更有价值，队尾出队 
				q[++tail]=k; //下标入队 
			}
		}
	}
	cout<<dp[m]<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	//cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}