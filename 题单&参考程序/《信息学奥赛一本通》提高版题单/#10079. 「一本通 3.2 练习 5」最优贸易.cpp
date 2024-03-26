#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+7;

int n,m,a[maxn],ma[maxn],mi[maxn];
vector<int> G[maxn];
bool can[maxn];

void init(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=m;++i){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        if(c==1){
            G[a].push_back(b);
        }else{
            G[a].push_back(b);
            G[b].push_back(a);
        }
    }
}

queue<int> q;
bool vis[maxn];

void rspfa(int s){
	memset(vis,0,sizeof(vis));
	memset(ma,0,sizeof(ma));
	memset(can,0,sizeof(can));
	vis[s]=1;
	can[s]=1;
	ma[s]=a[s];
	q.push(s);
	while(!q.empty()){
		int fro=q.front();
		q.pop();
		vis[fro]=0;
		for(auto to:G[fro]){
			if(ma[to]<max(ma[fro],a[to])){
				ma[to]=max(ma[fro],a[to]);
				if(!can[to]) can[to]=1;
				if(!vis[to]){
					vis[to]=1;
					q.push(to);
				}
			}
		}
	}
}

void spfa(int s){
    memset(vis,0,sizeof(vis));
    memset(mi,0x3f3f3f,sizeof(mi));
    memset(can,0,sizeof(can));
    vis[s]=1;
    mi[s]=a[s];
    can[s]=1;
    q.push(s);
    while(!q.empty()){
        int fro=q.front();
        q.pop();
        vis[fro]=0;
        for(auto to:G[fro]){
            if(mi[to]>min(mi[fro],a[to])){
                mi[to]=min(mi[fro],a[to]);
                if(!can[to]) can[to]=1;
                if(!vis[to]){
                	vis[to]=1;
                    q.push(to);
				}
            }
        }
    }
}

signed main(){
    init();
    spfa(1);
    rspfa(n);
    int ans=0;
    for(int i=1;i<=n;++i)
   		if(ma[i]!=0&&mi[i]!=0x3f3f3f&&ma[i]>=mi[i])
   			ans=max(ans,ma[i]-mi[i]);
    printf("%d",ans);
    return 0;
}