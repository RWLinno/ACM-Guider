//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=107*107;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
struct E{
	int v,w,f,nxt;  //f为是否加油 
}e[N<<4];
int head[N],cnt=0;
inline void addedge(int u,int v,int w,int f){
//	cout<<u<<" "<<v<<" "<<w<<" "<<f<<" 加边！！\n";
	e[++cnt]=(E){v,w,f,head[u]};head[u]=cnt;
}

int n,k,A,B,C,id[105][105],idx=0,inq[N][15],cost[N][15];
char mp[105][105];

struct node{
	int w,lf,id;
	bool operator <(node B)const{
		if(w!=B.w) return w>B.w;  //花费小的在前 
		return lf<B.lf;  //油多的在前 
	}
};

void dij(int s){
	priority_queue<node>q;
	for(int i=1;i<=idx;++i){
		for(int j=0;j<=k;++j) inq[i][j]=0,cost[i][j]=inf;
	}
	cost[1][k]=0;
	q.push((node){0,k,1});
	while(q.size()){
	//	cout<<q.top().id<<" "<<q.top().w<<" "<<q.top().lf<<" !!\n"; 
		int fro=q.top().id,lf=q.top().lf;
		q.pop();
		if(!lf) continue; //没油去不了 
		inq[fro][lf]=0;
		for(int i=head[fro];i;i=e[i].nxt){
			int to=e[i].v,nw=(e[i].f)?(k):(lf-1);
			if(cost[to][nw]>cost[fro][lf]+e[i].w){
				cost[to][nw]=cost[fro][lf]+e[i].w;
				if(!inq[to][nw]){
					inq[to][nw]=1;
					q.push((node){cost[to][nw],nw,to});
				}
			}
		}
	}
}

void Solve(){
	cin>>n>>k>>A>>B>>C;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			cin>>mp[i][j];
			id[i][j]=++idx;
		//	if(mp[i][j]) is[idx]=1;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(mp[i+1][j]=='1'){  //向下走 
				addedge(id[i][j],id[i+1][j],A,1);
			}else{
				addedge(id[i][j],id[i+1][j],0,0);
				addedge(id[i][j],id[i+1][j],A+C,1); //新设加油站 
			}
			if(mp[i][j+1]=='1'){  //向右走 
				addedge(id[i][j],id[i][j+1],A,1);
			}else{
				addedge(id[i][j],id[i][j+1],0,0);
				addedge(id[i][j],id[i][j+1],A+C,1);
			}
			if(mp[i][j]=='1'){  //建反向边
				addedge(id[i+1][j],id[i][j],A+B,1);
				addedge(id[i][j+1],id[i][j],A+B,1);
			}else{
				addedge(id[i+1][j],id[i][j],B,0);
				addedge(id[i][j+1],id[i][j],B,0);
			}
		}
	}
	dij(1);
	int ans=inf;
	for(int i=0;i<=k;++i) ans=min(ans,cost[id[n][n]][i]);
	cout<<ans<<"\n"; 
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
//	cin>>T;
//	clock_t start,finish;
//	start=clock();
	while(T--){
		Solve();
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;
	return 0;
}
