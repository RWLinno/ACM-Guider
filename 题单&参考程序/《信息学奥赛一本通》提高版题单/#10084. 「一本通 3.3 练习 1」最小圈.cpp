//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 1e7
#define eps 1e-9
using namespace std;
const int N=30007;

struct E{int v,nxt;double w;}e[N<<1];
int head[N],cnt=0;
inline void addedge(int u,int v,double w){e[++cnt]=(E){v,head[u],w};head[u]=cnt;}

int n,m,inq[N],num[N];
double dis[N];

inline bool check(double x){
	queue<int>q;
	for(int i=1;i<=n;++i) q.push(i),dis[i]=0,inq[i]=1,num[i]=0;
	while(q.size()){
		int fro=q.front();
		q.pop();
		inq[fro]=0;
		for(int i=head[fro];i;i=e[i].nxt){
			int to=e[i].v;
			double w=e[i].w-x; //每条边都减去这个长度之后是否还有负环 
			if(dis[to]>dis[fro]+w){
				dis[to]=dis[fro]+w;
				num[to]=num[fro]+1;
				if(num[to]>200) return true; 
				if(!inq[to]){
					inq[to]=1;
					q.push(to);
				}
			}
		}
	}
	return false;
}

void Solve(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;++i){
		double w;
		scanf("%d%d%lf",&u,&v,&w);
		addedge(u,v,w);
	}
	double L=-inf,R=inf,M;
	while(R-L>eps){
		M=(L+R)/2;
		if(check(M)) R=M;
		else L=M;
	}
	printf("%.8lf",R);
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
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
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;	return 0;
}
