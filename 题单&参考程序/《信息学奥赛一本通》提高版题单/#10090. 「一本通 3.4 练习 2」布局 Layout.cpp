#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
const int N=1e3+7,M=3e4+7;

struct E{
	int v,w,nxt;
}e[M];

int cnt=0,head[N];
inline void addedge(int u,int v,int w){
	e[++cnt]=(E){v,w,head[u]};head[u]=cnt;
}

int n,m1,m2,dis[N],vis[N],num[N];
bool OK;
inline bool spfa(int sz){
	for(int i=0;i<=n;++i) dis[i]=inf,vis[i]=0,num[i]=0;
	queue<int>q;
	for(int i=1;i<=sz;++i) q.emplace(i),dis[i]=0,vis[i]=1;
	while(q.size()){
		int fro=q.front();
		q.pop();
		vis[fro]=0;
		for(int i=head[fro];i;i=e[i].nxt){
			int to=e[i].v,w=e[i].w;
			if(dis[to]>dis[fro]+w){
				dis[to]=dis[fro]+w;
				++num[to];
				if(num[to]>=n) return true; //有环无方案 
				if(!vis[to]){
					vis[to]=1;
					q.emplace(to);
				}
			}
		}
	}
	return false;
}

signed  main(){
	scanf("%d%d%d",&n,&m1,&m2);
	for(int i=1,u,v,w;i<=m1;++i){
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
	}
	for(int i=1,u,v,w;i<=m2;++i){
		scanf("%d%d%d",&u,&v,&w);
		addedge(v,u,-w);
	}
	for(int i=1;i<n;++i) addedge(i,i-1,0);
	if(spfa(n)) puts("-1");
	else{
		spfa(1);
		if(dis[n]>=inf) puts("-2");
		else printf("%d\n",dis[n]);
	}
	return 0;
}