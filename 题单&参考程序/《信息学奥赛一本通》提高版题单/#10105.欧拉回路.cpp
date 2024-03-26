#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

struct E{
int v,nxt;
}e[N<<1];

int head[N],cnt=0;
inline void addedge(int u,int v){
	e[++cnt]=(E){v,head[u]};head[u]=cnt;
}

int t,n,m;
int deg[N],ru[N],chu[N];
int vis[N],ans[N],num=0;

void dfs(int x){  //对于无向图，记录每条边流向哪个点 
	for(int &i=head[x];i;i=e[i].nxt){ //当前弧优化 
		if(!vis[i]){
			int tmp=i;
			vis[i]=1;
			if(t==1){
				if(i&1) vis[i+1]=1;
				else vis[i-1]=1;
			}
			dfs(e[i].v);
			ans[++num]=tmp; //因为前面dfs使当前弧改变了，所以不能直接用i 
		}
	}
}

void Solve(){
	cin>>t; 
	cin>>n>>m;
	if(t==1){
		for(int i=1,u,v;i<=m;i++){
			cin>>u>>v;
			addedge(u,v);
			addedge(v,u);
			deg[u]++;deg[v]++;
		}
		for(int i=1;i<=n;i++){ //无向图欧拉回路：无度为奇数的点 
			if(deg[i]&1){
				cout<<"NO\n";
				return;
			}
		}
	}else{
		for(int i=1,u,v;i<=m;i++){
			cin>>u>>v;
			addedge(u,v);
			chu[u]++;ru[v]++;
		}
		for(int i=1;i<=n;i++){
			if(chu[i]!=ru[i]){ //所有点的入度和出度相同 
				cout<<"NO\n";
				return; 
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(head[i]){  //任选一点出发进行dfs 
			dfs(i);
			break;
		}
	}
	if(num!=m){  //如果没有把点都走完 
		cout<<"NO\n";
		return;
	}
	cout<<"YES\n";  //输出答案 
	if(t==2) for(int i=0;i<num;i++) cout<<ans[num-i]<<" ";
	else{
		for(int i=0;i<num;i++){
			if(ans[num-i]&1) cout<<(ans[num-i]+1)/2<<" ";
			else cout<<(ans[num-i]/(-2))<<" ";
		}
	}
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