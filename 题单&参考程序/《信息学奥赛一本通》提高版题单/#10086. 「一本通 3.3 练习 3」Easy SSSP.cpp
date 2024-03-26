//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 1e17
#define int long long
using namespace std;
const int N=1007;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
struct E{
	int v,w,nxt;
}e[N*N];
int head[N],cnt=0;
inline void addedge(int u,int v,int w){e[++cnt]=(E){v,w,head[u]};head[u]=cnt;}

int n,m,s,inq[N],num[N],dis[N];

inline bool dij(){
	queue<int>q;
	for(int i=1;i<=n;++i) inq[i]=1,num[i]=0,dis[i]=inf,q.push(i);
	dis[s]=0;
	while(q.size()){
		int fro=q.front();
		q.pop();
		inq[fro]=0;
		for(int i=head[fro];i;i=e[i].nxt){
			int to=e[i].v;
			if(dis[to]>dis[fro]+e[i].w){
				dis[to]=dis[fro]+e[i].w;
				++num[to];
				if(num[to]>n+1){
					return true;
				}
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
	cin>>n>>m>>s;
	for(int i=1,u,v,w;i<=m;++i){
		cin>>u>>v>>w;
		addedge(u,v,w);
	}
	if(dij()) cout<<"-1\n";
	else{
		for(int i=1;i<=n;++i){
			if(dis[i]>=1e9) cout<<"NoPath\n";
			else cout<<dis[i]<<"\n";
		}	
	}
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
