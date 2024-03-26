//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=1007;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,ans=0,deg[N],mp[N][N],mp2[N][N];

int dfn[N],low[N],vis[N],bel[N],idx=0;
int stk[N],top=0,sccnum=0;
inline void tarjan(int x){
	dfn[x]=low[x]=++idx;
	stk[++top]=x;
	vis[x]=1;
	for(int to=1;to<=n;to++){
		if(mp[x][to]){
			if(!dfn[to]){
				tarjan(to);
				low[x]=min(low[x],low[to]);
			}else if(vis[to]) low[x]=min(low[x],dfn[to]);
		}
	}
	if(dfn[x]==low[x]){
		int y;sccnum++;
		while(y=stk[top--]){
			bel[y]=sccnum;
			vis[y]=0;
			if(x==y) break;
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>mp[i][j];
		}
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(mp[i][j]) mp2[bel[i]][bel[j]]=1;
		}
	}
//	for(int i=1;i<=n;i++) cout<<"bel: "<<i<<" "<<bel[i]<<"\n"; 
	for(int i=1;i<=sccnum;i++){
		for(int j=1;j<=sccnum;j++){
//			cout<<mp2[i][j]<<" ";
			if(i!=j&&mp2[i][j]) deg[j]++;
		}
//		cout<<"\n";
	}
	for(int i=1;i<=sccnum;i++) if(!deg[i]) ans++; 
	cout<<ans<<"\n";
	return 0;
}
