//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=1e6+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,m,ans,fu,fv;
int fa[N],deg[N],num[N];

int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}

void init(){
	memset(deg,0,sizeof(deg));
	memset(num,0,sizeof(num));
	for(int i=1;i<=n;i++) fa[i]=i;
	ans=0;
}

void Solve(){
	init(); 
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		deg[u]++;
		deg[v]++;
		fu=find(u),fv=find(v);
		fa[fu]=fv;
	}
	for(int i=1;i<=n;i++) if(deg[i]%2) num[find(i)]++;
	for(int i=1;i<=n;i++) if(fa[i]==i&&deg[i]) ans+=max(1ll,num[i]/2);
	cout<<ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	while(cin>>n>>m){
		Solve();
	}
	return 0;
}