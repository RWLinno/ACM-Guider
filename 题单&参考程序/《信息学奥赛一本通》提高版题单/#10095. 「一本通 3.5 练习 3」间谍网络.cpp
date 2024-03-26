#include<bits/stdc++.h>
using namespace std;
const int maxn=3005;
const int inf=1e9+7;

struct E{
	int next,to;
}e[maxn<<2];

int n,m,p,r,id,a,b,st[maxn],ru[maxn],ans;
int cnt,head[maxn];
int dfn[maxn],low[maxn],vis[maxn],bel[maxn],idx;
int stk[maxn],top;
int can[maxn],ct[maxn];

void addedge(int from,int to){
	e[++cnt].next=head[from];
	e[cnt].to=to;
	head[from]=cnt;
} 

void tarjan(int x){
	dfn[x]=low[x]=++idx;
	vis[x]=1;
	stk[++top]=x;
	for(int i=head[x];i;i=e[i].next){
		int to=e[i].to;
		if(!dfn[to]){
			tarjan(to); //遍历下一个节点 
		//	ans-=ct[bel[to]];
			low[x]=min(low[x],low[to]); //最早访问时间 
		//	ct[x]=min(ct[x],ct[to]);
		}else if(vis[to]){
			//cout<<to<<"已经vis "<<bel[to]<<" "<<ct[bel[to]]<<endl; 
		//	ans-=ct[bel[to]];
			//if(st[to]) ct[x]=min(ct[x],ct[to]);
			low[x]=min(low[x],dfn[to]);
		}
	}
	if(dfn[x]==low[x]){
		int y;
		while(y=stk[top--]){ 
			bel[y]=x;
			vis[y]=0;
			if(st[y]){ //缩点操作 
				if(ct[x]) ct[x]=min(ct[x],ct[y]); //如果都能买，只需要买最小的 
				else ct[x]=ct[y]; //否则先买能买的 
			}
			if(x==y) break;
		}
	}
} 

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;cin>>p;
	//for(int i=1;i<=n;i++) ct[i]=inf;
	for(int i=1;i<=p;i++){
		cin>>id;
		cin>>ct[id]; 
	}
	cin>>r;
	for(int i=1;i<=r;i++){
		cin>>a>>b;
		addedge(a,b);
		ru[b]++;
	}
	for(int i=1;i<=n;i++){
		if(!ru[i]&&ct[i]){ //肯定选入度为0的作为起点的呀 
			ans+=ct[i]; //答案先加上 
			tarjan(i);   //开始遍历 
		}
	}
	//可能有成环的情况 
	for(int i=1;i<=n;i++){
		if(!dfn[i]&&ct[i]){ //没有遍历过并且可以被收买
			st[i]=1; //环的起点 
			tarjan(i);   //开始遍历 
		}
	}	
	for(int i=1;i<=n;i++){
		if(!dfn[i]){ //还是有节点没被访问到，那么不能控制所有间谍
			cout<<"NO"<<endl;
			cout<<i<<endl;
			return 0; 
		}
	}
	//可以控制所有的间谍。
	for(int i=1;i<=n;i++){
		if(st[i]) ans+=ct[i];  
	}
	cout<<"YES"<<endl;
	cout<<ans<<endl; 
	return 0;
}