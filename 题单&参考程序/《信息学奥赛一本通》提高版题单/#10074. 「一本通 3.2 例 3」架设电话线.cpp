//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define int long long
using namespace std;
const int N=1007;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

struct E{int v,w,nxt;}e[N<<2];
int head[N],cnt=0;
inline void addedge(int u,int v,int w){e[++cnt]=(E){v,w,head[u]};head[u]=cnt;}

int n,m,k,inq[N],dis[N];

inline bool check(int x){
	queue<int>q;
	memset(dis,inf,sizeof(dis));
	q.push(1);inq[1]=1;dis[1]=0;
	while(q.size()){
		int fro=q.front();
		q.pop();
		inq[fro]=0;
		for(int i=head[fro];i;i=e[i].nxt){
			int to=e[i].v;
			if(dis[to]>dis[fro]+(e[i].w>x)){
				dis[to]=dis[fro]+(e[i].w>x);
				if(!inq[to]){
					inq[to]=1;
					q.push(to);
				}
			}
		}
	}
//	for(int i=1;i<=n;++i) cout<<i<<" "<<dis[i]<<"!!\n";
	return dis[n]<=k;
}

void Solve(){
	cin>>n>>m>>k;
	for(int i=1,u,v,w;i<=m;++i){
		cin>>u>>v>>w;
		addedge(u,v,w);
		addedge(v,u,w);
	}
	int L=0,R=inf+7,M;
	while(R-L>1){
		M=((L+R)>>1);
		if(check(M)) R=M;
		else L=M;
	}
	if(check(L)) R=L;
	if(R>=inf) cout<<"-1\n";
	else cout<<R<<"\n";
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
