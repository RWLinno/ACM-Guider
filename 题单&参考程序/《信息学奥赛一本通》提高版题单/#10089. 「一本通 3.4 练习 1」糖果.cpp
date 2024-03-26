#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7,M=3e5+7;
typedef long long ll;

int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void write(ll x){if(x>9) write(x/10);putchar(x%10+'0');}
struct E{
	int v,w,nxt;
}e[M];

int head[N],cnt=0;
int n,k,num[N];
bool inq[N];
ll dis[N],ans=0;
stack<int>st;

void addedge(int u,int v,int w){
	e[++cnt]=(E){v,w,head[u]};head[u]=cnt;
}

signed main(){
	n=read();k=read();
	for(int i=1,op,u,v;i<=k;++i){
		op=read();u=read();v=read();
		if(op==1) addedge(u,v,0),addedge(v,u,0);
		else if(op==2) addedge(u,v,1);
		else if(op==3) addedge(v,u,0);
		else if(op==4) addedge(v,u,1);
		else if(op==5) addedge(u,v,0);
	}
	for(int i=1;i<=n;++i) addedge(0,i,1); //建一个超级源点 
	st.push(0);dis[0]=0; 
	while(st.size()){
		int fro=st.top();
		st.pop();
		inq[fro]=0;
		for(int i=head[fro],to;i;i=e[i].nxt){
			to=e[i].v;
			if(dis[to]<dis[fro]+e[i].w){ //最长路 
				dis[to]=dis[fro]+e[i].w;
				num[to]=num[fro]+1;
				if(num[to]>n){ //判环 
					puts("-1");
					return 0;
				}
				if(!inq[to]){
					inq[to]=1;
					st.push(to);
				}
			}
		}
	}
	for(int i=1;i<=n;++i) ans+=dis[i];
	write(ans);
	return 0;
}