#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#define inf 0x3f3f3f3f

using namespace std;
const int N=30,M=2e5+7;
const int mod=1e9+7;

struct E{int v,w,nxt;}e[M];
int head[N],cnt;
inline void addedge(int u,int v,int w){e[++cnt]=(E){v,w,head[u]};head[u]=cnt;}

int n,need[N],work[N],dis[N],inq[N],used[N];

inline int spfa(int k){
	cnt=0;
	memset(head,0,sizeof(head));
	for(int i=1;i<=24;++i){
		addedge(i-1,i,0);
		addedge(i,i-1,-work[i]); 
		if(i>=8) addedge(i-8,i,need[i]);
		else addedge(i+16,i,need[i]-k);
	}
	addedge(0,24,k); //24小时内有k个人 x
	for(int i=0;i<=24;++i) dis[i]=-inf,inq[i]=0,used[i]=0;
	dis[0]=0;inq[0]=1;used[0]=1;
	queue<int>q;
	q.push(0);
	while(q.size()){
		int fro=q.front();
		q.pop();
		inq[fro]=0;
		for(int i=head[fro];i;i=e[i].nxt){
			int v=e[i].v,w=e[i].w;
			if(dis[v]<dis[fro]+w){
				dis[v]=dis[fro]+w;
				if(!inq[v]){
					inq[v]=1;
					++used[v];
					if(used[v]>24) return 0;//存在负环
					q.push(v); 
				}
			}
		}
	}
	return dis[24]==k;
}

void Solve(){
	memset(need,0,sizeof need);
	memset(work,0,sizeof work);
	for(int i=1;i<=24;++i){
		cin>>need[i];
		addedge(i-1,i,need[i]);
	}
	cin>>n;
	for(int i=1,s;i<=n;++i){
		cin>>s;
		++work[s+1];
	}
	int L=0,R=n+1,mid;
	while(R-L>1){  //二分以下需要的人数，直接枚举也可以 
		mid=((L+R)>>1);
		if(spfa(mid)) R=mid;
		else L=mid;
	}
	if(spfa(L)) R=L; 
	if(R>n) cout<<"No Solution\n"; 
	else cout<<R<<"\n";	
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	cin>>T;
	while(T--){
		Solve();
	}
}