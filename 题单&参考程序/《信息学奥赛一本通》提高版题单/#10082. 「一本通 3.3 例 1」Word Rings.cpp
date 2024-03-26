//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 1e8
#define eps 1e-4
using namespace std;
const int N=2e5+7;

struct E{int v,nxt;double w;}e[N<<1];
int head[N],cnt=0;
inline void addedge(int u,int v,double w){e[++cnt]=(E){v,head[u],w};head[u]=cnt;}

int n,m,inq[N],num[N],len[N],idx=0;
double dis[N];
string str[N];
map<int,int>rk;

inline bool check(double x){
	queue<int>q;
	for(int i=1;i<=idx;++i) q.push(i),dis[i]=0,inq[i]=1,num[i]=0;
	while(q.size()){
		int fro=q.front();
		q.pop();
		inq[fro]=0;
		for(int i=head[fro];i;i=e[i].nxt){
			int to=e[i].v;
			double w=e[i].w-x; //每条边都减去这个长度之后是否还有负环 
			if(dis[to]<dis[fro]+w){
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
	for(int i=1;i<=n;++i){
		cin>>str[i];
		len[i]=str[i].length();
		int s=(str[i][0]-'a')*26+(str[i][1]-'a'),t=(str[i][len[i]-2]-'a')*26+(str[i][len[i]-1]-'a');
		if(!rk.count(s)) rk[s]=++idx;
		if(!rk.count(t)) rk[t]=++idx;
		addedge(rk[s],rk[t],len[i]); 
	}
	if(!check(0)){
		cout<<"No solution\n";
		return;
	}
	double L=0,R=inf,M;
	while(R-L>eps){
		M=(L+R)/2;
		if(check(M)) L=M;
		else R=M;
	}
	printf("%.2lf\n",L);
	rk.clear();idx=0;cnt=0;
	memset(head,0,sizeof(head));
	memset(len,0,sizeof(len));
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	cin>>n;
	while(n){
		Solve();
		cin>>n;
	}
	return 0;	 
}
