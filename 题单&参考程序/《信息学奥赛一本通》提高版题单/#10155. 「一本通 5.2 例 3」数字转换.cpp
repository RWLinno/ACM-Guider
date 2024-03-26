//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=1e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,ans;
vector<int>G[N];

int vis[N],dep[N],rt=0;
inline void dfs(int x,int f){
	vis[x]=1;
	if(dep[x]>dep[rt]) rt=x;
	for(auto to:G[x]){
		if(to==f) continue;
		dep[to]=dep[x]+1;
		dfs(to,x);
	}
}

void Solve(){
	cin>>n;
	for(int i=2;i<=n;i++){
		int res=1; //约数和 
		for(int j=2;j*j<=i;j++){
			if(i%j==0){
				res+=j;
				if(j*j!=i) res+=i/j;
			}
		}
		if(res<i){
			G[res].push_back(i);
			G[i].push_back(res);
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			rt=i;
			dep[i]=0;
			dfs(i,0);
			dep[rt]=0;
			dfs(rt,0);
			ans=max(ans,dep[rt]);
		}
	}
	cout<<ans<<"\n";
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