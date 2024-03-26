/*
https://blog.csdn.net/D_Bamboo_/article/details/104099787
分层图，以携带的钥匙作为层数，用二进制存，建图后跑spfa 
*/
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=207,M=5007;

int xx[]={0,0,-1,1},yy[]={1,-1,0,0};
int key[N*N],dis[M][N],mp[N][N];
int n,m,s,t,id[N][N];

struct node{
	int x,v;
	node(int a,int b):x(a),v(b){}
};

struct E{int v,w,nxt;}e[N*N];
int head[N*N],cnt=0;
inline void addedge(int u,int v,int w){e[++cnt]=(E){v,w,head[u]};head[u]=cnt;}

void init(){
	cnt=0;s=1;t=n*m;
	memset(head,0,sizeof(head));
	memset(mp,-1,sizeof(mp));
	memset(key,0,sizeof(key));
}

int spfa(){
	queue<node>q;
	memset(dis,0x3f,sizeof(dis));
	dis[1][s]=0;
	q.push(node(1,s));
	while(q.size()){
		int u=q.front().v,d=q.front().x;
		q.pop();
		dis[d|key[u]][u]=min(dis[d|key[u]][u],dis[d][u]);
		d|=key[u];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].v;
			if((d&e[i].w)==e[i].w){  //如果有当前门的钥匙 
				if(dis[d][v]>dis[d][u]+1){
					dis[d][v]=dis[d][u]+1;
					q.push(node(d,v));
				}
			}
		}		
	}
	int ans=inf;
	for(int i=1;i<5005;++i) ans=min(ans,dis[i][t]); 
	if(ans==inf) return -1; //不可到达 
	return ans;
}

signed main(){
	int x1,x2,y1,y2,z,p,k,idx=0;
	cin>>n>>m>>p>>k;
	init(); //初始化 
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			id[i][j]=++idx; //给坐标编号 
		}
	}
	for(int i=1;i<=k;++i){
		cin>>x1>>y1>>x2>>y2>>z;
		int u=id[x1][y1],v=id[x2][y2];
		mp[u][v]=mp[v][u]=z;
		if(z){ //以钥匙的代价建边 
			addedge(u,v,1<<z);
			addedge(v,u,1<<z);
		}
	}
	cin>>k; //钥匙 
	for(int i=1;i<=k;++i){
		cin>>x1>>y1>>z;
		key[id[x1][y1]]|=1<<z; //表示这个单元的钥匙集合 
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			int u=id[i][j];
			for(int d=0;d<4;++d){ //对相邻点建边，代价为1 
				int nx=i+xx[d],ny=j+yy[d],v=id[nx][ny];
				if(mp[u][v]==-1&&id[nx][ny]){
					addedge(u,v,1);
				}
			}
		}
	}
	cout<<spfa()<<"\n";
	return 0;
}