//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
struct E{int v,w,nxt;}e[N<<2];
int head[N],cnt=0;
inline void addedge(int u,int v,int w){e[++cnt]=(E){v,w,head[u]};head[u]=cnt;}

int n,m,p,u,v,w;
int dis[N],inq[N],num[N];

bool spfa(){
	for(int i=1;i<=n;++i) dis[i]=inf,num[i]=0,inq[i]=0;
	queue<int>q;
	q.push(1);dis[1]=0;
	while(q.size()){
		int fro=q.front();
		q.pop();
		inq[fro]=0;
		for(int i=head[fro];i;i=e[i].nxt){
			int to=e[i].v;
			if(dis[to]>dis[fro]+e[i].w){
				dis[to]=dis[fro]+e[i].w;
				num[to]=num[fro]+1;
				if(num[to]>n) return false;
				if(!inq[to]){
					inq[to]=1;
					q.push(to);
				}
			}
		}
	}
	return true;
}

void Solve(){
	cin>>n>>m>>p;
	for(int i=1;i<=m;++i){
		cin>>u>>v>>w;
		addedge(u,v,w);
		addedge(v,u,w);
	}	
	for(int i=1;i<=p;++i){
		cin>>u>>v>>w;
		addedge(u,v,-w);
	}
	if(spfa()) cout<<"NO\n";
	else cout<<"YES\n";
	memset(head,0,sizeof(head));
	cnt=0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
	cin>>T;
//	clock_t start,finish;
//	start=clock();
	while(T--){
		Solve();
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;	return 0;
}
