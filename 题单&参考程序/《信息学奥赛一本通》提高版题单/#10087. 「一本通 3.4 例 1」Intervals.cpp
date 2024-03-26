#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
const int N=5e5+7;

struct E{int v,w,nxt;}e[N<<1];
int head[N],cnt=0;
void addedge(int u,int v,int w){
	e[++cnt]=(E){v,w,head[u]};head[u]=cnt;
}

int n,l,r,dis[N],inq[N];
queue<int>q;

signed main(){
	scanf("%d",&n);
	for(int i=1,u,v,w;i<=n;i++){ //差分约束系统建图 
		scanf("%d%d%d",&u,&v,&w);
		addedge(u-1,v,w); 
		l=min(l,u-1);
		r=max(r,v);
	}
	for(int i=l;i<=r;++i){
		addedge(i,i+1,0); //i+1不放数 
		addedge(i+1,i,-1); //退一个数 
		dis[i]=-inf;
	}
	dis[l]=0;inq[l]=1;
	q.push(l);
	while(!q.empty()){
		int fro=q.front();
		q.pop();
		inq[fro]=0;
		for(int i=head[fro];i;i=e[i].nxt){
			int to=e[i].v;
			if(dis[to]<dis[fro]+e[i].w){ //跑最长路 
				dis[to]=dis[fro]+e[i].w;
				if(!inq[to]){
					q.push(to);
					inq	[to]=1;
				}
			}
		}
	}
	printf("%d",dis[r]);
	return 0;
}